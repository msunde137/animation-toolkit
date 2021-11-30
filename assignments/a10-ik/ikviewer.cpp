#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include "ik_controller.h"
#include <algorithm>
#include <string>
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

using namespace atk;
using namespace glm;
using namespace std;

class AIKViewer : public atkui::Framework
{
public:
  AIKViewer() : atkui::Framework(atkui::Perspective),
                mIKChainSize(-1),
                mThreshold(10),
                mNudge(0.1),
                mEpsilon(0.001),
                mMaxIters(50),
                mType(CCD) {
    setWindowSize(1000,800);
  }

  virtual ~AIKViewer() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

protected:
  virtual void setup() {

    BVHReader bvhLoader;
    bool v = bvhLoader.load("../motions/Beta/Beta.bvh", mActor, mMotion);
    assert(v);
    reset();

    // assemble joint list for UI
    mJointChoices = "";
    for (int i = 0; i < mActor.getNumJoints(); i++) {
      mJointChoices += mActor.getByID(i)->getName() + '\0';
    }
    mJointChoices += '\0';

    vec3 eye = vec3(-50, 100, 323);
    lookAt(eye, vec3(-50, 100, 0) );

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

  virtual void reset() {
    mActor.setPose(mMotion.getKey(0));
    mActor.fk();

    Joint* hand = mActor.getByName("Beta:LeftHand");
    mSelectedJoint = hand->getID();
    mGoalPosition = hand->getGlobalTranslation();
    computeIKChain();
  }

  virtual void draw() {
    if (mSelectedJoint != -1) {
      if (mType == ANALYTIC)
      {
        mIKController.solveIKAnalytic(mActor, mSelectedJoint, mGoalPosition, mEpsilon);
      }
      else
      {
        mIKController.solveIKCCD(mActor, mSelectedJoint,
          mGoalPosition, mChain, mThreshold, mMaxIters, mNudge);
      }
    }

    mDrawer.draw(mActor, *this);
    drawFloor(2000, 20, 50);

    vec2 screenPos = worldToScreen(mGoalPosition);

    ortho(0, width(), 0, height(), -1000, 1000);
    renderer.lookAt(vec3(0,0,1), vec3(0), vec3(0,1,0));

    vec3 c = vec3(screenPos, 0);
    vec3 v1 = c + vec3(10,0,0);
    vec3 v2 = c - vec3(10,0,0);
    vec3 h1 = c + vec3(0,10,0);
    vec3 h2 = c - vec3(0,10,0);

    beginShader("unlit");
    setColor(vec3(1.0, 0.0, 1.0));
    drawCircle(c, 5.0f);
    drawLine(v1, v2);
    drawLine(h1, h2);
    endShader();

    // reset projection
    perspective(glm::radians(60.0f), width()/(float)height(), 10.0f, 2000.0f);
    renderer.lookAt(camera.position(), camera.look(), camera.up());

    // draw GUI
    static const char* type[] = {"Analytic", "CCD"};

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Demo Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SetWindowSize(ImVec2(150, 450));
    ImGui::SetWindowPos(ImVec2(5, 5));
    ImGui::SliderFloat("X", &mGoalPosition[0], -500.0f, 500.0f);
    ImGui::SliderFloat("Y", &mGoalPosition[1], -500.0f, 500.0f);
    ImGui::SliderFloat("Z", &mGoalPosition[2], -500.0f, 500.0f);
    if (ImGui::Button("Reset")) reset();

    int chainSize = mIKChainSize;
    int selectedJoint = mSelectedJoint;
    ImGui::Separator();
    ImGui::Combo("Type", (int*) &mType, type, 2);
    ImGui::Combo("Joint", (int*) &selectedJoint, mJointChoices.c_str());
    ImGui::SliderFloat("Epsilon", &mEpsilon, 0.001f, 1.0f);
    ImGui::InputFloat("Threshold", &mThreshold, 0.01f, 100.0f);
    ImGui::InputFloat("Nudge", &mNudge, 0.001f, 1.0f);
    ImGui::InputInt("Max Iterations", &mMaxIters, 50);
    ImGui::InputInt("Chain Length", &chainSize, -1);
    ImGui::End();

    if (chainSize != mIKChainSize || mSelectedJoint != selectedJoint) {
      mIKChainSize = chainSize;
      mSelectedJoint = selectedJoint;
      mGoalPosition = mActor.getByID(mSelectedJoint)->getGlobalTranslation();
      computeIKChain();
    }

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  virtual void computeIKChain() {
    mChain.clear();
    int num = mIKChainSize == -1? mActor.getNumJoints() : mIKChainSize;
    for (Joint* current = mActor.getByID(mSelectedJoint); 
        current->getParent() && mChain.size() < num; 
        current = current->getParent()) {
      mChain.push_back(current);
    }
  }

  virtual void mouseMotion(int px, int py, int dx, int dy) {
    setCameraEnabled(px > 350 || py > 350);
  }

protected:
  IKController mIKController;
  Skeleton mActor;
  Motion mMotion;
  atkui::SkeletonDrawer mDrawer;
  std::vector<Joint*> mChain;
  vec3 mGoalPosition;
  int mSelectedJoint;
  int mIKChainSize;
  float mEpsilon;
  float mThreshold;
  float mNudge;
  int mMaxIters;
  enum IKType
  {
    ANALYTIC,
    CCD
  } mType;

  std::string mJointChoices; 
};

int main(int argc, char **argv)
{
  AIKViewer viewer;
  viewer.run();
  return 0;
}
