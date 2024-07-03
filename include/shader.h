/*
 *
 *     Created on: 2024-07-03
 *     Author: Giovanni Santini 
 *     License: MIT
 *
 */

#ifndef SHADER_H
#define SHADER_H

#include <iostream>

class Shader
{

public:
    unsigned int ID; /* Program ID */

    /* Constructor reads and builds the shader */
    Shader(const char* vertexPath, const char* fragmentPath);

    /* Use/activate the shader */
    void use();

    /* Utility uniform functions */
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
