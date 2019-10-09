#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>
#include <fstream>
#include <vector>

namespace glhelper
{   
  // return id of the gpu program 
  GLuint create_program_from_file(const std::string& vs_file,
      const std::string& fs_file);


  // return id of the gpu program 
  GLuint create_program(const std::string& vs_content, 
      const std::string& fs_content);

  GLuint create_program_from_file(
      const std::string& vs_file,
      const std::string& fs_file,
          const std::string& gs_file);


  // return id of the compiled shader
  GLuint compile_shader(const char* shader_content, GLenum shader_type);

  // return content of file filename
  std::string read_file(const std::string& filename);

} // namespace glhelper
