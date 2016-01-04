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
  "  gl_Position = position;\n"
  "}";

const char* fragment_shader =
  "#version 130\n"
  "out vec4 out_color;\n"
  "void main() {\n"
  "  out_color = vec4(1.0, 1.0, 1.0, 1.0);\n"
  "}";

namespace
{
  double rad2deg(double rad)
  {
    return 57.29577951308232087721 * rad;
  }

  unsigned int createStarDisplayList(const TextureManager& textures)
  {
    unsigned int index = glGenLists(1);

    glNewList(index, GL_COMPILE);

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1,0,1);
    glVertex2f(0.0f, 0.0f);
    glColor3f(1,1,1);

    const float pi = M_PI;

    const int n = 36;
    for(int i = 0; i <= n; ++i) {
      const float x = cos(2 * pi * i / n);
      const float y = sin(2 * pi * i / n);
      glVertex2f(x, y);
    }

    glEnd();

    glEndList();

    return index;
  }
}

Renderer::Renderer(DataStore& datastore)
  : m_datastore(datastore)
  , m_shader_program(0)
{
}

void Renderer::init()
{
  glfw::swapInterval(0);

  glClearColor(0.0, 0.0, 0.0, 0.0);

  const double minX = m_datastore.get<double>("viewport-min-x");
  const double minY = m_datastore.get<double>("viewport-min-y");
  const double maxX = m_datastore.get<double>("viewport-max-x");
  const double maxY = m_datastore.get<double>("viewport-max-y");

  set_viewport(0, 0, maxX - minX, maxY - minY);
  set_projection(minX, maxX, minY, maxY);

  m_starDisplayList = createStarDisplayList(m_textures);


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

  const StarList& stars = universe.stars();
  for(StarList::const_iterator it = stars.begin(); it != stars.end(); it++){
    const Star* star = *it;
    glColor3f(star->cr, star->cg, star->cb);
    glPushMatrix();
    glTranslatef(star->x, star->y, 0.0);
    glScalef(star->r, star->r, star->r);
    glCallList(m_starDisplayList);
    glPopMatrix();
  }
}

void Renderer::render_text(int x, int y, const std::string& text) const
{
  FTPixmapFont font(m_datastore.get<std::string>("debug-font-family").c_str());

  font.FaceSize(m_datastore.get<int>("debug-font-size"));
  font.Render(text.c_str(), -1, FTPoint(x, y));
}

