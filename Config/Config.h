//
// Created by Theodora Vraimakis on 10/02/2023.
//

#ifndef FINALYEARPROJECT_CONFIG_H
#define FINALYEARPROJECT_CONFIG_H

//#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "../Shapes/Cylinder.h"
#include "../Shapes/Cone.h"
#include "../Shapes/Mesh.h"


namespace Config {
    inline const unsigned int SCR_WIDTH = 800;
    inline const unsigned int SCR_HEIGHT = 600;
    inline const char *TITLE = "Generative Algorithms Toolkit";
};

class Light {
public:
    explicit Light() :
                        m_lpos(glm::vec3(-1.0f, 1.0f, 1.0f)),
                        m_lcolor(glm::vec3(1.0f, 1.0f, 1.0f)),
                        m_lambient(0.5)
                        { }

    inline void setLightPos(glm::vec3 pos) {
        m_lpos = pos;
    };

    glm::vec3 m_lcolor;
    glm::vec3 m_lpos;
    float m_lambient;
};

class coordinateAxesArrows {
public:
    inline coordinateAxesArrows()
    {
//        Mesh m;
//        m_cylinder = Cylinder(true, 16, glm::vec3(1.f, 0.f, 0.f),
//                            glm::scale(glm::mat4(1.0f), glm::vec3(5.f, 0.1f, 0.1f))
//                            ).getMesh();
////        m_cone = Cone(true, 16, glm::vec3(0.f, 0.f, 0.f),
////                      glm::scale(glm::mat4(1.0f), glm::vec3( 1.f, 0.3f, 0.3f ))
////                      * glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.f, 0.f))
////                        ).getMesh();
//        auto x_arrow = m.concatenate( std::move(m_cylinder), m_cone );
//        m.clearMesh(m_cylinder); m.clearMesh(m_cone);
//
//        m_cylinder = Cylinder(true, 16, glm::vec3(0.f, 1.f, 0.f),
//                              glm::rotate(glm::mat4(1.0f), -kPi_/2, glm::vec3(0.0f, 0.0f, 1.0f))
//                              * glm::scale(glm::mat4(1.0f), glm::vec3(5.f, 0.1f, 0.1f))
//                              ).getMesh();
//        m_cone = Cone(true, 16, glm::vec3(0.f, 0.f, 0.f),
//                      glm::rotate(glm::mat4(1.0f), -kPi_/2, glm::vec3(0.0f, 0.0f, 1.0f))
//                                  * glm::scale(glm::mat4(1.0f), glm::vec3( 1.f, 0.3f, 0.3f ))//translation
//                                  * glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.f, 0.f))
//                      ).getMesh();
//        auto y_arrow = m.concatenate( std::move(m_cylinder), m_cone );
//        m.clearMesh(m_cylinder); m.clearMesh(m_cone);
//        auto xy_arrow = m.concatenate(std::move(x_arrow), y_arrow);
//        m.clearMesh(x_arrow); m.clearMesh(y_arrow);
//
//        m_cylinder = Cylinder(true, 16, glm::vec3(0.f, 0.f, 1.f),
//                              glm::rotate(glm::mat4(1.0f), -kPi_/2, glm::vec3(0.0f, 1.0f, 0.0f))
//                              * glm::scale(glm::mat4(1.0f), glm::vec3(5.f, 0.1f, 0.1f))
//        ).getMesh();
//        m_cone = Cone(true, 16, glm::vec3(0.f, 0.f, 0.f),
//                      glm::rotate(glm::mat4(1.0f), -kPi_/2, glm::vec3(0.0f, 1.0f, 0.0f))
//                      * glm::scale(glm::mat4(1.0f), glm::vec3( 1.f, 0.3f, 0.3f ))
//                      * glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.f, 0.f))
//        ).getMesh();
//        auto z_arrow = m.concatenate( std::move(m_cylinder), m_cone );
//        m.clearMesh(m_cylinder); m.clearMesh(m_cone);
//
//        m_axesArrows = m.concatenate(
//                std::move(xy_arrow),
//                z_arrow
//        );
//        m_vertexCount = m_axesArrows.positions.size();
//        m.clearMesh(z_arrow);
//
//        m_VAO = m.createVAO(m_axesArrows);
    };
    MeshData m_axesArrows;
//    MeshData m_cylinder;
//    MeshData m_cone;
    GLuint m_VAO;
    size_t m_vertexCount;

    inline void draw() {
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3 * m_vertexCount);
    }

    inline ~coordinateAxesArrows() {
        Mesh m;
//        m.clearMesh(m_cylinder); m.clearMesh(m_cone); m.clearMesh(m_axesArrows);
        glDeleteBuffers(1, &m_VAO);
    }
};

#endif //FINALYEARPROJECT_CONFIG_H
