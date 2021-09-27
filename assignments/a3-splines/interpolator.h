#ifndef interpolator_H_
#define interpolator_H_

#include <string>
#include <vector>
#include <map>
#include "atk/glmmath.h"

//-------------------------------------------------------------------
// Interpolator is an abstract base class for 
//   managing control points and performing interpolation
// Interpolators manage a list of control points
//-------------------------------------------------------------------

class Interpolator
{
public:
   // destructor
   virtual ~Interpolator() {}

   // Return an interpolated value for the given segment and time
   // @param segment: ID of the segment to interpolate. First segment has ID = 0
   // @param u: normalized time. u is in the range [0,1]
   virtual glm::vec3 interpolate(int segment, double time) const = 0;

   // Recompute control points based on the given keys
   virtual void computeControlPoints(const std::vector<glm::vec3>& keys) = 0;

   // Returns the type of this interpolator
   // Determined by child class; Not settable 
   const std::string& getType() const;

   // Edit a control point based on their raw ID
   // Control points include keys
   // @param ID: Raw ID, Valid IDs range from 0 to getNumControlPoints()-1 
   // @param value: new value for the control point
   void editControlPoint(int ID, const glm::vec3& value);

   // Return the number of control points across all segments
   int getNumControlPoints() const;

   // Return the value of the control point having raw ID
   // @param ID: Valid IDs range from 0 to getNumControlPoints()-1
   const glm::vec3& getControlPoint(int ID) const;

   // Remove all control points
   void clearControlPoints();

protected:
   // constructor - callable from child classes only
   Interpolator(const std::string& type);

   // member variables
   std::vector<glm::vec3> mCtrlPoints;
   std::string mType;
};

#endif
