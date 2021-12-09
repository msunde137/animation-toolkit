#include "steerable.h"
#include "behaviors.h"

using namespace glm;
using namespace atk;

float ASteerable::kVelKv = 150.0; 
float ASteerable::kOriKv = 150.0;  
float ASteerable::kOriKp = 150.0;

// Given a desired velocity, veld, and dt, compute a transform holding 
// the new orientation and change in position
//
// rotation control: tau = I * (-Kv1 * thetaDot + Kp1 * (thetaD - theta))
// translation control: f = m * Kv0 * (vd - v)
void ASteerable::senseControlAct(const vec3& veld, float dt)
{
   // Compute _vd and _thetad

   // compute _force and _torque

   // find derivative

   // update state

   // compute global position and orientation and update _characterRoot
   quat rot = glm::angleAxis(_state[ORI], vec3(0,1,0));
   vec3 localPos(0,0,_state[POS]);

   _characterRoot.setT(rot * localPos + _characterRoot.t());
   _characterRoot.setR(rot); 
}

// randomize the colors, characters, and animation times here
void ASteerable::randomizeAppearance()
{
   // to randomize the walking animations, compute different initial values 
   // for _time

   // to randomize color, call _drawer.setColor

   // to randomize shape, compute random values for _drawer.setJointRadius
   // or randomly assign different drawers to have a mix of characters
}

