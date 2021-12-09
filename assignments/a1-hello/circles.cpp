#include "atkui/framework.h"

using namespace glm;
class Circles : public atkui::Framework
{
public:
   Circles() : atkui::Framework(atkui::Orthographic) {
   }

   virtual void setup() {
	   rotCenter = vec3(0);
	   rotRadius = 15;
	   theta = 0.0f;
	   rotSpeed = 0.5f;
	   rows = 15;

	   for (int i = 0; i < rows; i++)
	   {
		   colors.push_back(agl::randomUnitCube() + vec3(0.5, 0.5, 0.5));
	   }
   }

   virtual void scene() {
	   float dt = atkui::Framework::dt();
	   vec3 center = vec3((float)atkui::Framework::width() / 2.0f, (float)atkui::Framework::height() / 2.0f, 0.0f);

	   theta += rotSpeed * dt;


	   float offset = 3.0f;
	   float thetaOffset = 0.0f;
	   for (int j = 0; j < rows; j++)
	   {
		   setColor(colors[j]);
		   for (int i = 0; i < 36; i++)
		   {
				float dx = rotRadius * glm::sin((theta + thetaOffset) * ((j % 2) * 2 - 1));
				float dy = rotRadius * glm::cos((theta + thetaOffset) * ((j % 2) * 2 - 1));
				drawSphere(center + vec3(dx * offset, dy * offset, -100), 5);
				thetaOffset += (2.0f * glm::pi<float>()) / 36.0f;
		   }
		   offset += 1.0f;
	   }
   }

   int rotRadius;
   vec3 rotCenter;
   float theta;
   float rotSpeed;
   int rows;
   std::vector<vec3> colors;
};

int main(int argc, char** argv)
{
   Circles viewer;
   viewer.run();
   return 0;
}
