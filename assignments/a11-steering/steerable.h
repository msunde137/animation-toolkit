#ifndef STEERINGCHARACTER_H_
#define STEERINGCHARACTER_H_

#include "atkui/skeleton_drawer.h"
#include "atk/toolkit.h"

class ASteerable
{
public:
   ASteerable();
   virtual ~ASteerable();
   bool operator==(const ASteerable& other) const;

   void reset();
   void reset(const glm::vec3& pos);
   void update(const glm::vec3& desiredVelocity, float dt);
   void draw(atkui::Framework& f);

   glm::vec3 getPosition() const;
   glm::vec3 getVelocity() const;
   glm::vec3 getDesiredVelocity() const;
   glm::quat getRotation() const;
   void setColor(const glm::vec3& color); 

private:
   void senseControlAct(const glm::vec3& veld, float dt);
   void randomizeAppearance();

protected:
   int _id;
   atkui::SkeletonDrawer _drawer;
   atk::Skeleton _skeleton;
   atk::Motion _walk;
   atk::Motion _idle;
   atk::Transform _characterRoot;
   float _time;

   // rigid body state and derivative
   enum {POS, ORI, VEL, AVEL};
   float _state[4];
   float _derivative[4];
   float _mass;
   float _inertia;

    // Input vector: 1D force and torque
   float _force;
   float _torque;

   // Control input: 1D speed and heading
   float _vd;
   float _thetad;

   // computed quantities (kept for visualization)
   glm::vec3 _veld; // desired velocity
   glm::vec3 _vel;  // current velocity

public:
   // translation control: f = m * Kv0 * (vd - v)
   static float kVelKv;  

   // rotation control: tau = I * (-Kv1 * thetaDot + Kp1 * (thetaD - theta))
   static float kOriKv;  
   static float kOriKp;

   static bool kDebugDraw;
   static bool kDrawCharacter;
};

#endif
