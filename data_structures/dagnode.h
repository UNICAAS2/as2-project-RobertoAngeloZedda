#ifndef DAGNODE_H
#define DAGNODE_H

#include <cstddef>

enum NodeType {
    point,
    segment,
    trapezoid
};

class DAGnode {
    private:
        NodeType type;

        size_t value;

        size_t left;
        size_t right;
    public:
        DAGnode(NodeType type, size_t value);

        void setLeft(const size_t leftNode);
        void setRight(const size_t rightNode);

        NodeType getType() const;
        size_t getValue() const;
        size_t getLeft() const;
        size_t getRight() const;
};

#endif // DAGNODE_H
