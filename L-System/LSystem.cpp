//
// Created by Theodora Vraimakis on 24/02/2023.
//

#include "LSystem.h"

#include <utility>
#include "Output.h"
#include "../UI/UI.h"


std::vector<Command> LSystem::getAxiom() {
    return m_axiom;
}

int& LSystem::getGenerations() {
    return m_generations;
}

void LSystem::setGenerations(int newGenerations)
{
    m_generations = newGenerations;
}


bool LSystem::ruleExists(char n) {
    auto rules = m_rules;
    for (const auto& rule: rules)
    {
        if (rule.m_name.find(n) != std::string::npos)
            return true;
    }
    return false;
}

bool LSystem::isPolygon(const std::string& commands) {
    for (const auto cm: commands)
    {
        if (cm == '{')
            return true;
    }
    return false;
}

void LSystem::addRule(const std::string& newRule, std::string newCmds,
                      const std::string& newLeft,
                      const std::string& newRight,
                      const std::string& newVariables,
                      const std::string& newCondition
) {

    char t = *newRule.c_str();
    if (ruleExists(t) && !(this->parametric || this->contextSensitive)) {
        std::cout << "Rule already exists, cannot have duplicated in context-free L-systems" << std::endl;
        return;
    }

    std::vector<Command> newCommands = {};
    std::shared_ptr<Shape> newshape;
    bool isPoly = false;


    auto cmds = stringToCommands(this, newCommands, newCmds, true
    );

    if(isPolygon(newCmds)) {
        newshape = std::make_shared<Shape>(ShapeType::TRIANGLE);
        newshape->makePolygon(cmds);
        newshape->createVAO();
        isPoly = true;
    }
    else {
        newshape = std::make_shared<Cylinder>();
        newshape->make();
        newshape->createVAO();
    }
    m_rules.emplace_back(newRule,
                         cmds,
                         newshape,
                         newLeft,
                         newRight,
                         newVariables,
                         newCondition,
                         isPoly
    );

}

std::shared_ptr<Output> LSystem::evaluateProduction(std::vector<Command>& commands,
                                                    std::shared_ptr<Shape> &shape,
                                                    const std::shared_ptr<AllShapes> &allShapes)
{
    auto out = std::make_shared<Output>();

    std::shared_ptr<std::vector<Command>> v = std::make_shared<std::vector<Command>>();
    std::vector<turtleState> stack;


    turtleState state(
            m_angle,
            m_length,
            m_width,
            allShapes->m_cylinder
    );
    for (auto &command: commands) {
        const auto &cmd = command;
        bool ref = false;
        switch (cmd.m_type) {
            case CommandType::FORWARD: {
                auto newSegment = std::make_shared<OutputElement>(
                        state.m_worldMat,
                        state.m_translation,
                        state.m_length,
                        state.m_width,
                        (cmd.m_childRule == nullptr) ? allShapes->m_cylinder : cmd.m_childRule->m_shape,
                        cmd.m_shapeType,
                        (cmd.m_childRule == nullptr) ? std::make_shared<bool>(ref) : cmd.m_childRule->m_useTexture,
                        (cmd.m_childRule == nullptr) ? &this->m_textures->tree : cmd.m_childRule->m_texture
                );
                out->addElement(newSegment);
                state.forward();
                state.m_element = newSegment;
                break;
            }
            case CommandType::SKIP: {
                state.forward();
                break;
            }
            case CommandType::RIGHT: {
                state.rotateYaw(+*m_angle);
                break;
            }
            case CommandType::LEFT: {
                state.rotateYaw(-*m_angle);
                break;
            }
            case CommandType::TURN: {
                state.rotateYaw(+180.0f);
                break;
            }
            case CommandType::CW: {
                state.rotatePitch(-*m_angle);
                break;
            }
            case CommandType::CCW: {
                state.rotatePitch(+*m_angle);
                break;
            }
            case CommandType::UP: {
                state.rotateRoll(-*m_angle);
                break;
            }
            case CommandType::DOWN: {
                state.rotateRoll(+*m_angle);
                break;
            }
            case CommandType::PUSH: {
                stack.push_back(state);
                break;
            }
            case CommandType::POP: {
                if (stack.size() == 0) {
                    std::cerr << "Nothing to pop." << std::endl;
                    exit(1);
                }
                state = stack.back();
                stack.pop_back();
                break;
            }
            case CommandType::SCALE:
                state.scaleShape(std::stof(cmd.m_value));
                break;
            case CommandType::SCALE_LENGTH: {
                state.scaleLength((float) std::stof(cmd.m_value));
                break;
            }
            case CommandType::SCALE_WIDTH: {
                auto scale = (float) std::stof(cmd.m_value);
                state.scaleLength(1.0f / scale);
                state.scaleShape(scale);
                break;
            }
            case CommandType::START_POLYGON: {
                break;
            }
            case CommandType::END_POLYGON: {
                break;
            }
            case CommandType::ID: {
                if (cmd.m_childRule != nullptr && *cmd.m_childRule->m_polygon){
                    auto newSegment = std::make_shared<OutputElement>(
                            state.m_worldMat,
                            state.m_translation,
                            state.m_length,
                            state.m_width,
                            (cmd.m_childRule == nullptr) ? allShapes->m_cylinder : cmd.m_childRule->m_shape,
                            cmd.m_shapeType,
                            (cmd.m_childRule == nullptr) ? std::make_shared<bool>(ref)
                                                         : cmd.m_childRule->m_useTexture,
                            (cmd.m_childRule == nullptr) ? &this->m_textures->tree : cmd.m_childRule->m_texture
                    );
                    out->addElement(newSegment);
                    break;
                }

            }

        }
    }

    return out;
}





