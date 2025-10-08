#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
#include "../../cmake-build-debug/_deps/glm-src/glm/detail/type_vec3.hpp"
using namespace std;

vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
  vector<Point2D> path;
  unordered_map<Point2D, int> costSoFar;
  // bootstrap state
  //optimal route to get cat out. For cat return direction to move, for hunter return where they should place
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  costSoFar[catPos] = 0;
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points
//find closest border
  while (!frontier.empty()) {
    Point2D current = frontier.front();
    frontier.pop();
    frontierSet.erase(current);
    visited[current] = true;
    vector<Point2D> neighbors = getVisitableNeighbors(w, current, visited, frontierSet);
    for (int i = 0; i < neighbors.size(); i++) {
      cameFrom.insert({neighbors[i], current});
      frontier.push(neighbors[i]);
      frontierSet.insert(neighbors[i]);
      costSoFar[neighbors[i]] = costSoFar[current] + 1;
      if (w->catWinsOnSpace(neighbors[i])) {
        borderExit = neighbors[i];
        path.push_back(borderExit);
        break;
      }
    }
    if (path.size() > 0) {
      while (path.back() != catPos)
      {
        path.push_back(cameFrom.at(path.back()));
      }
      if (path.back() == catPos) {
        path.pop_back();
        return path;
      }
    }

  }
  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

float Agent::ManhatatanDistance(Point2D a, Point2D b){
  return abs(a.x - b.x) + abs(a.y - b.y);
}
int Agent::Heuristic(Point2D& p, int sideSizeOver2) {
  int x = abs(p.x), y = abs(p.y);
  return std::min(sideSizeOver2 - x, sideSizeOver2 - y);
}

std::vector<Point2D> Agent::getVisitableNeighbors(World* w, Point2D p, std::unordered_map<Point2D, bool>& visited, std::unordered_set<Point2D> frontierSet) {
  vector<Point2D> neighbors;
  for (int x = -1; x<= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      if (x == 0 && y == 0)
        continue;
      Point2D temp = Point2D(p.x+x, p.y+y);
      int tempX = x;
      int tempY = y;
      if (p.y % 2 == 0) {
        tempX++;
      }
      if (!w->catcherCanMoveToPosition(temp))  continue;
      if (w->getContent(temp)) continue;
      if (visited[temp]) continue;
      if (y != 0) {
        if (tempX == 0 || tempX == 1) {}
        else continue;

      }
      if (frontierSet.contains(temp)) continue;
      neighbors.push_back(temp);
    }
  }
  return neighbors;
}

std:: vector<Point2D> Agent::getBorderPoints(World* w, Point2D p) {
  vector<Point2D> neighbors;
  for (int x = -1; x<= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      if (x == 0 && y == 0)
        continue;
      //if even add one to x
      //if y != 0 then if tempx = 0  or tempy = 1 keep going else skip
      Point2D temp = Point2D(p.x+x, p.y+y);
      int tempX = x;
      int tempY = y;
      if (p.y % 2 == 0) {
        tempX++;
      }
      if (y != 0) {
        if (tempX == 0 || tempX == 1) {}
        else
          continue;
      }
      if (w->catWinsOnSpace(temp) && !w->getContent(temp))
        neighbors.push_back(temp);
    }
  }
  return neighbors;
}
vector<Point2D> Agent::catValidNeighbors(World* w) {
  auto catPos = w->getCat();
  vector<Point2D> neighbors;
  for (int x = -1; x<= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      if (x == 0 && y == 0)
        continue;
      //if even add one to x
      //if y != 0 then if tempx = 0  or tempy = 1 keep going else skip
      Point2D temp = Point2D(catPos.x+x, catPos.y+y);
      int tempX = x;
      int tempY = y;
      if (catPos.y % 2 == 0) {
        tempX++;
      }
      if (y != 0) {
        if (tempX == 0 || tempX == 1) {}
        else
          continue;
      }
      if (w->catCanMoveToPosition(temp) && !w->getContent(temp))
        neighbors.push_back(temp);
    }
  }
  return neighbors;
}
