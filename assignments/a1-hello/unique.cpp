#include "atkui/framework.h"

using namespace glm;

struct particle
{
	vec3 position;
	vec3 velocity;
	vec3 color;
};

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {

	  winx = 0;
	  winy = 0;
	  glfwGetWindowPos(atkui::Framework::getWindow(), &winx, &winy);

	  gravity = -300;
	  drag = .05;
	  bounce = .7;

	  numParticles = 150;
	  for (int i = 0; i < numParticles; i++)
	  {
		  particle p;
		  p.position = (agl::randomUnitSquare() + vec3(0.5, 0.5, 0)) * vec3(width() - 22, height() - 22, 0) + vec3(11, 11, 0);
		  p.velocity = agl::randomUnitDisk() * 20.0f;
		  p.color = agl::randomUnitCube() + vec3(0.5, 0.5, 0.5);
		  particles.push_back(p);
	  }
  }

  virtual void scene() {
	  float dt = atkui::Framework::dt();
	  
	  // tried implementing window movement
	  //int wincx = 0;
	  //int wincy = 0;
	  //glfwGetWindowPos(atkui::Framework::getWindow(), &wincx, &wincy);

	  //vec3 dwin = vec3(0, -winy, 0) - vec3(0, -wincy, 0);
	  //winx = wincx;
	  //winy = wincy;

	  for (int i = 0; i < particles.size(); i++)
	  {

		  particles[i].position += particles[i].velocity * dt;
		  particles[i].velocity += vec3(0, gravity, 0) * dt;
		  particles[i].velocity -= particles[i].velocity * drag * dt;
		  setColor(particles[i].color);
		  drawSphere(particles[i].position, 10);

		  // bounding box
		  if (particles[i].position.x + 10 > width())
		  {
			  particles[i].velocity = glm::reflect(particles[i].velocity, vec3(-1, 0, 0));
			  particles[i].velocity *= bounce;
			  particles[i].position.x = width() - 11;
		  }
		  else if (particles[i].position.x - 10 < 0)
		  {
			  particles[i].velocity = glm::reflect(particles[i].velocity, vec3(1, 0, 0));
			  particles[i].velocity *= bounce;
			  particles[i].position.x = 11;
		  }
		  if (particles[i].position.y + 10 > height())
		  {
			  particles[i].velocity = glm::reflect(particles[i].velocity, vec3(0, 1, 0));
			  particles[i].velocity *= bounce;
			  particles[i].position.y = height() - 11;
		  }
		  else if (particles[i].position.y - 10 < 0)
		  {
			  particles[i].velocity = glm::reflect(particles[i].velocity, vec3(0, -1, 0));
			  particles[i].velocity *= bounce;
			  particles[i].position.y = 11;
		  }

		  if (atkui::Framework::keyIsDown(GLFW_KEY_R))
		  {
			  particles.clear();
			  setup();
		  }
	  }
  }

  int winx, winy;
  vec3 dwin;

  std::vector<particle> particles;
  int numParticles;
  float drag;
  float bounce;
  float gravity;
};

int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
  return 0;
}