std::vector<Command> LSystem::applyGeneration(
        std::vector<Command>& commands,
        int generation
) {
    std::vector<Command> newCommands;
    const Command* prevCmd = nullptr;
    Command* nextCmd = nullptr;


    for (auto it = commands.begin(); it != commands.end(); ++it) {
        Command& cmd = *it;
        bool skipCmd = false;

        if (contextSensitive && (cmd.m_value == "F")) {

            newCommands.push_back(cmd);
            skipCmd = true;
        }

        if (contextSensitive && skipCmd) {
            skipCmd = false;
            continue; // skip to the next command
        }
        if (it == std::prev(commands.end())) {
            nextCmd = nullptr;
        } else {
            auto nextIt = std::next(it);
            while (nextIt != commands.end() &&
                   (nextIt->m_value == "F" || nextIt->m_value == "[" || nextIt->m_value == "]"  || nextIt->m_value == "+" || nextIt->m_value == "-")
                    ) {
                ++nextIt;
            }
            if (nextIt != commands.end()) {
                nextCmd = &(*nextIt);
            } else {
                nextCmd = nullptr;
            }
        }

        if (cmd.m_type == CommandType::ID || cmd.m_type == CommandType::FORWARD
            || cmd.m_type == CommandType::LEFT || cmd.m_type == CommandType::RIGHT
                ) {
            bool foundRule = false;
            for (auto& rule : this->m_rules) {
                if(contextSensitive)
                {
                    if (cmd.m_value == rule.m_name) {
                        if (
                                (
                                        rule.m_left.empty() || //there is a left condition
                                        (prevCmd != nullptr && rule.m_left == prevCmd->m_value)
                                )
                                &&
                                (
                                        rule.m_right.empty() || //there is a right condition
                                        (nextCmd != nullptr && rule.m_right == nextCmd->m_value)
                                )

                                ) {

                            for (auto subCmd: rule.m_commands) {
                                subCmd.m_generation = generation;
                                subCmd.m_shapeType = rule.m_shape->m_type;
                                subCmd.m_childRule = &rule;
                                newCommands.push_back(subCmd);
                            }

                            foundRule = true;
                            break;
                        } else if (rule.m_left.empty() &&
                                   rule.m_right.empty())
                        {
                            for (auto subCmd: rule.m_commands) {
                                subCmd.m_generation = generation;
                                subCmd.m_shapeType = rule.m_shape->m_type;
                                subCmd.m_childRule = &rule;
                                newCommands.push_back(subCmd);
                            }
                            foundRule = true;
                            break;
                        }
                    }
                }
                else if (parametric)
                {
                    if(nextCmd != nullptr && nextCmd->m_type == CommandType::PARAMETER && !nextCmd->m_value.empty()) {
                        if (cmd.m_value == rule.m_name) {
                            if(!rule.m_variables.empty()){
                                if(isdigit(*nextCmd->m_value.c_str()) && !isConditionTrue(nextCmd->m_value, &rule))
                                    break;

                                for (auto subCmd: rule.m_commands) {
                                    if(subCmd.m_type == CommandType::PARAMETER && !isdigit(*subCmd.m_value.c_str()))
                                    {
                                        std::vector<std::string> variables;
                                        std::stringstream ss(rule.m_variables);
                                        std::string token;
                                        while (std::getline(ss, token, ',')) {
                                            variables.push_back(token);
                                        }
                                        std::string condition = rule.m_condition;
                                        for (const std::string& variable : variables) {
                                            size_t pos = subCmd.m_value.find(variable);
                                            if (pos != std::string::npos) {
                                                subCmd.m_value.replace(pos, variable.length(), nextCmd->m_value.c_str());
                                            }
                                        }
                                    }
                                    subCmd.m_generation = generation;
                                    subCmd.m_shapeType = rule.m_shape->m_type;
                                    subCmd.m_childRule = &rule;
                                    newCommands.push_back(subCmd);
                                }
                                foundRule = true;
                                break;
                            }
                            else if(rule.m_variables.empty()){
                                for (auto subCmd: rule.m_commands) {
                                    subCmd.m_generation = generation;
                                    subCmd.m_shapeType = rule.m_shape->m_type;
                                    subCmd.m_childRule = &rule;
                                    newCommands.push_back(subCmd);
                                }
                                foundRule = true;
                                break;
                            }
                        }
                    }

                }
                else {
                    if (rule.m_name == cmd.m_value && !*rule.m_polygon) {
                        if (generation == m_generations) {
                            for (auto subCmd: rule.m_commands) {
                                if (subCmd.m_value == "3") {
                                    subCmd.m_value = "f";
                                    subCmd.m_type = CommandType::SKIP;
                                    subCmd.m_childRule = &rule;
                                    newCommands.push_back(subCmd);
                                }
                                else if (subCmd.m_value == "l" || subCmd.m_value == "r") {
                                    subCmd.m_value = "F";
                                    subCmd.m_type = CommandType::FORWARD;
                                    subCmd.m_childRule = &rule;
                                    newCommands.push_back(subCmd);
                                }
                                else {
                                    subCmd.m_generation = generation;
                                    subCmd.m_shapeType = rule.m_shape->m_type;
                                    subCmd.m_childRule = &rule;
                                    newCommands.push_back(subCmd);
                                }
                            }
                            foundRule = true;
                            break;
                        }
                        else if(generation == m_generations - 1)
                        {
                            for (auto subCmd: rule.m_commands) {
                                if (subCmd.m_value == "H") {
                                    std::vector<Command> nC;
                                    auto n = stringToCommands(this, nC, "[cf&c/cf^cf^c-\\f^c]");
                                    for (auto &i: n) {
                                        i.m_generation = generation;
                                        newCommands.push_back(i);
                                    }
                                }
                                else if (subCmd.m_value == "3") {
                                    subCmd.m_value = "f";
                                    subCmd.m_type = CommandType::SKIP;
                                    subCmd.m_childRule = &rule;
                                    newCommands.push_back(subCmd);
                                }
                                else
                                {
                                    newCommands.push_back(subCmd);
                                }
                            }
                            foundRule = true;
                            break;
                        }
                        else{
                            for (auto subCmd: rule.m_commands) {
                                subCmd.m_generation = generation;
                                subCmd.m_shapeType = rule.m_shape->m_type;
                                subCmd.m_childRule = &rule;
                                newCommands.push_back(subCmd);
                            }
                            foundRule = true;
                            break;
                        }
                    }
                    else if (rule.m_name == cmd.m_value && *rule.m_polygon)
                    {
                        if (cmd.m_value == "c")
                        {
                            Command subCmd = Command(rule.m_name, CommandType::ID);
                            subCmd.m_shapeType = rule.m_shape->m_type;
                            subCmd.m_childRule = &rule;
                            newCommands.push_back(subCmd);
                            foundRule = true;
                            break;
                        }
                        else
                        {
                            cmd.m_shapeType = rule.m_shape->m_type;
                            cmd.m_childRule = &rule;
                            newCommands.push_back(cmd);
                            foundRule = true;
                            break;
                        }
                    }
                }
            }
            if (!foundRule) {
                newCommands.push_back(cmd);
            }
        }
        else {
            newCommands.push_back(cmd);
        }
        prevCmd = &*it;

    }
    return newCommands;
}


