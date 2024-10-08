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
 * The above copyright notice and this permission notice shall be included in
 all
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

#include "buffer.hpp"

namespace brenta
{

namespace types
{

/**
 * @brief FrameBuffer class
 *
 * This class contains the FrameBuffer functions,
 * It's a wrapper around OpenGL FrameBuffers, providing
 * functions to create, bind, unbind, delete and rescale
 * the FrameBuffer.
 */
class framebuffer : public buffer
{
  public:
    /**
     * @brief Itexture ID
     */
    GLuint texture_id;
    /**
     * @brief Render Buffer ID
     */
    GLuint render_buffer_id;
    /**
     * @brief Format of the framebuffer
     * Default is GL_RGBA
     */
    GLenum format;
    /**
     * @brief Empty constructor
     * Does nothing
     */
    framebuffer()
    {
    }
    /**
     * @brief Constructor
     * Creates a framebuffer with a texture and a render buffer
     * @param width Width of the framebuffer
     * @param height Height of the framebuffer
     */
    framebuffer(int width, int height, GLenum format = GL_RGBA);
    /**
     * @brief Destructor
     * Deletes the framebuffer and its texture
     */
    ~framebuffer();
    /**
     * @brief Bind the framebuffer
     */
    void bind();
    /**
     * @brief Unbind the framebuffer
     */
    void unbind();
    /**
     * @brief Delete the framebuffer and its texture
     */
    void destroy();
    void copy_data(GLsizeiptr size, const void *data, GLenum usage)
    {
    }

    void copy_vertices(GLsizeiptr size, const void *data, GLenum usage)
    {
    }
    void copy_indices(GLsizeiptr size, const void *data, GLenum usage)
    {
    }
    /**
     * @brief Rescale the framebuffer
     * @param width New width of the framebuffer
     * @param height New height of the framebuffer
     */
    void rescale(int width, int height);
    /**
     * @brief Set the format of the framebuffer
     * @param format New format of the framebuffer
     */
    void set_format(GLenum format);
};

} // namespace types

} // namespace brenta
