#include "atkui/framework.h"
#include "atk/toolkit.h"
#include <string>
using namespace atk;
using glm::vec3;

class Tentacle : public atkui::Framework {
public:
   Tentacle() : atkui::Framework(atkui::Perspective) {}
   virtual ~Tentacle() {}

   virtual void setup() {
      lookAt(vec3(200), vec3(0));

      Joint* root  = new Joint("root");
      root->setLocalTranslation(vec3(0,0,0));
      _tentacle.addJoint(root);

      // todo: add more joints
      Joint* last = root;
      for (int i = 0; i < 6; i++)
      {
          Joint* j = new Joint("joint" + std::to_string(i));
          j->setLocalTranslation(vec3(0, 50, 0));
          _tentacle.addJoint(j, last);
          last = j;
      }
      _tentacle.fk(); // compute local2global transforms
   }

   virtual void scene()
   {
      // todo animate joints
      // hint: use glm::angleAxis(...) to compute quaternions for each joint
      // todo: loop over all joints and draw

      for (int i = 1; i < _tentacle.getNumJoints(); i++)
      {
          Joint* j = _tentacle.getByID(i);
          Joint* p = j->getParent();

          glm::quat q1 = p->getLocalRotation();
          angle += Framework::dt() * .2;
          glm::quat q2 = glm::angleAxis(
              std::sin(angle + i) * (float)std::_Pi / 4.0f,
              vec3(0, 0, 1));
          p->setLocalRotation(q2);
          
          drawEllipsoid(p->getGlobalTranslation(), j->getGlobalTranslation(), 5);
      }

      //Joint* j = _tentacle.getByID(1);
      //Joint* p = j->getParent();
      //angle += Framework::dt();
      //glm::quat q2 = glm::angleAxis(angle, vec3(0, 0, 1));
      //p->setLocalRotation(q2);
      //std::cout << j->getLocalRotation() << std::endl;
      _tentacle.fk(); // computes local2global transforms

      //drawEllipsoid(p->getGlobalTranslation(), j->getGlobalTranslation(), 5);


      setColor(vec3(0,1,0));

   }

protected:
   Skeleton _tentacle;
   float angle = 0.0f;
};

int main(int argc, char** argv)
{
   Tentacle viewer;
   viewer.run();
} 

