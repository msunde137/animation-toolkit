#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>
#include "atk/toolkit.h"
#include "atkui/skeleton_drawer.h"
#include "atkui/framework.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

using namespace atk;
using namespace glm;

class Unique : public atkui::Framework
{
public:
	Unique()
		: atkui::Framework(atkui::Perspective), mDrawer(), mGoalPosition()
	{
		mDrawer.showAxes = true;
		mDrawer.color = vec3(0.6, 1.0, 0.4);
	}

	virtual ~Unique()
	{
	}

	void setup()
	{
		
		Joint* shoulder = new Joint("Shoulder");
		mActor.addJoint(shoulder);
		shoulder->setLocalTranslation(vec3(0, 180, 0));

		Joint* elbow = new Joint("Elbow");
		mActor.addJoint(elbow, shoulder);
		elbow->setLocalTranslation(vec3(100, 0, 0));

		Joint* wrist = new Joint("Wrist");
		mActor.addJoint(wrist, elbow);
		wrist->setLocalTranslation(vec3(80, 0, 0));

		mActor.fk();
		mGoalPosition = vec3(0, 1, 0);
	}


	void draw()
	{
		mDrawer.draw(mActor, *this);
		drawFloor(2000, 20, 50);

		vec2 screenPos = worldToScreen(mGoalPosition);

		setColor(vec3(1.0, 0.0, 1.0));
		ortho(0, width(), 0, height(), -1000, 1000);
		renderer.lookAt(vec3(0, 0, 1), vec3(0), vec3(0, 1, 0));

		vec3 c = vec3(screenPos, 0);
		vec3 v1 = c + vec3(10, 0, 0);
		vec3 v2 = c - vec3(10, 0, 0);
		vec3 h1 = c + vec3(0, 10, 0);
		vec3 h2 = c - vec3(0, 10, 0);

		beginShader("unlit");
		drawCircle(c, 5.0f);
		drawLine(v1, v2);
		drawLine(h1, h2);
		endShader();

		// reset projection
		perspective(glm::radians(60.0f), width() / (float)height(), 10.0f, 2000.0f);
		renderer.lookAt(camera.position(), camera.look(), camera.up());

		std::cout << dt() << std::endl;
		mActor.getRoot()->setLocalTranslation(vec3(0, 150 + 100 * cos(elapsedTime()), 0));
		solveIKTwoLink(mActor, mGoalPosition);
	}

	void solveIKTwoLink(Skeleton& skeleton, const vec3& goalPosition)
	{
		Joint* s = skeleton.getByName("Shoulder");
		Joint* e = skeleton.getByName("Elbow");
		Joint* w = skeleton.getByName("Wrist");
		float l1 = distance(s->getGlobalTranslation(), w->getGlobalTranslation());
		float l2 = distance(s->getGlobalTranslation(), e->getGlobalTranslation());
		float l3 = distance(e->getGlobalTranslation(), w->getGlobalTranslation());
		float d = distance(goalPosition, s->getGlobalTranslation());
		if (d >= l2 + l3)
		{
			vec3 axis = cross(vec3(1, 0, 0), normalize(goalPosition));
			if (axis != vec3(0)) axis = normalize(axis);
			else axis = vec3(0, 1, 0);
			float angle = -glm::acos(dot(vec3(1, 0, 0), normalize(goalPosition)));
			s->setLocalRotation(glm::angleAxis(angle, axis));
			e->setLocalRotation(glm::angleAxis(0.0f, vec3(0)));
		}
		else if (d < l2 - l3)
		{
			vec3 axis = cross(vec3(1, 0, 0), normalize(goalPosition));
			if (axis != vec3(0)) axis = normalize(axis);
			else axis = vec3(0, 1, 0);
			float angle = glm::acos(dot(vec3(1, 0, 0), normalize(goalPosition)));
			s->setLocalRotation(glm::angleAxis(angle, axis));
			e->setLocalRotation(glm::angleAxis(glm::pi<float>(), axis));
		}
		else
		{
			vec3 axis1 = cross(vec3(1, 0, 0), normalize(goalPosition));
			if (axis1 != vec3(0)) axis1 = normalize(axis1);
			else axis1 = vec3(0, 1, 0);
			float angle = - glm::acos(dot(vec3(1, 0, 0), normalize(goalPosition)));

			float a1 = acos((l2 * l2 + d * d - l3 * l3) / (2.0f * l2 * d));
			float a2 = glm::pi<float>() + acos((l3 * l3 + l2 * l2 - d * d) / (2.0f * l3 * l2));
			vec3 axis = vec3(0, 0, 1);
			s->setLocalRotation(glm::angleAxis(angle, axis1) * glm::angleAxis(a1, axis));
			e->setLocalRotation(glm::angleAxis(a2, axis));
		}

		skeleton.fk();
	}

private:
	atk::Skeleton mActor;
	atkui::SkeletonDrawer mDrawer;
	glm::vec3 mGoalPosition;
};

int main(int argc, char** argv)
{
	Unique viewer;
	viewer.run();
	return 0;
}
