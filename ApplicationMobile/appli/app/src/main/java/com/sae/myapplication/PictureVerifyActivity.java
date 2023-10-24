package com.sae.myapplication;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;


public class PictureVerifyActivity extends AppCompatActivity {
    private static final int PERMISSION_CODE = 1234;
    private static final int CAPTURE_CODE = 1001;

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
            finish();
        });

        ImageButton bReturn = findViewById(R.id.boutonReturn);
        bReturn.setOnClickListener(v -> {
            Intent intent = new Intent(this, MainActivity.class);
            startActivity(intent);
            finish();
        });

        Button bCancel = findViewById(R.id.btnCancel);
        bCancel.setOnClickListener(v -> {
            Intent intent = new Intent(this, PictureActivity.class);
            startActivity(intent);
            finish();
        });

        Button bVld = findViewById(R.id.btnValide);
        bVld.setOnClickListener(v -> {
            //--------code server----------
        });

    }

}
