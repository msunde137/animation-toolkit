#include <cstring>
#include <algorithm>
#include "steerable.h"
#include "behaviors.h"
#include "atk/bvhreader.h"
#include "atkui/framework.h"

using namespace glm;
using namespace atk;

static int counter = 0; // for assigning unique ids

// global constants for all characters
bool ASteerable::kDebugDraw = true;
bool ASteerable::kDrawCharacter = true;

// Class implemetation
ASteerable::ASteerable() :
   _id(counter++), _skeleton(), _drawer(), _walk(), _characterRoot(), 
   _time(0), _state{0,0,0,0}, _derivative{0,0,0,0}, _mass(1), _inertia(1),
   _force(0), _torque(0), _vd(0), _thetad(0), 
   _veld(0, 0, 0), _vel(0, 0, 0)
{
   _drawer.color = vec3(0,0,0.5);
}

ASteerable::~ASteerable()
{
}

bool ASteerable::operator==(const ASteerable& other) const
{
   return other._id == _id;
}

void ASteerable::reset()
{
   vec3 pos = _characterRoot.t();
   reset(pos);
}

void ASteerable::reset(const vec3& pos)
{
   BVHReader reader;
   reader.load("../motions/Beta/walking.bvh", _skeleton, _walk);
   reader.load("../motions/Beta/idle.bvh", _skeleton, _idle);
   _idle.update(_skeleton, 0);

   _characterRoot = _skeleton.getRoot()->getLocal2Parent();
   vec3 translation = _characterRoot.t();
   translation[0] = pos[0];
   translation[2] = pos[2];
   _characterRoot.setT(translation);

   memset(_state, 0, 4 * sizeof(float));
   memset(_derivative, 0, 4 * sizeof(float));
   _force = 0;
   _torque = 0;
   _thetad = 0;
   _vd = 0;

   randomizeAppearance();
}

void ASteerable::update(const vec3& desiredVelocity, float dt)
{
   // ASN: dt will be large, particularly if you are using gdb to inspect values
   // Clamping dt will make it easier for your dynamics to stay stable at the expense
   // of smoothness
   dt = std::min<float>(0.1, dt);
   _time += dt;

   // reset state
   _veld = desiredVelocity;
   _state[POS] = 0;

   // compute forces and update state
   senseControlAct(_veld, dt);

   // update global velocity (needed for viz and group behaviors)
   _vel = _characterRoot.r() * vec3(0,0,_state[VEL]);

   // draw character based on state
   if (kDrawCharacter)
   {
      if (_state[VEL] > 5)
      {
         _walk.update(_skeleton, _time);
      }
      else
      {
         _idle.update(_skeleton, _time);
      }
      Transform rootTransform = _skeleton.getRoot()->getLocal2Parent();
      vec3 fwd = rootTransform.transformVector(vec3(0,0,1));
      quat newRot = _characterRoot.r() * 
         glm::angleAxis<float>(atan2(fwd[0], fwd[2]), vec3(0,-1,0)) * 
         rootTransform.r();
      rootTransform.setT(_characterRoot.t());
      rootTransform.setR(newRot);
      _skeleton.getRoot()->setLocal2Parent(rootTransform);
      _skeleton.fk();
   }
}

void ASteerable::draw(atkui::Framework& f)
{
   if (kDrawCharacter)
   {
      _drawer.draw(_skeleton, f);
   }

   if (kDebugDraw)
   {
      vec3 p = _characterRoot.t();

      vec3 gx = _characterRoot.r() * vec3(1,0,0);
      vec3 gy = _characterRoot.r() * vec3(0,1,0);
      vec3 gz = _characterRoot.r() * vec3(0,0,1);

      f.beginShader("unlit");
      f.setColor(vec3(1,0,0));
      f.drawLine(p, p + 50.0f * gx);
      f.setColor(vec3(0,1,0));
      f.drawLine(p, p + 50.0f * gy);
      f.setColor(vec3(0,0,1));
      f.drawLine(p, p + 50.0f * gz);

      f.setColor(vec3(0.2f,0.2f,1));
      f.drawLine(p, p + 100.0f * _vel);

      f.setColor(vec3(0,1,1));
      f.drawLine(p, p + 100.0f * _veld);

      f.setColor(vec3(1,1,0));
      f.drawLine(p, p + 10.0f * vec3(0,_state[AVEL],0));
      f.endShader();
   }
}

vec3 ASteerable::getPosition() const
{
   vec3 pos = _characterRoot.t();
   pos[1] = 0;
   return pos;
}

vec3 ASteerable::getVelocity() const
{
   return _vel;
}

vec3 ASteerable::getDesiredVelocity() const
{
   return _veld;
}

quat ASteerable::getRotation() const
{
   return _characterRoot.r();
}

void ASteerable::setColor(const vec3& color)
{
   _drawer.color = color;
} 


