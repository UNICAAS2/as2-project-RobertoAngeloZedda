#include "dag.h"

DAG::DAG(const size_t trapezoid) {
    nodes.push_back(DAGnode(trapezoid));
}

const DAGnode& DAG::getRoot() const {
    return nodes[0];
}

const DAGnode& DAG::getNode(const size_t index) const {
    if(index >= 0 && index < nodes.size())
        return nodes[index];
    else
        exit(EXIT_FAILURE);
}

void DAG::updateNode(DAGnode& newNode, const size_t index) {
    if(index >= 0 && index < nodes.size())
        nodes[index] = newNode;
    else
        exit(EXIT_FAILURE);
}

size_t DAG::addNode(const DAGnode& newNode) {
    nodes.push_back(newNode);
    return nodes.size()-1;
}

size_t DAG::addLeftChild(const DAGnode& newNode, const size_t index) {
    if(index >= 0 && index < nodes.size()) {
        size_t newIndex = addNode(newNode);
        nodes[index].setLeft(newIndex);
        return newIndex;
    }
    else
        exit(EXIT_FAILURE);
}

size_t DAG::addRightChild(const DAGnode& newNode, const size_t index) {
    if(index >= 0 && index < nodes.size()) {
        size_t newIndex = addNode(newNode);
        nodes[index].setRight(newIndex);
        return newIndex;
    }
    else
        exit(EXIT_FAILURE);
}
