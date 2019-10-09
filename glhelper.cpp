#include "glhelper.h"

namespace glhelper
{  
  // return content of file filename
  std::string read_file(const std::string& filename)
  {
    std::ifstream ifs; 
    ifs.open(filename.c_str());
    if(!ifs)
    {
      std::cerr << "-------------------------\n";
      std::cerr << "Error reading file: " << filename << std::endl;
      std::cerr << "-------------------------\n";
    }
    return std::string((std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>()));
  }

  // return id of the compiled shader
  GLuint compile_shader(const char* shader_content, GLenum shader_type)
  {
    GLint success;
    char log[128];

    GLuint shader_id = glCreateShader(shader_type);

    glShaderSource(shader_id, 1, &shader_content, nullptr);
    glCompileShader(shader_id);

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(shader_id, 128, nullptr, log);
      std::cerr << "-------------------------\n";
      std::cerr << "Error compiling shader: \n" << log << "\n" << shader_content << std::endl;
      std::cerr << "-------------------------\n";

    }
    return shader_id;
  } 

  void check_error_link(GLuint program_id)
  {
    GLint success;
    char log[128];

    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(program_id, 128, nullptr, log);
      std::cerr << "-------------------------\n";
      std::cerr << "Error linking program: \n" << log << std::endl;
      std::cerr << "-------------------------\n";
    }
  }

  // return id of the gpu program 
  GLuint create_program(const std::string& vs_content,
      const std::string& fs_content)
  {

    GLuint vs_id = compile_shader(vs_content.c_str(),GL_VERTEX_SHADER);
    GLuint fs_id = compile_shader(fs_content.c_str(),GL_FRAGMENT_SHADER);

    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vs_id);
    glAttachShader(program_id, fs_id);

    glLinkProgram(program_id);
    check_error_link(program_id);
    glDeleteShader(vs_id);
    glDeleteShader(fs_id);

    return program_id;
  }


  GLuint create_program_from_file(
      const std::string& vs_file,
      const std::string& fs_file)
  {
    return create_program(read_file(vs_file), read_file(fs_file));
  }

  GLuint create_program_from_file(
      const std::string& vs_file,
      const std::string& fs_file,
          const std::string& gs_file)
  {
     GLuint vs_id = compile_shader(read_file(vs_file).c_str(),GL_VERTEX_SHADER);
     GLuint fs_id = compile_shader(read_file(fs_file).c_str(),GL_FRAGMENT_SHADER);
     GLuint gshader = compile_shader(read_file(gs_file).c_str(),GL_GEOMETRY_SHADER);
     GLuint program_id = glCreateProgram();

     glAttachShader(program_id, vs_id);
     glAttachShader(program_id, fs_id);
     glAttachShader(program_id , gshader);

     glLinkProgram(program_id);

     check_error_link(program_id);

     glDeleteShader(vs_id);
     glDeleteShader(fs_id);
     glDeleteShader(gshader);
     return program_id;
  }


}
