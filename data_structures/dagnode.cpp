#include "dagnode.h"

void DAGnode::setLeft(const size_t leftNode) {
    left = leftNode;
}

void DAGnode::setRight(const size_t rightNode) {
    right = rightNode;
}

size_t DAGnode::getLeft() const {
    return left;
}

size_t DAGnode::getRight() const {
    return right;
}

DAGnodePoint::DAGnodePoint(const cg3::Point2d& point,
                           const size_t left, const size_t right) {
    value = point;
    this->setLeft(left);
    this->setRight(right);
}

void DAGnodePoint::setValue(const cg3::Point2d& point) {
    value = point;
}

const cg3::Point2d& DAGnodePoint::getValue() const {
    return value;
}

DAGnodeSegment::DAGnodeSegment(const cg3::Segment2d& segment,
                             const size_t left, const size_t right) {
    this->value = segment;
    this->setLeft(left);
    this->setRight(right);
}

void DAGnodeSegment::setValue(const cg3::Segment2d& segment) {
    value = segment;
}

const cg3::Segment2d& DAGnodeSegment::getValue() const {
    return value;
}

DAGnodeTrapezoid::DAGnodeTrapezoid(const size_t trapezoid,
                               const size_t left, const size_t right) {
    this->value = trapezoid;
    this->setLeft(left);
    this->setRight(right);
}

void DAGnodeTrapezoid::setValue(const size_t trapezoid) {
    value = trapezoid;
}

size_t DAGnodeTrapezoid::getValue() const {
    return value;
}
