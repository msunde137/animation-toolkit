#include <iostream>
#include "atk/toolkit.h"

using namespace atk;
using namespace glm;

int main(int argc, char** argv)
{
   Skeleton skeleton;
   Motion motion;

   BVHReader reader;
   reader.load("../motions/Beta/walking.bvh", skeleton, motion);

   // How many frames (aka keys)?
   int numFrames = 0;
   std::cout << "The number of frames is " << numFrames << std::endl;

   // What is the framerate?
   float fps = 0.0f;
   std::cout << "The frame rate is " << fps << std::endl;

   // What is the duration?
   float duration = 0.0;
   std::cout << "The duration of the animation is " << duration << std::endl;

   // What is the root position on frame 5 (aka Key #5)?
   // Hint: Get a pose from the motion
   Pose frame5;
   vec3 rootPos = vec3(0);
   std::cout << "The root position on frame 5 is: " << glm::to_string(rootPos) << std::endl;

   // What is the local joint rotation of the left hand on frame 5? 
   // Give your answer in XYZ euler angles
   // Hint: use the skeleton to get the ID for the hand
   // Hint: use extractEulerAngleRO (defined in atk/glmmath.h)
   Joint* hand = NULL;
   vec3 eulerXYZ = vec3(0);
   std::cout << "The local rotation of the left hand on frame 5 is: " << glm::to_string(eulerXYZ) << std::endl;

   // What is the speed of the character?
   // Hint: Use the first and last frames to get the distance traveled over the motion clip
   Pose frame0;
   Pose frameN;
   vec3 delta = vec3(0);
   float distance = delta.length();
   float speed = 0.0;
   std::cout << "The speed of the motion is (units/s): " << speed << std::endl;
}
