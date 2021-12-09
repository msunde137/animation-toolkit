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
	vec3 position, color;
	float radius;
};

class ParticleCubic : public atkui::Framework {

public:
	ParticleCubic() : atkui::Framework(atkui::Orthographic) {
	}

	void setup() {
		cp1 = { vec3(50, 50, 0), vec3(0,1,1), 10 };
		cp2 = { vec3(150, 50, 0), vec3(0,1,1), 10 };
		cp3 = { vec3(50, 150, 0), vec3(0,1,1), 10 };
		cp4 = { vec3(150, 150, 0), vec3(0,1,1), 10 };
		t = 0;
		p = { vec3(0), vec3(1), 10 };
	}

	void scene() {
		vec3 mousePos = vec3(mousePosition().x, Framework::height() - mousePosition().y, 0);

		drawControlPoint(cp1, mousePos);
		drawControlPoint(cp2, mousePos);
		drawControlPoint(cp3, mousePos);
		drawControlPoint(cp4, mousePos);

		setColor(vec3(1, 0, 0));
		drawLine(cp1.position, cp2.position);
		drawLine(cp3.position, cp4.position);

		if (keyIsDown(GLFW_KEY_1))
			bez = true;
		if (keyIsDown(GLFW_KEY_2))
			bez = false;

		if (bez)
			bezierAlgorithm(cp1, cp2, cp3, cp4, 50);
		else
			casteljauAlgorithm(cp1, cp2, cp3, cp4, 50);

		animateParticle(p, .2, t, cp1, cp2, cp3, cp4);
	}

	void bezierAlgorithm(controlPoint cp1, controlPoint cp2, controlPoint cp3, controlPoint cp4, int steps)
	{
		// function p(t)
		auto p = [cp1, cp2, cp3, cp4](float t) {
			return (float)pow((1 - t), 3) * cp1.position + 3 * t * (float)pow((1 - t), 2) * cp2.position + 3 * (float)pow(t, 2) * (1 - t) * cp3.position + (float)pow(t, 3) * cp4.position;
		};

		setColor(vec3(1, 1, 0));
		float inc = 1 / (float)steps;
		for (float t = 0; t <= 1 - inc + .001; t += inc)
		{
			vec3 pos1 = p(t);
			vec3 pos2 = p(t + inc);
			drawLine(pos1, pos2);
		}
	}

	void casteljauAlgorithm(controlPoint cp1, controlPoint cp2, controlPoint cp3, controlPoint cp4, int steps)
	{
		// function p(t)
		auto p = [cp1, cp2, cp3, cp4](float t) {
			vec3 a = cp1.position * (1.0f - t) + cp2.position * t;
			vec3 b = cp3.position * (1.0f - t) + cp4.position * t;
			vec3 c = cp2.position * (1.0f - t) + cp3.position * t;

			vec3 a1 = a * (1.0f - t) + c * t;
			vec3 b1 = c * (1.0f - t) + b * t;
			
			return a1 * (1.0f - t) + b1 * t;
		};

		setColor(vec3(1, 0, 1));
		float inc = 1 / (float)steps;
		for (float i = 0; i < 1 - inc + .001; i += inc)
		{
			vec3 p1 = p(i);
			vec3 p2 = p(i + inc);
			drawLine(p1, p2);
		}
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

	void animateParticle(particle& p, float speed, float& t, controlPoint cp1, controlPoint cp2, controlPoint cp3, controlPoint cp4) 
	{
		auto f = [cp1, cp2, cp3, cp4](float t) {
			return (float)pow((1 - t), 3) * cp1.position + 3 * t * (float)pow((1 - t), 2) * cp2.position + 3 * (float)pow(t, 2) * (1 - t) * cp3.position + (float)pow(t, 3) * cp4.position;
		};

		float dt = Framework::dt();

		if (t > 1) t = 0;
		t += dt / 5;
		p.position = f(t);
		
		setColor(p.color);
		drawSphere(p.position, p.radius);
	};

private:
	controlPoint cp1, cp2, cp3, cp4;
	bool mouseDown = false;
	bool bez = false;

	particle p;
	float t;

};

int main(int argc, char** argv) {
	ParticleCubic viewer;
	viewer.run();
}

