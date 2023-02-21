//
// Created by Theodora Vraimakis on 10/02/2023.
//

#ifndef FINALYEARPROJECT_RENDER_H
#define FINALYEARPROJECT_RENDER_H

#include <vector>
#include <memory>
#include "../Window/Window.h"
#include "../Camera/ArcballCamera.h"
#include "../Config/Config.h"
#include "../Shader/Shader.h"
#include "../UI/UI.h"
#include "../Shapes/Cylinder.h"
#include "../Turtle/Turtle.h"

class Render {
public:
    void run();
private:
    void mainLoop();
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void reloadShader(GLFWwindow* aWindow, int aKey, int, int aAction, int);
    void handleInput();
    void configureCallbacks();
    void destroy();

    std::shared_ptr<Window>                         m_window;
    std::unique_ptr<UI>                             m_UI;
    std::shared_ptr<ArcballCamera>                  m_camera;
    std::shared_ptr<Cylinder>                       m_cylinder;
    std::shared_ptr<Cone>                           m_cone;
    std::shared_ptr<Shader>                         m_shader;
    std::shared_ptr<Light>                          m_light;
    std::shared_ptr<Turtle>                         m_turtle;
    std::shared_ptr<coordinateAxesArrows>           m_coordsAxis;
    std::shared_ptr<Shape>                          m_shape;

    bool m_isMouseInMotion;
    float ratio;
//    inline static float fov = 50.0f;
    inline static float fov;
    inline static glm::vec3 position;


};



#endif //FINALYEARPROJECT_RENDER_H
