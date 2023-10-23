package com.sae.myapplication;

import android.Manifest;
import android.content.ContentValues;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.MediaStore;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;


public class PictureVerifyActivity extends AppCompatActivity{
    private static final int PERMISSION_CODE = 1234;
    private static final int CAPTURE_CODE = 1001;

    ImageView imageView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_picture);

        imageView = findViewById(R.id.imageView);
        imageView.setImageURI(image_uri);

        ImageButton bHelp = findViewById(R.id.boutonHelp);
        bHelp.setOnClickListener(v -> {
            Intent intent = new Intent(this, HelpActivity.class);
            startActivity(intent);
            finish();
        });

        ImageButton bReturn = findViewById(R.id.boutonReturn);
        bReturn.setOnClickListener(v -> {
            Intent intent = new Intent(this, MainActivity.class);
            startActivity(intent);
            finish();
        });

        Button bOpen = findViewById(R.id.btnCancelPic);
        bOpen.setOnClickListener(v -> {
            Intent intent = new Intent(this, PictureActivity.class);
            startActivity(intent);
            finish();
        });

        Button bTake = findViewById(R.id.btnValidePic);
        bTake.setOnClickListener(v -> {
            //--------code server----------
        });

    }


}
