// Mosonik Faith Chepkoech SCT211-0044/2022

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <cmath>
#include <stack>
#include <utility>
#include <string>

// Window dimensions
const int winWidth = 600, winHeight = 600;

// Ellipse parameters
const float centerX = 1, centerY = 2;
const float a = 6, b = 5; // Semi-major and minor axes

// Convert world coordinates to pixel coordinates
int worldToPixelX(float x) { return (int)((x + 15) * (winWidth / 30.0)); }
int worldToPixelY(float y) { return (int)((y + 15) * (winHeight / 30.0)); }

// Convert pixel coordinates back to world coordinates
float pixelToWorldX(int px) { return px * 30.0 / winWidth - 15; }
float pixelToWorldY(int py) { return py * 30.0 / winHeight - 15; }

// Compare colors with a tolerance
bool isSameColor(float* color1, float* color2) {
    const float eps = 0.1;
    return (fabs(color1[0] - color2[0]) < eps &&
            fabs(color1[1] - color2[1]) < eps &&
            fabs(color1[2] - color2[2]) < eps);
}

// Flood Fill Algorithm
void floodFill(int px, int py, float* fillColor, float* borderColor) {
    std::stack<std::pair<int, int>> pixelStack;
    pixelStack.push({px, py});

    while (!pixelStack.empty()) {
        auto [x, y] = pixelStack.top();
        pixelStack.pop();

        float pixelColor[3];
        glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixelColor);

        if (!isSameColor(pixelColor, borderColor) && !isSameColor(pixelColor, fillColor)) {
            glColor3fv(fillColor);
            glBegin(GL_POINTS);
            glVertex2f(pixelToWorldX(x), pixelToWorldY(y));
            glEnd();
            glFlush();

            // Push adjacent pixels
            if (x > 0 && x < winWidth - 1 && y > 0 && y < winHeight - 1) {
                pixelStack.push({x + 1, y});
                pixelStack.push({x - 1, y});
                pixelStack.push({x, y + 1});
                pixelStack.push({x, y - 1});
            }
        }
    }
}

// Draw coordinate axes
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
    std::string label;
    for (int i = -15; i <= 15; i++) {
        if (i != 0) {
            label = std::to_string(i);
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

// Draw a continuous ellipse border
void drawEllipse() {
    glColor3f(1, 0, 0); // Red border
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 720; i++) {  // Increased point density for a smoother ellipse
        float angle = i * 3.14159 / 360.0; // More points for a denser shape
        float x = centerX + a * cos(angle);
        float y = centerY + b * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}


// Display function
void display() {
    glClearColor(1, 1, 1, 1); // White background
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawEllipse();

    // Define fill and border colors
    float fillColor[] = {1.0, 0.65, 0.0};   // Orange
    float borderColor[] = {1.0, 0.0, 0.0};  // Red border

    // Start flood fill inside the ellipse
    floodFill(worldToPixelX(centerX), worldToPixelY(centerY), fillColor, borderColor);

    glFlush();
}

// Initialization
void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-15, 15, -15, 15);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Ellipse with Midpoint Algorithm and Flood-Fill");

    glewInit();
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
