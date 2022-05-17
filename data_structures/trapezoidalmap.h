#ifndef TRAPEZOIDALMAP_H
#define TRAPEZOIDALMAP_H

#include "trapezoid.h"

class TrapezoidalMap {
    private:
        std::vector<Trapezoid> trapezoids;
    public:
        TrapezoidalMap();
        ~TrapezoidalMap();

        size_t addTrapezoid(const Trapezoid& trapezoid);
        void updateTrapezoid(const int index, const Trapezoid& trapezoid);

        void split4(const int index, cg3::Segment2d& segment);
        void split3Left(const int index, cg3::Segment2d& segment);
        void split3Right(const int index, cg3::Segment2d& segment);
        void split2(const int index, cg3::Segment2d& segment);
};

#endif // TRAPEZOIDALMAP_H
