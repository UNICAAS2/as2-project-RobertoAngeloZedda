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

        /* Will keep the index of the "deleted" Trapezoid after a Merge operation
           in order to put a new Trapezoid in that position when needed
           to not leave holes in the vector */
        size_t freeSlotIndex;

        /* Will store a copy of the first Trapezoid (the bounding box)
           in order to be able to restore its primal state */
        Trapezoid boundingBox;

        size_t addTrapezoid(const Trapezoid& trapezoid);
        void updateTrapezoid(const size_t& index, const Trapezoid& trapezoid);
    public:
        TrapezoidalMap();
        TrapezoidalMap(const cg3::Point2d& botLeft, const cg3::Point2d& topRight);

        Trapezoid& getTrapezoid(const size_t& index);
        const Trapezoid& getTrapezoid(const size_t& index) const;

        const std::array<size_t, 4> split4(const size_t& trpzToReplace, const cg3::Segment2d& segment);
        const std::array<size_t, 3> split3L(const size_t& trpzToReplace, const cg3::Segment2d& segment);
        const std::array<size_t, 2> split2(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                         const size_t& trpzPrevSplitTop, const size_t& trpzPrevSplitBot);
        const std::array<size_t, 3> split3R(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                          const size_t& trpzPrevSplitTop, const size_t& trpzPrevSplitBot);

        void merge(const size_t& leftTrpzIndex, const size_t& rightTrpzIndex);

        size_t getTrapezoidalMapSize() const;
        size_t getFreeSlotIndex() const;
        const Trapezoid& getBoundingBox() const;

        void clear();
};

#endif // TRAPEZOIDALMAP_H
