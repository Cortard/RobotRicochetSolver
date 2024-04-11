package com.sae.myapplication.activity;

import android.Manifest;
import android.content.ContentResolver;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
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
import android.widget.ProgressBar;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import com.sae.myapplication.R;

import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;

/**
 * Activité permettant de vérifier une image et de la transmettre au serveur pour correction.
 */
public class PictureVerifyActivity extends AppCompatActivity {

    ImageView imageView;

    private static final int TIMEOUT = 10000;

    private static final int PERMISSION_CODE_FOLDER = 1234;


    String filePath;

    Button bCancel;
    Button bVld;

    ProgressBar progressBar;

    int[] tab;

    Uri image_uri;

    @RequiresApi(api = Build.VERSION_CODES.TIRAMISU)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_picture_verify);

        imageView = findViewById(R.id.imageVerif);

        ImageButton bReturn = findViewById(R.id.boutonReturn);
        bVld = findViewById(R.id.btnValide);
        ImageButton bHelp = findViewById(R.id.boutonHelp);
        progressBar = findViewById(R.id.progressBar);
        //progressBar.setVisibility(View.INVISIBLE);

        tab = getIntent().getIntArrayExtra("tabPos");

        image_uri = getIntent().getData();
        if (image_uri != null) {
            imageView.setImageURI(image_uri);
            Log.d("bug", "dddd : " + image_uri);

            filePath = getRealPathFromURI(image_uri);
        }

        bHelp.setOnClickListener(v -> {
            bHelp.setBackgroundColor(getColor(R.color.blueFooterBoxPress));
            new Handler().postDelayed(() -> bHelp.setBackgroundColor(getColor(R.color.blueFooterBox)), 50);
            Intent intent = new Intent(this, HelpActivity.class);
            startActivity(intent);
        });

        bReturn.setOnClickListener(v -> {
            bReturn.setBackgroundColor(getColor(R.color.blueFooterBoxPress));
            new Handler().postDelayed(() -> bReturn.setBackgroundColor(getColor(R.color.blueFooterBox)), 50);
            finish();
        });

        bCancel = findViewById(R.id.btnCancel);
        bCancel.setOnClickListener(v -> {
            Intent intent = new Intent(this, MainActivity.class);
            startActivity(intent);
            finish();
        });


        bVld.setOnClickListener(v -> {

            if (checkSelfPermission(Manifest.permission.READ_MEDIA_IMAGES) == PackageManager.PERMISSION_DENIED ||
                    checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_DENIED) {

                String[] permissions = {Manifest.permission.CAMERA, Manifest.permission.READ_MEDIA_IMAGES, Manifest.permission.WRITE_EXTERNAL_STORAGE};
                requestPermissions(permissions, PERMISSION_CODE_FOLDER);
            } else {
                sendImage(MainActivity.ip, 9090, filePath, this);
                imageView.setVisibility(View.INVISIBLE);
                bCancel.setVisibility(View.INVISIBLE);
                bVld.setVisibility(View.INVISIBLE);
            }

        });



    }

    /**
     * Gestionnaire d'autorisations pour l'accès aux images du média.
     *
     * @param requestCode  Code de la demande d'autorisation.
     * @param permissions  Tableau des autorisations demandées.
     * @param grantResults Résultats de la demande d'autorisation.
     */
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == PERMISSION_CODE_FOLDER) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                sendImage(MainActivity.ip, 9090, filePath, this);
                imageView.setVisibility(View.INVISIBLE);
                bCancel.setVisibility(View.INVISIBLE);
                bVld.setVisibility(View.INVISIBLE);
            } else {
                Toast.makeText(this, "Permission Denied", Toast.LENGTH_SHORT).show();
            }
        }
    }

    /**
     * Méthode pour obtenir le chemin réel d'une URI d'image.
     *
     * @param contentUri URI de l'image.
     * @return Chemin réel de l'image.
     */
    public String getRealPathFromURI(Uri contentUri) {
        String filePath = null;
        String[] filePathColumn = { MediaStore.Images.Media.DATA };
        ContentResolver contentResolver = this.getContentResolver();
        Cursor cursor = contentResolver.query(contentUri, filePathColumn, null, null, null);
        if (cursor != null) {
            cursor.moveToFirst();
            int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
            filePath = cursor.getString(columnIndex);
            cursor.close();
        }
        return filePath;
    }


    /**
     * Méthode pour envoyer l'image au serveur pour correction.
     *
     * @param serverIp Adresse IP du serveur.
     * @param serverPort Port du serveur.
     * @param filePath  Chemin du fichier image.
     * @param answer    Activité courante.
     */
    public void sendImage(String serverIp, int serverPort, String filePath, PictureVerifyActivity answer) {
        Thread th = new Thread(() -> {
            Socket socket;
            FileInputStream fileInputStream;
            BufferedOutputStream bufferedOutputStream;

            //progressBar.setVisibility(View.VISIBLE);

            int width;
            int height;

            Log.d("bug", "1 : " + filePath);


            try {
                socket = new Socket();
                socket.connect(new InetSocketAddress(serverIp, serverPort), TIMEOUT);
                fileInputStream = new FileInputStream(filePath);
                bufferedOutputStream = new BufferedOutputStream(socket.getOutputStream());
                DataOutputStream dataOutputStream = new DataOutputStream(bufferedOutputStream);
                Log.d("bug", "2");
                BitmapFactory.Options options = new BitmapFactory.Options();
                options.inJustDecodeBounds = true;
                Log.d("bug", "3");
                Bitmap bitmap = BitmapFactory.decodeFile(filePath);
                BitmapFactory.decodeFile(filePath, options);
                Log.d("bug", "4");
                width = options.outWidth;
                height = options.outHeight;


                // Envoie du FLAG au serveur : 1
                dataOutputStream.writeByte(1);
                dataOutputStream.flush();
                Log.d("bug", "5");
                byte[] byteTab = new byte[4];

                // Attente de la réponse du serveur avec timeouts
                DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
                dataInputStream.read(byteTab);
                Log.d("bug", "6");
                if(byteTab[0] == 1) {
                    Log.d("bug", width + " " + height);

                    ByteBuffer byteBuffer = ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN);
                    byteBuffer.putInt(height);
                    byteBuffer.putInt(width);

                    dataOutputStream.write(byteBuffer.array());
                    dataOutputStream.flush();

                    dataInputStream.read();

                    if (width * height * 3 > 0) {

                        //Bitmap bitmap = ((BitmapDrawable) imageView.getDrawable()).getBitmap();

                        progressBar.setMax(width * height);
                        int cpt=0;

                        try {
                            int BUFFER_SIZE = 1024;
                            byte[] buffer = new byte[BUFFER_SIZE];
                            File file = new File(filePath);
                            FileInputStream fis = new FileInputStream(file);
                            progressBar.setMax((int) file.length());
                            int read_size = 0;
                            while(read_size != -1) {
                                read_size = fis.read(buffer);
                                Log.d("bug", String.valueOf(read_size));
                                dataOutputStream.write(buffer);
                                dataOutputStream.flush();
                                cpt+=read_size;
                                progressBar.setProgress(cpt);
                            }
                            String a = "EOF";
                            Log.d("bug", "File ended send EOF of size");
                            dataOutputStream.write(a.getBytes());
                            dataOutputStream.flush();
                        } catch (IOException e) {
                            fileInputStream.close();
                            bufferedOutputStream.close();
                            socket.close();
                            e.printStackTrace();
                        }
                        // Empty read buffer
                        dataInputStream.read();

                        // Attente de la confirmation de la réception
                        Thread.sleep(TIMEOUT);
                        byte[] byteTab2 = new byte[4];
                        dataInputStream.read(byteTab2);
                        Log.d("bug", "Confirmation received : " + byteTab2[0]);


                        // Envoie du FLAG au serveur : 1
                        int nbRobot = tab.length - 2;
                        ByteBuffer nbRobotByte = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN);
                        Log.d("bug", "nb : "+ nbRobot);

                        nbRobotByte.putInt(nbRobot);
                        dataOutputStream.write(nbRobotByte.array());
                        dataOutputStream.flush();


                        dataInputStream.read();

                        if (nbRobot > 3) {
                            ByteBuffer robPosByte = ByteBuffer.allocate(20).order(ByteOrder.LITTLE_ENDIAN);
                            for (int i = 0; i < nbRobot; i++) {
                                robPosByte.putInt(tab[i]);
                                Log.d("bug", "posRob : "+ tab[i]);
                            }
                            dataOutputStream.write(robPosByte.array());
                            dataOutputStream.flush();

                            Log.d("bug", "objectif : "+ tab[tab.length-2]);

                            ByteBuffer destiByte = ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN);
                            destiByte.putInt(tab[tab.length-2]);
                            dataOutputStream.write(destiByte.array());
                            dataOutputStream.flush();


                            int time = dataInputStream.readByte();
                            Log.d("bug", "time : " + time);

                            int flag;

                            dataInputStream.read();

                            do {

                                flag = dataInputStream.readByte();
                                Log.d("bug", "Flag reçu : " + flag);

                                if (flag != 1) {
                                    break;
                                }

                                int[] state = new int[2];
                                state[0] = dataInputStream.readInt();
                                state[1] = dataInputStream.readInt();

                                Log.d("bug", "Depth : " + state[0] + ", Time in seconds : " + state[1]);
                            } while (flag == 1);


                            if (flag == 2) { // Cas 2 (NOTFOUND)
                                fileInputStream.close();
                                bufferedOutputStream.close();
                                socket.close();

                                Intent intent = new Intent(answer, PictureActivity.class);
                                intent.putExtra("tabPos", tab);
                                startActivity(intent);
                                finish();
                            } else if (flag == 3) { // Cas 3 (SOLVED)

                                byte[] pathBytes = new byte[32];
                                dataInputStream.readFully(pathBytes);

                                Log.d("correction ", "2.1 : " + Arrays.toString(pathBytes));

                                int[] pathChars = new int[pathBytes.length];
                                for (int i = 0; i < pathBytes.length; i++) {
                                    pathChars[i] = pathBytes[i];
                                }


                                int[] grid = new int[256];
                                byte[] byteGrid = new byte[256 * 4]; // Chaque entier occupe 4 octets

                                dataInputStream.read(byteGrid);

                                Log.d("bug", "byteGrid : " + Arrays.toString(byteGrid));


                                ByteBuffer buffer = ByteBuffer.wrap(byteGrid).order(ByteOrder.LITTLE_ENDIAN);
                                for (int i = 0; i < grid.length; i++) {
                                    grid[i] = buffer.getInt();
                                }

                                Log.d("bug", "grid : " + Arrays.toString(grid));

                                Log.d("bug", "tab : " + Arrays.toString(tab));

                                Intent intent = new Intent(answer, PictureAnswerActivity.class);
                                intent.putExtra("correctionGrid", pathChars);
                                intent.putExtra("tabPos", tab);
                                intent.putExtra("grid", grid);
                                startActivity(intent);
                                finish();
                            } else {
                                Log.d("denied", "Cas inattendu : " + flag);
                            }
                        } else {
                            Log.d("denied", "Pas de réponse serveur : confirmFlag");
                        }
                    } else {
                        Log.d("denied", "Pas de réponse serveur : confirm_size ");}
                } else {
                    Log.d("denied", "Pas de réponse serveur : 1");
                }
                fileInputStream.close();
                bufferedOutputStream.close();
                socket.close();
            } catch (Exception e) {
                Intent intent = new Intent(answer, PictureActivity.class);
                intent.putExtra("tabPos", tab);
                startActivity(intent);
                finish();
                Log.d("bug", e.toString());
            }
        });
        th.start();
    }
}