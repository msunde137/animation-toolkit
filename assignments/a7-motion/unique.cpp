#include <map>
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include "atk/toolkit.h"
#include <iostream>
#include <cmath>
using namespace glm;
using namespace std;
using namespace atk;

class Unique : public atkui::Framework
{
public:
    Unique() : atkui::Framework(atkui::Orthographic) {}
    ~Unique() = default;

    virtual void setup()
    {
        //Joint* root = new Joint("root");
        //root->setLocalTranslation(vec3(width() / 2.0f, height() - height() / 3.0f, 0));
        //root->setLocalRotation(glm::angleAxis(angle, vec3(0, 0, 1)));
        //skeleton.addJoint(root);

        //Joint* j1 = new Joint("joint1");
        //j1->setLocalTranslation(vec3(0, -75, 0));
        //j1->setLocalRotation(glm::angleA s(angle1, vec3(0, 0, 1)));
        //skeleton.addJoint(j1, root);

        //Joint* j2 = new Joint("joint2");
        //j2->setLocalTranslation(vec3(0, -75, 0));
        //skeleton.addJoint(j2, j1);
        //skeleton.fk();

        angle = glm::pi<float>() / 2.0f;
        Transform root = Transform(
            glm::angleAxis(angle, vec3(0, 0, 1)), vec3(vec3(width() / 2.0f, height() - height() / 3.0f, 0))
        );
        transforms["root"] = root;
        angle1 = glm::pi<float>() / 2.0f;
        Transform p1 = root * Transform(
            glm::angleAxis(angle1, vec3(0, 0, 1)), vec3(0.0f, -75.0f, 0.0f)
        );
        transforms["point1"] = p1;
        position1 = p1.t();
        Transform p2 = p1 * Transform(
            glm::angleAxis(0.0f, vec3(0)), vec3(0.0f, -75.0f, 0.0f)
        );
        transforms["point2"] = p2;
        position2 = p2.t();
    }

    virtual void scene() 
    {
        setColor(vec3(1, 0, 0));


        //vec3 rt = skeleton.getByName("root")- etGlobalTranslation();
        //vec3 j1t = skeleton.getByName("joint1")->getGlobalTranslation();
        //vec3 j2t = skeleton.getByName("joint2")->getGlobalTranslation();
        //vec3 d = glm::normalize(rt - j1t);
        //vec3 d1 = glm::normalize(j1t - j2t);

        //dangle += glm::dot(vec3(0, -1, 0), glm::cross(d, vec3(0, 0, 1))) * dt();
        //angle += dangle * dt();
        //skeleton.getByName("root")->setLocalRotation(glm::angleAxis(angle, vec3(0, 0, 1)));

        //dangle1 += g ::dot(vec3(0, -1, 0), glm::cross(d1, vec3(0, 0, 1))) * dt();
        //angle1 += dangle1 * dt();
        //skeleton.getByName("joint1")->setLocalRotation(glm::angleAxis(angle1, vec3(0, 0, 1)));

        //skeleton.fk();

        vec3 rt = transforms["root"].t();
        vec3 p2t = transforms["point2"].t();
        vec3 p1t = transforms["point1"].t();

        vec3 d = glm::normalize(p1t - rt);
        vec3 d1 = glm::normalize(p2t - p1t);
        vec3 tangent1 = glm::cross(d, vec3(0, 0, 1));
        vec3 tangent2 = glm::cross(d1, vec3(0, 0, 1));

        //vec3 a1 = glm::dot(-tangent1, vec3(0, -1, 0)) * tangent1;
        //vec3 a2 = (glm::dot(-tangent2, vec3(0, -1, 0)) * glm::dot(d, d1) * tangent2 +
        //    vec3(0, -1, 0) * glm::dot(tangent1, tangent2));

        //velocity1 += a1 * dt();
        //velocity2 += a2 * dt();
        //position1 += velocity1 * dt();
        //position2 += velocity2 * dt();

        dangle1 += std::tan(1 / glm::length(d1)) * dt() * 
            glm::dot(tangent2, vec3(0, 1, 0));
        angle1 += dangle1 * dt();

        dangle += std::tan(1 / glm::length(d)) * dt() * glm::dot(tangent1, vec3(0, 1, 0));
        angle += dangle * dt();



        transforms["root"].setR(glm::angleAxis(angle, vec3(0, 0, 1)));
        transforms["point1"] = transforms["root"] *
            Transform(glm::angleAxis(0.0f, vec3(0)), vec3(0, -75, 0));
        transforms["point1"].setR(glm::angleAxis(angle1, vec3(0, 0, 1)));

        transforms["point2"] = transforms["point1"] *
            Transform(glm::angleAxis(0.0f, vec3(0)), vec3(0, -75, 0));


        drawSphere(transforms["root"].t(), 10);
        drawLine(transforms["root"].t(), transforms["point1"].t());
        drawSphere(transforms["point1"].t(), 10);
        drawLine(transforms["point1"].t(), transforms["point2"].t());
        drawSphere(transforms["point2"].t(), 10);
    }

private:

    std::map<std::string, Transform> transforms;
    Skeleton skeleton;

    float angle = 0.0f;
    float dangle = 0.0f;

    float angle1 = 0.0f;
    float dangle1 = 0.0f;

    vec3 velocity1 = vec3(0), velocity2 = vec3(0);
    vec3 position1, position2;

};

int main(int argc, char** argv) {
    Unique viewer;
    viewer.run();
}
