#ifndef teapots_H_
#define teapots_H_

#include "atkui/framework.h"
#include "atkmath/vector3.h"

class TeapotsViewer : public atkui::Framework {
 public:
  TeapotsViewer();
  virtual ~TeapotsViewer();

 protected:

  enum RotOrder { XYZ, XZY, YXZ, YZX, ZXY, ZYX } mRotOrder;

  virtual void setup();
  virtual void scene();
  virtual void runGui();
  virtual void teapots();
  virtual void drawText(const std::string& text, float x, float y);
  virtual void pushEulerRotation(RotOrder roo, const atkmath::Vector3& euler);

protected:
  float mXAngle, mYAngle, mZAngle;
};

#endif
