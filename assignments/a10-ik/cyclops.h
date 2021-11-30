#ifndef ACYCLOPS_H_
#define ACYCLOPS_H_

#include "atkui/skeleton_drawer.h"

class Cyclops : public atkui::SkeletonDrawer 
{
public:
	Cyclops() {}
	virtual ~Cyclops() {}
   virtual void draw(const atk::Skeleton& skeleton, atkui::Framework& f) {
      SkeletonDrawer::draw(skeleton, f);

      atk::Joint* head = skeleton.getByName("Beta:HeadSite");
      assert(head);

      atk::Joint* pParent = head->getParent();
      atk::Transform xform = pParent->getLocal2Global();

      // draw eyeball
      f.setColor(glm::vec3(1,1,1)); 
      glm::vec3 eyePos(0, 12, jointRadius * 0.25f);
      f.drawSphere(xform.transformPoint(eyePos), jointRadius);

      // draw pupil 
      f.setColor(glm::vec3(0,0,0));
      glm::vec3 pupilPos(0, 12, jointRadius * 0.7f);
      f.drawSphere(xform.transformPoint(pupilPos), 0.4f * jointRadius);
   }
};

#endif
