#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>

bool RecursiveBacktrackerExample::Step(World* w) {
  Point2D neighbor, currentPoint;
  //currentPoint = Point2D(stack.back().x, stack.back().y);

  if (stack.empty()) {
    stack.push_back(randomStartPoint(w));
  }
  else {
    visited[stack.back().x][stack.back().y] = true;
    w->SetNodeColor(stack.back(), Color::Red);
    std::vector<Point2D> visitables = getVisitables(w, stack.back());
    if (visitables.empty()) {
      w->SetNodeColor(stack.back(), Color::Black);
      stack.pop_back();
      return true;
    }
    neighbor = visitables.front();
    if (visitables.size() != 1) {
      Random random;
      int num = random.Range(0, visitables.size()-1);
      neighbor = visitables[num];
    }
    if (neighbor == stack.back().Up()) {
      w->SetNorth(stack.back(), false);
      w->SetSouth(stack.back().Up(), false);
    }
    else if (neighbor == stack.back().Down()) {
      w->SetSouth(stack.back(), false);
      w->SetNorth(stack.back().Down(), false);
    }
    else if (neighbor == stack.back().Left()) {
      w->SetWest(stack.back(), false);
      w->GetEast(stack.back().Left());
    }
    else if (neighbor == stack.back().Right()) {
      w->SetEast(stack.back(), false);
      w->SetWest(stack.back().Right(), false);
    }
    stack.push_back(neighbor);
    return true;
  }
  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: implement this
  Point2D pointNorth = p.Up();
  Point2D pointSouth = p.Down();
  Point2D pointWest = p.Left();
  Point2D pointEast = p.Right();
  bool northGood = (pointNorth.x >= -sideOver2) && (pointNorth.x <= sideOver2) && (pointNorth.y >= -sideOver2) && (pointNorth.y <= sideOver2);
  if (northGood && !visited[pointNorth.x][pointNorth.y]) {
    visitables.push_back(pointNorth);
  }
  bool southGood = (pointSouth.x >= -sideOver2) && (pointSouth.x <= sideOver2) && (pointSouth.y >= -sideOver2) && (pointSouth.y <= sideOver2);
  if (southGood && !visited[pointSouth.x][pointSouth.y]) {
    visitables.push_back(pointSouth);
  }
  bool westGood = (pointWest.x >= -sideOver2) && (pointWest.x <= sideOver2) && (pointWest.y >= -sideOver2) && (pointWest.y <= sideOver2);
  if (westGood && !visited[pointWest.x][pointWest.y]) {
    visitables.push_back(pointWest);
  }
  bool eastGood = (pointEast.x >= -sideOver2) && (pointEast.x <= sideOver2) && (pointEast.y >= -sideOver2) && (pointEast.y <= sideOver2);
  if (eastGood && !visited[pointEast.x][pointEast.y]) {
    visitables.push_back(pointEast);
  }
  return visitables;
}
