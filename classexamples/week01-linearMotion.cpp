#include "atkui/framework.cpp"

using glm::vec3;

class Example : public atkui::Framework {
 public:
  Example() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
     currentPos = vec3(0, 1, -4);
     vel = 100.0f * vec3(1, 3, 4);
  }

  virtual void scene() {
    // update position based on time
    currentPos = currentPos + vel * elapsedTime();

    // colors are RGB triplets in range [0,1]
    setColor(vec3(0,1,0));

    // draw a sphere at center of screen
    double radius = 100; 
    drawSphere(currentPos, radius);
  }
  vec3 currentPos;
  vec3 vel;
};

int main(int argc, char** argv) {
  Example example;
  example.run();
}