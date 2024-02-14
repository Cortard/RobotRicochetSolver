package com.sae.myapplication;

import android.Manifest;
import android.content.ContentValues;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.MediaStore;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

/**
 * Activité permettant à l'utilisateur de choisir ou de prendre une photo.
 */
public class PictureActivity extends AppCompatActivity {
    private static final int PERMISSION_CODE = 1234;
    private static final int CAPTURE_CODE = 1001;
    Uri image_uri;

    boolean galery = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_picture);

        ImageButton bReturn = findViewById(R.id.boutonReturn);
        ImageButton bHelp = findViewById(R.id.boutonHelp);

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

        Button bOpen = findViewById(R.id.btnOpenPicture);
        bOpen.setOnClickListener(v -> {

            Intent intent = new Intent(Intent.ACTION_PICK, MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
            startActivityForResult(intent, 3);
            galery = true;

        });

        Button bTake = findViewById(R.id.btnTakePicture);
        bTake.setOnClickListener(v -> {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                if (checkSelfPermission(Manifest.permission.CAMERA) == PackageManager.PERMISSION_DENIED ||
                        checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_DENIED ) {

                    String[] permissions = {Manifest.permission.CAMERA, Manifest.permission.WRITE_EXTERNAL_STORAGE};
                    requestPermissions(permissions, PERMISSION_CODE);
                } else {
                    openCamera();
                    galery=false;
                }
            } else {
                openCamera();
                galery=false;
            }
        });

    }

    /**
     * Ouvre la caméra pour prendre une photo.
     */
    private void openCamera() {
        ContentValues values = new ContentValues();
        values.put(MediaStore.Images.Media.TITLE,"new image");
        values.put(MediaStore.Images.Media.DESCRIPTION, "From the Camera");
        image_uri = getContentResolver().insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, values);

        Intent camintent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        camintent.putExtra(MediaStore.EXTRA_OUTPUT, image_uri);
        startActivityForResult(camintent, CAPTURE_CODE);
    }

    /**
     * Gère la réponse à la demande de permissions.
     *
     * @param requestCode  Code de la demande de permission.
     * @param permissions  Tableau de permissions demandées.
     * @param grantResults Résultats de la demande de permissions.
     */
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        switch (requestCode) {
            case PERMISSION_CODE:
                if (grantResults.length>0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    openCamera();
                } else {
                    Toast.makeText(this, "Permission Denied", Toast.LENGTH_SHORT).show();
                }
        }
    }

    /**
     * Gère le résultat de l'activité de sélection ou de prise de photo.
     *
     * @param requestCode Code de la requête.
     * @param resultCode  Code de résultat indiquant le succès ou l'échec de l'opération.
     * @param data        Intent contenant les données résultantes.
     */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode == RESULT_OK && !galery){
            Toast.makeText(this, "Photo Valide", Toast.LENGTH_SHORT).show();
            Intent intent = new Intent(this, PictureVerifyActivity.class);
            intent.setData(image_uri);
            int[] tab = getIntent().getIntArrayExtra("tabPos");
            intent.putExtra("tabPos", tab);
            startActivity(intent);
            finish();
        }

        if (resultCode == RESULT_OK && data != null && galery){
            image_uri = data.getData();
            Toast.makeText(this, "Photo Valide", Toast.LENGTH_SHORT).show();
            Intent intent = new Intent(this, PictureVerifyActivity.class);
            intent.setData(image_uri);
            int[] tab = getIntent().getIntArrayExtra("tabPos");
            intent.putExtra("tabPos", tab);
            startActivity(intent);
            finish();
        }
    }
}
