#include "atkmath/constants.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"
#include "atkmath/test_utils.h"
#include <iostream>

using atkmath::Matrix3;
using atkmath::Vector3;
using atkmath::Deg2Rad;

void PerformTest(Matrix3::RotOrder roo, const Vector3& eulerDeg)
{
    Matrix3 m(roo, eulerDeg * Deg2Rad);
    Vector3 test = m.toEulerAngles(roo);
    Matrix3 m1(roo, test);
    EXPECT_EQ(m, m1);
}

void TestIdentity()
{
    Matrix3 m(Vector3(0,1,0), 0);
    EXPECT_EQ(Matrix3::Identity, m);
}

void TestAllRoo(const Matrix3& m)
{
    Vector3 test;

    std::cout << "XYZ\n";
    test = m.toEulerAngles(Matrix3::XYZ);
    EXPECT_EQ(m, Matrix3(Matrix3::XYZ, test));


    std::cout << "XZY\n";
    test = m.toEulerAngles(Matrix3::XZY);
    EXPECT_EQ(m, Matrix3(Matrix3::XZY, test));


    std::cout << "YXZ\n";
    test = m.toEulerAngles(Matrix3::YXZ);
    EXPECT_EQ(m, Matrix3(Matrix3::YXZ, test));


    std::cout << "YZX\n";
    test = m.toEulerAngles(Matrix3::YZX);
    EXPECT_EQ(m, Matrix3(Matrix3::YZX, test));


    std::cout << "ZXY\n";
    test = m.toEulerAngles(Matrix3::ZXY);
    EXPECT_EQ(m, Matrix3(Matrix3::ZXY, test));


    std::cout << "ZYX\n";
    test = m.toEulerAngles(Matrix3::ZYX);
    EXPECT_EQ(m, Matrix3(Matrix3::ZYX, test));
}


void Test909090()
{
    Matrix3 Rzxy(-1, 0, 0,  
                   0, 0, 1,  
                   0, 1, 0); 

    Matrix3 Rzyx( 0, 0, 1,  
                   0, 1, 0,  
                  -1, 0, 0); 

    Matrix3 Ryxz( 1, 0, 0,  
                   0, 0,-1,  
                   0, 1, 0); 

    Matrix3 Ryzx( 0, 1, 0,  
                   1, 0, 0,  
                   0, 0,-1); 

    Matrix3 Rxyz( 0, 0, 1,  
                   0,-1, 0,  
                   1, 0, 0); 

    Matrix3 Rxzy( 0,-1, 0,  
                   1, 0, 0,  
                   0, 0, 1); 

    std::cout << "Rxyz\n";
    TestAllRoo(Rxyz);

    std::cout << "Rxzy\n";
    TestAllRoo(Rxzy);

    std::cout << "Ryxz\n";
    TestAllRoo(Ryxz);

    std::cout << "Ryzx\n";
    TestAllRoo(Ryzx);

    std::cout << "Rzxy\n";
    TestAllRoo(Rzxy);

    std::cout << "Rzyx\n";
    TestAllRoo(Rzyx);
}

void TestMinus909090()
{
    Matrix3 Rzxy( 1, 0, 0,  
                   0, 0, 1,  
                   0,-1, 0); 

    Matrix3 Rzyx( 0, 0, 1,  
                   0,-1, 0,  
                   1, 0, 0); 

    Matrix3 Ryxz(-1, 0, 0,  
                   0, 0, 1,  
                   0, 1, 0); 

    Matrix3 Ryzx( 0, 1, 0,  
                  -1, 0, 0,  
                   0, 0, 1); 

    Matrix3 Rxyz( 0, 0,-1,  
                   0, 1, 0,  
                   1, 0, 0); 

    Matrix3 Rxzy( 0, 1, 0,  
                   1, 0, 0,  
                   0, 0,-1); 

    std::cout << "Rxyz\n";
    TestAllRoo(Rxyz);

    std::cout << "Rxzy\n";
    TestAllRoo(Rxzy);

    std::cout << "Ryxz\n";
    TestAllRoo(Ryxz);

    std::cout << "Ryzx\n";
    TestAllRoo(Ryzx);

    std::cout << "Rzxy\n";
    TestAllRoo(Rzxy);

    std::cout << "Rzyx\n";
    TestAllRoo(Rzyx);
}

