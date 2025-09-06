#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;
  Vector2f centerMass = {0,0};
  float count = 0;
  float radius = boid->getDetectionRadius();
  // todo: add your code here to make a force towards the center of mass
  for (auto i : neighborhood) {
    if (i != boid) {
      Boid currentBoid = *i;
      Vector2f distance = currentBoid.getPosition() - boid->getPosition();
      float mag = distance.getMagnitude();
      if (mag <= radius) {
        centerMass += currentBoid.getPosition();
        count++;
      }
    }
  }
  if (count<=0) {
    return {0,0};
  }
  cohesionForce = centerMass/count;
  cohesionForce -= boid->getPosition();
  cohesionForce *= weight;

  return cohesionForce;
}