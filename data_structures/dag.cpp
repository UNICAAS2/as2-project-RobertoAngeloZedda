#include "dag.h"

/**
 * @brief DAG Constructor
 */
DAG::DAG() { }

/**
 * @brief Getter for the root of the DAG
 * @return the DAGnode as root
 */
const DAGnode& DAG::getRoot() {
    assert(nodes.size() > 0);
    return nodes[0];
}

/**
 * @brief Getter for a DAGnode
 * @param index, index of the needed DAGnode
 * @return the DAGnode in the index
 */
const DAGnode& DAG::getNode(const size_t& index) {
    assert(index >= 0 && index < nodes.size());
    return nodes[index];
}

/**
 * @brief Updates a DAGnode inside the DAG
 * @param newNode, DAGnode to replace the old with
 * @param index, index of the DAGnode to update
 * @return the index of the updated DAGnode
 */
size_t DAG::updateNode(const DAGnode& newNode, const size_t& index) {
    assert(index >= 0 && index < nodes.size());
    nodes[index] = newNode;
    return index;
}

/**
 * @brief Adds a DAGnode inside the DAG
 * @param newNode, DAGnode to add
 * @return the index of the added DAGnode
 */
size_t DAG::addNode(const DAGnode& newNode) {
    nodes.push_back(newNode);
    return nodes.size()-1;
}

/**
 * @brief Adds a DAGnode inside the DAG as the left "child" of another DAGnode
 * @param newNode, DAGnode to add
 * @param index, index of the "father" of the new DAGnode
 * @return the index of the added DAGnode
 */
size_t DAG::addLeftChild(const DAGnode& newNode, const size_t& index) {
    assert(index >= 0 && index < nodes.size());
    size_t newIndex = addNode(newNode);
    nodes[index].setLeft(newIndex);
    return newIndex;
}

/**
 * @brief Adds a DAGnode inside the DAG as the right "child" of another DAGnode
 * @param newNode, DAGnode to add
 * @param index, index of the "father" of the new DAGnode
 * @return the index of the added DAGnode
 */
size_t DAG::addRightChild(const DAGnode& newNode, const size_t& index) {
    assert(index >= 0 && index < nodes.size());
    size_t newIndex = addNode(newNode);
    nodes[index].setRight(newIndex);
    return newIndex;
}

/**
 * @brief Updates the DAG after a split 4
 * @param tm, the Trapezoidal Map
 * @param s, the segment the split has been performed around
 * @param nodeToReplace, index of the node in which the pattern gotta be attached to
 * @param trpsz, vecotr of indexes of Trapezoid involved in the split
 */
void DAG::split4(TrapezoidalMap& tm, const cg3::Segment2d& s,
                 const size_t& nodeToReplace, const std::array<size_t, 4>& trpzs) {
    size_t n1 = updateNode(DAGnode(s.p1()), nodeToReplace);

    size_t n2 = addLeftChild(DAGnode(trpzs[0]), n1);
    size_t n3 = addRightChild(DAGnode(s.p2()), n1);

    size_t n4 = addLeftChild(DAGnode(s), n3);
    size_t n5 = addRightChild(DAGnode(trpzs[3]), n3);

    size_t n6 = addLeftChild(DAGnode(trpzs[1]), n4);
    size_t n7 = addRightChild(DAGnode(trpzs[2]), n4);

    tm.getTrapezoid(trpzs[0]).setDAGlink(n2);
    tm.getTrapezoid(trpzs[1]).setDAGlink(n6);
    tm.getTrapezoid(trpzs[2]).setDAGlink(n7);
    tm.getTrapezoid(trpzs[3]).setDAGlink(n5);
}

/**
 * @brief Updates the DAG after a split 3 on the left side of the segment
 * @param tm, the Trapezoidal Map
 * @param s, the segment the split has been performed around
 * @param nodeToReplace, index of the node in which the pattern gotta be attached to
 * @param trpsz, vecotr of indexes of Trapezoid involved in the split
 */
void DAG::split3L(TrapezoidalMap& tm, const cg3::Segment2d& s,
                  const size_t& nodeToReplace, const std::array<size_t, 3>& trpzs) {
    size_t n1 = updateNode(DAGnode(s.p1()), nodeToReplace);

    size_t n2 = addLeftChild(DAGnode(trpzs[0]), n1);
    size_t n3 = addRightChild(DAGnode(s), n1);

    size_t n4 = addLeftChild(DAGnode(trpzs[1]), n3);
    size_t n5 = addRightChild(DAGnode(trpzs[2]), n3);

    tm.getTrapezoid(trpzs[0]).setDAGlink(n2);
    tm.getTrapezoid(trpzs[1]).setDAGlink(n4);
    tm.getTrapezoid(trpzs[2]).setDAGlink(n5);
}

