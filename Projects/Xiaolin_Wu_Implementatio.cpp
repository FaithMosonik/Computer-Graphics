#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    layout (location = 1) in float brightness;
    out float Brightness;
    void main() {
        gl_Position = vec4(aPos, 0.0, 1.0);
        Brightness = brightness;
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    in float Brightness;
    out vec4 FragColor;
    void main() {
        FragColor = vec4(vec3(0.0) * Brightness, 1.0);
    }
)";

std::vector<float> linePoints;

void plot(float x, float y, float brightness) {
    // Scale up to a larger coordinate system (normalized -1 to 1)
    float scaleFactor = 40.0f;  // Scale to fit viewport better
    float ndcX = (x / scaleFactor);
    float ndcY = (y / scaleFactor);

    linePoints.push_back(ndcX);
    linePoints.push_back(ndcY);
    linePoints.push_back(brightness);
}

void XiaolinWuLine(float x1, float y1, float x2, float y2) {
    bool steep = fabs(y2 - y1) > fabs(x2 - x1);
    if (steep) { std::swap(x1, y1); std::swap(x2, y2); }
    if (x1 > x2) { std::swap(x1, x2); std::swap(y1, y2); }

    float dx = x2 - x1;
    float dy = y2 - y1;
    float gradient = (dx == 0) ? 1.0f : dy / dx;

    float xEnd = round(x1);
    float yEnd = y1 + gradient * (xEnd - x1);
    float xGap = 1.0f - fmod(x1 + 0.5, 1.0);
    int xPixel1 = (int)xEnd;
    int yPixel1 = (int)yEnd;

    plot(xPixel1, yPixel1, (1 - (yEnd - yPixel1)) * xGap);
    plot(xPixel1, yPixel1 + 1, (yEnd - yPixel1) * xGap);

    float intery = yEnd + gradient;

    for (int x = xPixel1 + 1; x <= (int)x2; x++) {
        int y = (int)intery;
        plot(x, y, 1 - (intery - y));
        plot(x, y + 1, intery - y);
        intery += gradient;
    }
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(500, 500, "Xiaolin Wu's Line Algorithm", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glewInit();

    XiaolinWuLine(1, 1, 3, 5); // Drawing the line

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, linePoints.size() * sizeof(float), linePoints.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(5.0f);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, linePoints.size() / 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
