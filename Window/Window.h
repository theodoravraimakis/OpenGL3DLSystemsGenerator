//
// Created by Theodora Vraimakis on 09/02/2023.
//

#ifndef FINALYEARPROJECT_WINDOW_H
#define FINALYEARPROJECT_WINDOW_H


#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../Config.h"



//const char* TITLE = "Generative Algorithms Toolkit";

class Window {
public:

//    const unsigned int SCR_WIDTH = 800;
//    const unsigned int SCR_HEIGHT = 600;
//    int width = SCR_WIDTH;
//    int height = SCR_HEIGHT;

    Window(
            int width,
            int height,
            const char* title
    );

    ~Window();

    GLFWwindow* get();
    float fbwidth, fbheight;
    int nwidth, nheight;
    void resize();
    int getWidth();
    int getHeight();

    void destroy();

    void clearScreen();
    bool isWindowClosed() const;
    void closeWindow() const;
    void processInput();
    void swapBuffers();
    void pollEvents();

private:

    // ImGui needs to access to non-const GLFWwindow.
    friend class UI;
    friend class ArcballCamera;
    GLFWwindow*  window;
};


#endif //FINALYEARPROJECT_WINDOW_H
