//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {
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
int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
  //If y == even Need to check up then left
  // if y != even need to check up then right
  int count = 0;
  /*Point2D newPoint;
  if ((point.y %=2 ) == 0) {
    newPoint = Point2D(0,1);
    newPoint += point;
    if (world.Get(newPoint)){
      count++;
    }
    newPoint = Point2D(-1,1);
    newPoint += point;
    if (world.Get(newPoint)){
      count++;
    }
    if (world.Get(newPoint)){
      count++;
    }
    newPoint = Point2D(-1,1);
    newPoint += point;
    if (world.Get(newPoint)){
      count++;
    }
  }
    else {
      newPoint = Point2D(0,1);
      newPoint += point;
      if (world.Get(newPoint)){
        count++;
      }
      newPoint = Point2D(1,1);
      newPoint += point;
      if (world.Get(newPoint)){
        count++;
      }
      newPoint = Point2D(0,-1);
      newPoint += point;
      if (world.Get(newPoint)){
        count++;
      }
      newPoint = Point2D(1,1);
      newPoint += point;
      if (world.Get(newPoint)){
        count++;
      }
    }
    newPoint = Point2D(1,0);
    newPoint += point;
    if (world.Get(newPoint)){
      count++;
    }
    newPoint = Point2D(-1,0);
    newPoint += point;
    if (world.Get(newPoint)){
      count++;
    }*/

  return count;
}
