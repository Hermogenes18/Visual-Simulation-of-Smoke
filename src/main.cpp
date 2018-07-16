#include <memory>
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
    if (glfwInit() == GLFW_FALSE)
    {
        fprintf(stderr, "Initialization failed!\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE,
                                          NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Window creation failed!");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "GLEW initialization failed!\n");
    }

    // set background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glLineWidth(1.2f);

    glEnable(GL_TEXTURE_3D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    double time = 0.0;
    int step = 1;
    std::shared_ptr<MACGrid> grids = std::make_shared<MACGrid>();
    std::unique_ptr<Simulator> simulator = std::make_unique<Simulator>(grids, time);
    std::unique_ptr<Scene> scene = std::make_unique<Scene>(grids);

    printf("\n*** START SIMULATION ***\n");

    // scene->writeData();

    while (glfwWindowShouldClose(window) == GL_FALSE && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        printf("\n=== STEP %d ===\n", step);
        time += DT;
        simulator->update();

        scene->update();
        // scene->writeData();
        scene->render();
        ++step;

        if (time >= FINISH_TIME)
        {
            break;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    printf("\n*** END ***\n");

    return 0;
}