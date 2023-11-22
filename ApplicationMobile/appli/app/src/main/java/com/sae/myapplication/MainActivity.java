package com.sae.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.view.SurfaceView;
import android.view.TextureView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button bStart = findViewById(R.id.button);
        ImageButton bExit = findViewById(R.id.boutonExit);
        ImageButton bHelp = findViewById(R.id.boutonHelp);
        ImageView box = findViewById(R.id.footerbox);
        ImageView box2 = findViewById(R.id.footerbox2);

        bHelp.setOnClickListener(v -> {

            box.setBackgroundColor(Color.parseColor("#4288BF"));
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    box.setBackgroundColor(Color.parseColor("#1C5F93"));
                }
            }, 50);

            Intent intent = new Intent(this, HelpActivity.class);
            startActivity(intent);
        });


        bStart.setOnClickListener(v -> {
            EditText ipEditText = findViewById(R.id.ipInput);
            String ipAddress = ipEditText.getText().toString();

            if (isValidIpAddress(ipAddress)) {
                Intent intent = new Intent(this, PictureActivity.class);
                startActivity(intent);
            } else {
                Toast.makeText(this, "Adresse IP invalide. Veuillez entrer une adresse IP valide.", Toast.LENGTH_SHORT).show();
            }
        });

        bExit.setOnClickListener(v -> {
            box2.setBackgroundColor(Color.parseColor("#4288BF"));
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    box2.setBackgroundColor(Color.parseColor("#1C5F93"));
                }
            }, 50);
            System.exit(0);
        });
    }

    // Méthode de validation de l'adresse IP
    private boolean isValidIpAddress(String ipAddress) {

        String ipPattern = "^([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
                "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
                "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
                "([01]?\\d\\d?|2[0-4]\\d|25[0-5])$";

        return ipAddress.matches(ipPattern);
    }
}