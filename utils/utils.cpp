#include "utils.h"

namespace Algorithms {
    /**
     * @brief Calculates if a given Point is on the right of a given Segment
     * @param s, the Segment
     * @param p, the Point
     * @return true if p is on the right of s else otherwise
    */
    bool isPointOnTheRight(const cg3::Segment2d s, const cg3::Point2d p) {
        float det = s.p1().x() * (s.p2().y() - p.y()) -
                    s.p1().y() * (s.p2().x() - p.x()) +
                    s.p2().x() * p.y() - p.x() * s.p2().y();
        if(det >= 0)
            return true;
        else
            return false;
    }

    cg3::Segment2d fixSegmentDirection(const cg3::Segment2d& s) {
        if(s.p1().x() > s.p2().x() ||
           (s.p1().x() == s.p2().x() &&
            s.p1().y() > s.p2().y()))
            return cg3::Segment2d(s.p2(), s.p1());
        else
            return cg3::Segment2d(s.p1(), s.p2());
    }
}
