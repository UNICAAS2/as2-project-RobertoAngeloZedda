#ifndef DRAWABLETRAPEZOIDALMAP_H
#define DRAWABLETRAPEZOIDALMAP_H

#include "data_structures/trapezoidalmap.h"

#include <cg3/viewer/interfaces/drawable_object.h>

#include <cg3/utilities/color.h>

#include <cg3/viewer/opengl_objects/opengl_objects2.h>

class DrawableTrapezoidalMap : public TrapezoidalMap, public cg3::DrawableObject
{
    private:
        std::vector<cg3::Color> colors;
    public:
        DrawableTrapezoidalMap(const Trapezoid& boundingBox);

        void draw() const;

        const cg3::Color randomColor() const;
};

#endif // DRAWABLETRAPEZOIDALMAP_H
