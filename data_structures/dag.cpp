#include "dag.h"

/**
 * @brief DAG Constructor
 * @param trapezoid, first Trapezoid
 */
DAG::DAG(const size_t trapezoid) {
    nodes.push_back(DAGnode(trapezoid));
}

/**
 * @brief Getter for the root of the DAG
 * @return the DAGnode as root
 */
DAGnode& DAG::getRoot() {
    return nodes[0];
}

/**
 * @brief Getter for a DAGnode
 * @param index, index of the needed DAGnode
 * @return the DAGnode in the index
 */
DAGnode& DAG::getNode(const size_t index) {
    if(index >= 0 && index < nodes.size())
        return nodes[index];
    else
        exit(EXIT_FAILURE);
}

/**
 * @brief Updates a DAGnode inside the DAG
 * @param newNode, DAGnode to replace the old with
 * @param index, index of the DAGnode to update
 * @return the index of the updated DAGnode
 */
size_t DAG::updateNode(const DAGnode& newNode, const size_t index) {
    if(index >= 0 && index < nodes.size()) {
        nodes[index] = newNode;
        return index;
    }
    exit(EXIT_FAILURE);
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
size_t DAG::addLeftChild(const DAGnode& newNode, const size_t index) {
    if(index >= 0 && index < nodes.size()) {
        size_t newIndex = addNode(newNode);
        nodes[index].setLeft(newIndex);
        return newIndex;
    }
    else
        exit(EXIT_FAILURE);
}

/**
 * @brief Adds a DAGnode inside the DAG as the right "child" of another DAGnode
 * @param newNode, DAGnode to add
 * @param index, index of the "father" of the new DAGnode
 * @return the index of the added DAGnode
 */
size_t DAG::addRightChild(const DAGnode& newNode, const size_t index) {
    if(index >= 0 && index < nodes.size()) {
        size_t newIndex = addNode(newNode);
        nodes[index].setRight(newIndex);
        return newIndex;
    }
    else
        exit(EXIT_FAILURE);
}

/**
 * @brief Updates the DAG after a split 4
 * @param tm, the Trapezoidal Map
 * @param s, the segment the split has been performed around
 * @param nodeToReplace, index of the node in which the pattern gotta be attached to
 * @param trpsz, vecotr of indexes of Trapezoid involved in the split
 */
void DAG::split4(TrapezoidalMap& tm, cg3::Segment2d s, size_t nodeToReplace, std::vector<size_t> trpzs) {
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
void DAG::split3L(TrapezoidalMap& tm, cg3::Segment2d s, size_t nodeToReplace, std::vector<size_t> trpzs) {
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
void DAG::split3R(TrapezoidalMap& tm, cg3::Segment2d s, size_t nodeToReplace, std::vector<size_t> trpzs) {
    size_t n1 = updateNode(DAGnode(s.p1()), nodeToReplace);

    size_t n2 = addLeftChild(DAGnode(s), n1);
    size_t n3 = addRightChild(DAGnode(trpzs[2]), n1);

    size_t n4, n5;
    if(tm.getTrapezoid(trpzs[0]).getDAGlink() == SIZE_MAX)
        n4 = addLeftChild(DAGnode(trpzs[0]), n2);
    else {
        n4 = tm.getTrapezoid(trpzs[0]).getDAGlink();
        getNode(n2).setLeft(n4);
    }
    if(tm.getTrapezoid(trpzs[1]).getDAGlink() == SIZE_MAX)
        n5 = addRightChild(DAGnode(trpzs[1]), n2);
    else {
        n5 = tm.getTrapezoid(trpzs[1]).getDAGlink();
        getNode(n2).setRight(n5);
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
void DAG::split2(TrapezoidalMap& tm, cg3::Segment2d s, size_t nodeToReplace, std::vector<size_t> trpzs) {
    size_t n1 = updateNode(DAGnode(s), nodeToReplace);

    size_t n2 = tm.getTrapezoid(trpzs[0]).getDAGlink();
    size_t n3 = tm.getTrapezoid(trpzs[1]).getDAGlink();
    if(n2 == SIZE_MAX || n2 == n1)
        n2 = addLeftChild(DAGnode(trpzs[0]), n1);
    else {
        n2 = tm.getTrapezoid(trpzs[0]).getDAGlink();
        getNode(n1).setLeft(n2);
    }
    if(tm.getTrapezoid(trpzs[1]).getDAGlink() == SIZE_MAX)
        n3 = addRightChild(DAGnode(trpzs[1]), n1);
    else {
        n3 = tm.getTrapezoid(trpzs[1]).getDAGlink();
        getNode(n1).setRight(n3);
    }

    tm.getTrapezoid(trpzs[0]).setDAGlink(n2);
    tm.getTrapezoid(trpzs[1]).setDAGlink(n3);
}
