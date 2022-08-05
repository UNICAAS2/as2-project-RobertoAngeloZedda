#include "dag.h"

DAG::DAG(const size_t trapezoid) {
    nodes = std::vector<DAGnode>();
    DAGnodeTrapezoid root = DAGnodeTrapezoid(trapezoid);
    nodes.push_back(root);
}

const DAGnode& DAG::getRoot() const {
    return nodes[0];
}

const DAGnode& DAG::getNode(const size_t index) const {
    return nodes[index];
}

void DAG::updateNode(DAGnode& newNode, const size_t index) {
    /*if (dynamic_cast<DAGnodePoint*>(&(nodes[index])) != nullptr) {
        DAGnodePoint* ptr = dynamic_cast<DAGnodePoint*>(&(nodes[index]));
        ptr->~DAGnodePoint();
        nodes[index] = newNode;
    }*/
}

size_t DAG::addNode(const DAGnode& newNode) {
    nodes.push_back(newNode);
    return nodes.size()-1;
}

size_t DAG::addLeftChild(const DAGnode& newNode, const size_t index) {
    size_t newNodeIndex = this->addNode(newNode);
    nodes[index].setLeft(newNodeIndex);
    return newNodeIndex;
}

size_t DAG::addRightChild(const DAGnode& newNode, const size_t index) {
    size_t newNodeIndex = this->addNode(newNode);
    nodes[index].setRight(newNodeIndex);
    return newNodeIndex;
}
