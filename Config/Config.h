//
// Created by Theodora Vraimakis on 10/02/2023.
//

#ifndef FINALYEARPROJECT_CONFIG_H
#define FINALYEARPROJECT_CONFIG_H

#include "glm/glm.hpp"
#include "../Shapes/Cylinder.h"
#include "../Shapes/Mesh.h"
#include "../Export/OBJExport.h"



namespace Config {
    inline const unsigned int SCR_WIDTH = 800;
    inline const unsigned int SCR_HEIGHT = 600;
    inline const char *TITLE = "Generative Algorithms Toolkit";
};

class AllShapes {
public:
    explicit AllShapes() :
            m_cylinder(std::make_shared<Cylinder>())
    {
        m_cylinder=std::make_shared<Cylinder>();

        shapes.emplace_back(m_cylinder);
    }

    std::shared_ptr<Shape> m_cylinder = nullptr;
    std::vector<std::shared_ptr<Shape>> shapes;
    std::string m_name;
    ShapeType m_type;

};

class Light {
public:
    explicit Light() :
            m_lpos(glm::vec3(-1.0f, 1.0f, 1.0f)),
            m_lcolor(glm::vec3(1.0f, 1.0f, 1.0f)),
            m_lambient(0.5),
            m_specular(0.5)
    { }

    inline void setLightPos(glm::vec3 pos) {
        m_lpos = pos;
    };

    glm::vec3 m_lcolor;
    glm::vec3 m_lpos;
    float m_lambient;
    float m_specular;
};

struct Texture {
    std::string name;
    GLuint location = 0;
};

class Textures {
public:
    explicit Textures()
    {
        grass.name = "grass";
        grass.location = OBJExport::loadTexture("../textures/grass.png", 4);
        tree.name = "name";
        tree.location = OBJExport::loadTexture("../textures/treetexture.jpeg", 4);
        tree1.name = "tree1";
        tree1.location = OBJExport::loadTexture("../textures/treetexture1.jpg", 4);
        bush.name = "bush";
        bush.location = OBJExport::loadTexture("../textures/bush.jpg", 4);
        textures.push_back(grass);
        textures.push_back(tree);
        textures.push_back(tree1);
        textures.push_back(bush);

    }
    Texture grass;
    Texture tree;
    Texture tree1;
    Texture bush;
    std::vector<Texture> textures;
};

#endif //FINALYEARPROJECT_CONFIG_H
