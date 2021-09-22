#include "atk/motion.h"
#include <cmath>

namespace atk {
Motion::Motion(double fps) :
  mDt(1.0/fps),
  mFps(fps) {
}

Motion::~Motion() {
}

void Motion::update(Skeleton& skeleton, double time, bool loop) const {
  Pose pose = getValue(time, loop); 
  skeleton.setPose(pose);
}

void Motion::setFramerate(double fps) {
  mFps = fps;
  mDt = 1/fps;
}

double Motion::getFramerate() const {
  return mFps;
}

void Motion::setDeltaTime(double dt) {
  mDt = dt;
  mFps = 1/dt;
}

double Motion::getDeltaTime() const {
  return mDt;
}

void Motion::editKey(int keyID, const Pose& value) {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  mKeys[keyID] = value;
}

void Motion::appendKey(const Pose& value) {
  mKeys.push_back(value);
}

void Motion::deleteKey(int keyID) {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  mKeys.erase(mKeys.begin() + keyID);
}

Pose Motion::getKey(int keyID) const {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  return mKeys[keyID];
}

int Motion::getNumKeys() const {
  return (int) mKeys.size();
}

void Motion::clear() {
  mKeys.clear();
}

double Motion::getDuration() const {
  return (mKeys.size() - 1) * mDt;
}

double Motion::getNormalizedDuration(double t) const {
  return fmod(t, getDuration()) / getDuration(); 
}

int Motion::getKeyID(double t) const {
  if (mKeys.size() == 0) return 0;

  t = getNormalizedDuration(t) * getDuration();
  return (int)(t / mDt); 
}

Pose Motion::getValue(double t, bool loop) const {
  if (mKeys.size() == 0) return Pose();

  if (loop) {
    t = getNormalizedDuration(t) * getDuration();
  } else {
    if (t >= getDuration()-glm::epsilon<float>()) return mKeys[mKeys.size()-1];
    else if (t < 0) return mKeys[0];
  }

  int segment = (int)(t / mDt); // assumes uniform spacing
  double u = (t - segment*mDt)/mDt;
  //int sm1 = std::max<int>(segment-1, 0);
  //int sp1 = std::min<int>(segment+2, mKeys.size()-1);
  //return Pose::Squad(mKeys[sm1], mKeys[segment], mKeys[segment+1], mKeys[sp1], u); 
  return Pose::Lerp(mKeys[segment], mKeys[segment+1], u); 
}
}