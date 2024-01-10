package com.sae.myapplication;

import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;

public class PictureVerifyActivity extends AppCompatActivity {

    ImageView imageView;
     static TextView txt;
    private static final int TIMEOUT = 10000;
    private static final int MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE = 1;
    private static final int PERMISSION_CODE = 1234;

    String filePath;

    Button bCancel;
    Button bVld;


    Uri image_uri;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_picture_verify);

        imageView = findViewById(R.id.imageVerif);
        txt = findViewById(R.id.textView);

        ImageButton bReturn = findViewById(R.id.boutonReturn);
        bVld = findViewById(R.id.btnValide);
        ImageButton bHelp = findViewById(R.id.boutonHelp);

        image_uri = getIntent().getData();
        if (image_uri != null) {
            imageView.setImageURI(image_uri);
            filePath = getRealPathFromURI(image_uri);
        }

        bHelp.setOnClickListener(v -> {
            bHelp.setBackgroundColor(getColor(R.color.blueFooterBoxPress));
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    bHelp.setBackgroundColor(getColor(R.color.blueFooterBox));
                }
            }, 50);
            Intent intent = new Intent(this, HelpActivity.class);
            startActivity(intent);
        });

        bReturn.setOnClickListener(v -> {
            bReturn.setBackgroundColor(getColor(R.color.blueFooterBoxPress));
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    bReturn.setBackgroundColor(getColor(R.color.blueFooterBox));
                }
            }, 50);
            finish();
        });


        txt.setText("test");

        bCancel = findViewById(R.id.btnCancel);
        bCancel.setOnClickListener(v -> {
            Intent intent = new Intent(this, PictureActivity.class);
            startActivity(intent);
            finish();
        });


        bVld.setOnClickListener(v -> {
            //MainActivity.ip

           if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                if (checkSelfPermission(android.Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_DENIED) {

                    String[] permissions = {android.Manifest.permission.WRITE_EXTERNAL_STORAGE};
                    requestPermissions(permissions, PERMISSION_CODE);
                } else {
                    sendImage("195.201.205.241", 9090, filePath, this);
                    imageView.setVisibility(View.INVISIBLE);
                    bCancel.setVisibility(View.INVISIBLE);
                    bVld.setVisibility(View.INVISIBLE);
                }
           } else {
               sendImage("195.201.205.241", 9090, filePath, this);
               imageView.setVisibility(View.INVISIBLE);
               bCancel.setVisibility(View.INVISIBLE);
               bVld.setVisibility(View.INVISIBLE);
           }


        });

    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        switch (requestCode) {
            case PERMISSION_CODE:
                if (grantResults.length>0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    sendImage("195.201.205.241", 9090, filePath, this);
                    imageView.setVisibility(View.INVISIBLE);
                    bCancel.setVisibility(View.INVISIBLE);
                    bVld.setVisibility(View.INVISIBLE);
                } else {
                    Toast.makeText(this, "Permission Denied", Toast.LENGTH_SHORT).show();
                }
        }
    }

    public String getRealPathFromURI(Uri contentUri) {
        String[] proj = {MediaStore.Images.Media.DATA};
        Cursor cursor = getContentResolver().query(contentUri, proj, null, null, null);
        int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
        cursor.moveToFirst();
        String filePath = cursor.getString(column_index);
        cursor.close();
        return filePath;
    }


    public void sendImage(String serverIp, int serverPort, String filePath, PictureVerifyActivity answer) {
        Thread th = new Thread(new Runnable() {
            @Override
            public void run() {
                Socket socket = null;
                FileInputStream fileInputStream = null;
                BufferedOutputStream bufferedOutputStream = null;

                txt.setText(filePath);

                try {
                    BitmapFactory.Options options = new BitmapFactory.Options();
                    options.inJustDecodeBounds = true;

                    int width = options.outWidth;
                    int height = options.outHeight;

                    socket = new Socket();
                    socket.connect(new InetSocketAddress(serverIp, serverPort), TIMEOUT);
                    fileInputStream = new FileInputStream(new File(filePath));
                    bufferedOutputStream = new BufferedOutputStream(socket.getOutputStream());
                    DataOutputStream dataOutputStream = new DataOutputStream(bufferedOutputStream);


                    // Envoie du FLAG au serveur : 1
                    dataOutputStream.writeChar(0);
                    dataOutputStream.flush();

                    // Attente de la réponse du serveur avec timeout
                    socket.setSoTimeout(TIMEOUT); // Définit le timeout pour la réponse
                    DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
                    char response = dataInputStream.readChar();

                    txt.setText(String.valueOf((int)response));

                    if ((int)response == 0) {
                        int[] dimensions = {width, height};
                        for (int dimension : dimensions) {
                            dataOutputStream.writeInt(dimension);
                        }
                        dataOutputStream.flush();


                        DataInputStream dataInputStreamLong = new DataInputStream(socket.getInputStream());
                        long responseSize = dataInputStreamLong.readLong();

                        txt.setText(width * height *3);

                        if (responseSize == width * height * 3) {
                            char[] imageData = readFileToCharArray(filePath);

                            // Envoyer la taille du tableau
                            int size = imageData.length;
                            dataOutputStream.writeInt(size);

                            // Envoyer le tableau de chars
                            for (char c : imageData) {
                                dataOutputStream.writeChar(c);
                            }


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
                                        txt.setText("Pas de réponse serveur : finalFlag");

                                    }
                                } else {
                                    Log.d("denied", "Pas de réponse serveur : confirmFlag");
                                    txt.setText("Pas de réponse serveur : confirmFlag");

                                }
                            } else if (responseConfirm == 2) { // not found
                                // Cas où la communication est interrompue
                                Log.d("info", "Cas NOTFOUND - communication shutdown");
                                txt.setText("Cas NOTFOUND - communication shutdown");

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
                                        txt.setText("Pas de réponse serveur : confirmFlag : Correction");
                                    }
                                } else {
                                    Log.d("denied", "Pas de réponse serveur : confirmFlag : Grille");
                                    txt.setText("Pas de réponse serveur : confirmFlag : Grille");

                                }
                            } else {
                                Log.d("denied", "Pas de réponse serveur : responseConfirm");
                                txt.setText("Pas de réponse serveur : confirmFlag : responseConfirm");
                            }
                        } else {
                            Log.d("denied", "Pas de réponse serveur : confirm_size ");
                            //txt.setText("Pas de réponse serveur : confirmFlag : confirm_size");
                        }
                    } else {
                        Log.d("denied", "Pas de réponse serveur : 1");
                        txt.setText("Pas de réponse serveur : confirmFlag : 1");
                        //txt.setText(response + " confirm flag 1");

                    }

                    // Ferme les flux
                    fileInputStream.close();
                    bufferedOutputStream.close();
                    socket.close();
                } catch (SocketTimeoutException e) {
//                    Intent intent = new Intent(answer, PictureActivity.class);
//                    startActivity(intent);
                    txt.setText(e.toString());
                } catch (IOException | InterruptedException e) {
//                    Intent intent = new Intent(answer, PictureActivity.class);
//                    startActivity(intent);
                    e.printStackTrace();
                    txt.setText(e.toString());
                } catch (Exception e) {
//                    Intent intent = new Intent(answer, PictureActivity.class);
//                    startActivity(intent);
                    e.printStackTrace();
                    txt.setText(e.toString());
                }
            }
        });
        th.start();
    }

    private char[] readFileToCharArray(String file) {
        try {
            FileInputStream fileInputStream = new FileInputStream(file);
            char[] data = new char[(int) file.length()];
            int bytesRead;
            for (int i = 0; (bytesRead = fileInputStream.read()) != -1; i++) {
                data[i] = (char) bytesRead;
            }
            fileInputStream.close();
            return data;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
