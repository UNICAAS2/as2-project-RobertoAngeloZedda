#include "dagnode.h"

DAGnode::DAGnode(NodeType type, size_t value) {
    this->type = type;
    this->value = value;
}

void DAGnode::setLeft(const size_t leftNode) {
    left = leftNode;
}

void DAGnode::setRight(const size_t rightNode) {
    right = rightNode;
}

NodeType DAGnode::getType() const { return type; }

size_t DAGnode::getValue() const { return value; }

size_t DAGnode::getLeft() const { return left; }

size_t DAGnode::getRight() const { return right; }
