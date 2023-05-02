//
// Created by Theodora Vraimakis on 09/02/2023.
//

#include "Window.h"
#include <iostream>

Window::Window() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    m_darkMode = true;

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
void Window::clearScreen()
{
    if(m_darkMode)
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    else
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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


#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <../stb-src/stb_image_write.h>

void Window::takeScreenshot() const {

    std::unique_ptr<GLubyte[]> image(new GLubyte[nwidth * nheight * sizeof(GLubyte) * 3]);
    if (!image) {
        std::cout << "Couldn't allocate memory! " << std::endl;
        return;
    }

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, nwidth, nheight, GL_RGB, GL_UNSIGNED_BYTE, image.get());

    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::system_clock::to_time_t(now);
    std::stringstream fileNameStream;
    fileNameStream << "Screenshot " << std::put_time(std::localtime(&timestamp), "%Y-%m-%d at %H.%M.%S") << ".png";
    std::string fileName = fileNameStream.str();

    stbi_flip_vertically_on_write(true);
    stbi_write_png(std::string("../screenshots/").append(fileName).c_str(), nwidth, nheight, 3, image.get(), nwidth * 3);

    std::cout << "Successfully saved screenshot in '/screenshots' directory as: \n" << fileName << std::endl;
}

void Window::setBackground(bool darkMode)
{
    if (m_darkMode != darkMode)
    {
        m_darkMode = darkMode;
    }
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}