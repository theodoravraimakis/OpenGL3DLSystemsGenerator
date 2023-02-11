//
// Created by Theodora Vraimakis on 09/02/2023.
//

#include "Window.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

Window::Window(
        int width,
        int height,
        const char* title
) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(
            Config::SCR_WIDTH,
            Config::SCR_HEIGHT,
            Config::TITLE,
            nullptr,
            nullptr
    );

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);
}

GLFWwindow* Window::get()
{
    return window;
}

void Window::resize() //
{
    {
        glfwGetFramebufferSize(window, &nwidth, &nheight);

        fbwidth = float(nwidth);
        fbheight = float(nheight);

        if (0 == nwidth || 0 == nheight)
        {
            // Window minimized? Pause until it is unminimized.
            // This is a bit of a hack.
            do
            {
                glfwWaitEvents();
                glfwGetFramebufferSize(window, &nwidth, &nheight);
            } while (0 == nwidth || 0 == nheight);
        }

        glViewport(0, 0, (GLsizei)fbwidth, (GLsizei)fbheight);
    }

}
int Window::getWidth()
{
    return nwidth;
}
int Window::getHeight()
{
    return nheight;
}
void Window::clearScreen()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::isWindowClosed() const
{
    return glfwWindowShouldClose(window);
}

void Window::closeWindow() const
{
    glfwSetWindowShouldClose(window, true);
}

void Window::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        closeWindow();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::destroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

Window::~Window() = default;