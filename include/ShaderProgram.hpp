#pragma once

#include "Shader.hpp"

#include <glad/glad.h>

#include <vector>

namespace PrismRender
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::vector<Shader>& shaders);

        void bind() const;
        void unbind() const;

        unsigned int programID;
    };
}
