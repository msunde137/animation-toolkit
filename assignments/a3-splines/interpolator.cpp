#include "interpolator.h"

Interpolator::Interpolator(const std::string& type) : 
   mCtrlPoints(),
   mType(type) {
}

void Interpolator::editControlPoint(int ID, const glm::vec3& value) {
    assert(ID >= 0 && ID < (int) mCtrlPoints.size());
    mCtrlPoints[ID] = value;
}

const glm::vec3& Interpolator::getControlPoint(int ID) const {
    assert(ID >= 0 && ID < (int) mCtrlPoints.size());
    return mCtrlPoints[ID];
}

void Interpolator::clearControlPoints() {
    mCtrlPoints.clear();
}

int Interpolator::getNumControlPoints() const {
    return mCtrlPoints.size();
}

const std::string& Interpolator::getType() const { 
   return mType; 
}
