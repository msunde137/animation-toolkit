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
      Joint* body = new Joint("Body");
      body->setLocalTranslation(vec3(1,2,1)*100.0f);
      body->setLocalRotation(glm::angleAxis(glm::radians<float>(45.0f), vec3(0,1,0)));
      skeleton.addJoint(body);

      Joint* lwing = new Joint("LWing");
      lwing->setLocalTranslation(vec3(0));
      skeleton.addJoint(lwing, body);

      Joint* rwing = new Joint("RWing");
      rwing->setLocalTranslation(vec3(0));
      skeleton.addJoint(rwing, body);

      Joint* lwing2 = new Joint("LWing2");
      lwing2->setLocalTranslation(vec3(-210, 0, 0));
      skeleton.addJoint(lwing2, lwing);

      Joint* rwing2 = new Joint("RWing2");
      rwing2->setLocalTranslation(vec3(210,0,0));
      skeleton.addJoint(rwing2, rwing);

      skeleton.fk();
   }

   void scene() {
      Joint* body = skeleton.getByName("Body");
      Joint* lwing = skeleton.getByName("LWing");
      lwing->setLocalRotation(glm::angleAxis(sin(elapsedTime()), vec3(0,0,1)));

      Joint* rwing = skeleton.getByName("RWing");
      rwing->setLocalRotation(glm::angleAxis(-sin(elapsedTime()), vec3(0,0,1))); 

      Joint* lwing2 = skeleton.getByName("LWing2");
      lwing2->setLocalRotation(glm::angleAxis(sin(elapsedTime() - 1), vec3(0, 0, 1)));

      Joint* rwing2 = skeleton.getByName("RWing2");
      rwing2->setLocalRotation(glm::angleAxis(-sin(elapsedTime() - 1), vec3(0, 0, 1)));
      skeleton.fk();

      // attach geometry to skeleton 
      Transform B = body->getLocal2Global(); 
      Transform LT = lwing->getLocal2Global(); 
      Transform RT = rwing->getLocal2Global(); 
      Transform LT2 = lwing2->getLocal2Global();
      Transform RT2 = rwing2->getLocal2Global();

      // draw body
      Transform bodyGeometry(
         glm::angleAxis(glm::pi<float>()*0.5f, vec3(1,0,0)), // rotation
         vec3(0), vec3(25, 200, 25)); // position, scale
      body->setLocalRotation(glm::angleAxis(elapsedTime(), vec3(0, 1, 0)));
      body->setLocalTranslation(vec3(-cos(elapsedTime()), 0, sin(elapsedTime())) * 200.0f);

      Transform lwingGeometry(
         eulerAngleRO(XYZ, vec3(0,0,0)),
         vec3(-100,0,0), 
         vec3(120,20,200));

      Transform rwingGeometry(
         eulerAngleRO(XYZ, vec3(0,0,0)),
         vec3(100,0,0), 
         vec3(120,20,200));

      setColor(vec3(0.4, 0.4, 0.8));
      push();
      transform(B * bodyGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(vec3(0.8, 0, 0.0));
      push();
      transform(LT * lwingGeometry);
      drawSphere(vec3(0), 1);
      pop();

      push();
      transform(LT2 * lwingGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(vec3(0, 0.8, 0.0));
      push();
      transform(RT * rwingGeometry);
      drawSphere(vec3(0), 1);
      pop();
      

      push();
      transform(RT2 * rwingGeometry);
      drawSphere(vec3(0), 1);
      pop();

   }

private:
   Skeleton skeleton;
};


int main(int argc, char** argv) {
   Butterfly viewer;
   viewer.run();
}
