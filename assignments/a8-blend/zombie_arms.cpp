#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>

using namespace glm;
using namespace atk;
using namespace atkui;

class AZombieArms : public atkui::Framework {
public:
   AZombieArms() : atkui::Framework(atkui::Perspective) {}
   virtual ~AZombieArms() {}

   void setup() {
      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _original);

      _zombieFreeze = ComputeArmFreeze(_original);
      _zombieOffset = ComputeArmOffset(_original);
   }

   Motion ComputeArmFreeze(const Motion& motion) {
      quat leftLocalRot = eulerAngleRO(XYZ, radians(vec3(-53, -88, -33)));
      quat rightLocalRot = eulerAngleRO(XYZ, radians(vec3(14, 88, -33)));
      quat leftElbowLocalRot = eulerAngleRO(XYZ, radians(vec3(0, -23, 0)));
      quat rightElbowLocalRot = eulerAngleRO(XYZ, radians(vec3(0, 23, 0)));

      Joint* leftArm = _skeleton.getByName("Beta:LeftArm");
      Joint* rightArm = _skeleton.getByName("Beta:RightArm");

      Joint* leftElbow = _skeleton.getByName("Beta:LeftForeArm");
      Joint* rightElbow = _skeleton.getByName("Beta:RightForeArm");

      Motion result = motion;
      result.setFramerate(motion.getFramerate());
      
      for (int i = 0; i < result.getNumKeys(); i++)
      {
          Pose p = result.getKey(i);
          p.jointRots[leftArm->getID()] = leftLocalRot;
          p.jointRots[rightArm->getID()] = rightLocalRot;
          p.jointRots[leftElbow->getID()] = leftElbowLocalRot;
          p.jointRots[rightElbow->getID()] = rightElbowLocalRot;
          result.editKey(i, p);
      }

      return result;
   }

   Motion ComputeArmOffset(const Motion& motion) {
      quat leftElbowRot = eulerAngleRO(XYZ, radians(vec3(0, -23, 0)));
      quat rightElbowRot = eulerAngleRO(XYZ, radians(vec3(0, 23, 0)));

      Joint* leftArm = _skeleton.getByName("Beta:LeftArm");
      Joint* rightArm = _skeleton.getByName("Beta:RightArm");

      Joint* leftElbow = _skeleton.getByName("Beta:LeftForeArm");
      Joint* rightElbow = _skeleton.getByName("Beta:RightForeArm");

      Motion result = motion;
      result.setFramerate(motion.getFramerate());
      int nk = result.getNumKeys();
      for (int i = 0; i < nk; i++)
      {
          float f = i / (float)nk * glm::pi<float>() * 2.0f;
          quat leftRot = eulerAngleRO(XYZ, radians(vec3(-53, -88, -33 + 30 * cos(f))));
          quat rightRot = eulerAngleRO(XYZ, radians(vec3(14, 88, -33 + 30 * cos(f))));

          Pose p = result.getKey(i);
          p.jointRots[leftArm->getID()] = leftRot;
          p.jointRots[rightArm->getID()] = rightRot;
          p.jointRots[leftElbow->getID()] = leftElbowRot;
          p.jointRots[rightElbow->getID()] = rightElbowRot;
          result.editKey(i, p);
      }

      return result;
   }

   void update() {
      double t =  elapsedTime() * 0.5;
      if (_currentMotion == 1) {
         _zombieFreeze.update(_skeleton, t);
         drawText("Joint edit type: freeze", 10, 15);

      } else if (_currentMotion == 2) {
         _zombieOffset.update(_skeleton, t);
         drawText("Joint edit type: offset", 10, 15);

      } else {
         _original.update(_skeleton, t);
         drawText("Joint edit type: none", 10, 15);
      }
   }

   void scene() {  
      update();
      _drawer.draw(_skeleton, *this);
   }

   void keyUp(int key, int mods) {
      if (key == '1') {
          _currentMotion = 1;
      } else if (key == '2') {
          _currentMotion = 2;
      } else if (key == '0') {
          _currentMotion = 0;
      }
   }

   SkeletonDrawer _drawer;
   Skeleton _skeleton;
   Motion _original;
   Motion _zombieFreeze;
   Motion _zombieOffset;
   int _currentMotion = 0;
};

int main(int argc, char** argv) {
   AZombieArms viewer;
   viewer.run();
   return 0;
}

