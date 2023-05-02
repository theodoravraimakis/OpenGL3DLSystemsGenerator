//
// Created by Theodora Vraimakis on 25/02/2023.
//

#include "OutputElement.h"

int OutputElement::currentSegmentId = 0;


std::string commandsToString(LSystem* lsys,
                             std::vector<Command> commands) {
    std::string str;
    for (const auto& cmd: commands) {
        switch (cmd.m_type) {
            case CommandType::FORWARD:
                str.append("F");
                break;
            case CommandType::SKIP:
                str.append("f");
                break;
            case CommandType::LEFT:
                str.append("-");
                break;
            case CommandType::RIGHT:
                str.append("+");
                break;
            case CommandType::UP:
                str.append("&");
                break;
            case CommandType::DOWN:
                str.append("^");
                break;
            case CommandType::PUSH:
                str.append("[");
                break;
            case CommandType::CCW:
                str.append("/");
                break;
            case CommandType::CW:
                str.append("\\");
                break;
            case CommandType::TURN:
                str.append("|");
                break;
            case CommandType::POP:
                str.append("]");
                break;
            case CommandType::SCALE_LENGTH:
                str.append("\"");
                str.append("(");
                str.append(cmd.m_value);
                str.append(")");
                break;
            case CommandType::SCALE_WIDTH:
                str.append("\'");
                str.append("(");
                str.append(cmd.m_value);
                str.append(")");
                break;
            case CommandType::SCALE:
                str.append("@");
                str.append("(");
                str.append(cmd.m_value);
                str.append(")");
                break;
            case CommandType::PARAMETER:
                if(lsys->parametric)
                    str.append("(");
                str.append(cmd.m_value);
                str.append(")");
                break;
            case CommandType::START_POLYGON:
                str.append("{");
                break;
            case CommandType::END_POLYGON:
                str.append("}");
                break;
            case CommandType::ID:
                str.append(cmd.m_value);
                break;
            default:
                break;
        }
    }
    return str;
}



std::vector<Command> stringToCommands(LSystem* lsys,
                                      std::vector<Command> commands,
                                      std::string string,
                                      bool forward)
{
    std::string numberBuffer;
    std::string parameterBuffer;
    CommandType type;
    bool numberInput = false;
    bool parameterInput = false;
    auto str = string.c_str();
    for (int j = 0; j < strlen(str); j++) {
        auto i = str[j];
        if (i == '\0') break;
        switch (i) {
            case 'F': {
                if (forward) {
                    commands.emplace_back("F", CommandType::FORWARD);
                    break;
                }
                else if (lsys->ruleExists(i)) {
                    commands.emplace_back("F", CommandType::ID);
                    break;
                } else {
                    commands.emplace_back("F", CommandType::FORWARD);
                    break;
                }
            }
            case 'f':
                commands.push_back(Command(CommandType::SKIP));
                break;

            case '+':
                if (forward) {
                    commands.emplace_back("+", CommandType::RIGHT);
                    break;
                }
                if (lsys->ruleExists(i)) {
                    commands.emplace_back("+", CommandType::ID);
                    break;
                } else {
                    commands.emplace_back(Command("+", CommandType::RIGHT));
                    break;
                }
            case '-':
                if (forward) {
                    commands.emplace_back("-", CommandType::LEFT);
                    break;
                }
                if (lsys->ruleExists(i)) {
                    commands.emplace_back("-", CommandType::ID);
                    break;
                } else {
                    commands.emplace_back(Command("-", CommandType::LEFT));
                    break;
                }
            case '&':
                commands.emplace_back("&", CommandType::UP);
                break;
            case '^':
                commands.emplace_back("^", CommandType::DOWN);
                break;
            case '[':
                commands.emplace_back("[", CommandType::PUSH);
                break;
            case ']':
                commands.emplace_back("]", CommandType::POP);
                break;
            case '/':
                commands.emplace_back("/", CommandType::CCW);
                break;
            case '\\':
                commands.emplace_back("\\", CommandType::CW);
                break;
            case '|':
                commands.emplace_back("|", CommandType::TURN);
                break;
            case '"':
                type = CommandType::SCALE_LENGTH;
                break;
            case '@':
                type = CommandType::SCALE;
                break;
            case '\'':
                type = CommandType::SCALE_WIDTH;
                break;
            case '(':
                if(lsys->parametric && type != CommandType::SCALE_LENGTH && type != CommandType::SCALE && type != CommandType::SCALE_WIDTH)
                    parameterInput = true;
                else
                    numberInput = true;
                break;
            case ')':
                if(lsys->parametric && parameterInput) {
                    commands.emplace_back(parameterBuffer, CommandType::PARAMETER);
                    parameterBuffer = "";
                    parameterInput = false;
                }
                else if (numberInput) {
                    commands.emplace_back(numberBuffer, type);
                    numberBuffer = "";
                    numberInput = false;
                }
                break;
            case '{':
                commands.emplace_back(Command("{", CommandType::START_POLYGON));
                break;
            case '}':
                commands.emplace_back(Command("}", CommandType::END_POLYGON));
                break;
            default:
                if((isdigit(i) || i == '.') && numberInput) {
                    numberBuffer.append(std::string(1, i));
                    break;
                }
                if(lsys->parametric && parameterInput) {
                    parameterBuffer.append(std::string(1, i));
                    break;
                }
                if(!lsys->ruleExists(i)){
                    if (!numberInput && !parameterInput)
                    {
                        std::string s(1, i);
                        commands.emplace_back(s, CommandType::ID);
                    }
                    break;
                }
                else if(lsys->ruleExists(i)) {
                    if (!numberInput && !parameterInput)
                    {
                        std::string s(1, i);
                        commands.emplace_back(s, CommandType::ID);
                    }
                    break;
                }
                else {
                    break;
                }
        }
    }
    return commands;
}

bool isConditionTrue(const std::string& expression, Rule* rule) {
    return true;
}
