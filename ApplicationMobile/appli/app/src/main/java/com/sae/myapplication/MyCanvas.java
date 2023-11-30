package com.sae.myapplication;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.RectF;
import android.util.AttributeSet;
import android.view.View;

public class MyCanvas extends View {
    private static final int GRID_SIZE = 16;
    private static final int CELL_SIZE = 60; // Taille de chaque cellule en pixels

    private Paint gridPaint;
    private Paint correctionPaint;

    private int[] correctionPath;

    public MyCanvas(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        gridPaint = new Paint();
        gridPaint.setColor(getResources().getColor(android.R.color.black));
        gridPaint.setStrokeWidth(2);

        correctionPaint = new Paint();
        correctionPaint.setStyle(Paint.Style.FILL);
        correctionPaint.setAlpha(150); // Set the alpha value for transparency
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        drawGrid(canvas);
        drawCorrectionPath(canvas);
    }

    private void drawGrid(Canvas canvas) {
        int width = getWidth();
        int height = getHeight();

        // Dessine les lignes verticales
        for (int i = 0; i <= GRID_SIZE; i++) {
            float x = i * CELL_SIZE;
            canvas.drawLine(x, 0, x, height, gridPaint);
        }

        // Dessine les lignes horizontales
        for (int i = 0; i <= GRID_SIZE; i++) {
            float y = i * CELL_SIZE;
            canvas.drawLine(0, y, width, y, gridPaint);
        }
    }

    private void drawCorrectionPath(Canvas canvas) {
        if (correctionPath != null) {
            int cellSize = getWidth() / GRID_SIZE;

            for (int i = 0; i < correctionPath.length; i++) {
                int row = i / GRID_SIZE;
                int col = i % GRID_SIZE;
                int correction = correctionPath[i];

                // Extract robot position and direction from correction
                int robotPosition = (correction >> 4) & 0x0F;
                int direction = correction & 0x0F;

                if (robotPosition != 0) { // Only draw if robot is present in the cell
                    RectF rect = new RectF(col * cellSize, row * cellSize,
                            (col + 1) * cellSize, (row + 1) * cellSize);

                    correctionPaint.setColor(getColorForRobot(robotPosition));
                    canvas.drawRect(rect, correctionPaint);
                }
            }
        }
    }

    private int getColorForRobot(int robotPosition) {
        // Customize this method based on your color requirements
        switch (robotPosition) {
            case 1:
                return getResources().getColor(android.R.color.holo_red_light);
            case 2:
                return getResources().getColor(android.R.color.holo_green_light);
            case 3:
                return getResources().getColor(android.R.color.holo_blue_light);
            case 4:
                return getResources().getColor(android.R.color.holo_orange_light);
            default:
                return getResources().getColor(android.R.color.transparent);
        }
    }

    public void setCorrectionPath(int[] correctionPath) {
        this.correctionPath = correctionPath;
        invalidate(); // Trigger redraw
    }
}
