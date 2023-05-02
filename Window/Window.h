//
// Created by Theodora Vraimakis on 09/02/2023.
//

#ifndef FINALYEARPROJECT_WINDOW_H
#define FINALYEARPROJECT_WINDOW_H

#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../Config/Config.h"

class Window {
public:
    Window();

    ~Window();

    GLFWwindow* get();
    int nwidth, nheight;
    void resize();
    bool m_darkMode;

//    int getWidth();
//    int getHeight();
//
//    void destroy();

    void clearScreen();
    bool isWindowClosed() const;
    void closeWindow() const;
    void processInput();
    void swapBuffers();
    void pollEvents();
    void takeScreenshot();
    void setBackground(bool darkMode);
//    float& getDeltaTime();

//    float currentFrame = 0.0f;
//    float deltaTime = 0.0f;	// time between current frame and last frame
//    float lastFrame = 0.0f;

private:

    // ImGui needs to access to non-const GLFWwindow.
    friend class UI;
    friend class ArcballCamera;
    friend class Shader;
    GLFWwindow*  window;
};


#endif //FINALYEARPROJECT_WINDOW_H
