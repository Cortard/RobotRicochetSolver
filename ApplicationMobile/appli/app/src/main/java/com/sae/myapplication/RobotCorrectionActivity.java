package com.sae.myapplication;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Spinner;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.Arrays;
import java.util.List;

public class RobotCorrectionActivity extends AppCompatActivity {
    String newItem;

    List<String> states;
    Spinner spinner;
    EditText text1;
    EditText text2;
    EditText text3;
    EditText text4;
    EditText text5;
    EditText text6;
    EditText text7;
    EditText text8;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_robot_position);

        Button bValide = findViewById(R.id.btnRobotCor);
        ImageButton bReturn = findViewById(R.id.boutonReturn);
        ImageButton bHelp = findViewById(R.id.boutonHelp);

        text1 = findViewById(R.id.editTextNumber9);
        text2 = findViewById(R.id.editTextNumber2);
        text3 = findViewById(R.id.editTextNumber10);
        text4 = findViewById(R.id.editTextNumber11);
        text5 = findViewById(R.id.editTextNumber5);
        text6 = findViewById(R.id.editTextNumber6);
        text7 = findViewById(R.id.editTextNumber7);
        text8 = findViewById(R.id.editTextNumber8);


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


        bValide.setOnClickListener(v -> {

            EditText[] editTextArray = {
                    text1, text2, text3, text4,
                    text5, text6, text7, text8
            };

            if (validateEditTexts(editTextArray)) {
                Intent intent = new Intent(this, PictureAnswerActivity.class);
                startActivity(intent);
            } else {
                Toast.makeText(this, "Veuillez remplir toutes les cases (0 à 16 seulement) !", Toast.LENGTH_SHORT).show();
            }
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
                Toast.makeText(getApplicationContext(), "You selected: " + newItem, Toast.LENGTH_LONG).show();
            }
            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {}
        });

    }

    public boolean validateEditTexts(EditText[] editTexts) {
        for (EditText editText : editTexts) {
            String inputValue = editText.getText().toString().trim();

            if (inputValue.isEmpty()) {
                // L'EditText est vide
                return false;
            }

            try {
                int value = Integer.parseInt(inputValue);

                if (value < 0 || value > 16) {
                    return false;
                }
            } catch (NumberFormatException e) {
                return false;
            }
        }
        return true;
    }

}