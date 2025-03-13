// Mosonik Faith Chepkoech SCT211-0044/2022

/*
Midpoint Parabola Calculation (x = y^2) using the Midpoint Method

1. Midpoint Decision Parameter:
   P_k = 1 - 2y_k
   - If P_k < 0, next point is (x, y+1).
   - If P_k >= 0, next point is (x+1, y+1).
   - Symmetry is used: For each (x, y), plot (-x, y).

2. Points Computed for -10 <= y <= 10:
   (-10, 100), (-9, 81), (-8, 64), (-7, 49), (-6, 36), (-5, 25), (-4, 16), (-3, 9), (-2, 4), (-1, 1),
   (0, 0), (1, 1), (2, 4), (3, 9), (4, 16), (5, 25), (6, 36), (7, 49), (8, 64), (9, 81), (10, 100)

   Only points within the window (-11 <= x, y <= 11) are plotted:
   (0,0), (1,1), (4,2), (9,3), (-1,1), (-4,2), (-9,3)

*/

#include "GL/glut.h"
#include <stdio.h>
#include <string>
#include <math.h>

// Function to draw axes with labeled ticks
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
            glRasterPos2f(i - 0.3, -0.5); // Adjusted for visibility
            for (char c : label) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
        }
    }

    // Y-axis labels
    for (int i = -10; i <= 10; i++) {
        if (i != 0) {
            std::string label = std::to_string(i);
            glRasterPos2f(-0.9, i - 0.2); // Adjusted for visibility
            for (char c : label) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
        }
    }

    // Draw axis labels
    glRasterPos2f(9.0, -1.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');
    
    glRasterPos2f(-1.0, 9.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');
}

void drawParabola() {
    glColor3f(1.0, 0.0, 0.0); // Red color for parabola
    glPointSize(3.0);
    glBegin(GL_POINTS);

    for (int y = -10; y <= 10; y++) {
        int x = y * y; // x = y^2
        glVertex2f(x, y);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawParabola();
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-11, 11, -11, 11); // Adjusted for better visibility
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Midpoint Parabola");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
