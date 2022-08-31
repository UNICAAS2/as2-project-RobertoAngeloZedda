#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#import "drawables/drawabletrapezoidalmap.h"
#import "data_structures/dag.h"

namespace Algorithms {
    std::vector<size_t> followSegment(const cg3::Segment2d& segment, DAG& dag, TrapezoidalMap& tm);

    void updateTrapezoidalMapAndDAG(const cg3::Segment2d& segment, std::vector<size_t>& trapezoids, DAG& dag, DrawableTrapezoidalMap& tm);
}

#endif // ALGORITHMS_H
