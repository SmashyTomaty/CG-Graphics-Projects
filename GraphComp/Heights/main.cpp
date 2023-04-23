#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "Application.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static Application app;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    app.key_callback(key, scancode, action, mods);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    app.mouse_callback(xpos, ypos);
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    app.window = glfwCreateWindow(1080, 720, "Texturez", NULL, NULL);
    if (!app.window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(app.window);
    glewInit();
    app.Setup();

        glfwSetKeyCallback(app.window, key_callback);
        glfwSetCursorPosCallback(app.window, mouse_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(app.window))
    {
        glfwSetInputMode(app.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        app.Update();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        app.Draw();
        /* Swap front and back buffers */
        glfwSwapBuffers(app.window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    app.Terminate();
    glfwTerminate();
    return 0;
}