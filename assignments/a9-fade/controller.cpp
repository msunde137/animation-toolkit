#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include "atk/toolkit.h"
#include <iostream>
#include <cmath>

using namespace glm;
using namespace std;
using namespace atk;

class WASDSimple : public atkui::Framework
{
public:
  WASDSimple() : atkui::Framework(atkui::Perspective) {}

  virtual void setup()
  {
    BVHReader reader;
    reader.load("../motions/Beta/walking.bvh", _skeleton, _walk);
    _drawer.showAxes = true;

    for (int i = 0; i < _walk.getNumKeys(); i++)
    {
        Pose p = _walk.getKey(i);
        p.rootPos = vec3(0, p.rootPos.y, 0);
        _walk.editKey(i, p);
    }
  }

  virtual void scene()
  {
    update();

    // draw heading
    vec3 p = _skeleton.getRoot()->getGlobalTranslation();
    p[1] = 10; // set height close above the floor
    vec3 forward = glm::angleAxis(_heading, vec3(0, 1, 0)) * vec3(0, 0, 1);
    vec3 pos = p + forward * -400.0f + vec3(0, 200, 0);
    vec3 look = _skeleton.getByName("Beta:Head")->getGlobalTranslation();
    vec3 up = vec3(0, 1, 0); // cross(look - pos, -cross(vec3(0, 1, 0), pos));
    lookAt(pos, look, up);
    setColor(vec3(0, 1, 1));
    push();
    translate(p);
    rotate(_heading, vec3(0, 1, 0));
    translate(vec3(0,0,25));
    scale(vec3(10, 10, 50));
    drawCylinder(vec3(0), 1.0f);
    pop();

    drawFloor(400);
    _drawer.draw(_skeleton, *this);
  }

  virtual void update()
  {
    _walk.update(_skeleton, elapsedTime());

    // TODO: Your code here

    // TODO: Override the default camera to follow the character
    // lookAt(pos, look, vec3(0, 1, 0));

    // update heading when key is down
    if (keyIsDown('D'))
    {
        _heading -= 0.05f;
        for (int i = 0; i < _walk.getNumKeys(); i++)
        {
            Pose p = _walk.getKey(i);
            int id = _skeleton.getRoot()->getID();
            p.jointRots[id] = p.jointRots[id] * glm::angleAxis(-.05f, vec3(0, 1, 0));
            _walk.editKey(i, p);
        }
    }
    if (keyIsDown('A'))
    {
        _heading += 0.05f;
        for (int i = 0; i < _walk.getNumKeys(); i++)
        {
            Pose p = _walk.getKey(i);
            int id = _skeleton.getRoot()->getID();
            p.jointRots[id] = p.jointRots[id] * glm::angleAxis(.05f, vec3(0, 1, 0));
            _walk.editKey(i, p);
        }
    }
    for (int i = 0; i < _walk.getNumKeys(); i++)
    {
        Pose p = _walk.getKey(i);
        p.rootPos += glm::angleAxis(_heading, vec3(0, 1, 0)) * vec3(0, 0, 150) * dt();
        _walk.editKey(i, p);
    }
  }

protected:
  float _heading = 0.0f;

  Motion _walk;
  Skeleton _skeleton;
  atkui::SkeletonDrawer _drawer;
};

int main(int argc, char **argv)
{
  WASDSimple viewer;
  viewer.run();
}