void TestEulerToMatrix_XYZ()
{
    std::cout << "Rxyz: euler to matrix\n";
    Matrix3 m(Matrix3::XYZ, Vector3(45, -30, 60) * Deg2Rad);
    Matrix3 R(0.433013, -0.750000, -0.500000,
               0.435596,  0.659740, -0.612372,
               0.789149,  0.047367,  0.612372);
    EXPECT_EQ(m, R);

    std::cout << "Rxyz: matrix to euler\n";
    Vector3 euler = R.toEulerAnglesXYZ();
    EXPECT_EQ(euler, Vector3(45,-30,60) * Deg2Rad);

    std::cout << "Rxyz to euler +90\n";
    Matrix3 R90(0, 0, 1, 
                 0.96593, -0.25882, 0,
                 0.25882,  0.96593, 0);
    Vector3 euler90 = R90.toEulerAnglesXYZ();
    R.fromEulerAnglesXYZ(euler90);
    EXPECT_EQ(R, R90);

    std::cout << "Rxyz to euler -90\n";
    Matrix3 RM90(0,  0,  -1,
                2.5882e-01,  9.6593e-01, 0,
                9.6593e-01, -2.5882e-01, 0);
    Vector3 eulerM90 = RM90.toEulerAnglesXYZ();
    R.fromEulerAnglesXYZ(eulerM90);
    EXPECT_EQ(R, RM90);
}

void TestEulerToMatrix_XZY()
{
    std::cout << "Rxzy: euler to matrix\n";
    Matrix3 m(Matrix3::XZY, Vector3(45, -30, 60) * Deg2Rad);
    Matrix3 R(
       0.43301, -0.86603, -0.25000,
       0.17678,  0.35355, -0.91856,
       0.88388,  0.35355,  0.30619);
               
    EXPECT_EQ(m, R);

    std::cout << "Rxzy: matrix to euler\n";
    Vector3 euler = R.toEulerAnglesXZY();
    EXPECT_EQ(euler, Vector3(45,-30,60) * Deg2Rad);

    std::cout << "Rxzy to euler +90\n";
    Matrix3 R90(
       0, -1, 0,
       2.5882e-01,  0, -9.6593e-01,
       9.6593e-01,  0,  2.5882e-01);
                 
    Vector3 euler90 = R90.toEulerAnglesXZY();
    R.fromEulerAnglesXZY(euler90);
    EXPECT_EQ(R, R90);

    std::cout << "Rxzy to euler -90\n";
    Matrix3 RM90(
  0, 1 ,0,
  -9.6593e-01,  0, -2.5882e-01,
  -2.5882e-01,  0,  9.6593e-01);
                
    Vector3 eulerM90 = RM90.toEulerAnglesXZY();
    R.fromEulerAnglesXZY(eulerM90);
    EXPECT_EQ(R, RM90);
}
void TestEulerToMatrix_YXZ()
{
    std::cout << "Ryxz: euler to matrix\n";
    Matrix3 m(Matrix3::YXZ, Vector3(45, -30, 10) * Deg2Rad);
    Matrix3 R(
   0.79147, -0.49857, -0.35355,
   0.12279,  0.69636, -0.70711,
   0.59874,  0.51625,  0.61237);
    EXPECT_EQ(m, R);

    std::cout << "Ryxz: matrix to euler\n";
    Vector3 euler = R.toEulerAnglesYXZ();
    EXPECT_EQ(euler, Vector3(45,-30,10) * Deg2Rad);

    std::cout << "Ryxz to euler +90\n";
    Matrix3 R90(
   7.6604e-01, -6.4279e-01, -3.0616e-17,
   1.0633e-17,  6.0302e-17, -1.0000e+00,
   6.4279e-01,  7.6604e-01,  5.3029e-17);
    Vector3 euler90 = R90.toEulerAnglesYXZ();
    R.fromEulerAnglesYXZ(euler90);
    EXPECT_EQ(R, R90);

    std::cout << "Ryxz to euler -90\n";
    Matrix3 RM90(
   9.3969e-01,  3.4202e-01, -3.0616e-17,
   1.0633e-17,  6.0302e-17,  1.0000e+00,
   3.4202e-01, -9.3969e-01,  5.3029e-17);

    Vector3 eulerM90 = RM90.toEulerAnglesYXZ();
    R.fromEulerAnglesYXZ(eulerM90);
    EXPECT_EQ(R, RM90);
}
void TestEulerToMatrix_YZX()
{
    std::cout << "Ryzx: euler to matrix\n";
    Matrix3 m(Matrix3::YZX, Vector3(45, -30, 60) * Deg2Rad);
    Matrix3 R(
   0.43301, -0.88388,  0.17678,
   0.86603,  0.35355, -0.35355,
   0.25000,  0.30619,  0.91856);
               
    EXPECT_EQ(m, R);

    std::cout << "Ryzx: matrix to euler\n";
    Vector3 euler = R.toEulerAnglesYZX();
    EXPECT_EQ(euler, Vector3(45,-30,60) * Deg2Rad);

    std::cout << "Ryzx to euler +90\n";
    Matrix3 R90(
   0, -9.6593e-01,  2.5882e-01,
   1,  0, 0,
   0,  2.5882e-01,  9.6593e-01 );
                 
    Vector3 euler90 = R90.toEulerAnglesYZX();
    R.fromEulerAnglesYZX(euler90);
    EXPECT_EQ(R, R90);

    std::cout << "Ryzx to euler -90\n";
    Matrix3 RM90(
  0, 2.5882e-01 ,-9.6593e-01,
  -1,  0, 0,
   0,  9.6593e-01,  2.5882e-01);
                
    Vector3 eulerM90 = RM90.toEulerAnglesYZX();
    R.fromEulerAnglesYZX(eulerM90);
    EXPECT_EQ(R, RM90);
}
void TestEulerToMatrix_ZXY()
{
    std::cout << "Rzxy: euler to matrix\n";
    Matrix3 m(Matrix3::ZXY, Vector3(45, -30, 10) * Deg2Rad);
    Matrix3 R(
   0.91426, -0.12279, -0.38607,
  -0.19780,  0.69636, -0.68989,
   0.35355,  0.70711,  0.61237);
               
    EXPECT_EQ(m, R);

    std::cout << "Rzxy: matrix to euler\n";
    Vector3 euler = R.toEulerAnglesZXY();
    EXPECT_EQ(euler, Vector3(45,-30,10) * Deg2Rad);

    std::cout << "Rzxy to euler +90\n";
    Matrix3 R90(
   9.3969e-01, 0, -3.4202e-01,
  -3.4202e-01, 0, -9.3969e-01,
   0,  1,  0);

                 
    Vector3 euler90 = R90.toEulerAnglesZXY();
    R.fromEulerAnglesZXY(euler90);
    EXPECT_EQ(R, R90);

    std::cout << "Rzxy to euler -90\n";
    Matrix3 RM90(
   7.6604e-01, 0, -6.4279e-01,
   6.4279e-01, 0,  7.6604e-01,
   0, -1,  0);

                
    Vector3 eulerM90 = RM90.toEulerAnglesZXY();
    R.fromEulerAnglesZXY(eulerM90);
    EXPECT_EQ(R, RM90);
}

