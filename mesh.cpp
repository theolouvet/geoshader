#include "mesh.h"
#include <iostream> 


void Mesh::load_from_file(const std::string filename)
{
    std::string warn, err;
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str())) 
    {
        std::cerr << (warn + err) << std::endl;
    }
    n_elements = shapes[0].mesh.indices.size() ;
}


GLuint create_VAO(GLfloat* vertices, GLuint n_vertices, GLuint* indices, GLuint n_indices)
{
    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, n_vertices * sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_indices * sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    return vao;
}

GLuint Mesh::load_to_gpu() const
{
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    for (unsigned i = 0; i < attrib.vertices.size(); ++i)
    {
        vertices.push_back(attrib.vertices[i]);
    }

   for (unsigned i = 0; i < shapes[0].mesh.indices.size(); ++i)
   {
        indices.push_back(shapes[0].mesh.indices[i].vertex_index);
   }

    return create_VAO(vertices.data(), vertices.size(), indices.data(), indices.size());
}