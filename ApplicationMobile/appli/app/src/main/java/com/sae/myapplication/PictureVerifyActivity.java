package com.sae.myapplication;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class PictureVerifyActivity extends AppCompatActivity {

    ImageView imageView;
     static TextView txt;


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

        Button bCancel = findViewById(R.id.btnCancel);
        bCancel.setOnClickListener(v -> {
            Intent intent = new Intent(this, PictureActivity.class);
            startActivity(intent);
            finish();
        });


        bVld.setOnClickListener(v -> {
            //MainActivity.ip
            Intent intent = new Intent(this, PictureLoadActivity.class);
            intent.setData(image_uri);
            startActivity(intent);
        });

    }
}
