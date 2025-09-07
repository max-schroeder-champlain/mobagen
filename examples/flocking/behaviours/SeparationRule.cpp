#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f separatingForce = Vector2f::zero();
  if (!neighborhood.empty()) {
    Vector2f pos = boid->getPosition();

    for (auto i : neighborhood) {
      if (i != boid) {
        //get magnitude and hat
        Vector2f distance = i->getPosition() - pos;
        float mag = distance.getMagnitude();
        Vector2f hat = distance/mag;
        if (mag <= desiredMinimalDistance) {
          //divide the hat by the magnitude and make it relative to the radius
          separatingForce += (hat*weight)/(mag*desiredMinimalDistance);
        }
      }
    }
  }
  //normalize
  separatingForce = Vector2f::normalized(separatingForce);
  separatingForce *= -weight; // Multiply weight and inverse

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
