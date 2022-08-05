#ifndef UTILS_H
#define UTILS_H

#include <cg3/geometry/segment2.h>
#include <cg3/geometry/point2.h>

namespace Algorithms {
    bool isPointOnTheRight(const cg3::Segment2d s, const cg3::Point2d p);
}

#endif // UTILS_H