/**
 * @brief Updates the DAG after a split 3 on the right of the segment
 * @param tm, the Trapezoidal Map
 * @param s, the segment the split has been performed around
 * @param nodeToReplace, index of the node in which the pattern gotta be attached to
 * @param trpsz, vecotr of indexes of Trapezoid involved in the split
 */
void DAG::split3R(TrapezoidalMap& tm, const cg3::Segment2d& s,
                  const size_t& nodeToReplace, const std::array<size_t, 3>& trpzs) {
    size_t n1 = updateNode(DAGnode(s.p2()), nodeToReplace);

    size_t n2 = addLeftChild(DAGnode(s), n1);
    size_t n3 = addRightChild(DAGnode(trpzs[2]), n1);

    size_t n4, n5;
    if(tm.getTrapezoid(trpzs[0]).getDAGlink() == SIZE_MAX)
        n4 = addLeftChild(DAGnode(trpzs[0]), n2);
    else {
        n4 = tm.getTrapezoid(trpzs[0]).getDAGlink();
        nodes[n2].setLeft(n4);
    }
    if(tm.getTrapezoid(trpzs[1]).getDAGlink() == SIZE_MAX)
        n5 = addRightChild(DAGnode(trpzs[1]), n2);
    else {
        n5 = tm.getTrapezoid(trpzs[1]).getDAGlink();
        nodes[n2].setRight(n5);
    }

    tm.getTrapezoid(trpzs[0]).setDAGlink(n4);
    tm.getTrapezoid(trpzs[1]).setDAGlink(n5);
    tm.getTrapezoid(trpzs[2]).setDAGlink(n3);
}

/**
 * @brief Updates the DAG after a split 2
 * @param tm, the Trapezoidal Map
 * @param s, the segment the split has been performed around
 * @param nodeToReplace, index of the node in which the pattern gotta be attached to
 * @param trpsz, vecotr of indexes of Trapezoid involved in the split
 */
void DAG::split2(TrapezoidalMap& tm, const cg3::Segment2d& s,
                 const size_t& nodeToReplace, const std::array<size_t, 2>& trpzs) {
    size_t n1 = updateNode(DAGnode(s), nodeToReplace);

    size_t n2 = tm.getTrapezoid(trpzs[0]).getDAGlink();
    size_t n3 = tm.getTrapezoid(trpzs[1]).getDAGlink();
    if(n2 == SIZE_MAX || n2 == n1)
        n2 = addLeftChild(DAGnode(trpzs[0]), n1);
    else {
        n2 = tm.getTrapezoid(trpzs[0]).getDAGlink();
        nodes[n1].setLeft(n2);
    }
    if(tm.getTrapezoid(trpzs[1]).getDAGlink() == SIZE_MAX)
        n3 = addRightChild(DAGnode(trpzs[1]), n1);
    else {
        n3 = tm.getTrapezoid(trpzs[1]).getDAGlink();
        nodes[n1].setRight(n3);
    }

    tm.getTrapezoid(trpzs[0]).setDAGlink(n2);
    tm.getTrapezoid(trpzs[1]).setDAGlink(n3);
}

/**
 * @brief Finds the Trapezoid containing a given Point
 * @param point, the Point
 * @param dag, the DAG
 * @param point2, the second Point used in case the first one overlaps with one already used
 * @return returns the index (inside the TrapezoidalMap) of the Trapezoid containing the Point.
 */
size_t DAG::findPoint(const cg3::Point2d& point, const cg3::Point2d& point2) {
    DAGnode currentNode = getRoot();

    while(!currentNode.isTrapezoidNode()) {
        if(currentNode.isPointNode()) {
            if(point.x() < currentNode.getPointValue().x())
                currentNode = getNode(currentNode.getLeft());
            else
                currentNode = getNode(currentNode.getRight());
        }
        if(currentNode.isSegmentNode()) {
            if(point != currentNode.getSegmentValue().p1()) {
                if(Utils::isPointOnTheLeft(currentNode.getSegmentValue(), point))
                    currentNode = getNode(currentNode.getLeft());
                else
                    currentNode = getNode(currentNode.getRight());
            } else {
                if(Utils::isPointOnTheLeft(currentNode.getSegmentValue(), point2))
                    currentNode = getNode(currentNode.getLeft());
                else
                    currentNode = getNode(currentNode.getRight());
            }
        }
    }

    return currentNode.getTrapezoidValue();
}

/**
 * @brief Clears the DAG.
 */
void DAG::clear() {
    nodes.clear();
}
