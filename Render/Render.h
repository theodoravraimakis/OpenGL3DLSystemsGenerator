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
#include "../UI/UI.h"
#include "../Cylinder/Cylinder.h"

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
    static void r(GLFWwindow* aWindow, int aKey, int, int aAction, int);
    void handleInput();
    void configureCallbacks();
    void destroy();

    std::shared_ptr<Window>             m_window;
    std::unique_ptr<UI>                 m_UI;
    std::shared_ptr<ArcballCamera>      m_camera;
    std::shared_ptr<Cylinder>           m_cylinder;
    std::shared_ptr<Shader>             m_shader;
    std::shared_ptr<Light>              m_light;

    bool m_isMouseInMotion;

};



#endif //FINALYEARPROJECT_RENDER_H
