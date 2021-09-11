#include "atkui/framework.h"

using namespace glm;
class Eyes : public atkui::Framework
{
  public:
    Eyes() : atkui::Framework(atkui::Orthographic) {
        offset = vec3(0);
        theta = 0;
        range = 40;
        speed = 1.5;
    }

    virtual void scene() {
        float width = (float)atkui::Framework::width() / 2.0f;
        float height = (float)atkui::Framework::height() / 2.0f;
        float dt = atkui::Framework::dt();

        offset = vec3(sin(theta) * range, 0, 0);
        theta += dt * speed;

        setColor(vec3(1, 1, 1));

        drawSphere(vec3(-120, 0, -150) + vec3(width, height, 0), 100);
        drawSphere(vec3(120, 0, -150) + vec3(width, height, 0), 100);

        setColor(vec3(0, 0, 0));

        drawSphere(vec3(-120, 0, 0) + vec3(width, height, 0) + offset, 20);
        drawSphere(vec3(120, 0, 0) + vec3(width, height, 0) + offset, 20);
    }

private:
    vec3 offset;
    float theta;
    float range;
    float speed;
};

int main(int argc, char** argv) {
  Eyes viewer;
  viewer.run();
  return 0;
}
