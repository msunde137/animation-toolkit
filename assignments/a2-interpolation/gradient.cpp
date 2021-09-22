#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class Gradient : public atkui::Framework {
 public:
  Gradient() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void scene() {
  }
};

int main(int argc, char **argv) {
  Gradient viewer;
  viewer.run();
}
