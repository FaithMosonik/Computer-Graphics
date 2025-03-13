// Mosonik Faith Chepkoech SCT211-0044/2022

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <cmath>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Circle properties
const int circleRadius = 4;
const int circleCenterX = 1;
const int circleCenterY = 1;
const int numSegments = 100; // Number of segments for smoothness

void drawAxes() {
    glColor3f(0.0, 0.0, 0.0); // Black color
    glLineWidth(2.0);

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

    // Draw X-axis labels
    for (int i = -10; i <= 10; i++) {
        if (i != 0) {
            std::string label = std::to_string(i);
            glRasterPos2f(i - 0.3, -0.5);
            for (char c : label) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
        }
    }

    // Draw Y-axis labels
    for (int i = -10; i <= 10; i++) {
        if (i != 0) {
            std::string label = std::to_string(i);
            glRasterPos2f(-0.7, i - 0.2);
            for (char c : label) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
        }
    }

    // Draw axis names
    glRasterPos2f(9.5, -1.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');
    glRasterPos2f(-1.0, 9.5);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');
}

void drawFilledCircle() {
    glPushMatrix();  // Save current transformation
    glTranslatef(circleCenterX, circleCenterY, 0); // Move to center
    glRotatef(-60, 0, 0, 1); // Rotate 60° clockwise
    glTranslatef(-circleCenterX, -circleCenterY, 0); // Move back

    glColor3f(1.0, 0.0, 0.0); // Red color (RGB: #FF0000)
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(circleCenterX, circleCenterY); // Center of the circle
        for (int i = 0; i <= numSegments; i++) {
            float angle = i * 2.0f * M_PI / numSegments;
            float x = circleCenterX + circleRadius * cos(angle);
            float y = circleCenterY + circleRadius * sin(angle);
            glVertex2f(x, y);
        }
    glEnd();

    glPopMatrix(); // Restore transformations
}

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawFilledCircle();
    glFlush();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Rotated and Filled Circle with Axes");

    glewInit();
    init();

    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
