#ifndef DEVIL_H_
#define DEVIL_H_

#include "atkui/framework.h"

using namespace atk;
using namespace glm;

class Devil
{
public:
   Devil() {}
   Devil(const vec3& p, const vec3& c, float s) {
      _pos = p;
      _size = vec3(s);
      _color = c;
   }
   virtual ~Devil() {}

   void draw(const Skeleton& skeleton, atkui::Framework& f) {

      f.push();
      f.translate(_pos);
      f.scale(_size);
      f.setColor(_color);

      float jointRadius = 15;
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;
         if (joint->getParent()->getName().find("Hand") != std::string::npos) continue; // skip hands

         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         f.drawEllipsoid(p1, p2, jointRadius);
         f.drawSphere(p2, jointRadius);
         f.drawSphere(p1, jointRadius);
      }

      Joint* head = skeleton.getByName("HeadTop_End");
      assert(head);

      // Use joint's global position and rotation to convert 
      // from local head coordinates to global coordinates
      Joint* pParent = head->getParent();
      Transform xform = pParent->getLocal2Global();

      float headLength = glm::distance(
         pParent->getGlobalTranslation(), 
         head->getGlobalTranslation());

      // eyes
      float pupilSize = jointRadius * 0.45;
      f.setColor(vec3(0));

      vec3 pupilPosL(jointRadius*0.3, headLength * 0.75, pupilSize); 
      f.drawSphere(xform.transformPoint(pupilPosL), pupilSize);

      vec3 pupilPosR(-jointRadius*0.3, headLength * 0.75, pupilSize); 
      f.drawSphere(xform.transformPoint(pupilPosR), pupilSize);

      // horns
      f.setColor(_color);
      float hs = jointRadius;
      vec3 hornPosL(jointRadius*0.25, 2*headLength, 0);
      mat3 hornRotL = eulerAngleRO(ZYX, glm::radians(vec3(-90, 0, -10)));

      f.push();
      f.transform(xform*Transform(hornRotL, hornPosL));
      f.scale(vec3(0.5*hs,0.5*hs,2*hs));
      f.drawCone(vec3(0), 1.0f);
      f.pop();

      vec3 hornPosR(-jointRadius*0.25, 2*headLength, 0);
      mat3 hornRotR = eulerAngleRO(ZYX, glm::radians(vec3(-90, 0, 10)));

      f.push();
      f.transform(xform*Transform(hornRotR, hornPosR));
      f.scale(vec3(0.5*hs,0.5*hs,2*hs));
      f.drawCone(vec3(0), 1.0f);
      f.pop();

      // pitch fork
      Joint* hand = skeleton.getByName("RightHand");
      assert(hand);
      xform = hand->getLocal2Global();

      hs = jointRadius*0.25;
      float len = 100;
      f.setColor(vec3(0,0,0));
      vec3 spearPos(0, 0, 0);
      mat3 spearRot = eulerAngleRO(ZYX, glm::radians(vec3(0, 0, 0)));

      f.push();
      f.transform(xform*Transform(spearRot, spearPos));
      f.scale(vec3(hs,hs,len));
      f.drawCylinder(vec3(0), 1.0f);
      f.pop();

      vec3 tipPos(0, 0, -len*0.5);
      mat3 tipRot = eulerAngleRO(ZYX, glm::radians(vec3(180, 0, 0)));
      f.push();
      f.transform(xform*Transform(tipRot, tipPos));
      f.scale(4.0f*vec3(hs,hs,hs*2.0f));
      f.drawCone(vec3(0), 1.0f);
      f.pop();

      f.pop();
   }

   virtual void keyUp(int key, int mods) {
      if (key == 'P') _paused = !_paused;
   }

protected:
   Motion _motion;
   Skeleton _skeleton;
   bool _paused = false;
   vec3 _color = vec3(1.0,0.0,0.0);
   vec3 _size = vec3(1.0);
   vec3 _pos = vec3(0);

};

#endif
