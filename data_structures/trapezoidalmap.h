#ifndef TRAPEZOIDALMAP_H
#define TRAPEZOIDALMAP_H

#include "trapezoid.h"

class TrapezoidalMap {
    private:
        std::vector<Trapezoid> trapezoids;

        void updateTrapezoid(const size_t index, const Trapezoid& trapezoid);

        void split4(const size_t trpzToReplace, const cg3::Segment2d& segment);
        void split3Left(const size_t trpzToReplace, const cg3::Segment2d& segment);
        void split2MergeTop(const size_t trpzToReplace, const cg3::Segment2d& segment, const size_t trpzToMerge, const size_t trpzNB);
        void split2MergeBot(const size_t trpzToReplace, const cg3::Segment2d& segment, const size_t trpzToMerge, const size_t trpzNB);
        void split3RightMergeTop(const size_t trpzToReplace, const cg3::Segment2d& segment, const size_t trpzToMerge, const size_t trpzNB);
        void split3RightMergeBot(const size_t trpzToReplace, const cg3::Segment2d& segment, const size_t trpezToMerge, const size_t trpzNB);
    public:
        TrapezoidalMap();
        ~TrapezoidalMap();

        size_t addTrapezoid(const Trapezoid& trapezoid);

        void updateTrapezoidalMap(const size_t startTrpz, const cg3::Segment2d& segment);
};

#endif // TRAPEZOIDALMAP_H
