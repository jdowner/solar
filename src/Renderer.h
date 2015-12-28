#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include "TextureManager.h"
#include "DataStore.h"

class Universe;

namespace glfw
{
  class Window;
}

/**
 *
 */
class Renderer
{
  public:
    explicit Renderer(DataStore& datastore);

    void init();
    void render(const Universe& universe) const;
    void renderText(int x, int y, const std::string& text) const;

    void createWindow(int width, int height, const char* title);

  private:
    void render_stars(const Universe& universe) const;

  private:
    unsigned int m_starDisplayList;
    TextureManager m_textures;
    DataStore m_datastore;
};

#endif // RENDERER_H

