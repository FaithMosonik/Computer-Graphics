#include <GL/glut.h>
#include <stdio.h>
#include <string>
#include <math.h>

#define DEG_TO_RAD 0.0174533 // Conversion factor from degrees to radians

// Original square vertices
GLfloat squareVertices[4][2] = {
    {0, 4}, {3, 4}, {4, 0}, {0, 0}
};

// Translation distances
GLfloat Tx = 2.0f, Ty = 2.0f;
// Rotation angle in degrees
GLfloat theta = 55.0f;

// Function to draw axes
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

void drawSquare(GLfloat vertices[4][2], GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    // Draw original square
    drawSquare(squareVertices, 0.0, 0.0, 1.0); // Blue color
    
    // Compute translated square
    GLfloat translatedVertices[4][2];
    for (int i = 0; i < 4; i++) {
        translatedVertices[i][0] = squareVertices[i][0] + Tx;
        translatedVertices[i][1] = squareVertices[i][1] + Ty;
    }
    
    // Draw translated square
    drawSquare(translatedVertices, 1.0, 0.0, 0.0); // Red color
    
    // Compute rotated square (around origin after translation)
    GLfloat rotatedVertices[4][2];
    GLfloat rad = theta * DEG_TO_RAD;
    for (int i = 0; i < 4; i++) {
        rotatedVertices[i][0] = translatedVertices[i][0] * cos(rad) - translatedVertices[i][1] * sin(rad);
        rotatedVertices[i][1] = translatedVertices[i][0] * sin(rad) + translatedVertices[i][1] * cos(rad);
    }
    
    // Draw rotated square
    drawSquare(rotatedVertices, 0.0, 1.0, 0.0); // Green color
    
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Square Rotation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}