package com.sae.myapplication;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Handler;
import android.util.AttributeSet;
import android.view.View;

public class MyCanvas extends View {

    private int[] gridData;
    private Paint paint;
    private int cellSize;

    private int correctionIndex = 0;

    private static final int NORTH = 0x01; // 0b00000001
    private static final int EAST = 0x02;  // 0b00000010
    private static final int SOUTH = 0x04; // 0b00000100
    private static final int WEST = 0x08;  // 0b00001000
    private static final int ROBOT = 0x10; // 0b00010000
    private static final int GOAL = 0x20; // 0b00100000

    private Handler correctionHandler;

    private Robot[] robots;

    public MyCanvas(Context context, AttributeSet attrs) {
        super(context, attrs);
        paint = new Paint();
        paint.setStyle(Paint.Style.FILL);

        correctionHandler = new Handler();
    }

    public void setGridData(int[] gridData, int[] initialRobotPositions, int goalPosition) {
        this.gridData = gridData;
        placeGoal(goalPosition);
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
                return Color.BLACK;  // Couleur par défaut au cas où
        }
    }

    private void placeGoal(int goalPosition) {
        if (goalPosition >= 0 && goalPosition < 256) {
            int x = goalPosition % 16;
            int y = goalPosition / 16;
            // Assurez-vous que la case d'arrivée n'est pas déjà occupée par un robot
            if ((gridData[y * 16 + x] & ROBOT) == 0) {
                gridData[y * 16 + x] |= GOAL;
            }
        }
    }

    private void drawRobot(Canvas canvas, int x, int y, int robotNumber) {
        float centerX = (x + 0.5f) * cellSize;
        float centerY = (y + 0.5f) * cellSize;
        float radius = 0.4f * cellSize;

        paint.setColor(getRobotColor(robotNumber));
        canvas.drawCircle(centerX, centerY, radius, paint);
    }

    private void initializeRobots(int[] initialRobotPositions) {
        if (initialRobotPositions.length > 0) {
            // Réinitialiser les positions précédentes des robots
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 16; j++) {
                    gridData[i * 16 + j] &= ~ROBOT;
                }
            }

            // Placer les robots aux positions initiales spécifiées
            robots = new Robot[initialRobotPositions.length];
            for (int i = 0; i < initialRobotPositions.length; i++) {
                int x = initialRobotPositions[i] % 16;
                int y = initialRobotPositions[i] / 16;
                int robotNumber = i;  // Numérotation des robots à partir de 0
                int robotColor = getRobotColor(robotNumber);
                robots[i] = new Robot(x, y, robotNumber, robotColor);
                gridData[y * 16 + x] |= ROBOT;
            }

            // Mettre à jour l'affichage après la réinitialisation des positions des robots
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

        // Dessiner les robots
        if (robots != null) {
            for (Robot robot : robots) {
                drawRobot(canvas, robot.getX(), robot.getY(), robot.getNumber());
            }
        }
    }

    public void startCorrection(int[] correctionGrid) {
        if (correctionIndex < correctionGrid.length) {
            int correctionValue = correctionGrid[correctionIndex];
            int robotNumber = (correctionValue & 0x70) >> 4;
            int direction = correctionValue & 0x0F;

            moveRobot(robotNumber, direction);
            correctionIndex++;

            // Répéter le mouvement après un délai de 500 millisecondes (modifiable)
            correctionHandler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    startCorrection(correctionGrid);
                }
            }, 500);
        }
    }

    private void updateRobotPosition(int oldX, int oldY, int newX, int newY, int robotNumber) {
        gridData[oldY * 16 + oldX] &= ~ROBOT; // Effacer l'ancienne position du robot
        gridData[newY * 16 + newX] |= ROBOT;  // Mettre à jour la nouvelle position du robot

        // Mettez à jour la position du robot dans votre tableau de robots (si vous en avez un)
        if (robots != null && robotNumber >= 0 && robotNumber < robots.length) {
            robots[robotNumber].setX(newX);
            robots[robotNumber].setY(newY);
        }
    }

    private void moveRobot(int robotNumber, int direction) {
        Robot currentRobot = findRobotByNumber(robotNumber);

        if (currentRobot == null) {
            // Le robot n'a pas été trouvé, traitement d'erreur
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

    private void drawCell(Canvas canvas, int x, int y, int value) {
        float centerX = (x + 0.5f) * cellSize;
        float centerY = (y + 0.5f) * cellSize;
        float radius = 0.4f * cellSize;

        // Effacer l'ancienne position du robot
        paint.setColor(Color.WHITE); // Cellule vide
        canvas.drawRect(x * cellSize, y * cellSize, (x + 1) * cellSize, (y + 1) * cellSize, paint);

        if ((value & GOAL) == GOAL) {
            paint.setColor(Color.GRAY);
            canvas.drawCircle(centerX, centerY, radius, paint);
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
