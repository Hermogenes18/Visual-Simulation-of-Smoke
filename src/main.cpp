#include <iostream>

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "constants.hpp"
#include "Scene.hpp"
#include "Simulator.hpp"
#include "MACGrid.hpp"

int main()
{
    if (glfwInit() == GL_FALSE)
    {
        fprintf(stderr, "Initialization failed!\n");
    }

    GLFWwindow *window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE,
                                          NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Window creation failed!");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "GLEW initialization failed!\n");
    }

    // set background color black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_3D);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    double time = 0.0;
    int step = 1;
    MACGrid *grids = new MACGrid();
    Scene *scene = new Scene(grids);
    Simulator *simulator = new Simulator(grids, time);

    std::cout << "\n*** START SIMULATION ***\n";

    // scene->writeData();

    while (glfwWindowShouldClose(window) == GL_FALSE)
    {
        // std::cout << "\n=== STEP " << step << " ===\n";
        // time += DT;
        // simulator->update();
        // scene->writeData();
        scene->update();
        scene->render();
        // ++step;

        // if (time >= FINISH_TIME)
        // {
        //     break;
        // }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << "\n*** END ***\n";

    if (simulator)
    {
        delete simulator;
    }
    if (scene)
    {
        delete scene;
    }
    if (grids)
    {
        delete grids;
    }

    return 0;
}