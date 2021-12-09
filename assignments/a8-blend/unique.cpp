#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <cmath>
#include <string>

using namespace glm;
using namespace atk;
using namespace atkui;

class Unique : public atkui::Framework
{
public:
    Unique() : atkui::Framework(atkui::Perspective) {}
    virtual ~Unique() {}

    void setup()
    {
        BVHReader reader;
        reader.load("../motions/Beta/walking.bvh", _skeleton, _motion);
        reader.load("../motions/Beta/idle.bvh", _skeleton1, _motion1);

        _rotation = 0;
        _offset = vec3(0);
        _offset[1] = _motion.getKey(0).rootPos[1];
        _time = 0;

        _reoriented = reorient(_motion, _offset, glm::angleAxis(_rotation, vec3(1, 0, 0)));
    }

    Motion reorient(const Motion& motion, const vec3& pos, const glm::quat& rot)
    {
        Motion result = motion;
        result.setFramerate(motion.getFramerate());

        // todo: your code here
        for (int i = 0; i < result.getNumKeys(); i++)
        {
            Pose p = result.getKey(i);
            p.rootPos = pos;
            p.jointRots[0] = rot;
            result.editKey(i, p);
        }
        return result;
    }

    void update()
    {
        _time += dt() * 0.5;
        _rotation += dt() / 2.0f;
        vec3 pos = vec3(cos(_time), 0, sin(_time)) * 100.0f + vec3(0, 100, 0);
        _reoriented = reorient(_reoriented, pos, glm::angleAxis(_rotation, vec3(0, -1, 0)));
        _motion1 = reorient(_motion1, pos + vec3(0, 150, 0), glm::angleAxis(_rotation, vec3(0, -1, 0)));
        _reoriented.update(_skeleton, _time);
        _motion1.update(_skeleton1, _time);

        drawFloor(300);
    }

    void scene()
    {
        update();
        SkeletonDrawer drawer;
        drawer.draw(_skeleton, *this);
        drawer.draw(_skeleton1, *this);
    }

    Skeleton _skeleton;
    Skeleton _skeleton1;
    Motion _motion;
    Motion _motion1;
    Motion _reoriented;
    vec3 _offset;
    float _rotation;
    float _time;
};

int main(int argc, char** argv)
{
    Unique viewer;
    viewer.run();
    return 0;
}

