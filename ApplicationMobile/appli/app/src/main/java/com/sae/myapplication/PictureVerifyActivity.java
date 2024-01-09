package com.sae.myapplication;

import android.content.Intent;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;

public class PictureVerifyActivity extends AppCompatActivity {

    ImageView imageView;
     static TextView txt;

    private static final int TIMEOUT_IN_MILLISECONDS = 10000; // 0b00010000

    Uri image_uri;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_picture_verify);

        imageView = findViewById(R.id.imageVerif);
        txt = findViewById(R.id.textView);

        ImageButton bReturn = findViewById(R.id.boutonReturn);
        Button bVld = findViewById(R.id.btnValide);
        ImageButton bHelp = findViewById(R.id.boutonHelp);

        image_uri = getIntent().getData();
        if (image_uri != null) {
            imageView.setImageURI(image_uri);
        }

        bHelp.setOnClickListener(v -> {
            bHelp.setBackgroundColor(Color.parseColor("#4C647A"));
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    bHelp.setBackgroundColor(Color.parseColor("#506F8A"));
                }
            }, 50);
            Intent intent = new Intent(this, HelpActivity.class);
            startActivity(intent);
        });

        bReturn.setOnClickListener(v -> {
            bReturn.setBackgroundColor(Color.parseColor("#4C647A"));
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    bReturn.setBackgroundColor(Color.parseColor("#506F8A"));
                }
            }, 50);
            finish();
        });


        txt.setText("test");

        Button bCancel = findViewById(R.id.btnCancel);
        bCancel.setOnClickListener(v -> {
            Intent intent = new Intent(this, PictureActivity.class);
            startActivity(intent);
            finish();
        });

        //sendImage("195.201.205.241", 9090, new File(image_uri.getPath()),this);

        bVld.setOnClickListener(v -> {
            //MainActivity.ip
            Intent intent = new Intent(this, PictureLoadActivity.class);
            intent.setData(image_uri);
            startActivity(intent);
        });

    }

    public void sendImage(String serverIp, int serverPort, File imageFile, PictureVerifyActivity answer) {
        Thread th = new Thread(new Runnable() {
            @Override
            public void run() {
                Socket socket = null;
                FileInputStream fileInputStream = null;
                BufferedOutputStream bufferedOutputStream = null;

                txt.setText("1");

                try {
                    BitmapFactory.Options options = new BitmapFactory.Options();
                    options.inJustDecodeBounds = true;
                    BitmapFactory.decodeFile(imageFile.getAbsolutePath(), options);
                    int width = options.outWidth;
                    int height = options.outHeight;

                    socket = new Socket();
                    socket.connect(new InetSocketAddress(serverIp, serverPort), TIMEOUT_IN_MILLISECONDS);
                    fileInputStream = new FileInputStream(imageFile);
                    bufferedOutputStream = new BufferedOutputStream(socket.getOutputStream());
                    DataOutputStream dataOutputStream = new DataOutputStream(bufferedOutputStream);

                    txt.setText("2");

                    // Envoie du FLAG au serveur : 1
                    dataOutputStream.writeChar('1');
                    dataOutputStream.flush();

                    // Attente de la réponse du serveur avec timeout
                    socket.setSoTimeout(TIMEOUT_IN_MILLISECONDS); // Définit le timeout pour la réponse
                    DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
                    char response = dataInputStream.readChar();

                    txt.setText(response);

                    txt.setText("reponse");

                    if (response == '1') {
                        int[] dimensions = {width, height};
                        for (int dimension : dimensions) {
                            dataOutputStream.writeInt(dimension);
                        }
                        dataOutputStream.flush();

                        txt.setText(width * height + " ");

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
                            Log.d("denied", "Pas de réponse server : confirm_size ");
                        }
                    } else {
                        Log.d("denied", "Pas de réponse server : 1");
                    }

                    // Ferme les flux
                    fileInputStream.close();
                    bufferedOutputStream.close();
                    socket.close();
                } catch (SocketTimeoutException e) {
                    Log.d("timeout", "Timeout lors de l'attente de la réponse du serveur");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        th.start();
    }
}
