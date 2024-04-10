package com.sae.myapplication.model;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

/**
 * Vue personnalisée représentant une grille d'attributs avec des cases colorées.
 */
public class Grid extends View {
    private int id = 0;
    private int[] cases;
    private static final int TAILLE_GRILLE = 16;
    //private static final int NB = 5;

    public int robot = 5;
    private int NOMBRE_MAX_MODIFICATIONS = robot;
    private Paint paint;
    private int[][] grid;
    private int modificationsEffectuees = 0;

    /**
     * Constructeur de la classe.
     *
     * @param context Contexte de l'application.
     */
    public Grid(Context context) {
        super(context);
        init();
    }

    /**
     * Constructeur de la classe.
     *
     * @param context Contexte de l'application.
     * @param attrs   Attributs de l'interface utilisateur.
     */
    public Grid(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    /**
     * Choix du nombre de robot 4 ou 5.
     *
     * @param r Nombre de robots.
     */
    public void choseRobots(int r){
        robot = r+1;
        NOMBRE_MAX_MODIFICATIONS = robot;
        cases = new int[robot];
    }

    /**
     * Initialisation des composants de la vue.
     */
    private void init() {
        paint = new Paint();
        grid = new int[TAILLE_GRILLE][TAILLE_GRILLE];
        cases = new int[robot];
    }

    /**
     * Méthode appelée pour dessiner la grille.
     *
     * @param canvas Zone de dessin.
     */
    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        dessinerGrille(canvas);
    }

    /**
     * Méthode pour dessiner la grille sur le canvas.
     *
     * @param canvas Zone de dessin.
     */
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
                if ((i == 7 && j == 7) || (i == 7 && j == 8) || (i == 8 && j == 7) || (i == 8 && j == 8)) {
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

    /**
     * Méthode appelée lors d'un événement tactile.
     *
     * @param event Objet représentant l'événement tactile.
     * @return Vrai si l'événement est géré, sinon faux.
     */
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            int colonne = (int) (event.getX() / (getWidth() / TAILLE_GRILLE));
            int ligne = (int) (event.getY() / (getHeight() / TAILLE_GRILLE));

            if (colonne >= 0 && colonne < TAILLE_GRILLE && ligne >= 0 && ligne < TAILLE_GRILLE
                    && !((ligne == 7 && colonne == 7) || (ligne == 7 && colonne == 8) || (ligne == 8 && colonne == 7) || (ligne == 8 && colonne == 8))
                    && !(((ligne * TAILLE_GRILLE) + colonne == cases[0]) || ((ligne * TAILLE_GRILLE) + colonne == cases[1]) || ((ligne * TAILLE_GRILLE) + colonne == cases[2]) || ((ligne * TAILLE_GRILLE) + colonne == cases[3]) || ((ligne * TAILLE_GRILLE) + colonne == cases[4]))) {
                if (modificationsEffectuees < NOMBRE_MAX_MODIFICATIONS) {
                    changerCouleur(colonne, ligne);
                    invalidate(); // Redessiner la grille
                    Log.d("debug pos", (ligne * TAILLE_GRILLE) + colonne + " x : " + ligne + " y : " + colonne);
                    modificationsEffectuees++;
                }
                return true;
            }
        }
        return super.onTouchEvent(event);
    }

    /**
     * Méthode pour changer la couleur d'une case de la grille.
     *
     * @param colonne Colonne de la case.
     * @param ligne   Ligne de la case.
     */
    private void changerCouleur(int colonne, int ligne) {
        cases[id] = (ligne) * TAILLE_GRILLE + (colonne);
        int nouvelleCouleur = getCouleurSuivante(id);
        id++;
        grid[colonne][ligne] = nouvelleCouleur;
    }

    /**
     * Méthode pour obtenir la couleur suivante en fonction de l'index actuel.
     *
     * @param couleurActuelle Index actuel de la couleur.
     * @return Couleur suivante.
     */
    private int getCouleurSuivante(int couleurActuelle) {
        if (robot == 6){
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
                    return Color.BLACK;
                default:
                    return Color.GRAY; // Défaut vers la couleur rouge si la couleur actuelle n'est pas gérée
            }
        }else{
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
                    return Color.BLACK; // Défaut vers la couleur rouge si la couleur actuelle n'est pas gérée
            }
        }
    }

    /**
     * Méthode pour vérifier si suffisamment de cases ont été validées.
     *
     * @return Vrai si le nombre de cases validées est suffisant, sinon faux.
     */
    public boolean getCasesValide() {
        return id >= robot;
    }

    /**
     * Méthode pour obtenir les indices des cases en fonction de la destination spécifiée.
     *
     * @param dest Destination spécifiée ("objectifr1", "objectifr2", "objectifr3", "objectifr4", "objectifb1",
     *             "objectifb2", "objectifb3", "objectifb4", "objectifv1", "objectifv2", "objectifv3", "objectifv4",
     *             "objectifj1", "objectifj2", "objectifj3", "objectifj4", ou "tout").
     * @return Tableau d'indices des cases avec la couleur correspondante en dernière position.
     */
    public int[] getCases(String dest) {
        int[] rep = new int[robot + 1];
        int couleur = 0;

        if (dest.equals("objectifr1") || dest.equals("objectifr2") || dest.equals("objectifr3") || dest.equals("objectifr4")) {
            rep[0] = cases[0];
            couleur = 1;
            for (int i = 1; i < robot; i++) {
                if (i != 0) {
                    rep[i] = cases[i];
                }
            }
            // Rouge
        } else if (dest.equals("objectifb1") || dest.equals("objectifb2") || dest.equals("objectifb3") || dest.equals("objectifb4")) {
            rep[0] = cases[1];
            couleur = 2;
            for (int i = 1; i < robot; i++) {
                if (i != 1) {
                    rep[i] = cases[i];
                } else {
                    rep[i] = cases[0];
                }
            }
            // Bleu
        } else if (dest.equals("objectifv1") || dest.equals("objectifv2") || dest.equals("objectifv3") || dest.equals("objectifv4")) {
            rep[0] = cases[2];
            couleur = 3;
            for (int i = 1; i < robot; i++) {
                if (i != 2) {
                    rep[i] = cases[i];
                } else {
                    rep[i] = cases[0];
                }
            }
            // Vert
        } else if (dest.equals("objectifj1") || dest.equals("objectifj2") || dest.equals("objectifj3") || dest.equals("objectifj4")) {
            rep[0] = cases[3];
            couleur = 4;
            for (int i = 1; i < robot; i++) {
                if (i != 3) {
                    rep[i] = cases[i];
                } else {
                    rep[i] = cases[0];
                }
            }
            // Jaune
        } else {
            for (int i = 0; i < robot; i++) {
                rep[i] = cases[i];
            }
            // Tout
        }

        rep[robot] = couleur;
        return rep;
    }
}
