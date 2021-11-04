#include <random>
#include <functional>
#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "agl/renderer.h"
#include "devil.h"

using namespace atk;
using namespace glm;

class Thriller : public atkui::Framework
{
public:
   Thriller() : atkui::Framework(atkui::Perspective) {}
   virtual ~Thriller() {}

   virtual void setup() {
      BVHReader reader;
      reader.load("../motions/Warrok/WarrokThriller.bvh", _skeleton, _motion);

      vec3 position = vec3(0);
      vec3 color = vec3(1,0,0);
      float size = 1.0f;
      _devil = Devil(position, color, size);

      for (int i = 0; i < 4; i++)
      {
          for (int j = 0; j < 3; j++)
          {
              positions.push_back(vec3(i - 2, 0, j - 1));
              colors.push_back(agl::randomUnitCube() + vec3(.5));
              sizes.push_back(agl::randomUnitCube() + vec3(1));
          }
      }
   }

   virtual void scene() {
      if (!_paused) _motion.update(_skeleton, elapsedTime());
      for (int i = 0; i < positions.size(); i++)
      {
          translate(positions[i] * 100.0f);
          scale(sizes[i]);
          setColor(colors[i]);
          _devil.draw(_skeleton, *this);
      }
   }

   virtual void keyUp(int key, int mods) {
      if (key == 'P') _paused = !_paused;
   }

protected:
   Motion _motion;
   Skeleton _skeleton;
   bool _paused = false;
   Devil _devil;

   std::vector<vec3> colors;
   std::vector<vec3> sizes;
   std::vector<vec3> positions;
};

int main(int argc, char** argv) {
   Thriller viewer;
   viewer.run();
}

