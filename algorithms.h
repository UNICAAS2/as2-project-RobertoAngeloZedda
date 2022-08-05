#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#import "data_structures/trapezoidalmap.h"
#import "data_structures/dag.h"

#include "utils/utils.h"

namespace Algorithms {
    size_t findPoint(cg3::Point2d& point, DAG& dag);

    std::vector<size_t> followSegment(cg3::Segment2d& segment, DAG& dag, TrapezoidalMap& tm);

    void updateTrapezoidalMapAndDAG(cg3::Segment2d& segment, std::vector<size_t>& trapezoids, DAG& dag, TrapezoidalMap& tm);
}

#endif // ALGORITHMS_H
