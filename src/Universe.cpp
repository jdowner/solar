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
  Star* star = new Star();
  star->x = 0.0;
  star->y = 0.0;
  star->u = 0.0;
  star->v = 0.0;
  star->r = 50.0;
  star->cr = 1.0;
  star->cg = 0.0;
  star->cb = 0.0;

  m_stars.push_back(star);
}

Universe::~Universe()
{
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
}

void Universe::resolve_collisions()
{
}
