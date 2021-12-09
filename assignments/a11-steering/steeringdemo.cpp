#include "steeringdemo.h"
#include "agl/camera.h"

using namespace glm;
using namespace atk;

ASteeringDemo::ASteeringDemo() :
   atkui::Framework(atkui::Perspective),
   _character(),
   _behavior(),
   _target(100,0,100)
{
}

ASteeringDemo::~ASteeringDemo()
{
}

void ASteeringDemo::reset()
{
   setupPerspectiveScene(vec3(0,0,0), vec3(1000,1500,1000));
   _character.reset();
}

void ASteeringDemo::setup()
{
   reset();
}

void ASteeringDemo::scene()
{
   vec3 dvel = _behavior.calculateDesiredVelocity(_character, AWorld(), _target);
   _character.update(dvel, dt());
   _character.draw(*this);

   setColor(vec3(1,0,0));
   drawSphere(_target, 10);
}

void ASteeringDemo::onInitializeGui()
{
}

void ASteeringDemo::mouseUp(int key, int mods)
{
   _modifierState = mods;
   vec2 mousePos = mousePosition();
   if (_modifierState == GLFW_MOD_CONTROL) // move target
   {
      vec3 target = screenToWorld(vec2(mousePos[0], height() - mousePos[1]));

      vec3 origin = camera.position();
      vec3 dir = target - origin;

      // Intersect with XZ plane 
      float t = -origin[1] / dir[1];
      _target = origin + t*dir;
   }
}

void ASteeringDemo::mouseMotion(int x, int y, int dx, int dy)
{
}

void ASteeringDemo::keyUp(int key, int mods)
{
   if (key == ' ') reset();
}

int main(int argc, char** argv)
{
    ASteeringDemo viewer;
    viewer.run();
    return 0;
}
