#include "atkui/framework.h"

using namespace glm;

struct particle
{
	vec3 position;
	vec3 velocity;
	vec3 color;
};

class Particles : public atkui::Framework
{
 public:
  Particles() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
	  numParticles = 150;
	  vec3 velocity = agl::randomUnitDisk();
	  for (int i = 0; i < numParticles; i++)
	  {
		  particle p;
		  p.position = (agl::randomUnitSquare() + vec3(0.5, 0.5, 0)) * vec3(width(), height(), 0);
		  p.velocity = velocity * agl::random() * 20.0f;
		  p.color = agl::randomUnitCube() + vec3(0.5, 0.5, 0.5);
		  particles.push_back(p);
	  }
  }

  virtual void scene() {
	  float dt = atkui::Framework::dt();
	  for (int i = 0; i < particles.size(); i++)
	  {
		  particles[i].position += particles[i].velocity * dt;
		  setColor(particles[i].color);
		  drawSphere(particles[i].position, 10);

		  // x wrapping
		  if (particles[i].position.x - 10 > width()) particles[i].position.x = -10;
		  else if (particles[i].position.x + 10 < 0) particles[i].position.x = width() + 10;
		  // y wrapping
		  if (particles[i].position.y - 10 > width()) particles[i].position.y = -10;
		  else if (particles[i].position.y + 10 < 0) particles[i].position.y = width() + 10;
	  }
  }

  std::vector<particle> particles;
  int numParticles;
};

int main(int argc, char** argv) {
  Particles viewer;
  viewer.run();
  return 0;
}
