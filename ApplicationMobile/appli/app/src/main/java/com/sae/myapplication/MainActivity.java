package com.sae.myapplication;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

/**
 * Activité principale de l'application. Permet à l'utilisateur d'entrer une adresse IP
 * pour se connecter au serveur et propose des options telles que le lancement de l'application
 * et l'accès à la page d'aide.
 */
public class MainActivity extends AppCompatActivity {

    public static String ip = "1.1.1.1";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button bStart = findViewById(R.id.button);
        ImageButton bExit = findViewById(R.id.boutonExit);
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


        bStart.setOnClickListener(v -> {
            EditText ipEditText = findViewById(R.id.ipInput);
            String ipAddress = ipEditText.getText().toString();

            if (isValidIpAddress(ipAddress)) {
                ip = ipAddress;
                Intent intent = new Intent(this, RobotCorrectionActivity.class);
                startActivity(intent);
            } else {
                Toast.makeText(this, "Adresse IP invalide. Veuillez entrer une adresse IP valide.", Toast.LENGTH_SHORT).show();
            }
        });

        bExit.setOnClickListener(v -> {
            bExit.setBackgroundColor(getColor(R.color.blueFooterBoxPress));
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    bExit.setBackgroundColor(getColor(R.color.blueFooterBox));
                }
            }, 50);
            System.exit(0);
        });
    }

    /**
     * Méthode appelée pour vérifier si une adresse IP est valide.
     *
     * @param ipAddress Adresse IP à valider.
     * @return True si l'adresse IP est valide, false sinon.
     */
    private boolean isValidIpAddress(String ipAddress) {

        String ipPattern = "^([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
                "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
                "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
                "([01]?\\d\\d?|2[0-4]\\d|25[0-5])$";

        return ipAddress.matches(ipPattern);
    }
}