void LSystem::run() {

//    auto start = std::chrono::high_resolution_clock::now();

//    std::cout << "\nbefore applying generations:  " << commandsToString(this, m_axiom) << std::endl;
    m_final = applyGeneration(m_axiom, 0);
//    std::cout << "generation 0: " << commandsToString(this, m_final) << std::endl;
    for(int i = 0; i <= m_generations; i++) {
        m_final = applyGeneration(m_final, i);
//        std::cout<< "generation " << i + 1 << ": " << commandsToString(this, m_final) << std::endl;
    }

    m_output = evaluateProduction(m_final, this->m_allShapes->m_cylinder, this->m_allShapes);

//    auto end = std::chrono::high_resolution_clock::now();
//
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//
//    std::cout << "L-system: " << m_setting << ". " << m_generations << " generation time: " << duration.count() << " ms" << std::endl;

    m_final.clear();

    glm::vec3 center(0.0f);
    for (auto segment : m_output->getAllElements()) {
        auto shape = segment->m_shape;
        auto matrix = segment->m_mat;
        for (auto vertex : segment->m_shape->m_mesh.positions) {
            center += glm::vec3(matrix * glm::vec4(vertex, 1.0f));
        }
    }
    center /= (float)(m_output->getAllElements().size() * m_allShapes->m_cylinder->getVertexCount());

    m_camera->setObjectPos(glm::vec4(center, 1.0f));
    m_output->center = center;

    float distanceFromObject = 20.0f;
    glm::vec3 offset(0.0f, 0.0f, distanceFromObject);
    glm::vec3 cameraPos = center + offset;
    m_camera->setPos(glm::vec4(cameraPos, 1.0f));

}


