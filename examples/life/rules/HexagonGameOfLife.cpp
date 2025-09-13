//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {
  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {
      Point2D currentPoint = Point2D(i,j);
      int neighborsCount = CountNeighbors(world, currentPoint);
      if (world.Get(currentPoint)) {
        if (neighborsCount < 2) {
          world.SetNext(currentPoint, false);
        }
        else if (neighborsCount >= 3) {
          world.SetNext(currentPoint, false);
        }
      }
      if (neighborsCount == 2) {
        world.SetNext(currentPoint, true);
      }
    }
  }
}
int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
  //If y == even Need to check up then left
  // if y != even need to check up then right
  int count = 0;
  if (world.Get(point.Left()))
    count++;
  if (world.Get(point.Right()))
    count++;
  if (world.Get(point.Up()))
    count++;
  if (world.Get(point.Down()))
    count++;
  int temp = point.y %= 2;
  if (temp == 0) {
    if (world.Get(point.Down().Left()))
      count++;
    if (world.Get(point.Up().Left()))
      count++;
  }
  else {
    if (world.Get(point.Down().Right()))
      count++;
    if (world.Get(point.Up().Right()))
      count++;
  }

  return count;
}
