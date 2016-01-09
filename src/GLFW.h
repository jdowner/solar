#ifndef GLFW_H
#define GLFW_H

#include <memory>

class WindowSize
{
  public:
    WindowSize(int width, int height)
      : m_width(width)
      , m_height(height)
    {
    }

    int width() const {
      return m_width;
    }

    int height() const {
      return m_height;
    }

  private:
    int m_width;
    int m_height;
};


class WindowInterface {
  public:
    virtual void swap_buffers() const = 0;
    virtual void make_current() const = 0;
    virtual void poll_events() const = 0;

    virtual bool is_open() const = 0;
    virtual int get_key(int key) const = 0;

    virtual WindowSize size() const = 0;
};


namespace glfw
{
  void init();
  void terminate();

  void sleep(double duration);
  double time();
  int get_key(int key);
  void swap_interval(int interval);

  /**
   * This class is used to abstract the GLFW interface in order to support both
   * GLFW and GLFW3.
   */
  class Window
  {
    public:
      Window(int width, int height, const char* title);
      Window(const WindowSize& size, const char* title);
      explicit Window(const Window& window);

    public:
      void swap_buffers() const;
      void make_current() const;
      void poll_events() const;

      bool is_open() const;
      int get_key(int key) const;

      WindowSize size() const;

    public:
      std::shared_ptr<WindowInterface> m_impl;
  };

  extern const int KEY_LEFT;
  extern const int KEY_RIGHT;
  extern const int KEY_UP;
  extern const int KEY_DOWN;
  extern const int KEY_TAB;
  extern const int KEY_ESC;

  extern const int KEY_G;
  extern const int KEY_H;

  extern const int KEY_PRESS;
  extern const int KEY_RELEASE;
}

#endif // GLFW_H
