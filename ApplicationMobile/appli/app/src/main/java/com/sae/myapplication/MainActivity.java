package com.sae.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button bStart = findViewById(R.id.button);
        ImageButton bExit = findViewById(R.id.boutonExit);
        ImageButton bHelp = findViewById(R.id.boutonHelp);

        bHelp.setOnClickListener(v -> {
            Intent intent = new Intent(this, HelpActivity.class);
            startActivity(intent);
        });

        bStart.setOnClickListener(v -> {
            EditText ipEditText = findViewById(R.id.ipInput);
            String ipAddress = ipEditText.getText().toString();

            if (isValidIpAddress(ipAddress)) {
                if (ipAddress.equals(getString(R.string.IP))){
                    Intent intent = new Intent(this, PictureActivity.class);
                    startActivity(intent);
                } else {
                    Toast.makeText(this, "Adresse IP invalide. Mauvaise adresse IP.", Toast.LENGTH_SHORT).show();
                }
            } else {
                Toast.makeText(this, "Adresse IP invalide. Veuillez entrer une adresse IP valide.", Toast.LENGTH_SHORT).show();
            }
        });

        bExit.setOnClickListener(v -> {
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