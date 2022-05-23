#ifndef DAG_H
#define DAG_H

#import "dagnode.h"

class DAG {
    private:
        std::vector<DAGnode> nodes;
    public:
        DAG(const size_t trapezoid);

        const DAGnode& getRoot() const;
        const DAGnode& getNode(const size_t index) const;

        void updateNode(DAGnode& newNode, const size_t index);

        size_t addNode(const DAGnode& newNode);
        size_t addLeftChild(const DAGnode& newNode, const size_t index);
        size_t addRightChild(const DAGnode& newNode, const size_t index);
};

#endif // DAG_H
