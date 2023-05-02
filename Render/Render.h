//
// Created by Theodora Vraimakis on 10/02/2023.
//

#ifndef FINALYEARPROJECT_RENDER_H
#define FINALYEARPROJECT_RENDER_H

#include <vector>
#include <memory>
#include "../L-System/LSystem.h"
#include "../Window/Window.h"
#include "../Camera/Camera.h"
#include "../Config/Config.h"
#include "../Shader/Shader.h"
#include "../UI/UI.h"
#include "../Shapes/Cylinder.h"
#include "iostream"
#include "vector"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Shapes/Cylinder.h"
#include "../Shader/Shader.h"
#include <memory>


#include "../Export/OBJExport.h"

#include "../L-System/OutputElement.h"

class Render {
public:
    void run();
    void mainLoop();
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    void handleInput();
    void configureCallbacks();
    void destroy();

    std::shared_ptr<Window>                         m_window;
    std::unique_ptr<UI>                             m_UI;
    std::shared_ptr<Camera>                  m_camera;
    std::shared_ptr<Shader>                         m_shader;
    std::shared_ptr<Light>                          m_light;
    std::shared_ptr<AllShapes>                      m_allShapes;
    std::shared_ptr<Shape>                          m_shape;
    std::shared_ptr<LSystem>                        m_lsys;
    std::vector<Rule>                               m_rules;


    bool m_isMouseInMotion;
    float ratio;
    inline static float fov;
    inline static glm::vec3 position;
    static inline std::shared_ptr<bool> isOnUI = std::make_shared<bool>(false);

};



#endif //FINALYEARPROJECT_RENDER_H
