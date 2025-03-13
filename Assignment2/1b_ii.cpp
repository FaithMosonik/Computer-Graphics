// Mosonik Faith Chepkoech SCT211-0044/2022

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <cmath>
#include <string>

// Triangle vertices
const float triangleVertices[3][2] = {
    {1, 6}, {2, 0}, {-4, 9}
};

// Function to calculate the circumcenter and radius of the circumcircle
void computeCircumcircle(float &cx, float &cy, float &radius) {
    float x1 = triangleVertices[0][0], y1 = triangleVertices[0][1];
    float x2 = triangleVertices[1][0], y2 = triangleVertices[1][1];
    float x3 = triangleVertices[2][0], y3 = triangleVertices[2][1];

    float d = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
    cx = ((x1 * x1 + y1 * y1) * (y2 - y3) +
          (x2 * x2 + y2 * y2) * (y3 - y1) +
          (x3 * x3 + y3 * y3) * (y1 - y2)) / d;
    cy = ((x1 * x1 + y1 * y1) * (x3 - x2) +
          (x2 * x2 + y2 * y2) * (x1 - x3) +
          (x3 * x3 + y3 * y3) * (x2 - x1)) / d;
    radius = sqrt((cx - x1) * (cx - x1) + (cy - y1) * (cy - y1));
}

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
            glVertex2f(i, -0.2);
            glVertex2f(i, 0.2);
            glVertex2f(-0.2, i);
            glVertex2f(0.2, i);
        }
    }
    glEnd();

    // Draw Labels
    glColor3f(0.0, 0.0, 0.0);
    for (int i = -15; i <= 15; i++) {
        if (i != 0) {
            std::string label = std::to_string(i);
            glRasterPos2f(i - 0.3, -0.5);
            for (char c : label) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
            glRasterPos2f(-0.7, i - 0.2);
            for (char c : label) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
        }
    }

    glRasterPos2f(14.5, -1.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');
    glRasterPos2f(-1.0, 14.5);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');
}

void drawTriangle() {
    glColor3f(0.0, 0.0, 1.0);
    glLineWidth(2.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(triangleVertices[0][0], triangleVertices[0][1]);
        glVertex2f(triangleVertices[1][0], triangleVertices[1][1]);
        glVertex2f(triangleVertices[2][0], triangleVertices[2][1]);
    glEnd();
}

void drawCircumscribedCircle() {
    float cx, cy, radius;
    computeCircumcircle(cx, cy, radius);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(cx + radius * cos(theta), cy + radius * sin(theta));
    }
    glEnd();
}

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawTriangle();
    drawCircumscribedCircle();
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
    glutCreateWindow("Triangle with Circumscribed Circle");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
