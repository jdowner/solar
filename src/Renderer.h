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
    void render_text(int x, int y, const std::string& text) const;

    void set_viewport(int x, int y, int w, int h);
    void set_projection(double left, double right, double bottom, double top);
    void load_texture(const std::string& filename, const std::string& key);

  private:
    void render_stars(const Universe& universe) const;

  private:
    unsigned int m_starDisplayList;
    TextureManager m_textures;
    DataStore m_datastore;
};

#endif // RENDERER_H

