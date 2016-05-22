#ifndef MATHUTILS_H
#define MATHUTILS_H

namespace utils
{
    class MathUtils
    {
    public:
        template<typename T>
        static T gcd(T a, T b)
        {
            T c = a % b;
            while(c != 0) {
             a = b;
             b = c;
             c = a % b;
            }
        return b;
        }
    };
}


#endif // MATHUTILS_H
