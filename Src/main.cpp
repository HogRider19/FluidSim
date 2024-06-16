#include <GL/glut.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Simulation.cpp"


static Simulation sim = Simulation(800, 600, 1000);

void drawFPS() 
{
    static int frameCount = 0;
    static int currentTime = 0;
    static int previousTime = 0;

    frameCount++;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    int elapsedTime = currentTime - previousTime;

    if (elapsedTime > 1000) 
    {
        float fps = frameCount / (elapsedTime / 1000.0f);
        std::stringstream ss;
        ss << "FluidSim (FPS: " << fps << ")";
        std::string title = ss.str();
        glutSetWindowTitle(title.c_str());
        previousTime = currentTime;
        frameCount = 0;
    }
}

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT);
    sim.Display();
    glFlush();
    drawFPS();
}

void reshape(int width, int height) 
{
    sim.SetDimention(width, height);
    glViewport(0, 0, width, height);
}

void timer(int value) 
{
    glutPostRedisplay(); 
    glutTimerFunc(1000 / 200, timer, 0);
}

const char *vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    layout (location = 1) in vec2 aTexCoord;

    out vec2 TexCoord;

    void main() {
        gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
        TexCoord = aTexCoord;
    }
)";

const char *fragmentShaderSource = R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;

    uniform vec2 pointPositions[100];
    uniform int numPoints;

    vec3 getColor(vec2 fragPos) {
        float maxDistance = 0.0;
        vec3 finalColor = vec3(0.0);

        for (int i = 0; i < numPoints; ++i) {
            vec2 pointPos = pointPositions[i];
            float distance = length(pointPos - fragPos);
            maxDistance = max(maxDistance, distance);
        }

        for (int i = 0; i < numPoints; ++i) {
            vec2 pointPos = pointPositions[i];
            float distance = length(pointPos - fragPos);
            float intensity = 1.0 - (distance / maxDistance); // Интенсивность от 0 до 1
            finalColor += intensity * vec3(1.0, 0.0, 0.0); // Красный цвет, можно изменить
        }

        return finalColor;
    }

    void main() {
        vec2 fragPos = TexCoord;
        FragColor = vec4(getColor(fragPos), 1.0);
    }
)";

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutCreateWindow("FluidSim");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000 / 200, timer, 0);
    glutMainLoop();

    return 0;
}