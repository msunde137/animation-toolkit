#include "atkui/framework.h"

using glm::vec3;

class Example : public atkui::Framework {
 public:
  Example() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
  }

  virtual void scene() {
      vec3 b0 = vec3(0, 0, 0);
      vec3 b1 = vec3(0.25 * width(), height(), 0);
      vec3 b2 = vec3(0.75 * width(), height(), 0);
      vec3 b3 = vec3(width(), 0, 0);
      setColor(vec3(1,1,0));
      drawLine(b0, b1);
      drawLine(b1, b2);
      drawLine(b2, b3);
  }
};

int main(int argc, char** argv)
{
  Example viewer;
  viewer.run();
  return 0;
}
