//
// Created by Theodora Vraimakis on 09/02/2023.
//

#include "Window.h"
#include <iostream>
//

Window::Window() {
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

    glfwGetFramebufferSize(window, &nwidth, &nheight);
    glViewport( 0, 0, nwidth, nheight );
    lastFrame = currentFrame;
}

GLFWwindow* Window::get()
{
    return window;
}

void Window::resize() //
{
    glfwGetFramebufferSize(window, &nwidth, &nheight);
    glViewport(0, 0, (GLsizei) nwidth, (GLsizei) nheight);
}
//int Window::getWidth()
//{
//    return nwidth;
//}
//int Window::getHeight()
//{
//    return nheight;
//}
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
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
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
    currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;

    glfwPollEvents();
}

//void Window::destroy()
//{
//    glfwDestroyWindow(window);
//    glfwTerminate();
//}

float& Window::getDeltaTime()
{
    return deltaTime;
}


Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}