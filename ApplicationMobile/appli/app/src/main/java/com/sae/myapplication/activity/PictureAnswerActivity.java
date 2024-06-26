package com.sae.myapplication.activity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.widget.Button;
import android.widget.ImageButton;

import androidx.appcompat.app.AppCompatActivity;

import com.sae.myapplication.model.MyCanvas;
import com.sae.myapplication.R;

import java.util.Arrays;

/**
 * Activité qui affiche la grille et sa correction après avoir sélectionné ou pris une photo.
 */
public class PictureAnswerActivity extends AppCompatActivity {

    int[] gridData;
    int[] correctionData;
    int[] initialRobotPositions;


    private boolean isCorrectionRunning = false;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_picture_answer);

        ImageButton bHelp = findViewById(R.id.boutonHelp);
        ImageButton bReturn = findViewById(R.id.boutonReturn);

        initialRobotPositions = getIntent().getIntArrayExtra("tabPos");
        correctionData = getIntent().getIntArrayExtra("correctionGrid");
        gridData = getIntent().getIntArrayExtra("grid");

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
            Intent intent = new Intent(this, PictureActivity.class);
            startActivity(intent);
            finish();
        });

        MyCanvas myCanvas = findViewById(R.id.canva);

        //gridData = new int[]{9, 1, 5, 1, 3, 9, 1, 1, 1, 3, 9, 1, 1, 1, 1, 3, 8, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 3, 8, 0, 0, 0, 0, 2, 12, 0, 2, 9, 0, 0, 0, 0, 4, 2, 12, 0, 0, 0, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 10, 9, 0, 0, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 6, 8, 0, 0, 0, 0, 4, 4, 0, 0, 2, 12, 0, 0, 2, 8, 1, 0, 0, 0, 0, 2, 9, 3, 8, 0, 0, 1, 0, 0, 2, 8, 0, 4, 0, 2, 12, 2, 12, 6, 8, 0, 0, 0, 0, 0, 6, 8, 18, 9, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 4, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 0, 2, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 0, 0, 0, 2, 9, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1, 0, 0, 2, 12, 2, 8, 0, 0, 16, 3, 8, 0, 0, 0, 4, 0, 0, 0, 0, 1, 2, 8, 6, 8, 0, 0, 0, 0, 0, 0, 3, 8, 0, 0, 0, 16, 2, 12, 5, 4, 4, 4, 6, 12, 4, 4, 4, 4, 6, 12, 4, 4, 6};
        //correctionData = new int[]{1, 2, 4, 17, 18, 40, 33, 8, 1, 2, 1, 2, 56, 49, 56, 49, 50, 49, 8, 4, 63};

        Log.d("answer", "tab : " + Arrays.toString(initialRobotPositions));
        Log.d("answer", "grid : " + Arrays.toString(gridData));
        Log.d("answer", "corr : " + Arrays.toString(correctionData));

        myCanvas.setGridData(gridData,initialRobotPositions);

        Button btnCorrect = findViewById(R.id.btnCor);
        btnCorrect.setOnClickListener(v -> {
            myCanvas.startCorrection(correctionData);
            btnCorrect.setText("Recommencer");
            if (isCorrectionRunning) {
                Intent intent = new Intent(this, PictureAnswerActivity.class);
                intent.putExtra("correctionGrid", correctionData);
                intent.putExtra("tabPos", initialRobotPositions);
                intent.putExtra("grid", gridData);
                startActivity(intent);
                finish();
            }
            isCorrectionRunning = true;
        });

    }

}
