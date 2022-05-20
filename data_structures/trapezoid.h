#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <cg3/geometry/segment2.h>
#include <cg3/geometry/point2.h>

class Trapezoid {
    private:
        cg3::Segment2d top;
        cg3::Segment2d bot;
        cg3::Point2d leftP;
        cg3::Point2d rightP;

        size_t topLeftNeighbor;
        size_t topRightNeighbor;
        size_t botLeftNeighbor;
        size_t botRightNeighbor;
    public:
        Trapezoid();
        Trapezoid(const cg3::Segment2d& top, const cg3::Segment2d& bot, const cg3::Point2d& leftP, const cg3::Point2d& rightP);
        Trapezoid(const Trapezoid& trapezoid);
        ~Trapezoid();

        void setTop(const cg3::Segment2d& segment);
        void setBot(const cg3::Segment2d& segment);
        void setLeftP(const cg3::Point2d& point);
        void setRightP(const cg3::Point2d& point);

        void setTopLeftNeighbor(const size_t trapezoid);
        void setTopRightNeighbor(const size_t trapezoid);
        void setBotLeftNeighbor(const size_t trapezoid);
        void setBotRightNeighbor(const size_t trapezoid);

        const cg3::Segment2d& getTop() const;
        const cg3::Segment2d& getBot() const;
        const cg3::Point2d& getLeftP() const;
        const cg3::Point2d& getRightP() const;

        size_t getTopLeftNeighbor() const;
        size_t getTopRightNeighbor() const;
        size_t getBotLeftNeighbor() const;
        size_t getBotRightNeighbor() const;
};

#endif // TRAPEZOID_H
