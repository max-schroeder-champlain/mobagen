#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {

  std::vector<Point2D> path = generatePath(world);
  if (path.size() > 0) {
    return path.front();
    /*if (world->catCanMoveToPosition(path.front())) return path.front();
    std::vector<Point2D> nearbyWinPoints = getBorderPoints(world, path.front());
    if (nearbyWinPoints.size()>0) {
      int i = Random::Range(0, nearbyWinPoints.size());
      return nearbyWinPoints[i];
    }*/

  }
  std::vector<Point2D> catVistiblePoints = catValidNeighbors(world);
  int i = Random::Range(0, catVistiblePoints.size());
  return catVistiblePoints[i];
}
