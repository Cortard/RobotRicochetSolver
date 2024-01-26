package com.sae.myapplication;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Handler;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

import androidx.annotation.NonNull;

/**
 * Custom View pour afficher une grille et effectuer la correction des robots.
 */
public class MyCanvas extends View {

    private int[] gridData;
    private final Paint paint;
    private int cellSize;

    private int correctionIndex = 0;

    private static final int NORTH = 0x01; // 0b00000001
    private static final int EAST = 0x02;  // 0b00000010
    private static final int SOUTH = 0x04; // 0b00000100
    private static final int WEST = 0x08;  // 0b00001000
    private static final int ROBOT = 0x10; // 0b00010000
    private static final int GOAL = 0x20; // 0b00100000

    private final Handler correctionHandler;

    private Robot[] robots;

    public MyCanvas(Context context, AttributeSet attrs) {
        super(context, attrs);
        paint = new Paint();
        paint.setStyle(Paint.Style.FILL);

        correctionHandler = new Handler();
    }

    /**
     * Définit les données de la grille et les positions initiales des robots.
     *
     * @param gridData               Données de la grille.
     * @param initialRobotPositions Positions initiales des robots.
     */
    public void setGridData(int[] gridData, @NonNull int[] initialRobotPositions) {
        this.gridData = gridData;
        placeGoal(initialRobotPositions[initialRobotPositions.length-2]);
        initializeRobots(initialRobotPositions);
        invalidate();
    }


    private int getRobotColor(int robotNumber) {
        switch (robotNumber) {
            case 0:
                return Color.RED;
            case 1:
                return Color.BLUE;
            case 2:
                return Color.GREEN;
            case 3:
                return Color.YELLOW;
            default:
                return Color.BLACK;
        }
    }

    /**
     * Place l'objectif (goal) sur la grille à la position spécifiée.
     *
     * @param goalPosition Position de l'objectif.
     */
    private void placeGoal(int goalPosition) {
        if (goalPosition >= 0 && goalPosition < 256) {
            int x = goalPosition % 16;
            int y = goalPosition / 16;
            if ((gridData[y * 16 + x] & ROBOT) == 0) {
                gridData[y * 16 + x] |= GOAL;
            }
        }
    }

    /**
     * Dessine un robot sur le canvas à la position spécifiée.
     *
     * @param canvas      Canvas sur lequel dessiner.
     * @param x           Position horizontale du robot.
     * @param y           Position verticale du robot.
     * @param robotNumber Numéro du robot.
     */
    private void drawRobot(Canvas canvas, int x, int y, int robotNumber) {
        float centerX = (x + 0.5f) * cellSize;
        float centerY = (y + 0.5f) * cellSize;
        float radius = 0.4f * cellSize;

        paint.setColor(getRobotColor(robots[robotNumber].getColor()));
        canvas.drawCircle(centerX, centerY, radius, paint);
    }

    /**
     * Initialise la position des robots sur la grille.
     *
     * @param initialRobotPositions Positions initiales des robots.
     */
    private void initializeRobots(int[] initialRobotPositions) {
        if (initialRobotPositions.length-2 > 0) {
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 16; j++) {
                    gridData[i * 16 + j] &= ~ROBOT;
                }
            }

