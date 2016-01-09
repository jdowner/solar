#include "Canvas.h"
#include <GL/gl.h>

Canvas::Canvas(Window* window, int x, int y, int w, int h)
  : m_window(window)
  , m_x(x)
  , m_y(y)
  , m_w(w)
  , m_h(h)
{
}

Canvas::Canvas(Window* window, const Rect<int>& rect)
  : m_window(window)
  , m_x(rect.x)
  , m_y(rect.y)
  , m_w(rect.w)
  , m_h(rect.h)
{
}

void Canvas::set_x(int x) {
  if(x != m_x) {
    m_x = x;
    update_viewport();
  }
}

void Canvas::set_y(int y) {
  if(y != m_y) {
    m_y = y;
    update_viewport();
  }
}

void Canvas::set_w(int w) {
  if(w != m_w) {
    m_w = w;
    update_viewport();
  }
}

void Canvas::set_h(int h) {
  if(h != m_h) {
    m_h = h;
    update_viewport();
  }
}

void Canvas::set_rect(const Rect<int>& rect) {
  m_x = rect.x;
  m_y = rect.y;
  m_w = rect.w;
  m_h = rect.h;
  update_viewport();
}

void Canvas::update_viewport() const {
  glViewport(m_x, m_y, m_w, m_h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}
