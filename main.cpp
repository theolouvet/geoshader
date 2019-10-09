#include <iostream>
#include <fstream>
#include <chrono>
#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "glhelper.h"
#include "mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION 
#include "external/tiny_obj_loader.h"

#include "external/glm/gtc/matrix_transform.hpp"

GLuint program_id;
GLuint program_normal;
GLuint VAO;
GLuint n_elements;

GLuint mvp_id;

glm::mat4 mvp;


int WIDTH=800, HEIGHT=800;


std::string fragment = "basic.fs";
 std::chrono::time_point<std::chrono::system_clock> start, end;
void init()
{
    glClearColor(0.1, 0.1, 0.1, 0);     
    glEnable(GL_DEPTH_TEST);            

    program_id = glhelper::create_program_from_file("basic.vs", fragment, "basic.gs");
    program_normal = glhelper::create_program_from_file("basic.vs", "red.fs", "line.gs");
    //program_id = glhelper::create_program_from_file("basic.vs", fragment);

    Mesh m;
    // m.load_from_file("data/cube.obj");
    m.load_from_file("data/Frankie/Frankie.obj");
    n_elements=m.n_elements;
    VAO = m.load_to_gpu();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(
        glm::vec3(3,-1.5,3), 
        glm::vec3(0,0,0),
        glm::vec3(0,-1,0) 
        );
    glm::mat4 Model = glm::mat4(1.0f);
    mvp = Projection * View * Model;
    mvp_id = glGetUniformLocation(program_id, "MVP");//penser a le faire pour program_normal
    start = std::chrono::system_clock::now();
}
bool check = false;
float test = 1.0f;

static void display_callback()
{

    end = std::chrono::system_clock::now();
    float time = std::chrono::duration_cast<std::chrono::duration<float>>(start - end).count();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glUseProgram(program_normal);
    glBindVertexArray(VAO);
    glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
    glDrawElements(GL_TRIANGLES, n_elements, GL_UNSIGNED_INT, 0);
    GLint myUniformLocation = glGetUniformLocation(program_normal, "test");
    glUniform1f(myUniformLocation, cos(time));


    glBindVertexArray(0);

    glUseProgram(program_id);
    glBindVertexArray(VAO);
    glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
    glDrawElements(GL_TRIANGLES, n_elements, GL_UNSIGNED_INT, 0);
    GLint myUniformLocation2 = glGetUniformLocation(program_id, "test");
    glUniform1f(myUniformLocation2, cos(time));

    glBindVertexArray(0);

    glutSwapBuffers ();
    glutPostRedisplay();
}

static void keyboard_callback(unsigned char key, int, int)
{
  switch (key)
  {
    case 'q':
    case 'Q':
      if(fragment == "basic.fs")
          fragment = "red.fs";
      else
          fragment = "basic.fs";
      init();

      break;
    case 27:
      exit(0);
  }
  glutPostRedisplay();
}

static void reshape_callback(int width, int height)
{
  WIDTH  = width;
  HEIGHT = height;

  glViewport(0,0, width, height); 
  glutPostRedisplay();
}

int main(int argc, char** argv)
{
  glutInitContextVersion(3, 3); 
  glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
  glutInitContextProfile(GLUT_CORE_PROFILE);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("opengl");
  glutDisplayFunc(display_callback);
  glutKeyboardFunc(keyboard_callback);
  glutReshapeFunc(reshape_callback);

  glewExperimental=true;
  glewInit();
  
  init();
  glutMainLoop();

  return 0;
}
