#include "atkui/framework.h"
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
	vec3 position, velocity;
};

struct curve
{
	controlPoint cp1, cp2, cp3, cp4;
	vec3 color;
};

class DrawCurve : public atkui::Framework {

public:
	DrawCurve() : atkui::Framework(atkui::Orthographic) {
	}

	void setup() {
		// curve setup
		c.cp1 = { vec3(50, 50, 0), vec3(0,1,1), 10 };
		c.cp2 = { vec3(150, 50, 0), vec3(0,1,1), 10 };
		c.cp3 = { vec3(50, 150, 0), vec3(0,1,1), 10 };
		c.cp4 = { vec3(150, 150, 0), vec3(0,1,1), 10 };
		c.color = vec3(1);

		numCurves = 50;
		curves.resize(numCurves);

		color1 = agl::randomUnitCube() + vec3(.5);
		color2 = agl::randomUnitCube() + vec3(.5);

		// particle setup
		for (int i = 0; i < 4; i++)
		{
			particle p;
			p.position = (agl::randomUnitSquare() + vec3(0.5, 0.5, 0)) * vec3(width() - 22, height() - 22, 0) + vec3(11, 11, 0);
			p.velocity = agl::randomUnitDisk() * 20.0f;
			particles.push_back(p);
		}
	}

	void scene() {
		vec3 mousePos = vec3(mousePosition().x, Framework::height() - mousePosition().y, 0);

		// particle stuff
		computeParticles();

		if (c.cp1.selected)
		{
			particles[0].position = c.cp1.position;
			particles[0].velocity = vec3(0);
		}
		else c.cp1.position = particles[0].position;

		if (c.cp2.selected)
		{
			particles[1].position = c.cp2.position;
			particles[1].velocity = vec3(0);
		}
		else c.cp2.position = particles[1].position;
		
		if (c.cp3.selected)
		{
			particles[2].position = c.cp3.position;
			particles[2].velocity = vec3(0);
		}
		else c.cp3.position = particles[2].position;
		
		if (c.cp4.selected)
		{
			particles[3].position = c.cp4.position;
			particles[3].velocity = vec3(0);
		}
		else c.cp4.position = particles[3].position;

		// press e for controls!
		if (keyIsDown(GLFW_KEY_E))
		{
			if (!e) control = !control;
			e = true;
		}
		else e = false;

		// edit curve
		if (control)
		{
			drawControlPoint(c.cp1, mousePos);
			drawControlPoint(c.cp2, mousePos);
			drawControlPoint(c.cp3, mousePos);
			drawControlPoint(c.cp4, mousePos);

			setColor(vec3(1, 0, 0));
			drawLine(c.cp1.position, c.cp2.position);
			drawLine(c.cp3.position, c.cp4.position);
		}
		// see cool thing!
		else
		{
			vec3 color = interpolatePoints((float)i / (float)numCurves, color1, color2);
			c.color = color;
			curves[i] = c;
			i++;
			if (i >= numCurves)
			{
				i = 0;
				color1 = color2;
				color2 = agl::randomUnitCube() + vec3(.5);
			}
			
			for (int j = 0; j < curves.size(); j++)
			{
				drawCurve(curves[j]);
			}
		}
	}

	void bezierAlgorithm(controlPoint cp1, controlPoint cp2, controlPoint cp3, controlPoint cp4, int steps)
	{
		// function p(t)
		auto p = [cp1, cp2, cp3, cp4](float t) {
			return pow((1 - t), 3) * cp1.position + 3 * t * pow((1 - t), 2) * cp2.position + 3 * pow(t, 2) * (1 - t) * cp3.position + pow(t, 3) * cp4.position;
		};

		float inc = 1 / (float)steps;
		for (float t = 0; t <= 1 - inc + .001; t += inc)
		{
			vec3 pos1 = p(t);
			vec3 pos2 = p(t + inc);
			drawLine(pos1, pos2);
		}
	}

	void drawCurve(curve c)
	{
		setColor(c.color);
		bezierAlgorithm(c.cp1, c.cp2, c.cp3, c.cp4, 50);
	}

	void drawControlPoint(controlPoint& p, vec3 mousePos)
	{
		if (mouseIsDown(GLFW_MOUSE_BUTTON_1) && glm::distance(mousePos, p.position) < p.radius && !mouseDown)
		{
			mouseDown = true;
			p.selected = true;
		}
		else if (!mouseIsDown(GLFW_MOUSE_BUTTON_1))
		{
			mouseDown = false;
			p.selected = false;
		}
		if (mouseDown && p.selected &&
			mousePos.x < Framework::width() && mousePos.y < Framework::height() &&
			mousePos.x > 0 && mousePos.y > 0)
		{
			p.position = mousePos;
		}

		setColor(p.color);
		drawSphere(p.position, p.radius);
	}

	void computeParticles()
	{
		float gravity = -300;
		float drag = 0.f;
		float bounce = 1.f;
		float dt = atkui::Framework::dt();

		for (int i = 0; i < particles.size(); i++)
		{

			particles[i].position += particles[i].velocity * dt;
			particles[i].velocity += vec3(0, gravity, 0) * dt;
			particles[i].velocity -= particles[i].velocity * drag * dt;

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
		}
	}

	vec3 interpolatePoints(float t, vec3 v1, vec3 v2)
	{
		return v1 * (1.0f - t) + v2 * t;
	}

private:
	curve c;
	bool mouseDown = false;
	bool control = false;
	bool e = false;

	std::vector<curve> curves;
	vec3 color1, color2;
	int numCurves;
	int i = 0;

	std::vector<particle> particles;

};

int main(int argc, char** argv) {
	DrawCurve viewer;
	viewer.run();
}

