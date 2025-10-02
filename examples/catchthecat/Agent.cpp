#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  //optimal route to get cat out. For cat return direction to move, for hunter return where they should place
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points
//find closest border
  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
    Point2D current = frontier.front();
    frontierSet.erase(current);
    visited[current] = true;

  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

float Agent::ManhatatanDistance(Point2D a, Point2D b){
  return abs(a.x - b.x) + abs(a.y - b.y);

  //heuristic (input point2d, and int side/2)
  //int x = abs(point.x)  int y = abs(point.y)
  //return (

}
int Agent::Heuristic(Point2D& p, int sideSizeOver2) {
  int x = abs(p.x), y = abs(p.y);
  return std::min(sideSizeOver2 - x, sideSizeOver2 - y);
}

std:: vector<Point2D> getVisitableNeighbors(World* w, Point2D p) {

}
