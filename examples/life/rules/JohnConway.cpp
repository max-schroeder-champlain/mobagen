#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
/* If neighbor < 2 = Die
 * If neighbors == 2 or 3 = live
 * If neighbors > 3 = die
 * if point is dead and next to 3 = live
 */
void JohnConway::Step(World& world) {
  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {
      Point2D currentPoint = Point2D(i,j);
      int neighborsCount = CountNeighbors(world, currentPoint);
      if (neighborsCount < 2) {
        world.SetNext(currentPoint, false);
      }
      else if ((neighborsCount == 2 || neighborsCount == 3) && world.Get(currentPoint)) {
        world.SetNext(currentPoint, true);
      }
      else if (neighborsCount > 3) {
        world.SetNext(currentPoint, false);
      }
      else if (neighborsCount == 3 && !world.Get(currentPoint)) {
        world.SetNext(currentPoint, true);
      }
    }
  }
}

  int JohnConway::CountNeighbors(World& world, Point2D point) {
    int count = 0;
    for (int i = -1; i <=1; i++) {
      for (int j =-1; j <=1; j++) {
        if (i == 0 && j == 0) {
          continue;
        }
        Point2D newPoint = Point2D(i,j);
        newPoint += point;
        if (world.Get(newPoint)){
          count++;
        }
      }

    }
    return count;
  }
