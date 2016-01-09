#include "Engine.h"
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <cmath>
#include <GL/glu.h>
#include "DataStore.h"
#include "GLFW.h"
#include "UpdateContext.h"

#include <iostream>

Engine::Engine(DataStore& datastore) :
  m_running(false),
  m_frameRate(30.0),
  m_lastUpdate(0),
  m_window(NULL),
  m_datastore(datastore),
  m_renderer(datastore)
{
}

void Engine::init()
{
  glfw::init();

  const double height = m_datastore.get<float>("window-height");
  const double width = m_datastore.get<float>("window-width");

  m_window = new glfw::Window(width, height, "Solar");
  m_window->make_current();

  m_renderer.init();

  m_running = true;
}

void Engine::shutdown()
{
  glfw::terminate();
}

bool Engine::running() const
{
  return m_running;
}

void Engine::render()
{
  m_renderer.render(m_universe);
  m_window->swap_buffers();
}


void Engine::update()
{
  m_window->poll_events();

  m_running = !m_window->get_key(glfw::KEY_ESC) && m_window->is_open();

  UpdateContext context = createUpdateContext();
  m_universe.update(context);

  m_lastUpdate = context.currentTime;
}

UpdateContext Engine::createUpdateContext() const
{
  UpdateContext context;
  context.currentTime = glfw::time();
  context.frameRate = m_frameRate;
  context.keyLeft = (glfw::KEY_PRESS == m_window->get_key(glfw::KEY_LEFT));
  context.keyRight = (glfw::KEY_PRESS == m_window->get_key(glfw::KEY_RIGHT));
  context.keyUp = (glfw::KEY_PRESS == m_window->get_key(glfw::KEY_UP));
  context.keyG = (glfw::KEY_PRESS == m_window->get_key(glfw::KEY_G));
  context.keyH = (glfw::KEY_PRESS == m_window->get_key(glfw::KEY_H));
  context.keyTab = (glfw::KEY_PRESS == m_window->get_key(glfw::KEY_TAB));

  return context;
}

void Engine::sleep()
{
  double elapsed = glfw::time() - m_lastUpdate;
  const double period = 1.0 / m_frameRate;
  while (elapsed < period)
  {
    glfw::sleep(period - elapsed);
    elapsed = glfw::time() - m_lastUpdate;
  }
}

