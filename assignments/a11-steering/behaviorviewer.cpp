#include <string>
#include "behaviorviewer.h"
#include <algorithm>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

using namespace glm;
using namespace atk;

ABehaviorViewer::ABehaviorViewer() : 
   atkui::Framework(atkui::Perspective),
   _world(), _target(100,0,100),
   _numAgents(5), _numObstacles(5)
{
   _behaviors[SEEK] = new ASeek();
   _behaviors[FLEE] = new AFlee();
   _behaviors[ARRIVAL] = new AArrival();
   _behaviors[DEPARTURE] = new ADeparture();
   _behaviors[COHESION] = new ACohesion();
   _behaviors[ALIGNMENT] = new AAlignment();
   _behaviors[SEPARATION] = new ASeparation();
   _behaviors[LEADER] = new ALeader();
   _behaviors[FLOCKING] = new AFlocking();
   _behaviors[AVOID] = new AAvoid();
   _behaviors[WANDER] = new AWander();
   setWindowSize(1000,800);
}

ABehaviorViewer::~ABehaviorViewer()
{
   for (BehaviorIt it = _behaviors.begin(); it != _behaviors.end(); it++)
   {
      delete it->second;
   }
   _behaviors.clear();

   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();

/*
   for (unsigned int i = 0; i < _uiParams.size(); i++)
   {
      delete _uiParams[i];
   }
   _uiParams.clear();
*/
}

void ABehaviorViewer::setup()
{
   _beType = SEEK;
   reset(_numAgents, _numObstacles);

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

   for (BehaviorIt it = _behaviors.begin(); it != _behaviors.end(); ++it)
   {
      _uiParams[it->first] = std::map<std::string,float>();
      for (int i = 0; i < it->second->getNumParams(); i++)
      {
         std::string paramName = it->second->getParamName(i);
         float value = it->second->getParamValue(i);
         _uiParams[it->first][paramName] = value;
      }
   }
}

void ABehaviorViewer::setBehavior(BehaviorType type)
{
    _beType = type;
    AWorld::kDrawObstacles = (_beType == AVOID);
}

void ABehaviorViewer::draw()
{
   update();

   _world.draw(*this);
   setColor(vec3(1,0,0));
   drawSphere(_target, 10);
   drawFloor(2000, 20, 50);

   runGui();
}

void ABehaviorViewer::update()
{
   if (!_paused)
   {
      for (int i = 0; i < _world.getNumAgents(); i++)
      {
         ASteerable& agent = _world.getAgent(i);
         vec3 dvel = _behaviors[_beType]->calculateDesiredVelocity(agent, _world, _target);
         agent.update(dvel, dt());
      }
   }
}

void ABehaviorViewer::mouseUp(int button, int mods)
{
   vec2 mousePos = mousePosition();
   if (mods == GLFW_MOD_CONTROL) // move target
   {
      vec3 target = screenToWorld(vec2(mousePos[0], height() - mousePos[1]));
      vec3 origin = camera.position();
      vec3 dir = target - origin;

      // Intersect with XZ plane when?
      float t = -origin[1] / dir[1];
      _target = origin + t*dir;
   }
}

void ABehaviorViewer::mouseMotion(int px, int py, int dx, int dy) 
{
   setCameraEnabled(px > 350);
}

void ABehaviorViewer::keyUp(int key, int mods)
{
   if (key == ' ') reset(_numAgents, _numObstacles);
}

void ABehaviorViewer::reset(int numAgents, int numObstacles)
{
   setupPerspectiveScene(vec3(0,0,0), vec3(1000,1500,1000));

   _numAgents = numAgents;
   _numObstacles = numObstacles;
   _world.clear();
   _world.setNumAgents(_numAgents);
   _world.setNumObstacles(_numObstacles);
   _world.reset();

   setBehavior(_beType);
}

void ABehaviorViewer::runGui()
{
   ImGui_ImplOpenGL3_NewFrame();
   ImGui_ImplGlfw_NewFrame();
   ImGui::NewFrame();

   static const char* type[] = {
      "Seek", "Flee", "Arrival", "Departure", "Avoid", "Alignment",
      "Wander", "Separation", "Cohesion", "Flocking", "Leader"
   };

   ImGui::Begin("Demo Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize);
   ImGui::SetWindowSize(ImVec2(150, 600));
   ImGui::SetWindowPos(ImVec2(5, 5));
   ImGui::Checkbox("Paused", &_paused);
   ImGui::Checkbox("Debug draw", &ASteerable::kDebugDraw);
   ImGui::Separator();
   if (ImGui::Button("Reset")) reset(_numAgents, _numObstacles);
   ImGui::InputInt("Num agents", &_numAgents);
   ImGui::InputInt("Num obstacles", &_numObstacles);
   ImGui::Combo("Type", (int*) &_beType, type, 11);
   ImGui::Separator();
   ImGui::Text("Parameters:");

   setBehavior(_beType);
   ABehavior* behavior = _behaviors[_beType];
   for (int i = 0; i < behavior->getNumParams(); i++)
   {
      std::string paramName = behavior->getParamName(i);
      float value = behavior->getParamValue(i);
      ImGui::InputFloat(paramName.c_str(), &value);
      behavior->setParam(paramName, value);
   }
   ImGui::End();

   // Rendering
   ImGui::Render();
   ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main(int argc, char** argv)
{
   ABehaviorViewer viewer;
	viewer.run();
	return 0;
}

