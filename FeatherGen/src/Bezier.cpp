#include "Bezier.h"

ngl::Vec3 bezier(float t, const ngl::Vec3& p0, const ngl::Vec3& p1, const ngl::Vec3& p2, const ngl::Vec3& p3)

{
    const float B0 = (1.-t)*(1.-t)*(1.-t);
    const float B1 = 3.*t*(1.-t)*(1.-t);
    const float B2 = 3.*t*t*(1.-t);
    const float B3 = t*t*t;

    return B0*p0 + B1*p1 + B2*p2 + B3*p3;
}