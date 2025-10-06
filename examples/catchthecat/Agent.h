#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;
  //Returns float cost
  float ManhatatanDistance(Point2D a, Point2D b);
  int Heuristic(Point2D& p, int sideSizeOver2);
  std:: vector<Point2D> getVisitableNeighbors(World* w, Point2D p, std::unordered_map<Point2D, bool>& visited, std::unordered_set<Point2D> frontierSet);
  std::vector<Point2D> generatePath(World* w);
  std::vector<Point2D> getBorderPoints(World * w, Point2D p);
};

#endif  // AGENT_H
