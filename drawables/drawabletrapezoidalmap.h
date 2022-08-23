#ifndef DRAWABLETRAPEZOIDALMAP_H
#define DRAWABLETRAPEZOIDALMAP_H

#include "data_structures/trapezoidalmap.h"

#include <cg3/viewer/interfaces/drawable_object.h>

#include <cg3/utilities/color.h>

#include <cg3/viewer/opengl_objects/opengl_objects2.h>

#include <cg3/geometry/bounding_box2.h>

#include <cstdlib>
#include <ctime>

class DrawableTrapezoidalMap : public TrapezoidalMap, public cg3::DrawableObject
{
    private:
        std::vector<cg3::Color> colors;
        size_t selectedTrapezoid;
    public:
        DrawableTrapezoidalMap(const cg3::Point2d botLeft, const cg3::Point2d topRight);

        void updateColors();

        void draw() const;
        cg3::Point3d sceneCenter() const;
        double sceneRadius() const;

        const cg3::Color randomColor() const;

        cg3::Point2d aaa(cg3::Segment2d s, double x) const;

        void setSelectedTrapezoid(size_t index);

        void clear();
};

#endif // DRAWABLETRAPEZOIDALMAP_H
