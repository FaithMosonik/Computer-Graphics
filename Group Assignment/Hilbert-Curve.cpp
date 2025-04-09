#include <iostream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/glut.h>

// Structure to represent 2D points
struct Point {
    float x, y;
};

// Global variables
std::vector<Point> hilbertCurvePoints;

// Recursive Hilbert curve generator
void hilbert_curve(int n, float x, float y, float xi, float xj, float yi, float yj) {
    if (n <= 0) {
        float px = x + (xi + yi) / 2;
        float py = y + (xj + yj) / 2;
        hilbertCurvePoints.push_back({px, py});
    } else {
        hilbert_curve(n - 1, x, y, yi / 2, yj / 2, xi / 2, xj / 2);
        hilbert_curve(n - 1, x + xi / 2, y + xj / 2, xi / 2, xj / 2, yi / 2, yj / 2);
        hilbert_curve(n - 1, x + xi / 2 + yi / 2, y + xj / 2 + yj / 2, xi / 2, xj / 2, yi / 2, yj / 2);
        hilbert_curve(n - 1, x + xi / 2 + yi, y + xj / 2 + yj, -yi / 2, -yj / 2, -xi / 2, -xj / 2);
    }
}

// Render bitmap text
void renderText(float x, float y, const char* text, void* font = GLUT_BITMAP_HELVETICA_12) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(font, *text++);
    }
}


void drawAxesAndTicks() {
    float spacing = 0.2f;

    
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xAAAA);
    glColor3f(0.3f, 0.3f, 0.3f);
    for (float i = -1.0f; i <= 1.001f; i += spacing) {
        glBegin(GL_LINES); glVertex2f(i, -1.0f); glVertex2f(i, 1.0f); glEnd();
        glBegin(GL_LINES); glVertex2f(-1.0f, i); glVertex2f(1.0f, i); glEnd();
    }
    glDisable(GL_LINE_STIPPLE);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
    glVertex2f(0.0f, -1.0f); glVertex2f(0.0f, 1.0f);
    glEnd();

    for (float i = -1.0f; i <= 1.001f; i += spacing) {
        
        glBegin(GL_LINES);
        glVertex2f(i, -1.02f); glVertex2f(i, -0.98f);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(-1.02f, i); glVertex2f(-0.98f, i);
        glEnd();

        if (i != 0.0f) {
            char label[10];
            snprintf(label, sizeof(label), "%.1f", i);
            renderText(i - 0.03f, -1.15f, label);   // X-axis label at bottom
            renderText(-1.13f, i - 0.01f, label);   // Y-axis label at left
        }
    }

    // Axis labels
    renderText(1.05f, 0.03f, "X-axis");
    renderText(-0.06f, 1.05f, "Y-axis");

    // Title
    renderText(-0.2f, 1.15f, "Hilbert Curve with order 5", GLUT_BITMAP_HELVETICA_18);
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxesAndTicks();

    // Draw Hilbert curve
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glBegin(GL_LINE_STRIP);
    for (const auto& pt : hilbertCurvePoints) {
        glVertex2f(pt.x, pt.y);
    }
    glEnd();

    glutSwapBuffers();
}

// Initialization
void init() {
    glewInit();
    hilbertCurvePoints.clear();
    glLineWidth(2.0f);
    hilbert_curve(5, -0.9f, -0.9f, 1.8f, 0.0f, 0.0f, 1.8f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Hilbert Curve with order 5");
    init();
    glutDisplayFunc(display);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.2f, 1.2f, -1.2f, 1.2f);
    glutMainLoop();
    return 0;
}
