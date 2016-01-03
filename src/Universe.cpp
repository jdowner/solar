#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <set>
#include "UpdateContext.h"
#include "Universe.h"

namespace
{
  double uniform()
  {
    return double(rand()) / RAND_MAX;
  }
}

Universe::Universe()
{
  for(int i = 0; i < 100; ++i) {
    Star* star = new Star();
    star->x = uniform() * 300.0;
    star->y = uniform() * 300.0;
    star->u = uniform() * 1.0;
    star->v = uniform() * 1.0;
    star->r = 10.0;
    star->cr = 1.0;
    star->cg = 0.0;
    star->cb = 0.0;

    m_stars.push_back(star);
  }
}

Universe::~Universe()
{
  for(StarList::iterator it = m_stars.begin(); it != m_stars.end(); ++it) {
    delete *it;
  }
}

const StarList& Universe::stars() const
{
  return m_stars;
}

void Universe::update(const UpdateContext& context)
{
  update_positions(context);
  resolve_collisions();
}

void Universe::update_positions(const UpdateContext& context)
{
  for(StarList::iterator it = m_stars.begin(); it != m_stars.end(); ++it) {
    Star* starA = *it;
    starA->x += starA->u / context.frameRate;
    starA->y += starA->v / context.frameRate;

    const double mA = starA->r * starA->r;

    double fx = 0.0;
    double fy = 0.0;

    for(StarList::iterator jt = m_stars.begin(); jt != m_stars.end(); ++jt) {
      Star* starB = *jt;
      if(it != jt) {
        const double dx = starA->x - starB->x;
        const double dy = starA->y - starB->y;
        const double r1 = std::max(sqrt(dx * dx + dy * dy), starA->r + starB->r);
        const double r3 = r1 * r1 * r1;

        const double mB = starB->r * starB->r;

        fx -= mA * mB * dx / r3;
        fy -= mA * mB * dy / r3;
      }
    }

    starA->u += fx / context.frameRate;
    starA->v += fy / context.frameRate;
  }
}

void Universe::resolve_collisions()
{
}
