#include <GL/glut.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Simulation.cpp"


static Simulation sim = Simulation(800, 600, 50);

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