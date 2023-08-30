#pragma once

namespace PrismRender
{
    class Shader
    {
    public:
        Shader(const char* shaderFilePath, int shaderType);

        unsigned int shaderID;
    };
}