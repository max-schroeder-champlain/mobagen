#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();
  float count = 0;
  for (auto i : neighborhood) {
    //get velocity of all neighbors
    averageVelocity += i->getVelocity();
    count++;
  }
  if (count == 0) {
    return Vector2f::zero();
  }
  averageVelocity /= count; //get average
  return averageVelocity* weight; // multiply by weight
  //normalizing causes boids to jitter?
}