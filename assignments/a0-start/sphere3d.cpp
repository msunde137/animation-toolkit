#include "atkui/framework.h"

using glm::vec3;

class Sphere3D : public atkui::Framework {
public:
    Sphere3D() : atkui::Framework(atkui::Perspective) {
    }

    virtual void scene() {
        update();
        // colors are RGB triplets in range [0,1]
        setColor(vec3(0,1,0));

        // draw a sphere at center of the world
        float radius = 50.0;
        drawSphere(spherePos, radius);
    }

    void update() {
        float deltaTime = atkui::Framework::dt();
        if (atkui::Framework::keyIsDown(GLFW_KEY_SPACE))
        {
            if (space == false)
                randDir = agl::randomUnitSphere();
            space = true;
        }
        else space = false;

        spherePos += randDir * deltaTime * moveSpd;


        if (atkui::Framework::keyIsDown(GLFW_KEY_R))
        {
            spherePos = vec3(0);
            randDir = vec3(0);
        }
    }

private:
    vec3 spherePos = vec3(0, 50, 0);
    vec3 randDir = vec3(0);
    float moveSpd = 50;
    bool space = false;
};

int main(int argc, char** argv)
{
  Sphere3D viewer;
  viewer.run();
  return 0;
}
