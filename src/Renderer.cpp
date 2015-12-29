#include "Renderer.h"
#include <sstream>
#include <GL/glu.h>
#include <FTGL/ftgl.h>
#include <cmath>
#include "GLFW.h"
#include "Universe.h"
#include "DataStore.h"

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

    glBindTexture(GL_TEXTURE_2D, textures.getTextureHandle("star"));

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0, -1.0);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0, 1.0);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0, 1.0);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0, -1.0);
    glEnd();

    glEndList();

    return index;
  }
}

Renderer::Renderer(DataStore& datastore):
  m_datastore(datastore)
{
}

void Renderer::init()
{
  glfw::swapInterval(0);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);

  const double minX = m_datastore.get<double>("viewport-min-x");
  const double minY = m_datastore.get<double>("viewport-min-y");
  const double maxX = m_datastore.get<double>("viewport-max-x");
  const double maxY = m_datastore.get<double>("viewport-max-y");

  set_viewport(0, 0, maxX - minX, maxY - minY);
  set_projection(minX, maxX, minY, maxY);

  load_texture(m_datastore.get<std::string>("images-star"), "star");

  m_starDisplayList = createStarDisplayList(m_textures);
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  render_stars(universe);
}

void Renderer::render_stars(const Universe& universe) const
{
  const StarList& stars = universe.stars();
  for(StarList::const_iterator it = stars.begin(); it != stars.end(); it++){
    const Star* star = *it;
    glPushMatrix();
    glTranslatef(star->x, star->y, 0.0);
    glScalef(star->r, star->r, star->r);
    glCallList(m_starDisplayList);
    glPopMatrix();
  }
}

void Renderer::renderText(int x, int y, const std::string& text) const
{
  FTPixmapFont font(m_datastore.get<std::string>("debug-font-family").c_str());

  font.FaceSize(m_datastore.get<int>("debug-font-size"));
  font.Render(text.c_str(), -1, FTPoint(x, y));
}

