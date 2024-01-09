package com.sae.myapplication;

import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.widget.ImageButton;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

public class HelpActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_help);

        ImageButton bReturn = findViewById(R.id.boutonReturn);

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
    }
}