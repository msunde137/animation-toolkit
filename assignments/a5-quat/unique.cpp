#include "atkui/framework.h"
#include "atkmath/quaternion.h"
#include "atkmath/vector3.h"
using namespace glm;

#include "atkui/framework.h"
using namespace glm;


struct controlPoint
{
	vec3 position, color;
	float radius;
	bool selected;
};

struct particle
{
	vec3 position, velocity, color, size;
	atkmath::Quaternion rotation;
};

class DrawCurve : public atkui::Framework {

public:
	DrawCurve() : atkui::Framework(atkui::Orthographic) {
	}

	void setup() {
		color1 = agl::randomUnitCube() + vec3(.5);
		color2 = agl::randomUnitCube() + vec3(.5);

		// particle setup
		for (int i = 0; i < 100; i++)
		{
			particle p;
			p.position = (agl::randomUnitSquare() + vec3(0.5, 0.5, 0)) * vec3(width() - 22, height() - 22, 0) + vec3(11, 11, 0);
			p.color = agl::randomUnitCube() + vec3(.5);
			p.size = vec3(10);
			particles.push_back(p);
		}
	}

	void scene() 
	{
		computeParticles();

	}

	void computeParticles()
	{
		vec3 mousePos = vec3(mousePosition().x, Framework::height() - mousePosition().y, 0);

		for (int i = 0; i < particles.size(); i++)
		{
			atkmath::Quaternion q; 
			vec3 v = particles[i].position - mousePos;
			float angle = std::atan2(v.y, v.x);
			std::cout << angle << std::endl;
			q.fromAxisAngle(atkmath::Vector3(0, 0, 1), angle);
			particles[i].rotation = q;

			setColor(particles[i].color);
			drawCube(particles[i].position, particles[i].size, particles[i].rotation);

			particles[i].position -= v * moveSpd * Framework::dt();

			if (length(v) < particles[i].size.x)
			{
				particles[i].position = (agl::randomUnitSquare() + vec3(0.5, 0.5, 0)) * vec3(width() - 22, height() - 22, 0) + vec3(11, 11, 0);
				particles[i].color = agl::randomUnitCube() + vec3(.5);
			}
		}
	}

	vec3 interpolatePoints(float t, vec3 v1, vec3 v2)
	{
		return v1 * (1.0f - t) + v2 * t;
	}

private:
	vec3 color1, color2;
	float moveSpd = 5.0f;
	std::vector<particle> particles;

};

int main(int argc, char** argv) {
	DrawCurve viewer;
	viewer.run();
}

