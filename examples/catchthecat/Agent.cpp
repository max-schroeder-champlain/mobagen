#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<Point2DPrioritized> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
  vector<Point2D> path;
  unordered_map<Point2D, int> costSoFar;
  int sideOver2 = w->getWorldSideSize() / 2.0f;

  // bootstrap state
  auto catPos = w->getCat();
  Point2DPrioritized prioritizedCatPos = Point2DPrioritized(catPos, Heuristic(catPos, sideOver2));
  frontier.push(prioritizedCatPos);
  frontierSet.insert(catPos);
  costSoFar[catPos] = prioritizedCatPos.priority;
  Point2D borderExit = Point2D::INFINITE;

  while (!frontier.empty()) {

    Point2D current = frontier.top().position;
    frontier.pop();
    frontierSet.erase(current);
    visited[current] = true;

    vector<Point2D> neighbors = getVisitableNeighbors(w, current, visited, frontierSet);
    for (int i = 0; i < neighbors.size(); i++) {
      int newCost = costSoFar[current] + 1;
      if (costSoFar[neighbors[i]] == NULL || newCost < costSoFar[neighbors[i]]) {
        frontier.push(Point2DPrioritized(neighbors[i], Heuristic(neighbors[i], sideOver2) + newCost));
        frontierSet.insert(neighbors[i]);
        costSoFar[neighbors[i]] = costSoFar[current] + Heuristic(neighbors[i], sideOver2);
        cameFrom.insert({neighbors[i], current});
      }
      if (w->catWinsOnSpace(neighbors[i])) {
        if (borderExit == Point2D::INFINITE) {
          borderExit = neighbors[i];
          path.push_back(borderExit);
        }
        else if (ManhatatanDistance(catPos, borderExit) > ManhatatanDistance(catPos, neighbors[i])) {
          path.pop_back();
          borderExit = neighbors[i];
          path.push_back(borderExit);
        }
      }
    }

    if (path.size() > 0) {
      while (path.back() != catPos){
        path.push_back(cameFrom.at(path.back()));
      }
      if (path.back() == catPos) {
        path.pop_back();
        return path;
      }
    }

  }
  return vector<Point2D>();
}

float Agent::ManhatatanDistance(Point2D a, Point2D b){
  return abs(a.x - b.x) + abs(a.y - b.y);
}
int Agent::Heuristic(Point2D& p, int sideSizeOver2) {
  int x = abs(p.x), y = abs(p.y);
  return sideSizeOver2 - max(x,y);
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
      //if (visited[temp]) continue;
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
