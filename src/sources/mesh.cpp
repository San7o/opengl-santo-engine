#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "mesh.h"
#include "gl.h"
#include "texture.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MyTexture> textures)
{
    this->vertices = vertices;
    this->indices  = indices;
    this->textures = textures;

    setupMesh();
}

void Mesh::Draw(Shader &shader)
{
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < this->textures.size(); i++)
    {
        Texture::ActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        shader.setFloat(("material." + name + number).c_str(), i);
        Texture::BindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    Texture::ActiveTexture(GL_TEXTURE0);

    // draw mesh
    this->vao.Bind();
    GL::DrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    GL::BindVertexArray(0);

    Texture::ActiveTexture(GL_TEXTURE0);
    
}

void Mesh::setupMesh()
{
    this->vbo.CopyVertices(this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
    this->ebo.CopyIndices(this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);
    this->vao.SetVertexData(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    this->vao.SetVertexData(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    this->vao.SetVertexData(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    GL::BindVertexArray(0);
}
