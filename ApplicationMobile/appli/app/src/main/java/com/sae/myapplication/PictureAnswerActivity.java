package com.sae.myapplication;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.Socket;


public class PictureAnswerActivity extends AppCompatActivity {

    ImageView imageView;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_picture_answer);

        imageView = findViewById(R.id.imageRep);

        getImageFromServer();


        ImageButton bHelp = findViewById(R.id.boutonHelp);
        bHelp.setOnClickListener(v -> {
            Intent intent = new Intent(this, HelpActivity.class);
            startActivity(intent);
        });

        ImageButton bReturn = findViewById(R.id.boutonReturn);
        bReturn.setOnClickListener(v -> finish());

        Button bCancel = findViewById(R.id.btnCancel);
        bCancel.setOnClickListener(v -> {
            Intent intent = new Intent(this, PictureActivity.class);
            startActivity(intent);
            finish();
        });

        Button bSave = findViewById(R.id.btnSave);
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

            // Afficher l'image dans votre ImageView
            imageView.setImageURI(imageUri);

            // Fermer la connexion
            socket.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
