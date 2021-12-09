#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace atkui;
using namespace glm;

class ASplice : public atkui::Framework
{
    public:
    ASplice() : atkui::Framework(atkui::Perspective) {}
    virtual ~ASplice() {}

    void setup()
    {
        _alpha = 0;

        BVHReader reader;
        reader.load("../motions/Beta/walking.bvh", _skeleton, _lower);
        reader.load("../motions/Beta/gangnam_style.bvh", _skeleton, _upper);
        _splice = spliceUpperBody(_lower, _upper, _alpha);
    }

    void getIndices(Joint* j, std::vector<int>& inds)
    {
        inds.push_back(j->getID());
        if (j->getNumChildren() == 0)
            return;
        else
            for (int i = 0; i < j->getNumChildren(); i++)
                getIndices(j->getChildAt(i), inds);
    }

    Motion spliceUpperBody(const Motion& lower, const Motion& upper, float alpha)
    {
        Motion blend = lower;
        blend.setFramerate(lower.getFramerate());

        float duration = lower.getDuration() * (1 - alpha) + upper.getDuration() * alpha;
        float deltaT = 1 / upper.getFramerate();
        std::vector<int> indices = {};
        Joint* current = _skeleton.getByName("Beta:Spine1");
        getIndices(current, indices);

        for (int i = 0; i < blend.getNumKeys(); i++)
        {
            Pose p = blend.getKey(i);
            Pose q = upper.getKey(i+120);
            for (int j = 0; j < indices.size(); j++)
            {
                //std::cout << i << " " << j << std::endl;
                p.jointRots[j] = q.jointRots[j];
            }
            blend.editKey(i, p);
        }
        return blend;
    }

    void scene()
    {  
        _splice.update(_skeleton, elapsedTime() * 0.5);
        SkeletonDrawer drawer;
        drawer.draw(_skeleton, *this);
        drawText("alpha: "+std::to_string(_alpha), 10, 15);
    }

    void keyUp(int key, int mods) 
    {
        if (key == GLFW_KEY_UP)
        {
            _alpha = std::min(_alpha+0.05, 1.0);
            _splice = spliceUpperBody(_lower, _upper, _alpha);
        }
        else if (key == GLFW_KEY_DOWN)
        {
            _alpha = std::max(_alpha-0.05, 0.0);
            _splice = spliceUpperBody(_lower, _upper, _alpha);
        }
    }

    Skeleton _skeleton;
    Motion _upper;
    Motion _lower;
    Motion _splice;
    float _alpha;
};

int main(int argc, char** argv)
{
    ASplice viewer;
    viewer.run();
    return 0;
}