void LSystem::updateAxiom()
{
    auto newAxiom = m_axiomBuffer.c_str();
    auto oldAxiom = commandsToString(this, getAxiom());

//    if (strcmp(newAxiom, oldAxiom.c_str()) != 0) { //TODO MIGHT BE HELPFUL BUT ALLOWS FOR QUICK CHANGING OF RULES
    m_axiom.clear();
    m_axiom = stringToCommands(this, m_axiom, m_axiomBuffer);
    run();
//    }

}
void LSystem::updateRule(Rule* rule)
{
    auto newRule = rule->m_ruleBuffer.c_str();
    auto oldRule = commandsToString(this, rule->m_commands);

    if (strcmp(newRule, oldRule.c_str()) != 0) {

        if (!rule->m_commands.empty())
            rule->m_commands.clear();

        rule->m_commands = stringToCommands(this, rule->m_commands, rule->m_ruleBuffer
                , true
        );

        if(isPolygon(rule->m_ruleBuffer)) {
            Mesh::clearMesh(rule->m_shape->getMesh());
            rule->m_shape->makePolygon(rule->m_commands);
            rule->m_shape->createVAO();
            rule->m_polygon = std::make_shared<bool>(true);
        }

        run();

    }

}


void LSystem::deleteRule(Rule *rule) {
    auto it = std::find_if(m_rules.begin(), m_rules.end(), [rule](const Rule& r) {
        return &r == rule;
    });
    if (it != m_rules.end()) {
        m_rules.erase(it);
        run();
    }
}

void LSystem::setTexture(std::shared_ptr<Rule>& rule, GLuint texture) {
    *rule->m_useTexture = true;
    rule->m_texture->location = texture;
    rule->m_shape->updateShape();
}
void LSystem::clear() {
    m_axiom.clear();
    m_setting.clear();
    while(!m_rules.empty()) {
        for (auto &rule: m_rules)
            deleteRule(&rule);
    }
}
