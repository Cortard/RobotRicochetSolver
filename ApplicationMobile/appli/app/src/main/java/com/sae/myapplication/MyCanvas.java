package com.sae.myapplication;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.View;

import android.os.Handler;

public class MyCanvas extends View {

    private int[] gridData;
    private Paint paint;
    private int cellSize;

    // Variables pour la correction
    private int correctionIndex = 0;

    private Handler handler;
    private static final int MOVE_DELAY = 500; // Délai entre chaque déplacement du robot (en millisecondes)


    private static final int NORTH = 0x01; // 0b00000001
    private static final int EAST = 0x02;  // 0b00000010
    private static final int SOUTH = 0x04; // 0b00000100
    private static final int WEST = 0x08;  // 0b00001000
    private static final int ROBOT = 0x10; // 0b00010000


    public MyCanvas(Context context, AttributeSet attrs) {
        super(context, attrs);
        paint = new Paint();
        paint.setStyle(Paint.Style.FILL);
        paint.setColor(Color.BLACK);
        handler = new Handler();
    }

    public void setGridData(int[] gridData) {
        this.gridData = gridData;
        invalidate();
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

    }

    public void moveRobot(final int direction) {
        final int currentRobotPosition = findRobotPosition();
        final int currentRow = currentRobotPosition / 16;
        final int currentCol = currentRobotPosition % 16;

        int newRow = currentRow;
        int newCol = currentCol;

        // Move until a wall is encountered
        while (isValidPosition(newRow, newCol)) {
            int newIndex = newRow * 16 + newCol;

            if (hasWall(gridData[currentRobotPosition], direction)) {
                break;
            }

            if (isValidPosition(newRow, newCol) && !hasRobot(gridData[newIndex])) {
                gridData[currentRobotPosition] &= ~ROBOT; // Clear current position
                gridData[newIndex] |= ROBOT;  // Set new position

                invalidate(); // Redraw the canvas
            } else {
                break;
            }

            // Update row and column for the next step
            switch (direction) {
                case NORTH:
                    newRow--;
                    break;
                case EAST:
                    newCol++;
                    break;
                case SOUTH:
                    newRow++;
                    break;
                case WEST:
                    newCol--;
                    break;
            }
        }
    }

    private boolean hasWall(int cellValue, int direction) {
        return (cellValue & direction) == direction;
    }

    private boolean hasRobot(int cellValue) {
        return (cellValue & ROBOT) == ROBOT;
    }


    private int findRobotPosition() {
        for (int i = 0; i < gridData.length; i++) {
            if ((gridData[i] & ROBOT) == ROBOT) {
                return i;
            }
        }
        return -1;
    }

    private boolean isValidPosition(int row, int col) {
        return row >= 0 && row < 16 && col >= 0 && col < 16;
    }

    public void correctGrid(final int[] correctionData) {
        correctionIndex = 0;

        // Execute correction movements with a delay
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                if (correctionIndex < correctionData.length) {
                    int movement = correctionData[correctionIndex];
                    int direction = (movement & 0x10) == ROBOT ? movement & 0x0F : -1;

                    if (direction != -1) {
                        moveRobot(direction);
                    }

                    correctionIndex++;
                    handler.postDelayed(this, MOVE_DELAY);
                }
            }
        }, MOVE_DELAY);
    }

    private void drawCell(Canvas canvas, int x, int y, int value) {
        float left = x * cellSize;
        float top = y * cellSize;
        float right = left + cellSize;
        float bottom = top + cellSize;

        if ((value & 0x10) == ROBOT) {
            paint.setColor(Color.RED); // Robot
        } else {
            paint.setColor(Color.WHITE); // Empty cell
        }

        canvas.drawRect(left, top, right, bottom, paint);

        // Draw borders based on the direction flags
        paint.setColor(Color.BLACK);

        if ((value & 0x01) == NORTH) {
            canvas.drawLine(left, top, right, top, paint); // NORTH
        }
        if ((value & 0x02) == EAST) {
            canvas.drawLine(right, top, right, bottom, paint); // EAST
        }
        if ((value & 0x04) == SOUTH) {
            canvas.drawLine(left, bottom, right, bottom, paint); // SOUTH
        }
        if ((value & 0x08) == WEST) {
            canvas.drawLine(left, top, left, bottom, paint); // WEST
        }
    }


    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        cellSize = w / 16;
    }
}
