#ifndef DAGNODE_H
#define DAGNODE_H

#include <cg3/geometry/segment2.h>
#include <cg3/geometry/point2.h>

class DAGnode {
    private:
        size_t left;
        size_t right;
    public:
        void setLeft(const size_t leftNode);
        void setRight(const size_t rightNode);

        size_t getLeft() const;
        size_t getRight() const;
};

class DAGnodePoint : public DAGnode {
    private:
        cg3::Point2d value;
    public:
        DAGnodePoint(const cg3::Point2d& point,
                     const size_t left, const size_t right);

        void setValue(const cg3::Point2d& point);

        const cg3::Point2d& getValue() const;
};

class DAGnodeSegment : public DAGnode {
    private:
        cg3::Segment2d value;
    public:
        DAGnodeSegment(const cg3::Segment2d& segment,
                     const size_t left, const size_t right);

        void setValue(const cg3::Segment2d& segment);

        const cg3::Segment2d& getValue() const;
};

class DAGnodeTrapezoid: public DAGnode {
    private:
        size_t value;
    public:
        DAGnodeTrapezoid(const size_t trapezoid,
                     const size_t left, const size_t right);

        void setValue(const size_t trapezoid);

        size_t getValue() const;
};


#endif // DAGNODE_H
