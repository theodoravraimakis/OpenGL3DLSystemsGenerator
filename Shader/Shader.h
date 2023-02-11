//
// Created by Theodora Vraimakis on 10/02/2023.
//

#ifndef FINALYEARPROJECT_SHADER_H
#define FINALYEARPROJECT_SHADER_H

#include "glad/glad.h"

#include <string>
#include <vector>

#include <cstdint>
#include <cstdlib>

#include <cstdio>

#include "glm/glm.hpp"

class Shader {
public:
    struct ShaderSource
    {
        GLenum type;
        std::string sourcePath;
    };

public:
    explicit Shader(
            std::vector<ShaderSource> = {}
    );

    ~Shader();

    Shader( Shader const& ) = delete;
    Shader& operator= (Shader const&) = delete;

    Shader( Shader&& ) noexcept ;
    Shader& operator= (Shader&&) noexcept ;

public:
    GLuint programId() const;

    void reload();

    void setMat4(const std::string &name, const glm::mat4 &mat) const;



private:
    GLuint mProgram;
    std::vector<ShaderSource> mSources;
};


#endif //FINALYEARPROJECT_SHADER_H
