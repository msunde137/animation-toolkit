#include "atkui/framework.h"
using namespace glm;

class Screensaver : public atkui::Framework {
 public:
  Screensaver() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
  }

  void scene() {
  }
};

int main(int argc, char** argv) {
  Screensaver viewer;
  viewer.run();
}

