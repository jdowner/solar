#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <list>
#include "Star.h"

typedef std::list<Star*> StarList;

struct UpdateContext;

/**
 *
 */
class Universe
{
  public:
    Universe();
    ~Universe();

    const StarList& stars() const;

    void update(const UpdateContext& context);

  private:
    void resolve_collisions();
    void update_positions(const UpdateContext& context);

  private:
    StarList m_stars;
};

#endif // UNIVERSE_H

