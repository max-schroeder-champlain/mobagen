#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {

  std::vector<Point2D> path = generatePath(world);
  if (!path.empty()) {
    return path.front();
  }
  std::vector<Point2D> catVistiblePoints = catValidNeighbors(world);
  int i = Random::Range(0, catVistiblePoints.size()-1);
  return catVistiblePoints[i];
}
