#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#import "data_structures/trapezoidalmap.h"
#import "data_structures/dag.h"

#include "utils/utils.h"

namespace Algorithms {
    size_t findPoint(const cg3::Point2d& point, DAG& dag, const cg3::Point2d& point2);

    std::vector<size_t> followSegment(const cg3::Segment2d& segment, DAG& dag, TrapezoidalMap& tm);

    void updateTrapezoidalMapAndDAG(const cg3::Segment2d& segment, std::vector<size_t>& trapezoids, DAG& dag, TrapezoidalMap& tm);

    void DAGsplit4(DAG& dag, TrapezoidalMap& tm, cg3::Segment2d s, size_t t1, size_t t2, size_t t3, size_t t4);
    void DAGsplit3Left(DAG& dag, TrapezoidalMap& tm, cg3::Segment2d s, size_t t1, size_t t2, size_t t3);
    void DAGsplit3Right(DAG& dag, TrapezoidalMap& tm, cg3::Segment2d s, size_t t1, size_t t2, size_t t3);
    void DAGsplit2(DAG& dag, TrapezoidalMap& tm, cg3::Segment2d s, size_t t1, size_t t2, size_t tOrigin);
}

#endif // ALGORITHMS_H
