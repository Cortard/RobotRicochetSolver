package com.sae.myapplication;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;


public class PictureAnswerActivity extends AppCompatActivity {

    ImageView imageView;

    int[] gridData;
    int[] correctionData;
    int[] initialRobotPositions;
    private boolean isCorrectionRunning = false;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_picture_answer);

        imageView = findViewById(R.id.imageRep);
        ImageView box = findViewById(R.id.footerbox);
        ImageView box2 = findViewById(R.id.footerbox2);
        ImageButton bHelp = findViewById(R.id.boutonHelp);
        ImageButton bReturn = findViewById(R.id.boutonReturn);


        //getImageFromServer();

        //fromServ();


        bHelp.setOnClickListener(v -> {
            box.setBackgroundColor(Color.parseColor("#4C647A"));
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    box.setBackgroundColor(Color.parseColor("#506F8A"));
                }
            }, 50);
            Intent intent = new Intent(this, HelpActivity.class);
            startActivity(intent);
        });

        bReturn.setOnClickListener(v -> {
            box2.setBackgroundColor(Color.parseColor("#4C647A"));
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    box2.setBackgroundColor(Color.parseColor("#506F8A"));
                }
            }, 50);
            Intent intent = new Intent(this, PictureActivity.class);
            startActivity(intent);
            finish();
        });

        MyCanvas myCanvas = findViewById(R.id.canva);

        gridData = new int[]{9, 1, 5, 1, 3, 9, 1, 1, 1, 3, 9, 1, 1, 1, 1, 3, 8, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 3, 8, 0, 0, 0, 0, 2, 12, 0, 2, 9, 0, 0, 0, 0, 4, 2, 12, 0, 0, 0, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 10, 9, 0, 0, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 6, 8, 0, 0, 0, 0, 4, 4, 0, 0, 2, 12, 0, 0, 2, 8, 1, 0, 0, 0, 0, 2, 9, 3, 8, 0, 0, 1, 0, 0, 2, 8, 0, 4, 0, 2, 12, 2, 12, 6, 8, 0, 0, 0, 0, 0, 6, 8, 18, 9, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 4, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 0, 2, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 0, 0, 0, 2, 9, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1, 0, 0, 2, 12, 2, 8, 0, 0, 16, 3, 8, 0, 0, 0, 4, 0, 0, 0, 0, 1, 2, 8, 6, 8, 0, 0, 0, 0, 0, 0, 3, 8, 0, 0, 0, 16, 2, 12, 5, 4, 4, 4, 6, 12, 4, 4, 4, 4, 6, 12, 4, 4, 6};
        correctionData = new int[]{1, 2, 4, 17, 18, 40, 33, 8, 1, 2, 1, 2, 56, 49, 56, 49, 50, 49, 8, 4, 63};
        initialRobotPositions = new int[]{176, 145, 211, 238};

        myCanvas.setGridData(gridData,initialRobotPositions,54);

        Button btnCorrect = findViewById(R.id.btnCor);
        btnCorrect.setOnClickListener(v -> {
            myCanvas.startCorrection(correctionData);
            btnCorrect.setText("Recommencer");
            if (isCorrectionRunning) {
                Intent intent = new Intent(this, PictureAnswerActivity.class);
                startActivity(intent);
                finish();
            }
            isCorrectionRunning = true;
        });

    }

    public void fromServ() {
        Thread th = new Thread(new Runnable() {
            @Override
            public void run() {
                String serverAddress = "195.201.205.241"; // Remplacez par l'adresse IP de votre serveur
                int serverPort = 9090; // Remplacez par le port de votre serveur

                try {
                    Socket socket = new Socket(serverAddress, serverPort);

                    // Envoyer une demande au serveur pour obtenir les données
                    DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
                    dos.writeUTF("demande_donnees"); // Remplacez "demande_donnees" par la demande réelle

                    // Recevoir les données du serveur via la connexion socket
                    DataInputStream dis = new DataInputStream(socket.getInputStream());

                    // Recevoir les trois tableaux d'entiers
                    gridData = receiveIntArray(dis);
                    correctionData = receiveIntArray(dis);
                    initialRobotPositions = receiveIntArray(dis);

                    // Fermer la connexion
                    socket.close();

                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        th.start();
    }

    // Méthode pour recevoir un tableau d'entiers depuis le flux d'entrée
    private int[] receiveIntArray(DataInputStream dis) throws IOException {
        int length = dis.readInt(); // Recevoir la longueur du tableau
        int[] array = new int[length];
        for (int i = 0; i < length; i++) {
            array[i] = dis.readInt(); // Recevoir chaque élément du tableau
        }
        return array;
    }

}
