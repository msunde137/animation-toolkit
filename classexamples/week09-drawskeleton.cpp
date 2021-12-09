#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;

class Butterfly : public atkui::Framework
{
public:
   Butterfly() : atkui::Framework(atkui::Perspective) {
   }

   void setup() {
      BVHReader reader;
      reader.load("../motions/Beta/jump.bvh", skeleton, motion);
      motion.update(skeleton, 0);
   }


   void scene() {
      motion.update(skeleton, elapsedTime());

      setColor(vec3(0,0,0.8));
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;

         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         drawEllipsoid(p1, p2, 5);
      }
   }

private:
   Skeleton skeleton;
   Motion motion;
};


int main(int argc, char** argv) {
   Butterfly viewer;
   viewer.run();
}
