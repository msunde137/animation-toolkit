#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class Gradient : public atkui::Framework {
public:
	Gradient() : atkui::Framework(atkui::Orthographic) {
		ur = { 1, 1, 0 };
		ul = { 0, 1, 1 };
		br = { 1, 0, 1 };
		bl = { 0, 0, 1 };
		divisions = 50;
		startPos = { ((float)Framework::width() / (float)divisions), 
			((float)Framework::height() / (float)divisions), 0 };
		endPos = vec3(Framework::width(), Framework::height(), 0) - startPos;
		scale = { startPos.x, startPos.y, 1 };
	}

	virtual void scene() {

		for (float i = startPos.x; i <= endPos.x; i += scale.x * 2.0f)
		{
			for (float j = startPos.y; j <= endPos.y; j += scale.y * 2.0f)
			{
				vec3 c1 = bl * (1 - i / endPos.x) + br * (i / endPos.x);
				vec3 c2 = ul * (1 - i / endPos.x) + ur * (i / endPos.x);
				vec3 c3 = c1 * (1 - j / endPos.y) + c2 * (i / endPos.y);

				setColor(c3);
				drawCube({ i, j, 0 }, scale * 2.0f);
			}
		}
	}

	vec3 ur, ul, br, bl;
	int divisions;
	vec3 startPos, endPos;
	vec3 scale;
};

int main(int argc, char **argv) {
	Gradient viewer;
	viewer.run();
}
