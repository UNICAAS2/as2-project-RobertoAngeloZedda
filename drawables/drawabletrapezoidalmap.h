#ifndef DRAWABLETRAPEZOIDALMAP_H
#define DRAWABLETRAPEZOIDALMAP_H

#include "data_structures/trapezoidalmap.h"
#include "drawables/drawabletrapezoid.h"
#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/viewer/opengl_objects/opengl_objects2.h>
#include <cg3/geometry/bounding_box2.h>

class DrawableTrapezoidalMap : public TrapezoidalMap, public cg3::DrawableObject
{
    private:
        std::vector<DrawableTrapezoid> drawableTrapezoids;
        size_t selectedTrapezoid;

        const cg3::Color selectedTrapezoidColor;
        const cg3::Color segmentColor;
    public:
        DrawableTrapezoidalMap(const cg3::Point2d& botLeft, const cg3::Point2d& topRight);

        void draw() const;
        cg3::Point3d sceneCenter() const;
        double sceneRadius() const;

        void setSelectedTrapezoid(size_t index);

        const std::array<size_t, 4> split4(const size_t& trpzToReplace, const cg3::Segment2d& segment);
        const std::array<size_t, 3> split3L(const size_t& trpzToReplace, const cg3::Segment2d& segment);
        const std::array<size_t, 2> split2(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                         const size_t& trpzPrevSplitTop, const size_t& trpzPrevSplitBot);
        const std::array<size_t, 3> split3R(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                          const size_t& trpzPrevSplitTop, const size_t& trpzPrevSplitBot);

        void merge(const size_t& leftTrpzIndex, const size_t& rightTrpzIndex);

        void clear();
};

#endif // DRAWABLETRAPEZOIDALMAP_H
