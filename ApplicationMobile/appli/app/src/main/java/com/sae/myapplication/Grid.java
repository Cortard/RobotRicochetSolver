package com.sae.myapplication;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

public class Grid extends View {
    int id = 0;
    private int[] cases;
    private static final int TAILLE_GRILLE = 16;
    private static final int NB = 5;
    private static final int NOMBRE_MAX_MODIFICATIONS = NB;
    private Paint paint;
    private int[][] grid;
    private int modificationsEffectuees = 0;

    public Grid(Context context) {
        super(context);
        init();
    }

    public Grid(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        paint = new Paint();
        grid = new int[TAILLE_GRILLE][TAILLE_GRILLE];
        cases = new int [NB];
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        dessinerGrille(canvas);
    }

    private void dessinerGrille(Canvas canvas) {
        int largeurCellule = getWidth() / TAILLE_GRILLE;
        int hauteurCellule = getHeight() / TAILLE_GRILLE;

        for (int i = 0; i < TAILLE_GRILLE; i++) {
            for (int j = 0; j < TAILLE_GRILLE; j++) {
                int left = i * largeurCellule;
                int top = j * hauteurCellule;
                int right = (i + 1) * largeurCellule;
                int bottom = (j + 1) * hauteurCellule;

                paint.setColor(grid[i][j]);
                int color = 0;
                if((i==7 && j==7) || (i==7 && j==8) || (i==8 && j==7) || (i==8 && j==8)){
                    color = getCouleurSuivante(id);
                    paint.setColor(color);
                }
                canvas.drawRect(left, top, right, bottom, paint);

                paint.setColor(Color.BLACK);
                paint.setStyle(Paint.Style.STROKE);
                paint.setStrokeWidth(2);



                canvas.drawRect(left, top, right, bottom, paint);

                paint.setStyle(Paint.Style.FILL);
            }
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            int colonne = (int) (event.getX() / (getWidth() / TAILLE_GRILLE));
            int ligne = (int) (event.getY() / (getHeight() / TAILLE_GRILLE));

            if (colonne >= 0 && colonne < TAILLE_GRILLE && ligne >= 0 && ligne < TAILLE_GRILLE
                    && !((ligne==7 && colonne==7) || (ligne==7 && colonne==8) || (ligne==8 && colonne==7) || (ligne==8 && colonne==8))
                    && !(((colonne+1)*(ligne+1) == cases[0]) || ((colonne+1)*(ligne+1) == cases[1]) || ((colonne+1)*(ligne+1) == cases[2]) || ((colonne+1)*(ligne+1) == cases[3]) || ((colonne+1)*(ligne+1) == cases[4]))) {
                if (modificationsEffectuees < NOMBRE_MAX_MODIFICATIONS) {
                    changerCouleur(colonne, ligne);
                    invalidate(); // Redessiner la grille
                    Log.d("debug pos",(ligne*TAILLE_GRILLE)+colonne + " x : " + ligne + " y : " + colonne);
                    modificationsEffectuees++;
                }
                return true;
            }
        }
        return super.onTouchEvent(event);
    }

    private void changerCouleur(int colonne, int ligne) {
        cases[id] = (ligne)*TAILLE_GRILLE+(colonne);
        int nouvelleCouleur = getCouleurSuivante(id);
        id++;
        grid[colonne][ligne] = nouvelleCouleur;
    }

    private int getCouleurSuivante(int couleurActuelle) {
        switch (couleurActuelle) {
            case 0:
                return Color.RED;
            case 1:
                return Color.BLUE;
            case 2:
                return Color.GREEN;
            case 3:
                return Color.YELLOW;
            case 4:
                return Color.GRAY;
            default:
                return Color.BLACK; // DÃ©faut vers la couleur rouge si la couleur actuelle n'est pas gÃ©rÃ©e
        }
    }

    public boolean getCasesValide(){
        if(id<5){
            return false;
        }
        else{
            return true;
        }
    }

    public int[] getCases(String dest){
        int[] rep = new int [NB+1];
        int couleur = 0;

        if(dest == "objectifr1" || dest == "objectifr2" || dest == "objectifr3" || dest == "objectifr4"){
            rep[0] = cases[0];
            couleur = 1;
            for(int i = 1 ; i<NB ; i++){
                if(i!=0){
                    rep[i] = cases[i];
                }
            }
            //rouge

        }else if(dest == "objectifb1" || dest == "objectifb2" || dest == "objectifb3" || dest == "objectifb4"){
            rep[0] = cases[1];
            couleur = 2;
            for(int i = 1 ; i<NB ; i++){
                if(i!=1){
                    rep[i] = cases[i];
                }else{
                    rep[i] = cases[0];
                }
            }
            //bleu
        }else if(dest == "objectifv1" || dest == "objectifv2" || dest == "objectifv3" || dest == "objectifv4"){
            rep[0] = cases[2];
            couleur = 3;
            for(int i = 1 ; i<NB ; i++){
                if(i!=2){
                    rep[i] = cases[i];
                }else{
                    rep[i] = cases[0];
                }
            }
            //vert
        }else if(dest == "objectifj1" || dest == "objectifj2" || dest == "objectifj3" || dest == "objectifj4"){
            rep[0] = cases[3];
            couleur = 4;
            for(int i = 1 ; i<NB ; i++){
                if(i!=3){
                    rep[i] = cases[i];
                }else{
                    rep[i] = cases[0];
                }
            }
            //jaune
        }else {
            for(int i = 0 ; i<NB ; i++){
                rep[i] = cases[i];
            }
            //tout
        }

        rep[NB] = couleur;
        return rep;
    }
}