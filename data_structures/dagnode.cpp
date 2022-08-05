#include "dagnode.h"

DAGnode::DAGnode(const cg3::Point2d& p) {
    DAGnode(p, -1, -1);
}

DAGnode::DAGnode(const cg3::Point2d& p, const size_t l, const size_t r) {
    type = point;
    pointValue = p;
    left = l;
    right = r;
}

DAGnode::DAGnode(const cg3::Segment2d& s) {
    DAGnode(s, -1, -1);
}

DAGnode::DAGnode(const cg3::Segment2d& s, const size_t l, const size_t r) {
    type = segment;
    segmentValue = s;
    left = l;
    right = r;
}

DAGnode::DAGnode(const size_t t) {
    DAGnode(t, -1, -1);
}

DAGnode::DAGnode(const size_t t, const size_t l, const size_t r) {
    type = trapezoid;
    trapezoidValue = t;
    left = l;
    right = r;
}

void DAGnode::setLeft(const size_t leftNode) { left = leftNode; }

void DAGnode::setRight(const size_t rightNode) { right = rightNode; }

size_t DAGnode::getLeft() const { return left; }
size_t DAGnode::getRight() const { return right; }

bool DAGnode::isPointNode() const { return (type == point); }
bool DAGnode::isSegmentNode() const { return (type == segment); }
bool DAGnode::isTrapezoidNode() const { return (type == trapezoid); }

const cg3::Point2d DAGnode::getPointValue() const {
    if(type == point)
        return pointValue;
    else
        exit(EXIT_FAILURE);
}

const cg3::Segment2d DAGnode::getSegmentValue() const {
    if(type == segment)
        return segmentValue;
    else
        exit(EXIT_FAILURE);
}

size_t DAGnode::getTrapezoidValue() const {
    if(type == trapezoid)
        return trapezoidValue;
    else
        exit(EXIT_FAILURE);
}
