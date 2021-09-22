#include "atkui/framework.h"
using namespace glm;

class ParticleCubic : public atkui::Framework {
 public:
  ParticleCubic() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
  }

  void scene() {
    setColor(vec3(1));
    drawSphere(vec3(250, 250, 0), 10);
  }
};

int main(int argc, char** argv) {
  ParticleCubic viewer;
  viewer.run();
}

