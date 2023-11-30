package com.sae.myapplication;

import android.content.Intent;
import android.graphics.Canvas;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.ProgressBar;

import androidx.appcompat.app.AppCompatActivity;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.Socket;


public class PictureAnswerActivity extends AppCompatActivity {

    ImageView imageView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_picture_answer);

        imageView = findViewById(R.id.imageRep);
        ImageView box = findViewById(R.id.footerbox);
        ImageView box2 = findViewById(R.id.footerbox2);
        ImageButton bHelp = findViewById(R.id.boutonHelp);
        ImageButton bReturn = findViewById(R.id.boutonReturn);
        Button bCancel = findViewById(R.id.btnCancel);



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

        bCancel.setOnClickListener(v -> {
            Intent intent = new Intent(this, PictureActivity.class);
            startActivity(intent);
            finish();
        });


        Button btnCor = findViewById(R.id.btnCor); // Replace with the actual ID
        btnCor.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startCorrection();
            }
        });

    }

    private void startCorrection() {
        // Assume you have a method to obtain the correction path array
        int[] correctionPath = getCorrectionPath();
        MyCanvas myCanvas = findViewById(R.id.canva);
        // Set the correction path to the MyCanvas view
        myCanvas.setCorrectionPath(correctionPath);
    }

    private int[] getCorrectionPath() {
        // Replace this with your logic to obtain the correction path array
        // For example, you might have a separate class or method for correction calculation
        // that returns the correction path array.
        // The correctionPath array structure and values should match your requirements.
        // Dummy example:
        int[] dummyCorrectionPath = {
                1, 2, 4, 17, 18, 40, 33, 8, 1, 2, 1, 2, 56, 49, 56, 49, 50, 49, 8, 4, 63
        };
        return dummyCorrectionPath;
    }

    public void fromServ() {
        Thread th = new Thread(new Runnable() {
            @Override
            public void run() {
                String serverAddress = MainActivity.ip; // Remplacez par l'adresse IP de votre serveur
                int serverPort = 9090; // Remplacez par le port de votre serveur

                try {
                    Socket socket = new Socket(serverAddress, serverPort);

                    InputStream input = socket.getInputStream();

                    BufferedReader reader = new BufferedReader(new InputStreamReader(input));
                    String line = reader.readLine();    // reads a line of text

                    // Fermez la connexion
                    socket.close();

                } catch (Exception e) {

                }
            }
        });

        th.start();
    }


    private void getImageFromServer(){
        // Établir une connexion socket avec le serveur
        try {
            Socket socket = new Socket(MainActivity.ip, 9090);

            // Recevoir les données de l'image depuis le serveur via la connexion socket
            DataInputStream dis = new DataInputStream(socket.getInputStream());

            // Stocker les données de l'image dans un fichier localement
            File imageFile = new File(getFilesDir(), "correction.jpg");
            FileOutputStream fos = new FileOutputStream(imageFile);
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = dis.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
            fos.close();

            // Convertir le fichier en URI
            Uri imageUri = Uri.fromFile(imageFile);

            ProgressBar pb = (ProgressBar) findViewById(R.id.progressBar);
            pb.setVisibility(ProgressBar.INVISIBLE);

            // Afficher l'image dans votre ImageView
            imageView.setImageURI(imageUri);

            // Fermer la connexion
            socket.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
