#include "ik_controller.h"
#include <cmath>
#include <iostream>

using namespace atk;
using namespace glm;
using namespace std;

bool IKController::solveIKAnalytic(Skeleton& skeleton,
	int jointid, const vec3& goalPos, float epsilon) {
	if (jointid == -1) return true;

	Joint* w = skeleton.getByID(jointid);
	if (!w->getParent()) {
		std::cout << "Warning: solveIKAnalytic() needs joint "
			"with parent and grandparent\n";
		return false;
	}

	Joint* e = w->getParent();
	if (!e->getParent()) {
		std::cout << "Warning: solveIKAnalytic() needs joint "
			"with parent and grandparent\n";
		return false;
	}

	Joint* s = e->getParent();

	float l1 = distance(s->getGlobalTranslation(), w->getGlobalTranslation());
	float l2 = distance(s->getGlobalTranslation(), e->getGlobalTranslation());
	float l3 = distance(e->getGlobalTranslation(), w->getGlobalTranslation());
	float d = distance(goalPos, s->getGlobalTranslation());
	if (d >= l2 + l3)
	{
		vec3 axis = cross(vec3(1, 0, 0), normalize(goalPos));
		if (axis != vec3(0)) axis = normalize(axis);
		else axis = vec3(0, 1, 0);
		float angle = -glm::acos(dot(vec3(1, 0, 0), normalize(goalPos)));
		s->setLocalRotation(glm::angleAxis(angle, axis));
		e->setLocalRotation(glm::angleAxis(0.0f, vec3(0)));
	}
	else if (d < l2 - l3)
	{
		vec3 axis = cross(vec3(1, 0, 0), normalize(goalPos));
		if (axis != vec3(0)) axis = normalize(axis);
		else axis = vec3(0, 1, 0);
		float angle = glm::acos(dot(vec3(1, 0, 0), normalize(goalPos)));
		s->setLocalRotation(glm::angleAxis(angle, axis));
		e->setLocalRotation(glm::angleAxis(glm::pi<float>(), axis));
	}
	else
	{
		vec3 axis1 = cross(vec3(1, 0, 0), normalize(goalPos));
		if (axis1 != vec3(0)) axis1 = normalize(axis1);
		else axis1 = vec3(0, 1, 0);
		float angle = -glm::acos(dot(vec3(1, 0, 0), normalize(goalPos)));

		float a1 = acos((l2 * l2 + d * d - l3 * l3) / (2.0f * l2 * d));
		float a2 = glm::pi<float>() + acos((l3 * l3 + l2 * l2 - d * d) / (2.0f * l3 * l2));
		vec3 axis = vec3(0, 0, 1);
		s->setLocalRotation(glm::angleAxis(angle, axis1) * glm::angleAxis(a1, axis));
		e->setLocalRotation(glm::angleAxis(a2, axis));
	}

	skeleton.fk();
}

bool IKController::solveIKCCD(Skeleton& skeleton, int jointid,
	const vec3& goalPos, const std::vector<Joint*>& chain,
	float threshold, int maxIters, float nudgeFactor) 
{
	// There are no joints in the IK chain for manipulation
	if (chain.size() == 0)
		return true;
	else if (chain.size() < 3)
	{
		int i = 0;
		while (glm::distance(goalPos, chain[chain.size() - 1]->getGlobalTranslation()) > threshold &&
			i < maxIters)
		{
			Joint* first = chain[0];
			Joint* second = chain[1];
			vec3 firstpos = first->getGlobalTranslation();
			vec3 secondpos = second->getGlobalTranslation();
			vec3 v1 = normalize(firstpos - secondpos);
			vec3 v2 = normalize(goalPos - secondpos);
			float angle = glm::acos(clamp(glm::dot(v1, v2), 0.0f, 1.0f));
			vec3 axis = glm::cross(v1, v2);
			if (length(axis) != 0) axis = normalize(axis);
			second->setLocalRotation(second->getLocalRotation() * glm::angleAxis(angle * nudgeFactor, axis));
			skeleton.fk();
		}

	}
	else
	{
		int i = 0;
		while (glm::distance(goalPos, chain[chain.size() - 1]->getGlobalTranslation()) > threshold &&
			i < maxIters)
		{
			Joint* first = chain[0];
			for (int j = chain.size() - 1; j > 0; j--)
			{
				Joint* second = chain[j];
				vec3 firstpos = first->getGlobalTranslation();
				vec3 secondpos = second->getGlobalTranslation();
				vec3 v1 = normalize(firstpos - secondpos);
				vec3 v2 = normalize(goalPos - secondpos);
				float angle = glm::acos(clamp(glm::dot(v1, v2), 0.0f, 1.0f));
				vec3 axis = glm::cross(v1, v2);
				if (length(axis) != 0) axis = normalize(axis);
				else axis = vec3(0, 1, 0);
				second->setLocalRotation(second->getLocalRotation() * glm::angleAxis(angle * nudgeFactor, axis));
			}
			skeleton.fk();
			i++;
		}
	}

	return false;
}
