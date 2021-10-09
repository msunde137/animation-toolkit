#ifndef testUtils_H_
#define testUtils_H_

#include <cmath>
#include <limits>
#include <vector>
#include <sstream>
#include <string>


template<class T>
void EXPECT_FLOAT_VALUES(T a, const std::vector<T>& bs)
{
    bool ok = false;
  std::ostringstream stream;
    for (int i = 0; i < bs.size() && !ok; i++)
    {
        if (std::abs(a - bs[i]) < 0.0001f)
        {
            ok = true;
        }
        else
        {
            stream << bs[i] << " ";
        }
    }
    if (!ok)
    {
        std::cout << "  TEST FAIL\n";
        std::cout << "  " << a << std::endl;
        std::cout << "  " << stream.str() << std::endl;
    }
    else std::cout << "  TEST SUCCESS\n";
}

template<class T>
void EXPECT_VALUES(T a, const std::vector<T>& bs)
{
    bool ok = false;
    std::ostringstream stream;
    for (int i = 0; i < bs.size() && !ok; i++)
    {
        if (a == bs[i])
        {
            ok = true;
        }
        else
        {
            stream << bs[i] << " ";
        }
    }

    if (!ok)
    {
        std::cout << "  TEST FAIL\n";
        std::cout << "  " << a << std::endl;
        std::cout << "  " << stream.str() << std::endl;
    }
    else std::cout << "  TEST SUCCESS\n";
}

template<class T>
void EXPECT_FLOAT_EQ(T a, T b)
{
    if (std::abs(a - b) > 0.0001f)
    {
        std::cout << "  TEST FAIL\n";
        std::cout << "  " << a << std::endl;
        std::cout << "  " << b << std::endl;
    }
    else std::cout << "  TEST SUCCESS\n";
}

template<class T>
void EXPECT_FLOAT_EQ(T a, T b, float threshold)
{
    if (std::abs(a - b) > threshold)
    {
        std::cout << "  TEST FAIL\n";
        std::cout << "  " << a << std::endl;
        std::cout << "  " << b << std::endl;
    }
    else std::cout << "  TEST SUCCESS\n";
}

template<class T>
void EXPECT_EQ(T a, T b)
{
    if (a != b)
    {
        std::cout << "  TEST FAIL\n";
        std::cout << "  " << a << std::endl;
        std::cout << "  " << b << std::endl;
    }
    else std::cout << "  TEST SUCCESS\n";
}

#define RUN_TEST(name) std::cout << #name << std::endl; name;

#endif

