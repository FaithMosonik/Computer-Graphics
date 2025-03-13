#include <GL/glut.h>
#include <string>

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

void drawSquare() {
    glColor3f(0.0, 0.0, 1.0); // Blue color for square
    glBegin(GL_QUADS);
        glVertex2f(0, 4);
        glVertex2f(3, 4);
        glVertex2f(4, 0);
        glVertex2f(0, 0);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawSquare();
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
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL Square");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}