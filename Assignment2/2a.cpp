// Mosonik Faith Chepkoech SCT211-0044/2022

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <string>

// Ellipse parameters
const float centerX = 1, centerY = 2;
const float a = 6, b = 5; // Semi-major and semi-minor axes

void drawAxes() {
    glColor3f(0.0, 0.0, 0.0); // Black color
    glLineWidth(2.0);

    glBegin(GL_LINES);
        glVertex2f(-15, 0); glVertex2f(15, 0); // X-axis
        glVertex2f(0, -15); glVertex2f(0, 15); // Y-axis
    glEnd();

    // Draw tick marks
    glLineWidth(1.0);
    glBegin(GL_LINES);
    for (int i = -15; i <= 15; i++) {
        if (i != 0) {
            glVertex2f(i, -0.3); glVertex2f(i, 0.3); // X-axis tick marks
            glVertex2f(-0.3, i); glVertex2f(0.3, i); // Y-axis tick marks
        }
    }
    glEnd();

    // Draw Labels
    glColor3f(0.0, 0.0, 0.0);
    for (int i = -15; i <= 15; i++) {
        if (i != 0) {
            std::string label = std::to_string(i);
            glRasterPos2f(i - 0.3, -0.7);
            for (char c : label) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            glRasterPos2f(-0.7, i - 0.3);
            for (char c : label) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
    }

    // Axis names
    glRasterPos2f(14, -1.0); glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');
    glRasterPos2f(-1.0, 14); glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');
}

void drawEllipse() {
    glColor3f(1.0, 0.0, 0.0); // Red color
    glPointSize(3.0); // Increase point size
    glBegin(GL_POINTS);

    float x = 0, y = b;
    float d1 = b * b - a * a * b + 0.25 * a * a;
    float dx = 2 * b * b * x, dy = 2 * a * a * y;

    while (dx < dy) {
        glVertex2f(centerX + x, centerY + y);
        glVertex2f(centerX - x, centerY + y);
        glVertex2f(centerX + x, centerY - y);
        glVertex2f(centerX - x, centerY - y);
        if (d1 < 0) {
            x++;
            dx += 2 * b * b;
            d1 += dx + b * b;
        } else {
            x++; y--;
            dx += 2 * b * b;
            dy -= 2 * a * a;
            d1 += dx - dy + b * b;
        }
    }

    float d2 = (b * b) * ((x + 0.5) * (x + 0.5)) + (a * a) * ((y - 1) * (y - 1)) - (a * a * b * b);
    while (y >= 0) {
        glVertex2f(centerX + x, centerY + y);
        glVertex2f(centerX - x, centerY + y);
        glVertex2f(centerX + x, centerY - y);
        glVertex2f(centerX - x, centerY - y);
        if (d2 > 0) {
            y--;
            dy -= 2 * a * a;
            d2 += a * a - dy;
        } else {
            y--; x++;
            dx += 2 * b * b;
            dy -= 2 * a * a;
            d2 += dx - dy + a * a;
        }
    }
    glEnd();
}

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawEllipse();
    glFlush();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-15, 15, -15, 15);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ellipse using Midpoint Algorithm");

    glewInit();
    init();

    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
