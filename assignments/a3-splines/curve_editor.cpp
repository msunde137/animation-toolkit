#include "curve_editor.h"
#include <string>
#include <iostream>
#include <algorithm>
using glm::vec3;

CurveEditor::CurveEditor() : 
  atkui::Framework(atkui::Orthographic), 
  mSpline(),
  mRadius(10.0),
  mSelected(-1),
  mButtonState(0),
  mMode(ADD), 
  mShowControlPoints(false) {

  mSpline.addInterpolationType("Linear", &mLinear);
  mSpline.addInterpolationType("Hermite", &mHermite);
  mSpline.addInterpolationType("Catmull-Rom", &mCatmullRom);

  mHermite.setClamped(true);
  mHermite.setClampedDirection(vec3(100,0,0));
}

CurveEditor::~CurveEditor() {
}

void CurveEditor::setup() {
  listControls();
}

void CurveEditor::scene() {
  drawState();
  // todo: your code here
}

void CurveEditor::addPoint(const vec3& p) {
  //std::cout << "Add key: " << p << std::endl;
  mSpline.appendKey(mSpline.getNumKeys(), p);
}

void CurveEditor::deletePoint(int key) {
  mSpline.deleteKey(key);
}

void CurveEditor::drawState() {
  int th = 25;
  switch (mMode) {
    case ADD: drawText("Mode: ADD", 5, th); break;
    case EDIT: drawText("Mode: EDIT", 5, th); break;
    case REMOVE: drawText("Mode: DELETE", 5, th); break;
  }
  th += renderer.textHeight() + 5; 
  drawText("Type: "+mSpline.getInterpolationType(), 5, th); 
}

void CurveEditor::listControls() {

  std::cout << "Key controls:" << std::endl;
  std::cout << "0: Linear" << std::endl;
  std::cout << "1: Catmull-Rom" << std::endl;
  std::cout << "2: Hermite" << std::endl;
  std::cout << "c: Toggle control points" << std::endl;
  std::cout << "h: clamp hermite on/off" << std::endl;
  std::cout << "a: add mode" << std::endl;
  std::cout << "e: edit mode" << std::endl;
  std::cout << "d: delete mode" << std::endl;
  std::cout << "SPACEBAR: clear" << std::endl;
}

void CurveEditor::mouseMotion(int pX, int pY, int dx, int dy) {
  if (mMode != EDIT) return;
  if (mSelected == -1) return;
  
  if (mButtonState == GLFW_MOUSE_BUTTON_LEFT) {
    vec3 p = vec3(pX, height() - pY, 0);
    if (mShowControlPoints) {
      if (mSpline.getInterpolationType() == "Hermite" && mSelected % 2 == 1) {
        mSpline.editControlPoint(mSelected, p-mSpline.getControlPoint(mSelected-1));
      } else {
        mSpline.editControlPoint(mSelected, p);
      }
    }
    else mSpline.editKey(mSelected, p);
  }
}

int CurveEditor::pickPoint(int x, int y) {
  vec3 tmp = vec3(x, y, 0);

  int num = mSpline.getNumKeys();
  if (mShowControlPoints) {
    num = mSpline.getNumControlPoints();
  }

  // check data points -- needs to be done before ctrl points
  for (int i = 0; mSelected == -1 && i < num; i++) {
    vec3 pt;
    if (mShowControlPoints) {
      pt = mSpline.getControlPoint(i);
      if (mSpline.getInterpolationType() == "Hermite" && i % 2 == 1) {
        pt = pt + mSpline.getControlPoint(i-1);
      }
    } else {
      pt = mSpline.getKey(i);
    }

    if (length(tmp - pt) < mRadius) {
      return i;
    }
  }

  return -1;
}

void CurveEditor::mouseUp(int pButton, int state) {
  if (mButtonState == GLFW_MOUSE_BUTTON_LEFT) {
    mSelected = -1;
  }
}

void CurveEditor::mouseDown(int pButton, int state) {
  mButtonState = pButton;
  glm::vec2 p = mousePosition();
  int pX = (int) p.x;
  int pY = (int) p.y;

  if (mButtonState == GLFW_MOUSE_BUTTON_LEFT) {
    if (mMode == ADD) {
      vec3 tmp(p, 0);
      // guard against adding multiple copies of the same point
      // (multiple mouse events may be triggered for the same point)
      bool add = true;
      if (mSpline.getNumKeys() > 0) {
        vec3 lastKey = mSpline.getKey(mSpline.getNumKeys() - 1);
        float d = length(lastKey-tmp);
        if (d < 10) add = false;
      }

      if (add) {
        addPoint(vec3(pX, height()-pY, 0));
      }

    } else if (mMode == REMOVE) {
      mSelected = pickPoint(pX, height() - pY);
      deletePoint(mSelected);

    } else if (mMode == EDIT) {
      mSelected = pickPoint(pX, height() - pY);
      std::cout << "SELECTED: " << mSelected << std::endl;
      mouseMotion(pX, pY, 0, 0);
    }
  }

}

void CurveEditor::keyUp(int pKey, int mods) {
  if (pKey == 'p') {
    for (int i = 0; i < mSpline.getNumKeys(); i++) {
      std::cout << mSpline.getKey(i) << std::endl;
    }
  } else if (pKey == '1') {
    mSpline.setInterpolationType("Linear");

  } else if (pKey == '2') {
    mSpline.setInterpolationType("Catmull-Rom");

  } else if (pKey == '3') {
    mSpline.setInterpolationType("Hermite");

  } else if (pKey == 'A') {
    mMode = ADD;

  } else if (pKey == 'D') {
    mMode = REMOVE;

  } else if (pKey == 'E') {
    mMode = EDIT;

  } else if (pKey == 'C') {
    mShowControlPoints = !mShowControlPoints;

  } else if (pKey == GLFW_KEY_SPACE) {
    mSpline.clear();

  } else if (pKey == 'H') {
    mHermite.setClamped(!mHermite.isClamped());
    mSpline.computeControlPoints();
  } 
}

int main(int argc, char** argv)
{
	CurveEditor viewer;
	viewer.run();
}
