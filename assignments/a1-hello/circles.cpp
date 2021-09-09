#include "atkui/framework.h"

using namespace glm;
class Circles : public atkui::Framework
{
public:
   Circles() : atkui::Framework(atkui::Orthographic) {
   }

   virtual void setup() {
   }

   virtual void scene() {
   }

};

int main(int argc, char** argv)
{
   Circles viewer;
   viewer.run();
   return 0;
}
