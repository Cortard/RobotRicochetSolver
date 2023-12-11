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
import android.util.Log;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.io.BufferedOutputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
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
    static TextView txt;

    Uri image_uri;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_picture_verify);

        imageView = findViewById(R.id.imageVerif);
        ImageButton bReturn = findViewById(R.id.boutonReturn);
        Button bVld = findViewById(R.id.btnValide);
        ImageButton bHelp = findViewById(R.id.boutonHelp);
        ImageView box = findViewById(R.id.footerbox);
        ImageView box2 = findViewById(R.id.footerbox2);

        image_uri = getIntent().getData();
        if (image_uri != null) {
            imageView.setImageURI(image_uri);
        }

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
            finish();
        });

        Button bCancel = findViewById(R.id.btnCancel);
        bCancel.setOnClickListener(v -> {
            Intent intent = new Intent(this, PictureActivity.class);
            startActivity(intent);
            finish();
        });

        sendImage("195.201.205.241", 9090, new File(image_uri.getPath()));

        bVld.setOnClickListener(v -> {
            //MainActivity.ip

            Intent intent = new Intent(this, PictureAnswerActivity.class);
            startActivity(intent);
        });

    }

    public static void sendImage(String serverIp, int serverPort, File imageFile) {
        Thread th = new Thread(new Runnable() {
            @Override
            public void run() {
                Socket socket = null;
                FileInputStream fileInputStream = null;
                BufferedOutputStream bufferedOutputStream = null;

                try {
                    // Obtention des dimensions de l'image
                    BitmapFactory.Options options = new BitmapFactory.Options();
                    options.inJustDecodeBounds = true;
                    BitmapFactory.decodeFile(imageFile.getAbsolutePath(), options);
                    int width = options.outWidth;
                    int height = options.outHeight;

                    socket = new Socket(serverIp, serverPort);
                    fileInputStream = new FileInputStream(imageFile);
                    bufferedOutputStream = new BufferedOutputStream(socket.getOutputStream());
                    DataOutputStream dataOutputStream = new DataOutputStream(bufferedOutputStream);

                    // Envoie du FLAG au serveur : 1
                    dataOutputStream.writeChar('1');
                    dataOutputStream.flush();

                    // Attente de la réponse du serveur
                    DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
                    char response = dataInputStream.readChar();

                    txt.setText(response);

                    if (response == '1') {
                        int[] dimensions = {width, height};
                        for (int dimension : dimensions) {
                            dataOutputStream.writeInt(dimension);
                        }
                        dataOutputStream.flush();

                        txt.setText(width*height + " ");

                        DataInputStream dataInputStreamLong = new DataInputStream(socket.getInputStream());
                        long responseSize = dataInputStreamLong.readLong();

                        if (responseSize == width * height * 3) {
                            byte[] buffer = new byte[4096];
                            int bytesRead;
                            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                                bufferedOutputStream.write(buffer, 0, bytesRead);
                            }
                            bufferedOutputStream.flush();

                            txt.setText("fait");

                            // Attente de la confirmation de la réception
                            int responseConfirm = dataInputStream.readInt();
                            Log.d("finish", String.valueOf(responseConfirm));
                        } else {
                            Log.d("denied", "Pas de reponse server : confirm_size ");
                        }
                    } else {
                        Log.d("denied", "Pas de reponse server : 1");
                    }

                    // Ferme les flux
                    fileInputStream.close();
                    bufferedOutputStream.close();
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        th.start();
    }
}
