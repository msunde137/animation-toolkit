#include "atkui/framework.h"

using glm::vec3;

class Sphere3D : public atkui::Framework {
 public:
  Sphere3D() : atkui::Framework(atkui::Perspective) {
  }

  virtual void setup() {
    red = vec3(1,0,0);
    green = vec3(0,1,0);
    t = 0;
  }

  virtual void scene() {
    //t += dt(); // can also use elapsedTime 

    float duration = 8.0f;
    t = elapsedTime()/duration;
    t = glm::clamp(t, 0.0f, 1.0f); // clamp to range [0,1]

    vec3 c = red * (1 - t) + green * t;
    setColor(c);

    // draw a sphere at center of the world
    float radius = 100.0;
    drawSphere(vec3(0), radius);
  }

  float t;
  vec3 red;
  vec3 green;
};

int main(int argc, char** argv)
{
  Sphere3D viewer;
  viewer.run();
  return 0;
}
