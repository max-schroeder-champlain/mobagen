#include "Cat.h"
#include "World.h"
#include <stdexcept>
using namespace std;
Point2D Cat::Move(World* world) {
  vector<Point2D> path =  generatePath(world);
  if (path.size() > 0)
    return path.back();
  std::vector<Point2D> catVistiblePoints = catValidNeighbors(world);
  int i = Random::Range(0, catVistiblePoints.size());
  return catVistiblePoints[i];
}
