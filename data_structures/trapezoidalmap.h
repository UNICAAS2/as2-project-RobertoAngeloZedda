#ifndef TRAPEZOIDALMAP_H
#define TRAPEZOIDALMAP_H

#include "trapezoid.h"

/**
 * @brief The TrapezoidalMap class.
 * A TrapezoidalMap is defined through a vector of Trapezoid.
 */
class TrapezoidalMap {
    private:
        std::vector<Trapezoid> trapezoids;

        size_t freeSlotIndex;

        size_t addTrapezoid(const Trapezoid& trapezoid);
        void updateTrapezoid(const size_t& index, const Trapezoid& trapezoid);
    public:
        TrapezoidalMap(const Trapezoid& trapezoid);

        Trapezoid& getTrapezoid(const size_t& index);

        const std::vector<size_t> split4(const size_t& trpzToReplace, const cg3::Segment2d& segment);
        const std::vector<size_t> split3L(const size_t& trpzToReplace, const cg3::Segment2d& segment);
        const std::vector<size_t> split2(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                         const size_t& trpzPrevSplitTop, const size_t& trpzPrevSplitBot);
        const std::vector<size_t> split3R(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                          const size_t& trpzPrevSplitTop, const size_t& trpzPrevSplitBot);

        void merge(size_t leftTrpzIndex, size_t rightTrpzIndex);
};

#endif // TRAPEZOIDALMAP_H
