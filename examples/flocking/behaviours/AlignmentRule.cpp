#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();
  float count = 0;
  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood
  float radius = boid->getDetectionRadius();
  for (auto i : neighborhood) {
    Boid *currentBoid = i;
    averageVelocity += currentBoid->getVelocity();
    count++;
    currentBoid = nullptr;
  }
  if (count == 0) {
     return {0,0};
  }
  averageVelocity /= count;
  averageVelocity *= weight;
  //weighted average?
  //clamp to radius?
  return Vector2f::normalized(averageVelocity);
}