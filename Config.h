//
// Created by Theodora Vraimakis on 10/02/2023.
//

#ifndef FINALYEARPROJECT_CONFIG_H
#define FINALYEARPROJECT_CONFIG_H


#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include <memory>

//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//const char* TITLE = "Generative Algorithms Toolkit";
namespace Config {
    inline const unsigned int SCR_WIDTH = 800;
    inline const unsigned int SCR_HEIGHT = 600;
    inline const char *TITLE = "Generative Algorithms Toolkit";
};
class Light {
//public:
//    inline static glm::vec3 position = glm::vec3(1.0f, 1.0f, 1.0f);
//    inline static glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
//    inline static float ambient = 0.5;
//    void setPos(const glm::vec3 pos);
public:
    explicit Light() :
    m_lpos(glm::vec3(1.0f, 1.0f, 1.0f)),
    m_lcolor(glm::vec3(1.0f, 1.0f, 1.0f)),
    m_lambient(0.5)
    {}
    inline void setLightPos(glm::vec3 pos) {m_lpos = pos;};
    inline glm::vec3* getColor() {return &m_lcolor;};
    inline glm::vec3* getPosition() {return &m_lpos;};
    inline float* getAmbient() {return &m_lambient;};
//private:
    glm::vec3 m_lcolor;
    glm::vec3 m_lpos;
    float m_lambient;
};

#endif //FINALYEARPROJECT_CONFIG_H
