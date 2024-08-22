/*
 * MIT License
 * 
 * Copyright (c) 2024 Giovanni Santini

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */ 

#pragma once

#include "engine_logger.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>       /* OpenGL driver */

#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>

namespace ECS
{

namespace Types
{

typedef std::string ShaderName;

} // namespace Types

class Shader
{

public:
static std::unordered_map<Types::ShaderName, unsigned int> shaders;

template<typename... Args>
static void New(std::string shader_name, GLenum type, std::string path, Args... args)
{
    std::vector<unsigned int> compiled_shaders = {};
    compile_shaders(compiled_shaders, type, path, args...);

    /* shader Program */
    unsigned int ID = glCreateProgram();
    std::for_each(compiled_shaders.begin(), compiled_shaders.end(),
                    [&ID](auto shader){ glAttachShader(ID, shader); });
    
    glLinkProgram(ID);
    Shader::CheckCompileErrors(ID, "PROGRAM");

    Shader::shaders.insert({shader_name, ID});
    std::for_each(compiled_shaders.begin(), compiled_shaders.end(),
                    [](auto shader){ glDeleteShader(shader); });
}

template<typename... Args>
static void New(const GLchar** feedbackVaryings, int numVaryings,
                std::string shader_name, GLenum type, std::string path, Args... args)
{
    std::vector<unsigned int> compiled_shaders = {};
    compile_shaders(compiled_shaders, type, path, args...);

    /* shader Program */
    unsigned int ID = glCreateProgram();
    std::for_each(compiled_shaders.begin(), compiled_shaders.end(),
                    [&ID](auto shader){ glAttachShader(ID, shader); });
    
    if (feedbackVaryings != nullptr)
    {
        glTransformFeedbackVaryings(ID, numVaryings, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
    }

    glLinkProgram(ID);
    Shader::CheckCompileErrors(ID, "PROGRAM");

    Shader::shaders.insert({shader_name, ID});
    std::for_each(compiled_shaders.begin(), compiled_shaders.end(),
                    [](auto shader){ glDeleteShader(shader); });
}

static void compile_shaders(std::vector<unsigned int>& compiled)
{
    return;
}

template<typename... Args>
static void compile_shaders(std::vector<unsigned int>& compiled,
                GLenum type, std::string path, Args... args)
{
    std::string code;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        code = stream.str();
    }
    catch (std::ifstream::failure& e)
    {
        Logger::Log(Types::LogLevel::ERROR, "Error reading shader file: " + path);
        return;
    }

    const char* shader_code = code.c_str();
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &shader_code, NULL);
    glCompileShader(shader);
    Shader::CheckCompileErrors(shader, "SHADER");

    compiled.push_back(shader);
    compile_shaders(compiled, args...);
}

static unsigned int GetId(Types::ShaderName shader_name);

/* Use/activate the shader */
static void Use(Types::ShaderName shader_name);

/* Utility uniform functions */
static void SetBool(Types::ShaderName shader_name,
                    const std::string &name, bool value);
static void SetInt(Types::ShaderName shader_name,
                    const std::string &name, int value);
static void SetFloat(Types::ShaderName shader_name,
                    const std::string &name, float value);
static void SetMat4(Types::ShaderName shader_name,
                    const GLchar* name, glm::mat4 value);
static void SetVec3(Types::ShaderName shader_name,
                    const GLchar* name, float x, float y, float z);
static void SetVec3(Types::ShaderName shader_name,
                    const GLchar* name, glm::vec3 value);
private:
static void CheckCompileErrors(unsigned int shader, std::string type);

};

} // namespace ECS