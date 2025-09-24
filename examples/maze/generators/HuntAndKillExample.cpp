#include "HuntAndKillExample.h"
#include "../World.h"
#include "Random.h"
#include <climits>
bool HuntAndKillExample::Step(World* w) {
  if (stack.empty()) {
    stack.push_back(randomStartPoint(w));
    w->SetNodeColor(stack.back(), Color::Blue);
    if (getVisitables(w, stack.back()).empty()) {
      w->SetNodeColor(stack.back(), Color::Black);
      stack.pop_back();
      return true;
    }
    visited[stack.back().x][stack.back().y] = true;
    std::vector<Point2D> visitables = getVisitedNeighbors(w, stack.back());
    if (visitables.size() == 0)
      visitables = getVisitables(w, stack.back());
    Point2D neighbor;
    if (visitables.size() != 1) {
      Random random;
      int num = random.Range(0, visitables.size()-1);
      neighbor = visitables[num];
    }
    else if (visitables.size() == 1) {
      neighbor = visitables.front();
    }
    if (neighbor == stack.back().Up()) {
      w->SetNorth(stack.back(), false);
    }
    else if (neighbor == stack.back().Down()) {
      w->SetSouth(stack.back(), false);
    }
    else if (neighbor == stack.back().Left()) {
      w->SetWest(stack.back(), false);
    }
    else if (neighbor == stack.back().Right()) {
      w->SetEast(stack.back(), false);
    }
    stack.pop_back();
    stack.push_back(neighbor);
    return true;
  }
  else {
    w->SetNodeColor(stack.back(), Color::Blue);
    visited[stack.back().x][stack.back().y] = true;
    std::vector<Point2D> visitables = getVisitables(w, stack.back());
    if (visitables.empty()) {
      w->SetNodeColor(stack.back(), Color::Black);
      //finished[stack.back().x][stack.back().y] = true;
      stack.pop_back();
      return true;
    }
    Point2D neighbor = visitables.front();
    if (visitables.size() != 1) {
      Random random;
      int num = random.Range(0, visitables.size()-1);
      neighbor = visitables[num];
    }
    if (neighbor == stack.back().Up()) {
      w->SetNorth(stack.back(), false);
    }
    else if (neighbor == stack.back().Down()) {
      w->SetSouth(stack.back(), false);
    }
    else if (neighbor == stack.back().Left()) {
      w->SetWest(stack.back(), false);
    }
    else if (neighbor == stack.back().Right()) {
      w->SetEast(stack.back(), false);
    }
    stack.pop_back();
    stack.push_back(neighbor);
    return true;
  }
  return false;
}
void HuntAndKillExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}
Point2D HuntAndKillExample::randomStartPoint(World* world) {
  // Todo: improve this if you want
  auto sideOver2 = world->GetSize() / 2;

  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[x][y]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> HuntAndKillExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  Point2D pointNorth = p.Up();
  Point2D pointSouth = p.Down();
  Point2D pointWest = p.Left();
  Point2D pointEast = p.Right();
  bool northGood = (pointNorth.y >= -sideOver2);
  if (northGood && !visited[pointNorth.x][pointNorth.y]) {
    visitables.push_back(pointNorth);
  }
  bool southGood =(pointSouth.y <= sideOver2);
  if (southGood && !visited[pointSouth.x][pointSouth.y]) {
    visitables.push_back(pointSouth);
  }
  bool westGood = (pointWest.x >= -sideOver2);
  if (westGood && !visited[pointWest.x][pointWest.y]) {
    visitables.push_back(pointWest);
  }
  bool eastGood =(pointEast.x <= sideOver2);
  if (eastGood && !visited[pointEast.x][pointEast.y]) {
    visitables.push_back(pointEast);
  }
  return visitables;
}
std::vector<Point2D> HuntAndKillExample::getVisitedNeighbors(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitedNeighbors;

  Point2D pointNorth = p.Up();
  Point2D pointSouth = p.Down();
  Point2D pointWest = p.Left();
  Point2D pointEast = p.Right();
  bool northGood = (pointNorth.y >= -sideOver2);
  if (northGood && visited[pointNorth.x][pointNorth.y]) {
    visitedNeighbors.push_back(pointNorth);
  }
  bool southGood =(pointSouth.y <= sideOver2);
  if (southGood && visited[pointSouth.x][pointSouth.y]) {
    visitedNeighbors.push_back(pointSouth);
  }
  bool westGood = (pointWest.x >= -sideOver2);
  if (westGood && visited[pointWest.x][pointWest.y]) {
    visitedNeighbors.push_back(pointWest);
  }
  bool eastGood =(pointEast.x <= sideOver2);
  if (eastGood && visited[pointEast.x][pointEast.y]) {
    visitedNeighbors.push_back(pointEast);
  }
  return visitedNeighbors;
}

std::vector<Point2D> HuntAndKillExample::getNeighbors(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> neighbors;

  Point2D pointNorth = p.Up();
  Point2D pointSouth = p.Down();
  Point2D pointWest = p.Left();
  Point2D pointEast = p.Right();
  bool northGood = (pointNorth.y >= -sideOver2);
  if (northGood) {
    neighbors.push_back(pointNorth);
  }
  bool southGood =(pointSouth.y <= sideOver2);
  if (southGood) {
    neighbors.push_back(pointSouth);
  }
  bool westGood = (pointWest.x >= -sideOver2);
  if (westGood) {
    neighbors.push_back(pointWest);
  }
  bool eastGood =(pointEast.x <= sideOver2);
  if (eastGood) {
    neighbors.push_back(pointEast);
  }
  return neighbors;
}
