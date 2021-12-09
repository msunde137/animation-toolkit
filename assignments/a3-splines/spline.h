#ifndef spline_H_
#define spline_H_

#include "agl/aglm.h"
#include <map>
#include <vector>

class Spline
{
  public:
    // constructor
    Spline();

    // destructor
    virtual ~Spline();

    // Register an interpolator that corresponds to the given name
    void addInterpolationType(const std::string& name, class Interpolator* interpolator);

    // Set the interpolation type
    // @param type: must correspond to a registered Interpolator name
    void setInterpolationType(const std::string& name);

    // Get the current interpolation type
    const std::string& getInterpolationType() const;

    // Returns the value at realtime t
    // @param t: a non-negative value
    glm::vec3 getValue(float t) const;

    // Edit the key with the given ID
    // Triggers a recomputation of control points
    // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
    void editKey(int keyID, const glm::vec3& value); 

    // Appends a key with the given time and value
    // Triggers a recomputation of control points
    // Time must be larger than all previously added keys
    // (e.g,user must ensure keys are sorted)
    // @param time: a non-negative value
    // @param value: the key's value
    int appendKey(float time, const glm::vec3& value);

    // Delete the key with the given ID
    // Triggers a recomputation of control points
    // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
    void deleteKey(int keyID);

    // Return the value of the key with the given ID
    // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
    glm::vec3 getKey(int keyID) const;

    // Return the time  of the key with the given ID
    // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
    float getTime(int keyID) const;

    // Return the number of keys
    int getNumKeys() const;

    // Returns the number of segments (numkeys-1 if numkeys > 1)
    int getNumSegments() const;

    // Removes all keys
    void clear();

    // Returns the duration of the spline
    float getDuration() const;

    // Returns the number of control points (See interpolator.h)
    int getNumControlPoints() const;

    // Returns the value of control point by raw ID (See interpolator.h)
    const glm::vec3& getControlPoint(int id) const;

    // Recompute control points based on data points
    void computeControlPoints();

    // Returns the value of control point by segment and control point ID (See AInterpolator.h)
    //const glm::vec3& getControlPoint(int segment, int id) const;

    // Returns the number of control points (See interpolator.h)
    void editControlPoint(int id, const glm::vec3& v);

  protected:
    mutable bool mDirty;

    std::vector<glm::vec3> mKeys;
    std::vector<float> mTimes;

    std::map<std::string, Interpolator*> mInterpolators;
    class Interpolator* mInterpolator;
};
#endif
