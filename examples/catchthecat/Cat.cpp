#include "Cat.h"
#include "World.h"
#include <stdexcept>
using namespace std;
Point2D Cat::Move(World* world) {
  vector<Point2D> path =  generatePath(world);
  return path.back();
}
