package com.sae.myapplication;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
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

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.math.BigInteger;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;
import java.util.concurrent.Semaphore;

public class PictureVerifyActivity extends AppCompatActivity {

    ImageView imageView;
     static TextView txt;
    private static final int TIMEOUT = 10000;

    private static final int PERMISSION_CODE_FOLDER = 1234;


    String filePath;

    Button bCancel;
    Button bVld;

    int[] tab;

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

        tab = getIntent().getIntArrayExtra("tabPos");

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

        bCancel = findViewById(R.id.btnCancel);
        bCancel.setOnClickListener(v -> {
            Intent intent = new Intent(this, PictureActivity.class);
            startActivity(intent);
            finish();
        });


        bVld.setOnClickListener(v -> {

            try {
                if (ActivityCompat.checkSelfPermission(PictureVerifyActivity.this, Manifest.permission.READ_MEDIA_IMAGES) != PackageManager.PERMISSION_GRANTED) {
                    ActivityCompat.requestPermissions(PictureVerifyActivity.this, new String[]{Manifest.permission.READ_MEDIA_IMAGES, Manifest.permission.WRITE_EXTERNAL_STORAGE}, PERMISSION_CODE_FOLDER);
                } else {
                    sendImage("195.201.205.241", 9090, filePath, this);
                    imageView.setVisibility(View.INVISIBLE);
                    bCancel.setVisibility(View.INVISIBLE);
                    bVld.setVisibility(View.INVISIBLE);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }

        });


    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String permissions[], @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        switch (requestCode) {
            case PERMISSION_CODE_FOLDER:
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    sendImage("195.201.205.241", 9090, filePath, this);
                    imageView.setVisibility(View.INVISIBLE);
                    bCancel.setVisibility(View.INVISIBLE);
                    bVld.setVisibility(View.INVISIBLE);
                } else {
                    Toast.makeText(this, "Permission Denied", Toast.LENGTH_SHORT).show();
                }
                break;
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
                int width = 0;
                int height = 0;
                int x = 0;

                try {
                    BitmapFactory.Options options = new BitmapFactory.Options();
                    options.inJustDecodeBounds = true;

                    BitmapFactory.decodeFile(filePath, options);

                    width = options.outWidth;
                    height = options.outHeight;

                    socket = new Socket();
                    socket.connect(new InetSocketAddress(serverIp, serverPort), TIMEOUT);
                    fileInputStream = new FileInputStream(filePath);
                    bufferedOutputStream = new BufferedOutputStream(socket.getOutputStream());
                    DataOutputStream dataOutputStream = new DataOutputStream(bufferedOutputStream);

                    // Envoie du FLAG au serveur : 1
                    dataOutputStream.writeByte(1);
                    dataOutputStream.flush();

                    byte[] byteTab = new byte[8];

                    // Attente de la réponse du serveur avec timeouts
                    DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
                    dataInputStream.read(byteTab);

                    if(byteTab[0] == 1) {
                        Log.d("bug", width + " " + height);

                        ByteBuffer byteBuffer = ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN);
                        byteBuffer.putInt(height);
                        byteBuffer.putInt(width);

                        dataOutputStream.write(byteBuffer.array());
                        dataOutputStream.flush();

                        long responseSize = dataInputStream.read();

                        if (width * height * 3 > 0) {

                            Bitmap bitmap = ((BitmapDrawable) imageView.getDrawable()).getBitmap();

                            Log.d("bug", "2");
                            Log.d("bug", bitmap.toString());

                            try {
                                for (int i = 0; i < height; ++i) {
                                    for (int j = 0; j < width; ++j) {
                                        for (int k = 0; k < 3; ++k) {
                                            // Envoie de chaque valeur de pixel
                                            dataOutputStream.writeByte(bitmap.getPixel(j, i));
//                                            ByteBuffer byteImgBuffer = ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN);
//                                            byteImgBuffer.putInt(bitmap.getPixel(j, i));
                                            dataOutputStream.flush();
                                        }
                                    }
                                }
                            } catch (IOException e) {
                                fileInputStream.close();
                                bufferedOutputStream.close();
                                socket.close();
                                e.printStackTrace();
                            }

                            Log.d("bug", "3");

                            // Attente de la confirmation de la réception
                            Thread.sleep(TIMEOUT);
                            byte[] byteTab2 = new byte[8];
                            dataInputStream.read(byteTab2);

                            Log.d("bug", "4   " + byteTab2[0]);


                                // Envoie du FLAG au serveur : 1

                                Log.d("bug", "4.5");

                                int nbRobot = tab.length - 2;

                                ByteBuffer nbRobotByte = ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN);
                                nbRobotByte.putInt(nbRobot);

                                Log.d("bug", "5");

                                dataOutputStream.write(nbRobotByte.array());
                                dataOutputStream.flush();

                                Log.d("bug", "6");

                                // Attente de la réponse du serveur avec timeout
                                long confirmFlag = dataInputStream.read();

                                if (nbRobot > 3) {

                                    Log.d("bug", "7");

                                    for (int i = 1; i < nbRobot; i++) {
                                        dataOutputStream.writeInt(tab[i]);
                                    }
                                    dataOutputStream.flush();

                                    Log.d("bug", "8");

                                    txt.setText(tab[tab.length-2]);
                                    dataOutputStream.writeInt(tab[tab.length-2]);
                                    dataOutputStream.flush();

                                    Log.d("bug", "9");
                                    Thread.sleep(TIMEOUT);

                                    // Attente de la réponse du serveur avec timeout
                                    char finalFlag = dataInputStream.readChar();

                                    if ((int) finalFlag == 1) {
                                        // Processus terminé avec succès
                                        Intent intent = new Intent(answer, PictureAnswerActivity.class);
                                        intent.putExtra("tabPos", tab);
                                        startActivity(intent);
                                    } else {
                                        Log.d("denied", "Pas de réponse serveur : finalFlag");
                                        txt.setText("Pas de réponse serveur : finalFlag");

                                    }
                                } else {
                                    Log.d("denied", "Pas de réponse serveur : confirmFlag");
                                    txt.setText("Pas de réponse serveur : confirmFlag");

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
                    fileInputStream.close();
                    bufferedOutputStream.close();
                    socket.close();
                } catch (SocketTimeoutException e) {
//                    Intent intent = new Intent(answer, PictureActivity.class);
//                    startActivity(intent);

                    txt.setText(e.toString());
                } catch (IOException e) {
//                    Intent intent = new Intent(answer, PictureActivity.class);
//                    startActivity(intent);

                    Log.d("bug", e.toString());

                    //txt.setText(x + " io");
                    //txt.setText(e.toString());
                } catch (Exception e) {
//                    Intent intent = new Intent(answer, PictureActivity.class);
//                    startActivity(intent);

                    e.printStackTrace();
                }
            }
        });
        th.start();
    }
}
