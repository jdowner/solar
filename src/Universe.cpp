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
