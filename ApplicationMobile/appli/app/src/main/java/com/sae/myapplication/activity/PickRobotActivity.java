package com.sae.myapplication.activity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.widget.Button;
import android.widget.ImageButton;

import androidx.appcompat.app.AppCompatActivity;

import com.sae.myapplication.R;

/**
 * Activité Pour choisir le nombre de robot à corriger
 */
public class PickRobotActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_robot_pick);

        Button fourRobot = findViewById(R.id.btnFourRobots);
        Button fiveRobot = findViewById(R.id.btnFiveRobots);

        ImageButton bReturn = findViewById(R.id.boutonReturn);
        ImageButton bHelp = findViewById(R.id.boutonHelp);


        fourRobot.setOnClickListener(v -> {
            Intent intent = new Intent(this, RobotCorrectionActivity.class);
            intent.putExtra("robot",4);
            startActivity(intent);
            finish();
        });

        fiveRobot.setOnClickListener(v -> {
            Intent intent = new Intent(this, RobotCorrectionActivity.class);
            intent.putExtra("robot",5);
            startActivity(intent);
            finish();
        });




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
    }
}