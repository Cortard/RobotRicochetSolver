package com.sae.myapplication;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.Arrays;
import java.util.List;

/**
 * Activité pour la correction de la position des robots sur la grille.
 */
public class RobotCorrectionActivity extends AppCompatActivity {
    String newItem;

    List<String> states;
    Spinner spinner;
    int robot;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_robot_position);

        Button bValide = findViewById(R.id.btnRobotCor);
        Button bReset = findViewById(R.id.btnRobotCorReset);

        ImageButton bReturn = findViewById(R.id.boutonReturn);
        ImageButton bHelp = findViewById(R.id.boutonHelp);

        robot = getIntent().getIntExtra("robot",4);

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

        Grid grid = findViewById(R.id.grid);
        grid.choseRobots(robot);

        bValide.setOnClickListener(v -> {

            if (grid.getCasesValide()) {
                Intent intent = new Intent(this, PictureActivity.class);
                intent.putExtra("tabPos", grid.getCases(newItem));
                startActivity(intent);
                finish();
            } else {
                Toast.makeText(this, "Veuillez placer tout les robots !", Toast.LENGTH_SHORT).show();
            }
        });

        bReset.setOnClickListener(v -> {
            Intent intent = new Intent(this, RobotCorrectionActivity.class);
            intent.putExtra("robot",robot);
            startActivity(intent);
            finish();
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

        states = Arrays.asList("objectifr1", "objectifr2", "objectifr3", "objectifr4", "objectifb1", "objectifb2", "objectifb3", "objectifb4", "objectifj1", "objectifj2", "objectifj3", "objectifj4", "objectifv1", "objectifv2", "objectifv3", "objectifv4", "objectif");
        spinner = findViewById(R.id.spinner);
        // Our custom Adapter class that we created
        SpinnerAdapter adapter = new SpinnerAdapter(getApplicationContext(), states);
        adapter.setDropDownViewResource(R.layout.my_dropdown_item);

        spinner.setAdapter(adapter);

        // Make a Toast whenever the user selects something from the Spinner
        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
                newItem = states.get(i);
            }
            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {}
        });

    }

}