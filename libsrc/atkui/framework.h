#ifndef ATKUI_Framework_H_
#define ATKUI_Framework_H_

#include "atk/toolkit.h"
#include "agl/window.h"
#include "agl/aglm.h"
#include "atkmath/quaternion.h"
#include <vector>

namespace atkui {
enum Display { Orthographic, Perspective };

class Framework : public agl::Window {
 public:
  Framework(Display type, int width = 500, int height = 500);
  virtual ~Framework();

 protected:
  virtual void scene() {} // override to update and draw custom components
  virtual void draw() override;
  bool _type;

 public:
  virtual void setColor(const glm::vec3& c);
  virtual void push();
  virtual void pop();
  virtual void rotate(float angle, const glm::vec3& axis);
  virtual void translate(const glm::vec3& pos);
  virtual void scale(const glm::vec3& size);
  virtual void transform(const atk::trs& trs);
  virtual void transform(const glm::mat4& trs);
  virtual void drawTeapot(const glm::vec3& pos, float size);
  virtual void drawCube(const glm::vec3& pos, const glm::vec3& size, const atkmath::Quaternion& rot = atkmath::Quaternion::Identity);
  virtual void drawSphere(const glm::vec3& pos, float radius);
  virtual void drawLine(const glm::vec3& a, const glm::vec3& b);
  virtual void drawCone(const glm::vec3& pos, float size);
  virtual void drawTorus(const glm::vec3& pos, float size);
  virtual void drawCylinder(const glm::vec3& pos, float size);
  virtual void drawFloor(float size, float big = 200, float small = 50);
  virtual void drawText(const std::string& msg, float x, float y); // x in [0, width]; y in [0, height]
  virtual void drawEllipsoid(const glm::vec3& a, const glm::vec3& b, float width); 
  virtual void drawCircle(const glm::vec3& p, float r, int numVertices = 20);
  virtual void beginShader(const std::string& name);
  virtual void endShader();

  virtual glm::vec2 worldToScreen(const glm::vec3& p);
  virtual glm::vec3 screenToWorld(const glm::vec2& screenPos);

 private:
  glm::vec3 _color;
};
}
#endif
