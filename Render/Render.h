//
// Created by Theodora Vraimakis on 10/02/2023.
//

#ifndef FINALYEARPROJECT_RENDER_H
#define FINALYEARPROJECT_RENDER_H

#include <vector>
#include <memory>
#include "../Window/Window.h"
#include "../Camera/ArcballCamera.h"
#include "../Config.h"
#include "../Shader/Shader.h"

class Render {
public:
    void run();
private:
    void mainLoop();
//    static void mousePositionCallback(GLFWwindow* window, double xpos, double ypos);
//    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void scrollCallback(
            GLFWwindow* window,
            double xoffset,
            double yoffset
    );
    void handleInput();
    void configureCallbacks();
    void destroy();
    std::shared_ptr<Window>             m_window;
    std::shared_ptr<ArcballCamera>      m_camera;
    bool m_isMouseInMotion;
};



#endif //FINALYEARPROJECT_RENDER_H
