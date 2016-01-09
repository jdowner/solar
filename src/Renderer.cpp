#include "Renderer.h"
#include <sstream>
#include <iostream>
#include <GL/glu.h>
#include <FTGL/ftgl.h>
#include <cmath>
#include "GLFW.h"
#include "Universe.h"
#include "DataStore.h"

const char* vertex_shader =
  "#version 130\n"
  "in vec4 position;\n"
  "void main() {\n"
  "  gl_Position = gl_ModelViewProjectionMatrix * position;\n"
  "}";

const char* fragment_shader =
  "#version 130\n"
  "out vec4 out_color;\n"
  "void main() {\n"
  "  out_color = vec4(1.0, 1.0, 1.0, 1.0);\n"
  "}";

Renderer::Renderer(DataStore& datastore)
  : m_datastore(datastore)
  , m_shader_program(0)
  , m_star_vao(0)
  , m_star_vbo(0)
{
}

void Renderer::init()
{
  glfw::swap_interval(0);

  glClearColor(0.0, 0.0, 0.0, 0.0);

  const double minX = m_datastore.get<double>("viewport-min-x");
  const double minY = m_datastore.get<double>("viewport-min-y");
  const double maxX = m_datastore.get<double>("viewport-max-x");
  const double maxY = m_datastore.get<double>("viewport-max-y");

  set_viewport(0, 0, maxX - minX, maxY - minY);
  set_projection(minX, maxX, minY, maxY);

  glGenVertexArrays(1, &m_star_vao);
  glBindVertexArray(m_star_vao);

  std::vector<GLfloat> vertices;
  vertices.push_back(0.0f);
  vertices.push_back(0.0f);

  for(int i = 0; i <= 32; ++i){
    vertices.push_back(cos(2 * M_PI * i / 32));
    vertices.push_back(sin(2 * M_PI * i / 32));
  }

  GLuint vbo;
  glGenBuffers(1, &m_star_vbo);

  glBindBuffer(GL_ARRAY_BUFFER, m_star_vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

  m_shader_program = glCreateProgram();

  unsigned int handle;

  handle = load_shader(vertex_shader, GL_VERTEX_SHADER);
  glAttachShader(m_shader_program, handle);
  glDeleteShader(handle);

  handle = load_shader(fragment_shader, GL_FRAGMENT_SHADER);
  glAttachShader(m_shader_program, handle);
  glDeleteShader(handle);

  glLinkProgram(m_shader_program);
  glUseProgram(m_shader_program);

  GLint position = glGetAttribLocation(m_shader_program, "position");
  glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(position);
}

unsigned int Renderer::load_shader(const char* shader, unsigned int type) const {
  unsigned int handle = glCreateShader(type);
  glShaderSource(handle, 1, &shader, NULL);
  glCompileShader(handle);

  GLint test;
  glGetShaderiv(handle, GL_COMPILE_STATUS, &test);
  if(!test){
    std::cerr << "vertex shader compilation failed:" << std::endl;

    std::vector<char> log(512);
    glGetShaderInfoLog(handle, log.size(), NULL, &log[0]);
    std::cerr << &log[0] << std::endl;
  }

  return handle;
}

void Renderer::set_viewport(int x, int y, int w, int h) {
  glViewport(x, y, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void Renderer::set_projection(double left, double right, double bottom, double top) {
  glOrtho(left, right, bottom, top, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Renderer::load_texture(const std::string& path, const std::string& key) {
  m_textures.loadTexture(path, key);
}

void Renderer::render(const Universe& universe) const
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glBindVertexArray(m_star_vao);

  for(auto star: universe.stars()){
    glPushMatrix();
    glTranslatef(star->x, star->y, 0);
    glScalef(star->r, star->r, star->r);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 68);
    glPopMatrix();
  }
}

void Renderer::render_text(int x, int y, const std::string& text) const
{
  FTPixmapFont font(m_datastore.get<std::string>("debug-font-family").c_str());

  font.FaceSize(m_datastore.get<int>("debug-font-size"));
  font.Render(text.c_str(), -1, FTPoint(x, y));
}

