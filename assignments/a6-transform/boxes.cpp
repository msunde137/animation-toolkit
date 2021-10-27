#include "atkui/framework.h"
#include "atk/toolkit.h"

using atk::Transform;
using glm::quat;
using glm::vec3;

class StackingBoxes : public atkui::Framework
{
public:
   StackingBoxes() : atkui::Framework(atkui::Perspective) {}
   virtual ~StackingBoxes() {}

   void setup() {
      lookAt(vec3(150, 150, 150), vec3(0));
   }

   void scene()
   {
      // Question 1 - B1
      vec3 d10 = vec3(0);
      quat R10 = glm::angleAxis(0.f, vec3(1,0,0));
      Transform F10(R10, d10); // transform from frame 1 to world
      setColor(vec3(0,0.5,0));
      drawBox(F10);

      // Question 1 - B2
      vec3 d20 = vec3(0);
      quat R20 = glm::angleAxis(0.f, vec3(1,0,0));
      Transform F20(R20, d20); // transform from frame 2 to world
      setColor(vec3(0.5,0, 0.5));
      drawBox(F20);

      // Question 1 - B3
      vec3 d30 = vec3(0);
      quat R30 = glm::angleAxis(0.f, vec3(1,0,0));
      Transform F30(R30, d30); // transform from frame 3 to world
      setColor(vec3(0.0, 0.5,0.5));
      drawBox(F30);

      // Question 2
      Transform F21 = Transform::Identity; // transform from frame 2 to frame 1
      vec3 value = F21.transformPoint(vec3(0));
      if (!once) std::cout << "Position of b2 relative to b1 is " << value << std::endl;

      // Question 3
      Transform F32 = Transform::Identity; // transform from frame 3 to frame 2
      value = F32.transformPoint(vec3(0));
      if (!once) std::cout << "Position of b3 relative to b2 is " << value << std::endl;

      // Question 4
      // Compute a series of transforms that stack Box 2 onto Box 1
      Transform F = Transform::Identity;
      setColor(vec3(0.5, 0.5,0.5));
      drawBox(F * F20);

      once = true;
   }

   void drawBox(const Transform& xform)
   {
      vec3 size(3, 2, 1);
      vec3 halfSize(1.5, 1.0, -0.5);

      push();
      scale(vec3(10));
      transform(xform);
      translate(halfSize);
      drawCube(vec3(0), size);
      pop();

      vec3 pos = 10.0f * xform.t();
      setColor(vec3(1,0,0));
      drawLine(pos, pos + xform.transformVector(vec3(10,0,0)));

      setColor(vec3(0,1,0));
      drawLine(pos, pos + xform.transformVector(vec3(0,10,0)));

      setColor(vec3(0,0,1));
      drawLine(pos, pos + xform.transformVector(vec3(0,0,10)));
   }

private:
  bool once = false;
};

int main(int argc, char** argv)
{
   StackingBoxes viewer;
   viewer.run();
   return 0;
}
