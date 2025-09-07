#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;
  Vector2f centerMass = {0,0};
  float count = 0;
  float radius = boid->getDetectionRadius();
  // todo: add your code here to make a force towards the center of mass
  for (auto i : neighborhood) {
    // ensure current boid isn't counted
    if (i != boid) {
      //add boid position to center mass and increment count
      centerMass += i->getPosition();
      count++;
    }
  }
  //If three is no one nearby
  if (count<=0) {
    return {0,0};
  }

  cohesionForce = centerMass/count; //average
  cohesionForce -= boid->getPosition(); //get distance
  cohesionForce = cohesionForce.normalized(); //normalize
  return cohesionForce * weight; // return force times the weight
}