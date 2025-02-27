#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Function to plot a pixel
void plotPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Bresenham’s Line Algorithm
void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        plotPixel(x1, y1);
        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) { 
            err -= dy; 
            x1 += sx; 
        }
        if (e2 < dx) { 
            err += dx; 
            y1 += sy; 
        }
    }

    glFlush();
}

// OpenGL display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0, 1.0, 1.0); // Set color to white

    // Draw Bresenham's Line (1,5) to (2,8)
    drawLineBresenham(1, 5, 2, 8);

    glFlush();
}

// OpenGL initialization 
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

    GLFWwindow* window = glfwCreateWindow(500, 500, "Bresenham's Line Algorithm", NULL, NULL);
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