            robots = new Robot[initialRobotPositions.length-2];
            for (int i = 0; i < initialRobotPositions.length-2; i++) {

                int x = initialRobotPositions[i] % 16;
                int y = initialRobotPositions[i] / 16;
                Log.d("debug pos",initialRobotPositions[i] + " x : " + x + " y : " + y);

                int robotColor;
                if(i==0 && initialRobotPositions[initialRobotPositions.length - 1] == 1){
                    robotColor = 0;
                }else if(i==0 && initialRobotPositions[initialRobotPositions.length - 1] == 2){
                    robotColor = 1;
                }else if(i==0 && initialRobotPositions[initialRobotPositions.length - 1] == 3){
                    robotColor = 2;
                }else if(i==0 && initialRobotPositions[initialRobotPositions.length - 1] == 4){
                    robotColor = 3;
                }else {
                    robotColor = -1;
                }

                robots[i] = new Robot(x, y, i, robotColor);
                gridData[y * 16 + x] |= ROBOT;
                Log.d("placeGoal", "placeGoal: " + initialRobotPositions[i]);
            }
            invalidate();
        }
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        if (gridData == null || gridData.length != 256) {
            return;
        }
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                int value = gridData[i * 16 + j];
                drawCell(canvas, j, i, value);
            }
        }
        if (robots != null) {
            for (Robot robot : robots) {
                drawRobot(canvas, robot.getX(), robot.getY(), robot.getNumber());
            }
        }
    }

    /**
     * Démarre la correction des mouvements des robots.
     *
     * @param correctionGrid Tableau de correction des mouvements.
     */
    public void startCorrection(int[] correctionGrid) {
        if (correctionIndex < correctionGrid.length) {
            int correctionValue = correctionGrid[correctionIndex];
            int robotNumber = (correctionValue & 0x70) >> 4;
            int direction = correctionValue & 0x0F;

            moveRobot(robotNumber, direction);
            correctionIndex++;

            correctionHandler.postDelayed(() -> startCorrection(correctionGrid), 500);
        }
    }

    /**
     * Met à jour la position d'un robot sur la grille.
     *
     * @param oldX       Ancienne position horizontale.
     * @param oldY       Ancienne position verticale.
     * @param newX       Nouvelle position horizontale.
     * @param newY       Nouvelle position verticale.
     * @param robotNumber Numéro du robot.
     */
    private void updateRobotPosition(int oldX, int oldY, int newX, int newY, int robotNumber) {
        gridData[oldY * 16 + oldX] &= ~ROBOT;
        gridData[newY * 16 + newX] |= ROBOT;

        if (robots != null && robotNumber >= 0 && robotNumber < robots.length) {
            robots[robotNumber].setX(newX);
            robots[robotNumber].setY(newY);
        }
    }

    /**
     * Déplace un robot dans la direction spécifiée.
     *
     * @param robotNumber Numéro du robot.
     * @param direction   Direction du déplacement.
     */
    private void moveRobot(int robotNumber, int direction) {
        Robot currentRobot = findRobotByNumber(robotNumber);

        if (currentRobot == null) {
            return;
        }

        int oldX = currentRobot.getX();
        int oldY = currentRobot.getY();

        switch (direction) {
            case NORTH: //1
                while (currentRobot.getY() > 0 && (gridData[(currentRobot.getY() - 1) * 16 + currentRobot.getX()] & (SOUTH | ROBOT)) == 0) {
                    currentRobot.setY(currentRobot.getY() - 1);
                }
                break;
            case EAST: //2
                while (currentRobot.getX() < 15 && (gridData[currentRobot.getY() * 16 + currentRobot.getX() + 1] & (WEST | ROBOT)) == 0) {
                    currentRobot.setX(currentRobot.getX() + 1);
                }
                break;
            case SOUTH: //4
                while (currentRobot.getY() < 15 && (gridData[(currentRobot.getY() + 1) * 16 + currentRobot.getX()] & (NORTH | ROBOT)) == 0) {
                    currentRobot.setY(currentRobot.getY() + 1);
                }
                break;
            case WEST: //8
                while (currentRobot.getX() > 0 && (gridData[currentRobot.getY() * 16 + currentRobot.getX() - 1] & (EAST | ROBOT)) == 0) {
                    currentRobot.setX(currentRobot.getX() - 1);
                }
                break;
        }

        updateRobotPosition(oldX, oldY, currentRobot.getX(), currentRobot.getY(), robotNumber);
        invalidate();
    }

    /**
     * Recherche un robot par son numéro.
     *
     * @param robotNumber Numéro du robot à rechercher.
     * @return Instance du robot trouvé, sinon null.
     */
    private Robot findRobotByNumber(int robotNumber) {
        if (robots != null) {
            for (Robot robot : robots) {
                if (robot.getNumber() == robotNumber) {
                    return robot;
                }
            }
        }
        return null;
    }

    /**
     * Dessine une cellule de la grille avec des lignes pour représenter les murs.
     *
     * @param canvas Canvas sur lequel dessiner.
     * @param x      Position horizontale de la cellule.
     * @param y      Position verticale de la cellule.
     * @param value  Valeur de la cellule.
     */
    private void drawCell(Canvas canvas, int x, int y, int value) {

        paint.setStrokeWidth(2);
        paint.setColor(Color.WHITE);
        canvas.drawRect(x * cellSize, y * cellSize, (x + 1) * cellSize, (y + 1) * cellSize, paint);

        if ((value & GOAL) == GOAL) {
            paint.setColor(Color.GRAY);
            paint.setStrokeWidth(5);
            canvas.drawLine(x * cellSize, y * cellSize, (x + 1) * cellSize, (y + 1) * cellSize, paint); // 1er segment
            canvas.drawLine((x + 1) * cellSize, y * cellSize, x * cellSize, (y + 1) * cellSize, paint); // 2eme segment
        }

        paint.setColor(Color.BLACK);

        if ((value & NORTH) == NORTH) {
            canvas.drawLine(x * cellSize, y * cellSize, (x + 1) * cellSize, y * cellSize, paint); // NORTH
        }
        if ((value & EAST) == EAST) {
            canvas.drawLine((x + 1) * cellSize, y * cellSize, (x + 1) * cellSize, (y + 1) * cellSize, paint); // EAST
        }
        if ((value & SOUTH) == SOUTH) {
            canvas.drawLine(x * cellSize, (y + 1) * cellSize, (x + 1) * cellSize, (y + 1) * cellSize, paint); // SOUTH
        }
        if ((value & WEST) == WEST) {
            canvas.drawLine(x * cellSize, y * cellSize, x * cellSize, (y + 1) * cellSize, paint); // WEST
        }
    }


    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        cellSize = w / 16;
    }
}
