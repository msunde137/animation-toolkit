#include <iostream>
#include <fstream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;

class MotionViewer : public atkui::Framework
{
public:
    MotionViewer() : atkui::Framework(atkui::Perspective) {
    }

    void setup() {
        BVHReader reader;
        reader.load(filepath, skeleton, motion);
        motion.update(skeleton, 0);
        std::cout << "press 'N' to add a different file";
    }

    void scene() {
        if (!paused)
            time += dt() * timeScale;
        motion.update(skeleton, time);

        setColor(vec3(0,0,0.8));
        for (int i = 0; i < skeleton.getNumJoints(); i++) {
            Joint* joint = skeleton.getByID(i);
            if (joint->getParent() == 0) continue;

            vec3 p1 = joint->getGlobalTranslation();
            vec3 p2 = joint->getParent()->getGlobalTranslation();
            drawEllipsoid(p1, p2, 5);
        }

        drawText(paused? "Paused" : "Playing", 10, 15);
        drawText("Current frame: "+std::to_string(currentFrame), 10, 35);
        drawText("Time scale: "+std::to_string(timeScale), 10, 55);
    }

    virtual void keyUp(int key, int mods) 
    {
        switch (key)
        {
        case GLFW_KEY_P:
            paused = !paused; break;
        case GLFW_KEY_0:
            time = 0; break;
        case GLFW_KEY_PERIOD:
            if (paused) time += dt(); break;
        case GLFW_KEY_COMMA:
            if (paused) time -= dt(); break;
        case GLFW_KEY_LEFT_BRACKET:
            timeScale -= .2f; break;
        case GLFW_KEY_RIGHT_BRACKET:
            timeScale += .2f; break;
        case GLFW_KEY_N:
        {
            std::cout << "write a filepath: ";
            std::cin >> filepath;
            BVHReader reader;
            reader.load(filepath, skeleton, motion);
            motion.update(skeleton, 0);
            break;
        }
        default:
            break;
        }
    }

private:
    std::string filepath = "../motions/Beta/jump.bvh";
    Skeleton skeleton;
    Motion motion;

    float timeScale = 1.0f;
    int currentFrame = 0; 
    bool paused = false;
    float time = 0;
};


int main(int argc, char** argv) {
    MotionViewer viewer;
    viewer.run();
}
