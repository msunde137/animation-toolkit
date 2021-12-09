#ifndef ACurveEditor_H_
#define ACurveEditor_H_

#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "spline.h"
#include "interpolator_hermite.h"
#include "interpolator_linear.h"
#include "interpolator_catmullrom.h"

class CurveEditor : public atkui::Framework {
 public:
  CurveEditor();
  virtual ~CurveEditor();

 protected:

  virtual void setup();
  virtual void scene();
  virtual void addPoint(const glm::vec3& p);
  virtual void deletePoint(int key);
  virtual void drawState();

  virtual void listControls();
  virtual void mouseMotion(int x, int y, int dx, int dy);
  virtual void mouseUp(int button, int mods);
  virtual void mouseDown(int button, int mods);
  virtual void keyUp(int key, int mods); 
  virtual int pickPoint(int x, int y);

 protected:

  int mRadius;
  int mSelected;
  int mButtonState;

  enum Mode { ADD, EDIT, REMOVE } mMode;
  bool mShowControlPoints;

  Spline mSpline;
  InterpolatorLinear mLinear;
  InterpolatorCatmullRom mCatmullRom;
  InterpolatorHermite mHermite;
};

#endif
