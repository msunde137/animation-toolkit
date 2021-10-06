#include "teapots.h"
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

using glm::vec3;
using atkmath::Deg2Rad;
using atkmath::Rad2Deg;
using atkmath::Matrix3;
using atkmath::Vector3;
using atkmath::Quaternion;

TeapotsViewer::TeapotsViewer() : atkui::Framework(atkui::Orthographic), 
	mRotOrder(XYZ),
	mXAngle(50), mYAngle(0), mZAngle(0) {
}

void TeapotsViewer::scene() {
  renderer.beginShader("phong");
  renderer.ortho(-5, 5, -5, 5, 0.01, 100);
  renderer.lookAt(vec3(0, 0, -10), vec3(0, 0, 0), vec3(0, 1, 0));
  teapots();
  renderer.endShader();

  drawText("Euler to matrix", width()*0.675, height()*0.675+50); // top, right
  drawText("YXZ", width()*0.5, height()*0.675+50); // top, middle
  drawText("ZYX", width()*0.325, height()*0.675+50); // top, left

  drawText("XYZ", width()*0.675, height()*0.5+50); // middle, right
  drawText("YZX", width()*0.5, height()*0.5+50); // center
  drawText("Quat", width()*0.325, height()*0.5+50); // middle, left

  drawText("XZY", width()*0.675, height()*0.325+50); // middle, right
  drawText("ZXY", width()*0.5, height()*0.325+50); // center
  drawText("Quat to Matrix", width()*0.325, height()*0.325+50); // middle, left

  runGui();
}

void TeapotsViewer::drawText(const std::string& text, float x, float y) {
  x = x - renderer.textWidth(text)*0.5;
  y = height() - y;
  renderer.text(text, x, y);
}

void TeapotsViewer::pushEulerRotation(TeapotsViewer::RotOrder roo, const Vector3& euler) {
  Vector3 anglesRad = euler * Deg2Rad;
  switch (roo)
  {
  case XYZ: 
    rotate(anglesRad[0], vec3(1, 0, 0));
    rotate(anglesRad[1], vec3(0, 1, 0));
    rotate(anglesRad[2], vec3(0, 0, 1));
    break;
  case XZY: 
    rotate(anglesRad[0], vec3(1, 0, 0));
    rotate(anglesRad[2], vec3(0, 0, 1));
    rotate(anglesRad[1], vec3(0, 1, 0));
    break;
  case YXZ: 
    rotate(anglesRad[1], vec3(0, 1, 0));
    rotate(anglesRad[0], vec3(1, 0, 0));
    rotate(anglesRad[2], vec3(0, 0, 1));
    break;
  case YZX: 
    rotate(anglesRad[1], vec3(0, 1, 0));
    rotate(anglesRad[2], vec3(0, 0, 1));
    rotate(anglesRad[0], vec3(1, 0, 0));
    break;
  case ZXY: 
    rotate(anglesRad[2], vec3(0, 0, 1));
    rotate(anglesRad[0], vec3(1, 0, 0));
    rotate(anglesRad[1], vec3(0, 1, 0));
    break;
  case ZYX: 
    rotate(anglesRad[2], vec3(0, 0, 1));
    rotate(anglesRad[1], vec3(0, 1, 0));
    rotate(anglesRad[0], vec3(1, 0, 0));
    break;
  }
}

