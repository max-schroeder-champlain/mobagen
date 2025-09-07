#include "MouseInfluenceRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f MouseInfluenceRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  ImGuiIO& io = ImGui::GetIO();
  Vector2f vectorForce = {0,0};
  const float additionalForce = 25;
  //check if mouse 1 is pressed
  if (ImGui::IsMousePosValid() && io.MouseDown[0]) {
    //get mouse position
    Vector2f mousePos(io.MousePos.x, io.MousePos.y);
    //find distance and magnitude between current boid and mousePos
    Vector2f distance = mousePos - boid->getPosition();
    float mag = distance.getMagnitude();
    //make sure to not divide by zero
    if (mag != 0) {
      //get hat
      Vector2f hat = distance/mag;
      if (isRepulsive) {
        //multiply hat by the additional force
        vectorForce = (additionalForce*hat);
        //multiple again but negative to inverse
        vectorForce *= -additionalForce;
      }
      else {
        // pull together like cohesion
        vectorForce = distance * additionalForce;
      }
    }
  }
    return vectorForce * weight;
}

bool MouseInfluenceRule::drawImguiRuleExtra() {
  bool valueHasChanged = false;

  if (ImGui::RadioButton("Attractive", !isRepulsive)) {
    isRepulsive = false;
    valueHasChanged = true;
  }

  ImGui::SameLine();
  if (ImGui::RadioButton("Repulsive", isRepulsive)) {
    isRepulsive = true;
    valueHasChanged = true;
  }

  return valueHasChanged;
}