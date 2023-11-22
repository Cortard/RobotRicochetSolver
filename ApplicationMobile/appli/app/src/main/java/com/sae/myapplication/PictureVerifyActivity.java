package com.sae.myapplication;

import android.content.ContentResolver;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.provider.MediaStore;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import java.io.BufferedOutputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectOutputStream;
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
        ImageButton bReturn = findViewById(R.id.boutonReturn);
        Button bVld = findViewById(R.id.btnValide);
        ImageButton bHelp = findViewById(R.id.boutonHelp);
        ImageView box = findViewById(R.id.footerbox1);
        ImageView box2 = findViewById(R.id.footerbox2);

        image_uri = getIntent().getData();
        if (image_uri != null) {
            imageView.setImageURI(image_uri);
        }

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
            finish();
        });

        Button bCancel = findViewById(R.id.btnCancel);
        bCancel.setOnClickListener(v -> {
            Intent intent = new Intent(this, PictureActivity.class);
            startActivity(intent);
            finish();
        });

        bVld.setOnClickListener(v -> {
            System.out.println("Valide");
            System.out.println("sendimg");
            //sendImage(getString(R.string.IP), 9090, new File(image_uri.getPath()));
            Intent intent = new Intent(this, PictureAnswerActivity.class);
            startActivity(intent);
        });

    }

    private File compressImage(Uri imageUri) throws IOException {
        // Transformez l'URI en Bitmap
        Bitmap bitmap = null;

        try {
            bitmap = MediaStore.Images.Media.getBitmap(this.getContentResolver(), imageUri);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Comprimez le Bitmap en fichier JPG
        if (bitmap != null) {
            File compressedFile = compressBitmapToJpg(bitmap);

            // Nettoyez la mémoire
            bitmap.recycle();

            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            ObjectOutputStream oss = new ObjectOutputStream(bos);
            oss.writeObject(compressedFile);
            System.out.println(oss);
            System.out.println("test");
            return compressedFile;
        }
        return null;
    }

    private File compressBitmapToJpg(Bitmap bitmap) {
        File compressedFile = null;
        try {
            FileOutputStream outputStream = new FileOutputStream(new File(getCacheDir(), "tempBMP"));
            bitmap.compress(Bitmap.CompressFormat.JPEG, 80, outputStream);
            outputStream.flush();
            outputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return compressedFile;
    }

    public static void sendImage(String serverIp, int serverPort, File imageFile) {
        Thread th = new Thread(new Runnable() {
            @Override
            public void run() {
                Socket socket = null;
                FileInputStream fileInputStream = null;
                BufferedOutputStream bufferedOutputStream = null;

                try {
                    socket = new Socket(serverIp, serverPort);
                    fileInputStream = new FileInputStream(imageFile);
                    bufferedOutputStream = new BufferedOutputStream(socket.getOutputStream());
                    DataOutputStream dataOutputStream = new DataOutputStream(bufferedOutputStream);

                    // Envoie la taille du fichier au serveur
                    dataOutputStream.writeLong(imageFile.length());

                    // Envoie le contenu du fichier
                    byte[] buffer = new byte[4096];
                    int bytesRead;
                    while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                        bufferedOutputStream.write(buffer, 0, bytesRead);
                    }
                    bufferedOutputStream.flush();

                    // Ferme les flux
                    fileInputStream.close();
                    bufferedOutputStream.close();
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                } finally {
                    try {
                        if (fileInputStream != null) {
                            fileInputStream.close();
                        }
                        if (bufferedOutputStream != null) {
                            bufferedOutputStream.close();
                        }
                        if (socket != null) {
                            socket.close();
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        th.start();
    }
}
