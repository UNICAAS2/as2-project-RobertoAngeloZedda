#ifndef DAG_H
#define DAG_H

#import "dagnode.h"

/**
 * @brief The DAG class.
 * A DAG is defined through a vector of DAGnodes.
 */
class DAG {
    private:
        std::vector<DAGnode> nodes;
    public:
        DAG(const size_t trapezoid);

        DAGnode& getRoot();
        DAGnode& getNode(const size_t index);

        size_t updateNode(const DAGnode& newNode, const size_t index);

        size_t addNode(const DAGnode& newNode);
        size_t addLeftChild(const DAGnode& newNode, const size_t index);
        size_t addRightChild(const DAGnode& newNode, const size_t index);
};

#endif // DAG_H
