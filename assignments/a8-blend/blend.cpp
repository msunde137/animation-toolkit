#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace atkui;
using namespace glm;

class ABlend : public atkui::Framework
{
public:
   ABlend() : atkui::Framework(atkui::Perspective) {}
   virtual ~ABlend() {}

   void setup()
   {
      _alpha = 0.5;
      BVHReader reader;
      reader.load("../motions/Beta/left_strafe_walking.bvh", _skeleton, _motion1);
      reader.load("../motions/Beta/walking.bvh", _skeleton, _motion2);

      _blend = blend(_motion1, _motion2, _alpha);
   }

   Motion blend(const Motion& m1, const Motion& m2, double alpha)
   {
      Motion blend;
      blend.setFramerate(m1.getFramerate());

      // todo: replace the following line with your code
      blend.appendKey(m1.getKey(0)); // placeholder
      return blend;
   }

   void scene()
   {  
      drawMotion(_motion2, vec3(-150,0,0));
      drawMotion(_motion1, vec3(150,0,0));
      drawMotion(_blend, vec3(0,0,0));
      drawText(std::to_string(_alpha), 10, 15);
   }

   void drawMotion(const Motion& m, const vec3& offset)
   {
      double t = elapsedTime() * 0.5;
      double time = m.getNormalizedDuration(t) * m.getDuration();
      m.update(_skeleton, time, false);

      SkeletonDrawer drawer;
      drawer.pos = offset;
      drawer.draw(_skeleton, *this);
   }

   void keyUp(int key, int mods) 
   {
      if (key == GLFW_KEY_UP)
      {
         _alpha = std::min(_alpha+0.05, 1.0);
         _blend = blend(_motion1, _motion2, _alpha);
      }
      else if (key == GLFW_KEY_DOWN)
      {
         _alpha = std::max(_alpha-0.05, 0.0);
         _blend = blend(_motion1, _motion2, _alpha);
      }
   }

protected:
   Skeleton _skeleton;
   Motion _blend;
   Motion _motion1;
   Motion _motion2;
   double _alpha;
};

int main(int argc, char** argv)
{
   ABlend viewer;
   viewer.run();
   return 0;
}

