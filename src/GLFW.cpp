#include "GLFW.h"
#include <stdexcept>

#ifdef USE_GLFW3
  #include <GLFW/glfw3.h>
#else
  #include <GL/glfw.h>
#endif // USE_GLFW3

namespace {
#ifdef USE_GLFW3
  class WindowImpl : public WindowInterface {
    public:
      WindowImpl(int width, int height, const char* title) {
        m_window = glfwCreateWindow(width, height, title, NULL, NULL);
      }

    public:
      void swap_buffers() const override {
        glfwSwapBuffers(m_window);
      }

      void make_current() const override {
        glfwMakeContextCurrent(m_window);
      }

      void poll_events() const override {
        glfwPollEvents();
      }

      bool is_open() const override {
        return true;
      }

      int get_key(int key) const override {
        return glfwGetKey(m_window, key);
      }

      WindowSize size() const override {
        int width;
        int height;

        glfwGetWindowSize(m_window, &width, &height);

        return WindowSize(width, height);
      }

    private:
      mutable GLFWwindow* m_window;
  };

  std::shared_ptr<WindowInterface> create_window(int width, int height, const char* title){
    return std::shared_ptr<WindowInterface>(new WindowImpl(width, height, title));
  }

#else // USE_GLFW3
  class WindowImpl : public WindowInterface {
    public:
      WindowImpl(int width, int height, const char* title)
      {
        if (!glfwOpenWindow(width, height, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
        {
          throw std::runtime_error("Unable to create window");
        }
      }

    public:
      void swap_buffers() const override {
        glfwSwapBuffers();
      }

      void make_current() const override {
      }

      void poll_events() const override {
      }

      bool is_open() const override {
        return glfwGetWindowParam(GLFW_OPENED);
      }

      int get_key(int key) const override {
        return glfwGetKey(key);
      }

      WindowSize size() const override {
        int width;
        int height;

        glfwGetWindowSize(&width, &height);

        return WindowSize(width, height);
      }
  };

  std::shared_ptr<WindowInterface> global_instance;

  std::shared_ptr<WindowInterface> create_window(int width, int height, const char* title){
    if(global_instance.use_count() == 0){
      global_instance.reset(new WindowImpl(width, height, title));
    }

    return global_instance;
  }
#endif // USE_GLFW3
}


namespace glfw
{
#ifdef USE_GLFW3
  const int KEY_LEFT          = GLFW_KEY_LEFT;
  const int KEY_RIGHT         = GLFW_KEY_RIGHT;
  const int KEY_UP            = GLFW_KEY_UP;
  const int KEY_DOWN          = GLFW_KEY_DOWN;
  const int KEY_TAB           = GLFW_KEY_TAB;
  const int KEY_ESC           = GLFW_KEY_ESCAPE;

  const int KEY_G             = GLFW_KEY_G;
  const int KEY_H             = GLFW_KEY_H;

  const int KEY_PRESS         = GLFW_PRESS;
  const int KEY_RELEASE       = GLFW_RELEASE;

#else
  const int KEY_LEFT          = GLFW_KEY_LEFT;
  const int KEY_RIGHT         = GLFW_KEY_RIGHT;
  const int KEY_UP            = GLFW_KEY_UP;
  const int KEY_DOWN          = GLFW_KEY_DOWN;
  const int KEY_TAB           = GLFW_KEY_TAB;
  const int KEY_ESC           = GLFW_KEY_ESC;

  const int KEY_G             = 71;
  const int KEY_H             = 72;

  const int KEY_PRESS         = GLFW_PRESS;
  const int KEY_RELEASE       = GLFW_RELEASE;

#endif // USE_GLFW3

  void init()
  {
    if (!glfwInit())
    {
      throw std::runtime_error("Unable to initialize glfw");
    }
  }

  void terminate()
  {
    glfwTerminate();
  }

  double time()
  {
    return glfwGetTime();
  }

  void sleep(double duration)
  {
#ifdef USE_GLFW3
#else
    glfwSleep(duration);
#endif // USE_GLFW3
  }

  void swap_interval(int interval)
  {
    glfwSwapInterval(interval);
  }

  Window::Window(const WindowSize& size, const char* title)
    :Window(size.width(), size.height(), title)
  {
  }

  Window::Window(int width, int height, const char* title)
    : m_impl(create_window(width, height, title))
  {
  }

  Window::Window(const Window& window)
  {
    m_impl = window.m_impl;
  }

  void Window::swap_buffers() const
  {
    m_impl->swap_buffers();
  }

  bool Window::is_open() const
  {
    return m_impl->is_open();
  }

  void Window::make_current() const
  {
    m_impl->make_current();
  }

  void Window::poll_events() const
  {
    m_impl->poll_events();
  }

  int Window::get_key(int key) const
  {
    return m_impl->get_key(key);
  }

  WindowSize Window::size() const {
    return m_impl->size();
  }
}
