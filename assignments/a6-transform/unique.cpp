#include "atkui/framework.h"
#include "atkmath/constants.h"
#include "atkmath/vector3.h"
#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <string>
#include <algorithm>
#include <iostream>

using namespace atk;
using glm::vec3;

class Unique : public atkui::Framework {
public:
    Unique() : atkui::Framework(atkui::Perspective) {}
    virtual ~Unique() 
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    virtual void setup() {
        lookAt(vec3(200), vec3(0));

        
        for (int k = -6; k < 6; k++)
        {
            for (int j = -6; j < 6; j++)
            {
                Skeleton _tentacle;
                Joint* root = new Joint("root");
                root->setLocalTranslation(vec3(k * 50, 0, j * 50));
                _tentacle.addJoint(root);

                // todo: add more joints
                Joint* last = root;
                for (int i = 0; i < 3; i++)
                {
                    Joint* j = new Joint("joint" + std::to_string(i));
                    j->setLocalTranslation(vec3(0, 50, 0));
                    _tentacle.addJoint(j, last);
                    last = j;
                }

                _tentacle.fk(); // compute local2global transforms
                tentacles.push_back(_tentacle);
            }
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

#if defined(__APPLE__)
  // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
#else
  // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
#endif
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window(), true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    virtual void scene()
    {
        // todo animate joints
        // hint: use glm::angleAxis(...) to compute quaternions for each joint
        // todo: loop over all joints and draw

        for (int k = 0; k < tentacles.size(); k++)
        {
            for (int i = 1; i < tentacles[k].getNumJoints(); i++)
            {
                Joint* j = tentacles[k].getByID(i);
                Joint* p = j->getParent();

                glm::quat q1 = p->getLocalRotation();

                //if (glm::length(q1 - q1) < .01f)
                //    v += windVariance / 1000.0f * (agl::random() - .5f) * windSpeed;
                //else
                //    v += 0;

                //angle = windSpeed * std::cos(angle) / 1000.0f - grassRigidity * std::sin(angle) / 1000.0f;
                angle += Framework::dt() * windSpeed / 1000.0f;
                float s = abs(std::sin(angle + windVariance / 1000.0f * tentacles[k].getRoot()->getGlobalTranslation().x));
                glm::quat q2 = glm::angleAxis(s * (float)std::_Pi * windSpeed / 1000.0f, vec3(0, 0, 1));

                p->setLocalRotation(glm::slerp(q1, q2, Framework::dt() * 4.0f));

                drawEllipsoid(p->getGlobalTranslation(), j->getGlobalTranslation(), 5);

            }
            tentacles[k].fk(); // computes local2global transforms
        }

        setColor(vec3(0, 1, 0));

        drawFloor(1000);

        runGui();
    }

    void runGui() 
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Simulation Controls");
        ImGui::SetWindowSize(ImVec2(400, 150));
        ImGui::SetWindowPos(ImVec2(5, 5));
        ImGui::DragFloat("Wind Speed", &windSpeed, .1f, 0.0f, 360.0f);
        ImGui::DragFloat("Wind Variance", &windVariance, .1f, 0.0f, 360.0f);
        ImGui::DragFloat("Grass Rigidity", &grassRigidity, .1f, 0.0f, 360.0f);
        ImGui::End();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

protected:
    Skeleton _tentacle;
    std::vector<Skeleton> tentacles;
    float angle = 0.0f;

    float windSpeed = 0.0f; // force that the wind imparts
    float windVariance = 0.0f;
    float v;
    float grassRigidity = 1.0f;
};

int main(int argc, char** argv)
{
    Unique viewer;
    viewer.run();
}