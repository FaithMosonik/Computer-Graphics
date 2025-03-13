// Mosonik Faith Chepkoech SCT211-0044/2022

#include <GL/glut.h>
#include <stdio.h>
#include <string>

// Original polygon vertices
GLfloat polygonVertices[6][2] = {
    {8, 4}, {2, 4}, {0, 8}, {3, 12}, {7, 12}, {10, 8}
};

// Scaling factor
GLfloat scaleFactor = 2.0f;

// Function to compute centroid
void computeCentroid(GLfloat vertices[6][2], GLfloat* cx, GLfloat* cy) {
    *cx = 0;
    *cy = 0;
    for (int i = 0; i < 6; i++) {
        *cx += vertices[i][0];
        *cy += vertices[i][1];
    }
    *cx /= 6;
    *cy /= 6;
}

void drawAxes() {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    // X-axis
    glVertex2f(-30, 0);
    glVertex2f(30, 0);
    // Y-axis
    glVertex2f(0, -30);
    glVertex2f(0, 30);
    glEnd();

    // Draw tick marks and labels
    for (int i = -30; i <= 30; i += 1) {
        glBegin(GL_LINES);
        glVertex2f(i, -0.3);
        glVertex2f(i, 0.3);
        glVertex2f(-0.3, i);
        glVertex2f(0.3, i);
        glEnd();
    }

    // Draw Labels
    glColor3f(0.0, 0.0, 0.0);
    for (int i = -30; i <= 30; i++) {
        if (i != 0) {
            std::string label = std::to_string(i);
            glRasterPos2f(i - 0.3, -0.7);
            for (char c : label) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            glRasterPos2f(-0.7, i - 0.3);
            for (char c : label) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
    }

    // Axis names
    glRasterPos2f(28, -1.0); glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');
    glRasterPos2f(-1.0, 28); glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');
}

void drawPolygon(GLfloat vertices[6][2], GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 6; i++) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

bool isInsidePolygon(GLfloat x, GLfloat y, GLfloat vertices[6][2]) {
    int i, j, n = 6;
    bool inside = false;
    for (i = 0, j = n - 1; i < n; j = i++) {
        if (((vertices[i][1] > y) != (vertices[j][1] > y)) &&
            (x < (vertices[j][0] - vertices[i][0]) * (y - vertices[i][1]) / 
                 (vertices[j][1] - vertices[i][1]) + vertices[i][0])) {
            inside = !inside;
        }
    }
    return inside;
}

void fillPolygonWithAsterisks(GLfloat vertices[6][2]) {
    glColor3f(0.0, 0.5, 0.0); // Green color for asterisks
    
    GLfloat minX = vertices[0][0], maxX = vertices[0][0];
    GLfloat minY = vertices[0][1], maxY = vertices[0][1];
    
    for (int i = 1; i < 6; i++) {
        if (vertices[i][0] < minX) minX = vertices[i][0];
        if (vertices[i][0] > maxX) maxX = vertices[i][0];
        if (vertices[i][1] < minY) minY = vertices[i][1];
        if (vertices[i][1] > maxY) maxY = vertices[i][1];
    }
    
    for (GLfloat x = minX; x <= maxX; x += 0.5) {
        for (GLfloat y = minY; y <= maxY; y += 0.5) {
            if (isInsidePolygon(x, y, vertices)) {
                glRasterPos2f(x, y);
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '*');
            }
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    // Compute centroid
    GLfloat cx, cy;
    computeCentroid(polygonVertices, &cx, &cy);
    
    // Scale around origin (centroid)
    GLfloat scaledVertices[6][2];
    for (int i = 0; i < 6; i++) {
        scaledVertices[i][0] = polygonVertices[i][0] * scaleFactor;
        scaledVertices[i][1] = polygonVertices[i][1] * scaleFactor;
    }
    
    // Draw scaled polygon 
    drawPolygon(scaledVertices, 1.0, 0.0, 0.0);
    
    // Fill interior with green asterisks
    fillPolygonWithAsterisks(scaledVertices);
    
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-30, 30, -30, 30);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Polygon Scaling with Asterisks");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}