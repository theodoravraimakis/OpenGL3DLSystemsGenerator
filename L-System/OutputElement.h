//
// Created by Theodora Vraimakis on 25/02/2023.
//

#ifndef FINALYEARPROJECT_OUTPUTELEMENT_H
#define FINALYEARPROJECT_OUTPUTELEMENT_H

#include "iostream"
#include "glm/glm.hpp"
#include "LSystem.h"
#include "../Shapes/Cone.h"

enum class CommandType;
class Command;
class LSystem;
class Rule;
struct Texture;

class OutputElement {
public:
    OutputElement(
            glm::mat4 mat,
            glm::vec3 translation,
            float length,
            float width,
            std::shared_ptr<Shape> shape,
            ShapeType shapeType,
            std::shared_ptr<bool> useTexture,
            Texture* texture
            ) :
    m_mat(mat),
    m_translation(translation),
    m_length(length),
    m_width(width),
    m_shapeType(shapeType),
    m_shape(shape),
    m_useTexture(useTexture),
    m_texture(texture)
    {
        m_id = currentSegmentId++;
    }
//protected:
ShapeType m_shapeType;
    glm::mat4   m_mat;
    glm::vec3   m_translation = glm::vec3(0.0f);
    float       m_length;
    float       m_width;
    std::vector<std::shared_ptr<OutputElement>> children;
    int         m_id;
    static int  currentSegmentId;
    std::string m_type;
    std::shared_ptr<bool> m_useTexture;
    Texture* m_texture;
    std::shared_ptr<Shape> m_cone=std::make_shared<Cone>();
    std::shared_ptr<Shape> m_shape = m_cone;

};


std::string commandsToString(LSystem* lsys,
                             std::vector<Command> commands);
std::vector<Command> stringToCommands(LSystem* lsys,
                                        std::vector<Command> commands,
                                        std::string string,
                                        bool forward = false
                                                );

bool isConditionTrue(const std::string& expression, Rule* rule);


#endif //FINALYEARPROJECT_OUTPUTELEMENT_H
