package com.sae.myapplication;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.provider.MediaStore;
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
    static TextView txt;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_picture_answer);

        imageView = findViewById(R.id.imageRep);
        ImageView box = findViewById(R.id.footerbox1);
        ImageView box2 = findViewById(R.id.footerbox2);
        ImageButton bHelp = findViewById(R.id.boutonHelp);
        ImageButton bReturn = findViewById(R.id.boutonReturn);
        Button bCancel = findViewById(R.id.btnCancel);
        Button bSave = findViewById(R.id.btnSave);

        txt = findViewById(R.id.textView);


        fromServ();


        //getImageFromServer();


        bHelp.setOnClickListener(v -> {
            box.setBackgroundColor(Color.parseColor("#4288BF"));
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    box.setBackgroundColor(Color.parseColor("#1C5F93"));
                }
            }, 50);
            Intent intent = new Intent(this, HelpActivity.class);
            startActivity(intent);
        });

        bReturn.setOnClickListener(v -> {
            box2.setBackgroundColor(Color.parseColor("#4288BF"));
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    box2.setBackgroundColor(Color.parseColor("#1C5F93"));
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

        bSave.setOnClickListener(v -> {
            // Assurez-vous que l'imageView a été initialisé avec l'image du serveur au préalable.

            // Récupérez l'image affichée dans l'ImageView
            Bitmap imageBitmap = ((BitmapDrawable)imageView.getDrawable()).getBitmap();

            if (imageBitmap != null) {
                // Enregistrez l'image dans la galerie de l'utilisateur
                String savedImageURL = MediaStore.Images.Media.insertImage(
                        getContentResolver(), imageBitmap, "Image correction", "Correction du plateau de jeu ricochet robot"
                );

                // Si l'enregistrement est réussi, affichez un message de succès
                if (savedImageURL != null) {
                    Toast.makeText(this, "Image enregistrée avec succès", Toast.LENGTH_SHORT).show();
                } else {
                    // Sinon, affichez un message d'erreur
                    Toast.makeText(this, "Échec de l'enregistrement de l'image", Toast.LENGTH_SHORT).show();
                }
            }
        });



    }

    public static void fromServ() {
        String serverAddress = "195.201.205.241"; // Remplacez par l'adresse IP de votre serveur
        int serverPort = 9090; // Remplacez par le port de votre serveur

        try {
            Socket socket = new Socket(serverAddress, serverPort);

            System.out.println("Connexion...");

            InputStream input = socket.getInputStream();

            BufferedReader reader = new BufferedReader(new InputStreamReader(input));
            String line = reader.readLine();    // reads a line of text

            System.out.println("Connecté");

            System.out.println("Message reçu du serveur : " + line);

            txt.setText(line);

            // Fermez la connexion
            socket.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
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
