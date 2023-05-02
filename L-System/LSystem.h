//
// Created by Theodora Vraimakis on 24/02/2023.
//

#ifndef FINALYEARPROJECT_LSYSTEM_H
#define FINALYEARPROJECT_LSYSTEM_H

#include <chrono>

#include "iostream"
#include "vector"

//#include "../Turtle/Turtle.h"
#include "../Shapes/Mesh.h"
#include "Output.h"
#include "OutputElement.h"
#include "../Config/Config.h"
#include <thread>
#include <atomic>

class UI;


class OutputElement;
class Output;
class Rule;
class Textures;
class Camera;

enum class CommandType
{
    RIGHT,
    LEFT,
    UP,
    DOWN,
    CW,
    CCW,
    TURN,
    PUSH,
    POP,
    FORWARD,
    SKIP,
    SCALE,
    SCALE_LENGTH,
    SCALE_WIDTH,
    ID,
    START_POLYGON,
    END_POLYGON,
    PARAMETER
};


class Command {
public:
    Command(std::string value, CommandType type) :
            m_value(value),
            m_type(type) {
        m_childRule = nullptr;
    }

    Command(std::string value, CommandType type, Rule* child) :
            m_value(value),
            m_type(type),
            m_childRule(child){
        m_childRule = nullptr;
    }

    Command(CommandType type) :
            m_type(type) {
    }
    ShapeType m_shape;
    CommandType m_type;
    ShapeType m_shapeType;
    std::string m_value;
    Rule* m_childRule = nullptr;
    float m_scale;
    int m_generation = -1;
};

class Rule {
public:
    Rule(std::string name,
         std::vector<Command> commands,
         std::shared_ptr<Shape>& shape,
         std::string left = "",
         std::string right = "",
         std::string variables = "",
         std::string condition = "",
         bool isPolygon = false
    ) :
            m_name(std::move(name)),
            m_commands(std::move(commands)),
            m_variables(std::move(variables)),
            m_condition(std::move(condition)),
            m_left(std::move(left)),
            m_right(std::move(right)),
            m_shape(shape)
    {
        m_useTexture = std::make_shared<bool>(false);
        m_polygon = std::make_shared<bool>(isPolygon);
        m_textures = std::make_shared<Textures>();
        m_texture = &m_textures->grass;
    }
    ~Rule()
    {
        m_ruleBuffer.clear();
        m_name.clear();
        m_condition.clear();
        m_variables.clear();
        m_commands.clear();
        m_left.clear();
        m_right.clear();
    }

    std::string                             m_name;
    std::string                             m_condition;
    std::string                             m_variables;
    std::string                             m_left;
    std::string                             m_right;
    std::vector<Command>   m_commands;
    std::string m_ruleBuffer;
    std::shared_ptr<Shape> m_shape;
    std::shared_ptr<bool> m_useTexture;
    std::shared_ptr<bool> m_polygon;
    Texture* m_texture;
    std::shared_ptr<Textures> m_textures;

};

class LSystem {
public:
    LSystem(
            const std::vector<Command>& axiom,
            int generations,
            std::vector<Rule> rules,
            std::shared_ptr<float> angle,
            float length,
            std::shared_ptr<Shape>& shape,
            std::shared_ptr<AllShapes>& allShapes,
            std::shared_ptr<Camera>& camera

    ) :
            m_axiom(axiom),
            m_generations(generations),
            m_rules(std::move(rules)),
            m_angle(std::move(std::move(angle))),
            m_length(length),
            m_allShapes(allShapes),
            m_camera(camera)
    {
        parametric = false;
        contextSensitive = false;
        m_setting = "HELLO!";
        l = shape->getLength();
        length = shape->m_length;
        m_textures = std::make_shared<Textures>();
    }


    bool parametric;
    bool contextSensitive;
    std::string m_setting;
    std::string                     m_axiomBuffer;
    std::vector<Command>           m_axiom;
    std::vector<Command>           m_final;
    std::vector<Rule>               m_rules;
    std::shared_ptr<float>          m_angle;
    float          m_length;
    float          m_width;
    int                             m_generations;
    std::shared_ptr<Textures>       m_textures;


    std::string d;
    std::vector<Command> c;

    void addRule(const std::string& newRule,
                 std::string newCmds,
                 const std::string& newLeft = "",
                 const std::string& newRight = "",
                 const std::string& newVariables = "",
                 const std::string& newCondition = ""
    );
    void deleteRule(Rule* rule);
    void clear();

    bool ruleExists(char n);
    bool isPolygon(const std::string& commands);

    std::vector<Command> getAxiom();

    int& getGenerations();
    void setGenerations(int newGenerations);

    std::vector<Command> applyGeneration(std::vector<Command>& commands,
                                         int generation);
    void run();

    std::shared_ptr<Output> evaluateProduction(std::vector<Command>& commands,
                                               std::shared_ptr<Shape> &shape,
                                               const std::shared_ptr<AllShapes> &allShapes);


    void updateAxiom();
    void updateRule(Rule* rule);
    void setTexture(std::shared_ptr<Rule>& rule, GLuint texture);

    float l;

    std::shared_ptr<AllShapes>& m_allShapes;

    std::shared_ptr<Output>            m_output = nullptr;
    std::shared_ptr<Camera>            m_camera = nullptr;


};

class turtleState {
public:
    turtleState() {}
    turtleState(
            std::shared_ptr<float> angle,
            float length,
            float width,
            std::shared_ptr<Shape> &shape
    ) :
            m_worldMat(glm::mat4(1.0f)),
            m_angle(angle),
            m_length(length),
            m_width(width)
    {
        m_length = shape->getLength();
        m_width = shape->getWidth();
    }

    void rotateYaw(float angle) {
        angle = glm::radians(angle);

        if (angle != 0) {
            m_worldMat *= glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1.0f));
        }
    }
    void rotatePitch(float angle) {
        angle = glm::radians(angle);

        if (angle != 0) {
            m_worldMat *= glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1.0f , 0));
        }
    }
    void rotateRoll(float angle) {
        angle = glm::radians(angle);

        if (angle != 0) {
            m_worldMat *= glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0, 0));
        }
    }

    void forward() {
        glm::vec3 translateVec = glm::vec4(0, 1.0f * m_length, 0, 0);
        m_translation += translateVec;
        m_worldMat = translate(m_worldMat, translateVec);
    }

    void scaleShape(float scalingFactor) {
        m_worldMat = scale(m_worldMat, glm::vec3(scalingFactor));
    }

    void scaleLength(float scalingFactor = 1.0f) {
        m_length *= scalingFactor;
    }


public:
    float m_length;
    float m_width;
    glm::vec3 m_translation = glm::vec3(0.0f);
    glm::mat4 m_worldMat;
    std::shared_ptr<float> m_angle;
    std::shared_ptr<OutputElement> m_element = nullptr;
    bool polygon = false;
};










#endif //FINALYEARPROJECT_LSYSTEM_H
