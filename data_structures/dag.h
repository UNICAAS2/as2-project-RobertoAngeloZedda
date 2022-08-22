#ifndef DAG_H
#define DAG_H

#import "dagnode.h"

#import "trapezoidalmap.h"

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

        void split4(TrapezoidalMap& tm, cg3::Segment2d s, size_t nodeToReplace, std::vector<size_t> trpzs);
        void split3L(TrapezoidalMap& tm, cg3::Segment2d s, size_t nodeToReplace, std::vector<size_t> trpzs);
        void split3R(TrapezoidalMap& tm, cg3::Segment2d s, size_t nodeToReplace, std::vector<size_t> trpzs);
        void split2(TrapezoidalMap& tm, cg3::Segment2d s, size_t nodeToReplace, std::vector<size_t> trpzs);
};

#endif // DAG_H
