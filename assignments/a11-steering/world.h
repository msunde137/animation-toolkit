#ifndef WORLD_H_
#define WORLD_H_

#include "atk/toolkit.h"
#include "steerable.h"
#include "obstacle.h"

// container for objects representing the state of the 'world'
class AWorld
{
public:
   AWorld();
   AWorld(const glm::vec3& dim);
   virtual ~AWorld();

   // drawing
   void draw(atkui::Framework& f);

   // empty the world
   void clear();

   // create a new random world with same #agents and #obstacles
   void reset();

   // create agents with random position
   void setNumAgents(int numAgents);
   // create agent with given position
   void createAgent(const glm::vec3& pos);
   // return ith agent, i must be between 0 and getNumAgents
   const ASteerable& getAgent(int i) const;
   ASteerable& getAgent(int i);
   // return num agents
   int getNumAgents() const;

   // create num obstacles with random size and pos
   void setNumObstacles(int num);
   // create an obstacle with the given pos and r
   void createObstacle(const glm::vec3& pos, float r);
   // get ith obstacles, i should be between 0 and getNumObstacles
   const AObstacle& getObstacle(int i) const;
   AObstacle& getObstacle(int i);
   // return num obstacles
   int getNumObstacles() const;

private:
   glm::vec3 _dimension;
   AObstacle _empty;
   std::vector<ASteerable*> _agents;
   std::vector<AObstacle> _obstacles;

public:
   static bool kDrawObstacles;
};

#endif