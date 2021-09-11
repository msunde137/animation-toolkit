#include "atkui/framework.h"

using namespace glm;

class Look : public atkui::Framework {
 public:
  Look() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    _mouseX = width() * 0.5;
    _mouseY = height() * 0.5;
  }

  virtual void scene() {
    if (atkui::Framework::mouseIsDown(GLFW_MOUSE_BUTTON_1))
    {
        vec2 mousePos = atkui::Framework::mousePosition();
        mouseMove(mousePos.x, mousePos.y);
    }

    vec3 target = vec3(_mouseX, _mouseY, 0);
    setColor(vec3(1,0,0));
    drawSphere(target, 5);



    float width = (float)atkui::Framework::width() / 2.0f;
    float height = (float)atkui::Framework::height() / 2.0f;
    float dt = atkui::Framework::dt();

    setColor(vec3(1, 1, 1));

    vec3 posL = vec3(-120, 0, 0) + vec3(width, height, 0);
    vec3 posR = vec3(120, 0, 0) + vec3(width, height, 0);
    offsetL = glm::normalize(target - posL) * 40.0f;
    offsetR = glm::normalize(target - posR) * 40.0f;

    drawSphere(vec3(-120, 0, -150) + vec3(width, height, 0), 100);
    drawSphere(vec3(120, 0, -150) + vec3(width, height, 0), 100);

    setColor(vec3(0, 0, 0));

    drawSphere(posL + offsetL, 20);
    drawSphere(posR + offsetR, 20);
  }

  void mouseMove(int x, int y) {
    _mouseX = x;
    _mouseY = height() - y;
  }


 private:
    vec3 offsetL;
    vec3 offsetR;
    int _mouseX;
    int _mouseY;
};

int main(int argc, char** argv) {
  Look viewer;
  viewer.run();
  return 0;
}