void TeapotsViewer::teapots()
{
  // test euler to matrix
  Matrix3 rot;
  Vector3 euler(mXAngle, mYAngle, mZAngle);
  switch (mRotOrder)
  {
  case XYZ: rot.fromEulerAnglesXYZ(euler*Deg2Rad); break;
  case XZY: rot.fromEulerAnglesXZY(euler*Deg2Rad); break;
  case YXZ: rot.fromEulerAnglesYXZ(euler*Deg2Rad); break;
  case YZX: rot.fromEulerAnglesYZX(euler*Deg2Rad); break;
  case ZXY: rot.fromEulerAnglesZXY(euler*Deg2Rad); break;
  case ZYX: rot.fromEulerAnglesZYX(euler*Deg2Rad); break;
  }

  glm::mat4 rotm = rot.writeToMat4();
  Vector3 testXYZ, testXZY, testYXZ, testYZX, testZXY, testZYX;

  testXYZ = rot.toEulerAnglesXYZ();
  testXZY = rot.toEulerAnglesXZY();
  testYXZ = rot.toEulerAnglesYXZ();
  testYZX = rot.toEulerAnglesYZX();
  testZXY = rot.toEulerAnglesZXY();
  testZYX = rot.toEulerAnglesZYX();

  testXYZ = testXYZ * Rad2Deg;
  testXZY = testXZY * Rad2Deg;
  testYXZ = testYXZ * Rad2Deg;
  testYZX = testYZX * Rad2Deg;
  testZXY = testZXY * Rad2Deg;
  testZYX = testZYX * Rad2Deg;

  Quaternion quat;
  quat.fromMatrix(rot);
  Vector3 axis(1,0,0); double angle = 0;
  quat.toAxisAngle(axis, angle);

  Matrix3 qmat = quat.toMatrix();
  glm::mat4 qglm = qmat.writeToMat4();

  float size = 1.25f;
  // EXAMPLE: Euler angles mRotOrder
  setColor(vec3(1, 0, 0));
  push();
  translate(vec3(-3.5, 3.5, 0));
  pushEulerRotation(mRotOrder, euler);
  drawTeapot(vec3(0.0), size);
  pop();

  // TEST CONVERTING EULER mRotOrder to Matrix
  setColor(vec3(1, 0.5, 1));
  push();
  translate(vec3(-1.75, 1.75, 0));
  transform(rotm);
  drawTeapot(vec3(0), size);
  pop();
  
  // TEST CONVERTING matrix to EULER XYZ
  setColor(vec3(0, 0.5, 1));
  push();
  translate(vec3(-1.75, 0, 0));
  pushEulerRotation(XYZ, testXYZ);
  drawTeapot(vec3(0), size);
  pop();

  // TEST CONVERTING matrix to EULER XZY
  push();
  translate(vec3(-1.75, -1.75, 0));
  pushEulerRotation(XZY, testXZY);
  drawTeapot(vec3(0), size);
  pop();

  // TEST CONVERTING matrix to EULER YXZ
  push();
  translate(vec3(0, 1.75, 0));
  pushEulerRotation(YXZ, testYXZ);
  drawTeapot(vec3(0), size);
  pop();

  // TEST CONVERTING matrix to EULER YZX
  push();
  translate(vec3(0, 0, 0));
  pushEulerRotation(YZX, testYZX);
  drawTeapot(vec3(0), size);
  pop();

  // TEST CONVERTING matrix to EULER ZXY
  push();
  translate(vec3(0, -1.75, 0));
  pushEulerRotation(ZXY, testZXY);
  drawTeapot(vec3(0), size);
  pop();

  // TEST CONVERTING matrix to EULER ZYX
  push();
  translate(vec3(1.75, 1.75, 0));
  pushEulerRotation(ZYX, testZYX);
  drawTeapot(vec3(0), size);
  pop();

  // TEST CONVERTING matrix to quaternion to angle/axis
  setColor(vec3(0.5, 1, 0.5));
  push();
  translate(vec3(1.75, 0, 0));
  rotate(angle, vec3(axis[0], axis[1], axis[2]));
  drawTeapot(vec3(0), size);
  pop();
  
  // TEST CONVERTING quaternion to matrix
  push();
  translate(vec3(1.75, -1.75, 0));
  transform(qglm);
  drawTeapot(vec3(0), size);
  pop();

}

void TeapotsViewer::setup() {
  setWindowSize(800, 800);
  background(vec3(0));
  setCameraEnabled(false);
  renderer.fontSize(18);

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

TeapotsViewer::~TeapotsViewer() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void TeapotsViewer::runGui() {

  static const char* mGuiRoo[] = { "XYZ", "XZY", "YXZ", "YZX", "ZXY", "ZYX" };

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Demo Controls");
  ImGui::SetWindowSize(ImVec2(400, 150));
  ImGui::SetWindowPos(ImVec2(5, 5));
  ImGui::SliderFloat("X Rotation", &mXAngle, 0.0f, 360.0f);
  ImGui::SliderFloat("Y Rotation", &mYAngle, 0.0f, 360.0f);
  ImGui::SliderFloat("Z Rotation", &mZAngle, 0.0f, 360.0f);
  ImGui::Combo("Rotation Order", (int*) &mRotOrder, mGuiRoo, 6);
  ImGui::End();

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main(int argc, char** argv) {
  TeapotsViewer teapots;
  teapots.run();
}
