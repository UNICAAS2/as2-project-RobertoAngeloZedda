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

        size_t addTrapezoid(const Trapezoid& trapezoid);
        void updateTrapezoid(const size_t& index, const Trapezoid& trapezoid);
    public:
        TrapezoidalMap(const Trapezoid& trapezoid);

        const Trapezoid& getTrapezoid(const size_t& index) const;

        const std::vector<size_t> split4(const size_t& trpzToReplace, const cg3::Segment2d& segment);
        const std::vector<size_t> split3(const size_t& trpzToReplace, const cg3::Segment2d& segment);
        const std::vector<size_t> split2MergeTop(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                                 const size_t& trpzToMerge, const size_t& trpzNB);
        const std::vector<size_t> split2MergeBot(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                                 const size_t& trpzToMerge, const size_t& trpzNB);
        const std::vector<size_t> split3MergeTop(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                                 const size_t& trpzToMerge, const size_t& trpzNB);
        const std::vector<size_t> split3MergeBot(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                                 const size_t& trpezToMerge, const size_t& trpzNB);
};

#endif // TRAPEZOIDALMAP_H
