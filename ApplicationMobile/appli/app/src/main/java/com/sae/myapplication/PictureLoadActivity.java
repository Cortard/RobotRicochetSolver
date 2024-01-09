package com.sae.myapplication;

import android.content.Intent;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;

public class PictureLoadActivity extends PictureActivity {

    private static final int TIMEOUT = 10000;

    private TextView txt;

    ImageView imageView;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_load_verify);

        imageView = findViewById(R.id.imageVerif2);

        txt = findViewById(R.id.textView);


        sendImage("195.201.205.241", 9090, new File(image_uri.getPath()), this);

    }


    public void sendImage(String serverIp, int serverPort, File imageFile, PictureLoadActivity answer) {
        Thread th = new Thread(new Runnable() {
            @Override
            public void run() {
                Socket socket = null;
                FileInputStream fileInputStream = null;
                BufferedOutputStream bufferedOutputStream = null;

                txt.setText(imageFile + "");

                try {
                    BitmapFactory.Options options = new BitmapFactory.Options();
                    options.inJustDecodeBounds = true;
                    BitmapFactory.decodeFile(imageFile.getAbsolutePath(), options);
                    int width = options.outWidth;
                    int height = options.outHeight;

                    socket = new Socket();
                    socket.connect(new InetSocketAddress(serverIp, serverPort), TIMEOUT);
                    fileInputStream = new FileInputStream(imageFile);
                    bufferedOutputStream = new BufferedOutputStream(socket.getOutputStream());
                    DataOutputStream dataOutputStream = new DataOutputStream(bufferedOutputStream);

                    txt.setText("2");

                    // Envoie du FLAG au serveur : 1
                    dataOutputStream.writeChar('1');
                    dataOutputStream.flush();

                    // Attente de la réponse du serveur avec timeout
                    socket.setSoTimeout(TIMEOUT); // Définit le timeout pour la réponse
                    DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
                    char response = dataInputStream.readChar();

                    txt.setText(response);

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

                            if (responseConfirm == 1) { // confirm state
                                // Envoie du FLAG au serveur : 1
                                dataOutputStream.writeChar('1');
                                dataOutputStream.flush();

                                // Attente de la réponse du serveur avec timeout
                                char confirmFlag = dataInputStream.readChar();

                                if (confirmFlag == '1') {
                                    // Attendre quelque temps (tu peux remplacer par la logique que tu souhaites)
                                    Thread.sleep(TIMEOUT);

                                    // Envoie des informations sur l'état
                                    dataOutputStream.writeChar('1');
                                    dataOutputStream.flush();

                                    int depth = dataInputStream.readInt();
                                    int duration = dataInputStream.readInt();

                                    // Envoie du FLAG au serveur : 1
                                    dataOutputStream.writeChar('1');
                                    dataOutputStream.flush();

                                    // Attente de la réponse du serveur avec timeout
                                    char finalFlag = dataInputStream.readChar();

                                    if (finalFlag == '1') {
                                        // Processus terminé avec succès
                                        Intent intent = new Intent(answer, PictureAnswerActivity.class);
                                        startActivity(intent);
                                    } else {
                                        Log.d("denied", "Pas de réponse serveur : finalFlag");
                                    }
                                } else {
                                    Log.d("denied", "Pas de réponse serveur : confirmFlag");
                                }
                            } else if (responseConfirm == 2) { // not found
                                // Cas où la communication est interrompue
                                Log.d("info", "Cas NOTFOUND - communication shutdown");
                            } else if (responseConfirm == 3) { // solved
                                // Attendre la confirmation du serveur
                                char confirmFlag = dataInputStream.readChar();

                                if (confirmFlag == '1') {
                                    // Attendre quelque temps (tu peux remplacer par la logique que tu souhaites)
                                    Thread.sleep(TIMEOUT);

                                    // Envoie des informations sur l'état
                                    dataOutputStream.writeChar('1');
                                    dataOutputStream.flush();

                                    // Lire le chemin depuis le serveur : grille
                                    byte[] path = new byte[32];
                                    dataInputStream.readFully(path);


                                    if (confirmFlag == '1') {
                                        // Attendre quelque temps (tu peux remplacer par la logique que tu souhaites)
                                        Thread.sleep(TIMEOUT);

                                        // Envoie des informations sur l'état
                                        dataOutputStream.writeChar('1');
                                        dataOutputStream.flush();

                                        // Lire le chemin depuis le serveur : correction
                                        byte[] correction = new byte[32];
                                        dataInputStream.readFully(correction);

                                        // Processus terminé avec succès
                                        Intent intent = new Intent(answer, PictureAnswerActivity.class);
                                        startActivity(intent);
                                    } else {
                                        Log.d("denied", "Pas de réponse serveur : confirmFlag : Correction");
                                    }
                                } else {
                                    Log.d("denied", "Pas de réponse serveur : confirmFlag : Grille");
                                }
                            } else {
                                Log.d("denied", "Pas de réponse serveur : responseConfirm");
                            }
                        } else {
                            Log.d("denied", "Pas de réponse serveur : confirm_size ");
                        }
                    } else {
                        Log.d("denied", "Pas de réponse serveur : 1");
                    }

                    // Ferme les flux
                    fileInputStream.close();
                    bufferedOutputStream.close();
                    socket.close();
                } catch (SocketTimeoutException e) {
                    Intent intent = new Intent(answer, PictureActivity.class);
                    startActivity(intent);
                    Log.d("timeout", "Timeout lors de l'attente de la réponse du serveur");
                } catch (IOException | InterruptedException e) {
                    e.printStackTrace();
                    txt.setText(e.toString());
                }
            }
        });
        th.start();
    }

}
