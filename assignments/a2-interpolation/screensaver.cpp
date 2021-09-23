#include <vector>
#include "atkui/framework.h"
using namespace glm;


struct controlPoint
{
	vec3 position, color;
	float radius;
	bool selected;
};

struct curve
{
	controlPoint cp1, cp2, cp3, cp4;
	vec3 color;
};

class Screensaver : public atkui::Framework {

public:
	Screensaver() : atkui::Framework(atkui::Orthographic) {
	}

	void setup() {
		startCurve = getRandomCurve();
		middleCurve = startCurve;
		endCurve = getRandomCurve();

		numCurves = 100;
		curves.resize(numCurves);
	}

	void scene() {
		float dt = Framework::dt();

		middleCurve = interpolateCurves(t, startCurve, endCurve);
		t += dt / 1.5f;

		curves[i] = middleCurve;
		i++;
		if (i >= numCurves) i = 0;

		for (int j = 0; j < curves.size(); j++)
		{
			drawCurve(curves[j]);
		}

		if (t > 1)
		{
			t = 0;
			startCurve = endCurve;
			middleCurve = startCurve;
			endCurve = getRandomCurve();
		}
	}

	void drawCurve(curve c)
	{
		setColor(c.color);
		bezierAlgorithm(c.cp1, c.cp2, c.cp3, c.cp4, 50);
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

	controlPoint getRandomControlPoint()
	{
		controlPoint cp;
		cp.position = glm::abs( agl::randomUnitCube() * 2.0f * vec3(Framework::width(), Framework::height(), 0));
		return cp;
	}

	curve getRandomCurve()
	{
		curve c;
		c.cp1 = getRandomControlPoint();
		c.cp2 = getRandomControlPoint();
		c.cp3 = getRandomControlPoint();
		c.cp4 = getRandomControlPoint();
		c.color = agl::randomUnitCube() + vec3(.5);
		return c;
	}

	vec3 interpolatePoints(float t, vec3 v1, vec3 v2)
	{
		return v1 * (1.0f - t) + v2 * t;
	}

	curve interpolateCurves(float t, curve c1, curve c2)
	{
		curve c3;
		c3.cp1.position = interpolatePoints(t, c1.cp1.position, c2.cp1.position);
		c3.cp2.position = interpolatePoints(t, c1.cp2.position, c2.cp2.position);
		c3.cp3.position = interpolatePoints(t, c1.cp3.position, c2.cp3.position);
		c3.cp4.position = interpolatePoints(t, c1.cp4.position, c2.cp4.position);
		c3.color = interpolatePoints(t, c1.color, c2.color);
		return c3;
	}


private:
	curve startCurve, endCurve, middleCurve;
	std::vector<curve> curves;
	int numCurves;
	int i = 0;
	float t = 0;

	vec3 color1, color2, color3;
};

int main(int argc, char** argv) {
	Screensaver viewer;
	viewer.run();
}

