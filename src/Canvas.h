#ifndef canvas_h
#define canvas_h

#include "Rect.h"

class Window;

class Canvas {
  public:
    Canvas(Window* window, int x, int y, int w, int h);
    Canvas(Window* window, const Rect<int>& rect);

    void set_x(int x);
    void set_y(int y);
    void set_w(int w);
    void set_h(int h);
    void set_rect(const Rect<int>& rect);

  private:
    void update_viewport() const;

  private:
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    Window* m_window;
};

#endif // canvas_h
