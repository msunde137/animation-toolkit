#include "atkui/framework.h"

using namespace glm;

class Particles : public atkui::Framework
{
 public:
  Particles() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
  }

  virtual void scene() {
  }
};

int main(int argc, char** argv) {
  Particles viewer;
  viewer.run();
  return 0;
}
