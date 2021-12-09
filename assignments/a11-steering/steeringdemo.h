#ifndef STEERINGDEMO_H_
#define STEERINGDEMO_H_

#include "atkui/framework.h"
#include "steerable.h"
#include "behaviors.h"

class ASteeringDemo : public atkui::Framework
{
public:
   ASteeringDemo();
   virtual ~ASteeringDemo();

   virtual void setup();
   virtual void scene();
   virtual void onInitializeGui();
   virtual void keyUp(int key, int mods);
   virtual void mouseUp(int button, int mods);
   virtual void mouseMotion(int x, int y, int dx, int dy);
   virtual void reset();

protected:
   ASteerable _character;
   ASeek _behavior;
   glm::vec3 _target;

   // UI
   int _modifierState;
};

#endif