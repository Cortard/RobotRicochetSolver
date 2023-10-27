package com.sae.myapplication;

import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;


public class PictureVerifyActivity extends AppCompatActivity {

    ImageView imageView;

    Uri image_uri;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_picture_verify);

        imageView = findViewById(R.id.imageVerif);

        image_uri = getIntent().getData();
        if (image_uri != null) {
            imageView.setImageURI(image_uri);
        }

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

        Button bVld = findViewById(R.id.btnValide);
        bVld.setOnClickListener(v -> {
            sendImageToServer(image_uri, getString(R.string.IP), 8080);
            Intent intent = new Intent(this, PictureAnswerActivity.class);
            startActivity(intent);
        });

    }

    private void sendImageToServer(Uri imageUri, String serverIp, int serverPort) {
        new Thread(() -> {
            try {

                Socket clientSocket = new Socket(serverIp, serverPort);
                OutputStream outputStream = clientSocket.getOutputStream();

                // Ouvrir l'input stream pour lire l'URI de l'image
                try {
                    InputStream inputStream = getContentResolver().openInputStream(imageUri);
                    byte[] buffer = new byte[1024];
                    int bytesRead;

                    while ((bytesRead = inputStream.read(buffer)) != -1) {
                        outputStream.write(buffer, 0, bytesRead);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }

                // Fermer la socket
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }).start();
    }

    private static File uriToJpg(Context context, Uri imageUri) {
        File jpgFile = null;
        try {
            ContentResolver resolver = context.getContentResolver();
            InputStream inputStream = resolver.openInputStream(imageUri);
            if (inputStream != null) {
                Bitmap bitmap = BitmapFactory.decodeStream(inputStream);

                File storageDir = context.getExternalFilesDir(Environment.DIRECTORY_PICTURES);
                jpgFile = File.createTempFile("image", ".jpg", storageDir);

                FileOutputStream outputStream = new FileOutputStream(jpgFile);
                bitmap.compress(Bitmap.CompressFormat.JPEG, 100, outputStream);

                inputStream.close();
                outputStream.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return jpgFile;
    }
}
