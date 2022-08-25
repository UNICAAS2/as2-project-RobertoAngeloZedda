#ifndef DAGNODE_H
#define DAGNODE_H

#include <cg3/geometry/segment2.h>
#include <cg3/geometry/point2.h>

/**
 * @brief Base element of a DAG.
 * A DAGnode is represented by:
 *      a "type" which can be "point", "segment" or "trapezoid.
 *      "pointValue", a "segmentValue" and a "trapezoidValue":
 *      only one can be used based on the type of the node.
 *      "left" and "right" which are the indexes of the left
 *      and right sub-trees inside the DAG
 */
class DAGnode {
    private:
        enum NodeType {point, segment, trapezoid};
        NodeType type;

        cg3::Point2d pointValue;
        cg3::Segment2d segmentValue;
        size_t trapezoidValue;

        size_t left;
        size_t right;
    public:
        DAGnode(const cg3::Point2d& p);
        DAGnode(const cg3::Point2d& p, const size_t& l, const size_t& r);

        DAGnode(const cg3::Segment2d& s);
        DAGnode(const cg3::Segment2d& s, const size_t& l, const size_t& r);

        DAGnode(const size_t& t);
        DAGnode(const size_t& t, const size_t& l, const size_t& r);

        void setLeft(const size_t& leftNode);
        void setRight(const size_t& rightNode);

        size_t getLeft() const;
        size_t getRight() const;

        bool isPointNode() const;
        bool isSegmentNode() const;
        bool isTrapezoidNode() const;

        const cg3::Point2d& getPointValue() const;
        const cg3::Segment2d& getSegmentValue() const;
        size_t getTrapezoidValue() const;
};


#endif // DAGNODE_H
