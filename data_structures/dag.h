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
        DAG();

        const DAGnode& getRoot();
        const DAGnode& getNode(const size_t& index);

        size_t updateNode(const DAGnode& newNode, const size_t& index);

        size_t addNode(const DAGnode& newNode);
        size_t addLeftChild(const DAGnode& newNode, const size_t& index);
        size_t addRightChild(const DAGnode& newNode, const size_t& index);

        void split4(TrapezoidalMap& tm, const cg3::Segment2d& s,
                    const size_t& nodeToReplace, const std::array<size_t, 4>& trpzs);
        void split3L(TrapezoidalMap& tm, const cg3::Segment2d& s,
                     const size_t& nodeToReplace, const std::array<size_t, 3>& trpzs);
        void split3R(TrapezoidalMap& tm, const cg3::Segment2d& s,
                     const size_t& nodeToReplace, const std::array<size_t, 3>& trpzs);
        void split2(TrapezoidalMap& tm, const cg3::Segment2d& s,
                    const size_t& nodeToReplace, const std::array<size_t, 2>& trpzs);

        void clear();
};

#endif // DAG_H
