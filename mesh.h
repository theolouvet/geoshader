#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <string> 

#include "external/tiny_obj_loader.h"

class Mesh
{
public:
    void load_from_file(const std::string filename);
    GLuint load_to_gpu() const;
    GLuint n_elements;

private:
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
};

#endif