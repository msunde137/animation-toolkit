#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <stdio.h>
#include <string.h>

using namespace atk;
using namespace atkui;
using namespace glm;

class ACrossfadeViewer : public atkui::Framework
{
public:
  ACrossfadeViewer() : atkui::Framework(atkui::Perspective) {}
  virtual ~ACrossfadeViewer() {}

  void loadMotion1(const std::string &filename)
  {
    BVHReader reader;
    reader.load(filename, skeleton_, motion1_);
  }

  void loadMotion2(const std::string &filename)
  {
    BVHReader reader;
    reader.load(filename, skeleton_, motion2_);
  }

  void crossfade(int numBlendFrames)
  {
    assert(motion1_.getNumKeys() > 0);
    assert(motion2_.getNumKeys() > 0);
    assert(numBlendFrames > 0);
    assert(numBlendFrames <= motion1_.getNumKeys());
    assert(numBlendFrames <= motion2_.getNumKeys());

    int start1 = motion1_.getNumKeys() - numBlendFrames;
    int start2 = 0;

    quat rotOffset = motion1_.getKey(motion1_.getNumKeys()-1).jointRots[0];

    blend_.setFramerate(motion1_.getFramerate());

    for (int i = 0; i < start1; i++)
        blend_.appendKey(motion1_.getKey(i));
    
    for (; start2 < numBlendFrames; start1++, start2++)
    {
        Pose p = motion1_.getKey(start1);
        float t = (float)start2 / (float)numBlendFrames;
        for (int i = 0; i < p.jointRots.size(); i++)
        {
            glm::quat r1 = motion1_.getKey(start1).jointRots[i];
            glm::quat r2 = motion2_.getKey(start2).jointRots[i];
            p.jointRots[i] = slerp(r1, r2, t);
        }
        vec3 offset = motion1_.getKey(start1 - 1).rootPos;
        int rootid = skeleton_.getRoot()->getID();
        glm::quat r1 = motion1_.getKey(start1).jointRots[rootid];
        p.jointRots[0] = slerp(motion1_.getKey(start1).jointRots[0],
            rotOffset * motion2_.getKey(start2).jointRots[0], t);
        p.rootPos = motion1_.getKey(start1).rootPos * (1 - t) + (vec3(offset.x, 0, offset.z) + r1 * motion2_.getKey(start2).rootPos) * t;
        blend_.appendKey(p);
    }
    for (int i = start2; i < motion2_.getNumKeys(); i++)
    {
        Pose p = motion2_.getKey(i);
        vec3 offset = motion1_.getKey(start1 - 1).rootPos;

        int rootid = skeleton_.getRoot()->getID();
        glm::quat r1 = motion1_.getKey(start1 - 1).jointRots[rootid];
        p.jointRots[rootid] = r1 * p.jointRots[rootid];
        p.rootPos = vec3(offset.x, 0, offset.z) + r1 * p.rootPos;
        blend_.appendKey(p);
        //break;
    }
    
  }

  void save(const std::string &filename)
  {
    BVHWriter writer;
    writer.save(filename, skeleton_, blend_);
  }

  void scene()
  {
    blend_.update(skeleton_, elapsedTime());
    drawer_.draw(skeleton_, *this);
    drawFloor(400);
  }

private:
  Skeleton skeleton_;
  SkeletonDrawer drawer_;
  Motion motion1_;
  Motion motion2_;
  Motion blend_;
};

std::string PruneName(const std::string &name)
{
  int idx1 = name.find_last_of("/");
  int idx2 = name.find_last_of(".");
  return name.substr(idx1 + 1, idx2 - idx1 - 1);
}

int main(int argc, char **argv)
{
  std::string motion1 = "../motions/Beta/walking.bvh";
  std::string motion2 = "../motions/Beta/jump.bvh";
  //std::string motion2 = "../motions/Beta/walking.bvh";
  //std::string motion1 = "../motions/Beta/right_turn_90.bvh";
  int numFrames = 10;

  try
  {
    for (int i = 0; i < argc; i++)
    {
      if (strncmp(argv[i], "-m1", 3) == 0)
        motion1 = argv[i + 1];
      else if (strncmp(argv[i], "-m2", 3) == 0)
        motion2 = argv[i + 1];
      else if (strncmp(argv[i], "-nframes", 7) == 0)
        numFrames = std::stoi(argv[i + 1]);
    }
  }
  catch (const std::exception &e)
  {
    std::cout << "usage: crossfade -m1 <path> -m2 <path> -nframes <num frames>\n";
  }

  ACrossfadeViewer viewer;
  viewer.loadMotion1(motion1);
  viewer.loadMotion2(motion2);
  viewer.crossfade(numFrames);

  std::string saveName = "blend-" + PruneName(motion1) + PruneName(motion2);
  saveName += "-" + std::to_string(numFrames) + ".bvh";
  viewer.save(saveName);

  viewer.run();
  return 0;
}
