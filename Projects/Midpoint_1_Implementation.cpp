#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

// Function to plot a pixel
void plotPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Midpoint Line Algorithm
void drawLineMidpoint(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    bool steep = dy > dx;

    if (steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        std::swap(dx, dy);
        std::swap(sx, sy);
    }

    int d = (2 * dy) - dx;
    int y = y1;

    for (int x = x1; x != x2; x += sx) {
        if (steep) {
            plotPixel(y, x);
        } else {
            plotPixel(x, y);
        }
        if (d > 0) {
            y += sy;
            d += (2 * dy) - (2 * dx);
        } else {
            d += 2 * dy;
        }
    }

    glFlush();
}

// OpenGL display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0, 1.0, 1.0); // White color

    // Draw line using Midpoint Algorithm
    drawLineMidpoint(-3, 4, 5, -2);

    glFlush();
}

// OpenGL initialization (No GLU)
void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -1, 1); // No `gluOrtho2D`
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(500, 500, "Midpoint Line Algorithm", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    initOpenGL();

    while (!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
