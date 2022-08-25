#include "dagnode.h"

/**
 * @brief DAGnode Constructor for the "point" node type
 * @param p, the Point which will be store as value
 */
DAGnode::DAGnode(const cg3::Point2d& p) {
    type = point;
    pointValue = p;
    left = SIZE_MAX;
    right = SIZE_MAX;
}

/**
 * @brief DAGnode Constructor for the "point" node type
 * @param p, the Point which will be store as value
 * @param l, index of the left sub-tree inside the DAG
 * @param r, index of the right sub-tree inside the DAG
 */
DAGnode::DAGnode(const cg3::Point2d& p, const size_t& l, const size_t& r) {
    type = point;
    pointValue = p;
    left = l;
    right = r;
}

/**
 * @brief DAGnode Constructor for the "segment" node type
 * @param s, the Segment which will be store as value
 */
DAGnode::DAGnode(const cg3::Segment2d& s) {
    type = segment;
    segmentValue = s;
    left = SIZE_MAX;
    right = SIZE_MAX;
}

/**
 * @brief DAGnode Constructor for the "segment" node type
 * @param s, the Segment which will be store as value
 * @param l, index of the left sub-tree inside the DAG
 * @param r, index of the right sub-tree inside the DAG
 */
DAGnode::DAGnode(const cg3::Segment2d& s, const size_t& l, const size_t& r) {
    type = segment;
    segmentValue = s;
    left = l;
    right = r;
}

/**
 * @brief DAGnode Constructor for the "trapezoid" node type
 * @param t, the index of the Trapezoid inside the TrapezoidalMap which will be store as value
 */
DAGnode::DAGnode(const size_t& t) {
    type = trapezoid;
    trapezoidValue = t;
    left = SIZE_MAX;
    right = SIZE_MAX;
}

/**
 * @brief DAGnode Constructor for the "trapezoid" node type
 * @param t, the index of the Trapezoid inside the TrapezoidalMap which will be store as value
 * @param l, index of the left sub-tree inside the DAG
 * @param r, index of the right sub-tree inside the DAG
 */
DAGnode::DAGnode(const size_t& t, const size_t& l, const size_t& r) {
    type = trapezoid;
    trapezoidValue = t;
    left = l;
    right = r;
}

/**
 * @brief Setter for the left sub-tree
 * @param leftNode, the new DAGnode index
 */
void DAGnode::setLeft(const size_t& leftNode) { left = leftNode; }

/**
 * @brief Setter for the right sub-tree
 * @param rightNode, the new DAGnode index
 */
void DAGnode::setRight(const size_t& rightNode) { right = rightNode; }

/**
 * @brief Getter for the left sub-tree DAGnode index
 * @return the left sub-tree DAGnode index
 */
size_t DAGnode::getLeft() const { return left; }

/**
 * @brief Getter for the right sub-tree DAGnode index
 * @return the right sub-tree DAGnode index
 */
size_t DAGnode::getRight() const { return right; }

/**
 * @brief Checks the type of the DAGnode
 * @return true if the DAGnode is a Point type node, false otherwise
 */
bool DAGnode::isPointNode() const { return (type == point); }

/**
 * @brief Checks the type of the DAGnode
 * @return true if the DAGnode is a Segment type node, false otherwise
 */
bool DAGnode::isSegmentNode() const { return (type == segment); }

/**
 * @brief Checks the type of the DAGnode
 * @return true if the DAGnode is a Trapezoid type node, false otherwise
 */
bool DAGnode::isTrapezoidNode() const { return (type == trapezoid); }

/**
 * @brief Getter DAGnode value of a Point type node
 * @return the pointValue
 */
const cg3::Point2d& DAGnode::getPointValue() const {
    assert(type == point);
    return pointValue;
}

/**
 * @brief Getter DAGnode value of a Segment type node
 * @return the segmentValue
 */
const cg3::Segment2d& DAGnode::getSegmentValue() const {
    assert(type == segment);
    return segmentValue;
}

/**
 * @brief Getter DAGnode value of a Trapezoid type node
 * @return the trapezoidValue
 */
size_t DAGnode::getTrapezoidValue() const {
    assert(type == trapezoid);
    return trapezoidValue;
}
