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

        int[] gridData = {9, 1, 5, 1, 3, 9, 1, 1, 1, 3, 9, 1, 1, 1, 1, 3, 8, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 3, 8, 0, 0, 0, 0, 2, 12, 0, 2, 9, 0, 0, 0, 0, 4, 2, 12, 0, 0, 0, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 10, 9, 0, 0, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 6, 8, 0, 0, 0, 0, 4, 4, 0, 0, 2, 12, 0, 0, 2, 8, 1, 0, 0, 0, 0, 2, 9, 3, 8, 0, 0, 1, 0, 0, 2, 8, 0, 4, 0, 2, 12, 2, 12, 6, 8, 0, 0, 0, 0, 0, 6, 8, 18, 9, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 4, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 0, 2, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 0, 0, 0, 2, 9, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1, 0, 0, 2, 12, 2, 8, 0, 0, 16, 3, 8, 0, 0, 0, 4, 0, 0, 0, 0, 1, 2, 8, 6, 8, 0, 0, 0, 0, 0, 0, 3, 8, 0, 0, 0, 16, 2, 12, 5, 4, 4, 4, 6, 12, 4, 4, 4, 4, 6, 12, 4, 4, 6};
        int[] correctionData = {1, 2, 4, 17, 18, 40, 33, 8, 1, 2, 1, 2, 56, 49, 56, 49, 50, 49, 8, 4, 63};

        myCanvas.setGridData(gridData);

        Button btnCorrect = findViewById(R.id.btnCor);
        btnCorrect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                myCanvas.correctGrid(correctionData);
            }
        });


//        Button btnCor = findViewById(R.id.btnCor); // Replace with the actual ID
//        btnCor.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                startCorrection();
//            }
//        });
    }

//    private void startCorrection() {
//        MyCanvas myCanvas = findViewById(R.id.canva);
//
//        // Assume you have a method to obtain the correction path array
//        int[] correctionPath = getCorrectionPath();
//
//        // Set the correction path to the MyCanvas view
//        myCanvas.setCorrectionPath(correctionPath);
//    }
//
//    private int[] getCorrectionPath() {
//        // Replace this with your logic to obtain the correction path array
//        // For example, you might have a separate class or method for correction calculation
//        // that returns the correction path array.
//        // The correctionPath array structure and values should match your requirements.
//        // Dummy example:
//        int[] dummyCorrectionPath = {
//                1, 2, 4, 17, 18, 40, 33, 8, 1, 2, 1, 2, 56, 49, 56, 49, 50, 49, 8, 4, 63
//        };
//        return dummyCorrectionPath;
//    }

    public void fromServ() {
        Thread th = new Thread(new Runnable() {
            @Override
            public void run() {
                String serverAddress = "195.201.205.241"; // Remplacez par l'adresse IP de votre serveur
                int serverPort = 9090; // Remplacez par le port de votre serveur

                try {
                    Socket socket = new Socket(serverAddress, serverPort);

                    InputStream input = socket.getInputStream();

                    BufferedReader reader = new BufferedReader(new InputStreamReader(input));
                    String line = reader.readLine();    // reads a line of text


                    //txt.setText(line);
                    Log.d("MSG", line);

                    // Fermez la connexion
                    socket.close();

                } catch (Exception e) {
                    //txt.setText(e.toString());
                    Log.d("ERROR", e.toString());
                }
            }
        });

        th.start();
    }

    private void getImageFromServer(){
        // Établir une connexion socket avec le serveur
        try {
            Socket socket = new Socket(getString(R.string.IP), 8080);

            // Envoyer une demande au serveur pour récupérer l'image
            DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
            dos.writeUTF("demande_image"); // Remplacez "demande_image" par la demande réelle

            // Recevoir les données de l'image depuis le serveur via la connexion socket
            DataInputStream dis = new DataInputStream(socket.getInputStream());

            // Stocker les données de l'image dans un fichier localement
            File imageFile = new File(getFilesDir(), "image.jpg");
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
