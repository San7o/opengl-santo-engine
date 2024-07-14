#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>       /* Image loading library */
#include "texture.h"

unsigned int Texture::LoadTexture(const char* path, GLint internalFormat,
                GLint wrapping, GLint filtering_min, GLint filtering_mag,
                GLboolean hasMipmap, GLint mipmap_min, GLint mipmap_mag, bool flip)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    SetTextureWrapping(wrapping);
    SetTextureFiltering(filtering_min, filtering_mag);
    SetMipmap(hasMipmap, mipmap_min, mipmap_mag);

    ReadImage(path, internalFormat, flip);

    return texture;
}

void Texture::ActiveTexture(GLenum texture)
{
    glActiveTexture(texture);
}

void Texture::BindTexture(GLenum target, unsigned int texture)
{
    glBindTexture(target, texture);
}

void Texture::SetTextureWrapping(GLint wrapping)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
}

void Texture::SetTextureFiltering(GLint filtering_min, GLint filtering_mag)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering_mag);
}

void Texture::SetMipmap(GLboolean hasMipmap, GLint mipmap_min, GLint mipmap_mag)
{
    if (hasMipmap)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipmap_min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mipmap_mag);
    }
}

void Texture::ReadImage(const char* path, GLint internalFormat, bool flip)
{
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flip);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}