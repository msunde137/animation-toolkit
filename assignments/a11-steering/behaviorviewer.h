#ifndef BEHAVIORVIEWER_H_
#define BEHAVIORVIEWER_H_

#include "atkui/framework.h"
#include "steerable.h"
#include "world.h"
#include "behaviors.h" 

class ABehaviorViewer : public atkui::Framework
{
public:
   ABehaviorViewer();
   virtual ~ABehaviorViewer();

   void setup();
   void update();
   void draw();

protected:

   void runGui();
   void keyUp(int key, int mods);
   void mouseUp(int button, int mods);
   void mouseMotion(int px, int py, int dx, int dy); 

   enum BehaviorType { 
      SEEK, 
      FLEE, 
      ARRIVAL, 
      DEPARTURE, 
      AVOID, 
      WANDER, 
      ALIGNMENT, 
      SEPARATION, 
      COHESION, 
      FLOCKING, 
      LEADER } 
   _beType;

   virtual void setBehavior(BehaviorType type);
   virtual void reset(int numCharacters, int numObstacles);

protected:
   AWorld _world;
   glm::vec3 _target;
   int _numAgents;
   int _numObstacles;

   // Behaviors
   typedef std::map<BehaviorType, ABehavior*> BehaviorMap;
   typedef std::map<BehaviorType, ABehavior*>::iterator BehaviorIt;
   BehaviorMap _behaviors;

   // GUI
   bool _paused = false;
   std::map<BehaviorType,std::map<std::string,float>> _uiParams;
};

#endif