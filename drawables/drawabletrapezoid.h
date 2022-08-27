#ifndef DRAWABLETRAPEZOID_H
#define DRAWABLETRAPEZOID_H

#include <data_structures/trapezoid.h>
#include <cg3/utilities/color.h>
#include <cstdlib>
#include <ctime>

/**
 * @brief Base element of the DrawableTrapezoidalMap.
 * A DrawableTrapezoid is made off four effective points describing its boundaries and a Color.
 */
class DrawableTrapezoid
{
    private:
        cg3::Point2d topLeft;
        cg3::Point2d topRight;
        cg3::Point2d botRight;
        cg3::Point2d botLeft;

        cg3::Color color;

        const cg3::Color randomColor() const;
        const cg3::Point2d calculateIntersection(const cg3::Segment2d& s, const double& x) const;
    public:
        DrawableTrapezoid(Trapezoid& trapezoid);

        const cg3::Point2d& getTopLeft() const;
        const cg3::Point2d& getTopRight() const;
        const cg3::Point2d& getBotRight() const;
        const cg3::Point2d& getBotLeft() const;

        const cg3::Color& getColor() const;

        void setColor(cg3::Color& c);
};

#endif // DRAWABLETRAPEZOID_H
