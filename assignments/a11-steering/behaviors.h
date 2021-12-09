#ifndef _BEHAVIOR_H
#define _BEHAVIOR_H

#include <string>
#include "steerable.h"
#include "obstacle.h"
#include "world.h"

class ABehavior
{
public:
   virtual ~ABehavior() {}

   virtual glm::vec3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const glm::vec3& target) = 0;

   const std::string& getName() const;

   int getNumParams() const;
   const std::string& getParamName(int i) const;
   float getParamValue(int i) const; 
   float getParam(const std::string& name) const;
   void setParam(const std::string& name, float v);

protected:
   ABehavior(const char* name);
   std::string _name;
   std::map<std::string, float> _params;
};

class ASeek : public ABehavior
{
public:
   ASeek();
   virtual glm::vec3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const glm::vec3& target);
};

class AFlee : public ABehavior
{
public:
   AFlee();
   virtual glm::vec3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const glm::vec3& target);
};

class AArrival : public ABehavior
{
public:
   AArrival();
   virtual glm::vec3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const glm::vec3& target);
};

class ADeparture : public ABehavior
{
public:
   ADeparture();
   virtual glm::vec3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const glm::vec3& target);
};

class AAvoid : public ABehavior
{
public:
   AAvoid();
   virtual glm::vec3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const glm::vec3& target);
};

class AWander : public ABehavior
{
public:
   AWander();
   virtual glm::vec3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const glm::vec3& target);
};

class ASeparation : public ABehavior
{
public:
   ASeparation();
   virtual glm::vec3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const glm::vec3& target);
};

class ACohesion : public ABehavior
{
public:
   ACohesion();
   virtual glm::vec3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const glm::vec3& target);
};

class AAlignment : public ABehavior
{
public:
   AAlignment();
   virtual glm::vec3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const glm::vec3& target);
};

class AFlocking : public ABehavior
{
public:
   AFlocking();
   virtual glm::vec3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const glm::vec3& target);
};

class ALeader : public ABehavior
{
public:
   ALeader();
   virtual glm::vec3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const glm::vec3& target);
};

//----------------------------------------------------
// ABehavior implementation

inline const std::string& ABehavior::getName() const 
{ 
   return _name; 
}

inline int ABehavior::getNumParams() const 
{ 
   return _params.size(); 
}

inline const std::string& ABehavior::getParamName(int i) const 
{ 
   std::map<std::string, float>::const_iterator it = _params.begin();
   std::advance(it,i);
   return it->first; 
}

inline float ABehavior::getParamValue(int i) const 
{ 
   std::map<std::string, float>::const_iterator it = _params.begin();
   std::advance(it,i);
   return it->second; 
}

inline float ABehavior::getParam(const std::string& name) const
{ 
   std::map<std::string, float>::const_iterator it = _params.find(name);
   return it != _params.end()? it->second : 0;
}

inline void ABehavior::setParam(const std::string& name, float v) 
{ 
   _params[name] = v; 
}


#endif
