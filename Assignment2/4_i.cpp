// Mosonik Faith Chepoekch SCT211-0044/2022

#include <GL/glut.h>
#include <stdio.h>

// Polygon vertices
GLfloat vertices[][2] = {
    {8, 4}, {2, 4}, {0, 8}, {3, 12}, {7, 12}, {10, 8}
};

// Function to draw coordinate axes
void drawAxes() {
    glColor3f(0, 0, 0); // Black color
    glBegin(GL_LINES);
        glVertex2f(-15, 0);
        glVertex2f(15, 0);
        glVertex2f(0, -15);
        glVertex2f(0, 15);
    glEnd();

    // Label axes
    for (int i = -14; i <= 14; i++) {
        glRasterPos2f(i, -0.5);
        char label[3];
        sprintf(label, "%d", i);
        for (char *c = label; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        }
    }
    for (int i = -14; i <= 14; i++) {
        glRasterPos2f(-0.5, i);
        char label[3];
        sprintf(label, "%d", i);
        for (char *c = label; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        }
    }
}

// Function to draw and fill the polygon in red
void drawPolygon() {
    glColor3f(1.0, 0.0, 0.0); // Red color
    glBegin(GL_POLYGON);
    for (int i = 0; i < 6; i++) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawPolygon();
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-15, 15, -15, 15);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Filled Polygon");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
