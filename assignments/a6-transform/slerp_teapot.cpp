#include "atkui/framework.h"
#include "atkmath/quaternion.h"
#include "atkmath/vector3.h"
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>

using atkmath::Quaternion;
using atkmath::Vector3;

class ASlerpTeapot : public atkui::Framework
{
public:
    ASlerpTeapot() : atkui::Framework(atkui::Orthographic) {}
    virtual ~ASlerpTeapot() {}

protected:

    virtual void setup()
    {
       Quaternion q0, q1, q2;
       q0.fromAxisAngle(Vector3(0, 0, 1),  60 * atkmath::Deg2Rad);
       q1.fromAxisAngle(Vector3(0, 0, 1), -200 * atkmath::Deg2Rad);
       q2.fromAxisAngle(Vector3(0, 1, 0),  90 * atkmath::Deg2Rad);
       mKeys.push_back(q0);
       mKeys.push_back(q1);
       mKeys.push_back(q2);
       mKeys.push_back(q0);

       ortho(-3, 3, -3, 3, 0.01, 100);
       lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    }

    Quaternion getValue(float t)
    {
      float duration = 9;
      float frac = fmod(t, duration);
      int segment1 = glm::clamp((int) glm::floor(frac/3.0), 0, 12); // each key is 3s apart
      int segment2 = (segment1 + 1) % 4; 
      float u = (frac - segment1*3.0f)/3.0f;

      int y = 25;
      int th = renderer.textHeight() + 5; 

      drawText("time: "+std::to_string(t), 5, y);
      drawText("time % duration: "+std::to_string(frac), 5, y + th);
      drawText("Segment: "+std::to_string(segment1), 5, y + th*2);
      drawText("u: "+std::to_string(u), 5, y + th*3);

      Quaternion q0 = mKeys[segment1];
      Quaternion q1 = mKeys[segment2];
      return Quaternion::Slerp(q0, q1, u); 
    }

    virtual void scene()
    {
       renderer.beginShader("phong");
       Quaternion q = getValue(elapsedTime());
       double angle;
       Vector3 axis;
       q.toAxisAngle(axis, angle);

       setColor(glm::vec3(1, 1, 0));
       push();
       rotate(angle, glm::vec3(axis[0], axis[1], axis[2]));
       drawTeapot(glm::vec3(0), 4.25);
       pop();
       renderer.endShader();
    }

    std::vector<Quaternion> mKeys;
};

int main(int argc, char** argv)
{
   ASlerpTeapot viewer;
   viewer.run();
}

