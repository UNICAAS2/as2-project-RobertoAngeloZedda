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
