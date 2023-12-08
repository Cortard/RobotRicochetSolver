package com.sae.myapplication;

public class Robot {
    private int x;
    private int y;
    private int color;
    private int number;

    public Robot(int x, int y, int number, int color) {
        this.x = x;
        this.y = y;
        this.number = number;
        this.color = color;
    }

    public int getX() {
        return x;
    }

    void setX(int res) {
        this.x = res;
    }

    public int getY() {
        return y;
    }

    void setY(int res) {
        this.y = res;
    }

    public int getColor() {
        return color;
    }

    public int getNumber() {
        return number;
    }
}