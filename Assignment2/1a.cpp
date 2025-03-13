// Mosonik Faith Chepkoech SCT211-0044/2022

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <cmath>

// Circle parameters
const int circleRadius = 4;
const int circleCenterX = 1;
const int circleCenterY = 1;

// Function to plot 8 symmetric points
void plotCirclePoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
    glEnd();
}

// Bresenham's Circle Drawing Algorithm
void drawCircle() {
    int x = 0;
    int y = circleRadius;
    int d = 3 - (2 * circleRadius); // Decision parameter

    glPointSize(3.0);

    while (x <= y) {
        plotCirclePoints(circleCenterX, circleCenterY, x, y);
        x++;

        if (d < 0) {
            d = d + (4 * x) + 6;
        } else {
            y--;
            d = d + 4 * (x - y) + 10;
        }
    }
}

// Function to draw calibrated X and Y axes
void drawAxes() {
    glColor3f(0.0, 0.0, 0.0); // Black color for axes
    glLineWidth(2.0);

    // Draw X and Y axes
    glBegin(GL_LINES);
        glVertex2f(-10, 0); glVertex2f(10, 0); // X-axis
        glVertex2f(0, -10); glVertex2f(0, 10); // Y-axis
    glEnd();

    // Draw tick marks
    glLineWidth(1.0);
    glBegin(GL_LINES);
    for (int i = -10; i <= 10; i++) {
        if (i != 0) { // Skip origin

            // X-axis tick marks
            glVertex2f(i, -0.2);
            glVertex2f(i, 0.2);

            // Y-axis tick marks
            glVertex2f(-0.2, i);
            glVertex2f(0.2, i);
        }
    }
    glEnd();

    // Draw Labels
    glColor3f(0.0, 0.0, 0.0); // Black color for labels

    // X-axis labels
    for (int i = -10; i <= 10; i++) {
        if (i != 0) {
            std::string label = std::to_string(i);
            glRasterPos2f(i - 0.3, -0.6);
            for (char c : label) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
        }
    }

    // Y-axis labels
    for (int i = -10; i <= 10; i++) {
        if (i != 0) {
            std::string label = std::to_string(i);
            glRasterPos2f(-0.8, i - 0.2);
            for (char c : label) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
        }
    }

    // Draw axis labels
    glRasterPos2f(9.5, -1.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');
    
    glRasterPos2f(-1.0, 9.5);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');
}

// OpenGL display function
void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();  // Draw the coordinate system
    glColor3f(1.0, 0.0, 0.0); // Red color for the circle
    drawCircle(); // Draw the circle

    glFlush();
}

// Initialize OpenGL settings
void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10); // Set coordinate system
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bresenham Circle Drawing");

    glewInit();
    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