void TestEulerToMatrix_ZYX()
{
    std::cout << "Rzyx: euler to matrix\n";
    Matrix3 m(Matrix3::ZYX, Vector3(45, -30, 60) * Deg2Rad);
    Matrix3 R(
   0.433013, -0.789149,  0.435596,
   0.750000,  0.047367, -0.659740,
   0.500000,  0.612372,  0.612372);
               
    EXPECT_EQ(m, R);

    std::cout << "Rzyx: matrix to euler\n";
    Vector3 euler = R.toEulerAnglesZYX();
    EXPECT_EQ(euler, Vector3(45,-30,60) * Deg2Rad);

    std::cout << "Rzyx to euler +90\n";
    Matrix3 R90(
   0, -2.5882e-01,  9.6593e-01,
   0,  9.6593e-01,  2.5882e-01,
  -1,  0,  0);
                 
    Vector3 euler90 = R90.toEulerAnglesZYX();
    R.fromEulerAnglesZYX(euler90);
    EXPECT_EQ(R, R90);

    std::cout << "Rzyx to euler -90\n";
    Matrix3 RM90(
   0, -9.6593e-01,  2.5882e-01,
   0, -2.5882e-01, -9.6593e-01,
   1,  0,  0);
                
    Vector3 eulerM90 = RM90.toEulerAnglesZYX();
    R.fromEulerAnglesZYX(eulerM90);
    EXPECT_EQ(R, RM90);
}

int main(int argc, char** argv)
{
    RUN_TEST(TestIdentity())

    RUN_TEST(TestEulerToMatrix_XYZ());
    RUN_TEST(TestEulerToMatrix_XZY());
    RUN_TEST(TestEulerToMatrix_YXZ());
    RUN_TEST(TestEulerToMatrix_YZX());
    RUN_TEST(TestEulerToMatrix_ZXY());
    RUN_TEST(TestEulerToMatrix_ZYX());

    RUN_TEST(Test909090());
    RUN_TEST(TestMinus909090());
    return 0;
}
