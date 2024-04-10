package com.sae.myapplication.model;

/**
 * Classe représentant un robot dans la grille de correction.
 */
public class Robot {
    private int x;
    private int y;
    private final int color;
    private final int number;

    /**
     * Constructeur de la classe Robot.
     *
     * @param x      Coordonnée x du robot.
     * @param y      Coordonnée y du robot.
     * @param number Numéro du robot.
     * @param color  Couleur du robot.
     */
    public Robot(int x, int y, int number, int color) {
        this.x = x;
        this.y = y;
        this.number = number;
        this.color = color;
    }

    /**
     * Méthode pour obtenir la coordonnée x du robot.
     *
     * @return Coordonnée x du robot.
     */
    public int getX() {
        return x;
    }

    /**
     * Méthode pour définir la coordonnée x du robot.
     *
     * @param res Nouvelle coordonnée x du robot.
     */
    void setX(int res) {
        this.x = res;
    }

    /**
     * Méthode pour obtenir la coordonnée y du robot.
     *
     * @return Coordonnée y du robot.
     */
    public int getY() {
        return y;
    }

    /**
     * Méthode pour définir la coordonnée y du robot.
     *
     * @param res Nouvelle coordonnée y du robot.
     */
    void setY(int res) {
        this.y = res;
    }

    /**
     * Méthode pour obtenir la couleur du robot.
     *
     * @return Couleur du robot.
     */
    public int getColor() {
        return color;
    }

    /**
     * Méthode pour obtenir le numéro du robot.
     *
     * @return Numéro du robot.
     */
    public int getNumber() {
        return number;
    }
}
