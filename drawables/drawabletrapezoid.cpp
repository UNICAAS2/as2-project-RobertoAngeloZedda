#include "drawabletrapezoid.h"

#define RANDOM_COLOR_BASE 140
#define RANDOM_COLOR_OFFSET 75

#define ROUND 1e7

/**
 * @brief DrawableTrapezoid constructor.
 * @param t, Trapezoid the DrawableTrapezoid is constructed from.
 */
DrawableTrapezoid::DrawableTrapezoid(Trapezoid& t) {
    topLeft = calculateIntersection(t.getTop(), t.getLeftP().x());
    topRight = calculateIntersection(t.getTop(), t.getRightP().x());;
    botRight = calculateIntersection(t.getBot(), t.getRightP().x());;
    botLeft = calculateIntersection(t.getBot(), t.getLeftP().x());;

    color = randomColor();
}

/**
 * @brief Getter for the top left Point.
 * @return The top left Point.
 */
const cg3::Point2d& DrawableTrapezoid::getTopLeft() const { return topLeft; }
/**
 * @brief Getter for the top right Point.
 * @return The top right Point.
 */
const cg3::Point2d& DrawableTrapezoid::getTopRight() const { return topRight; }
/**
 * @brief Getter for the bot right Point.
 * @return The bot right Point.
 */
const cg3::Point2d& DrawableTrapezoid::getBotRight() const { return botRight; }
/**
 * @brief Getter for the bot left Point.
 * @return The bot left Point.
 */
const cg3::Point2d& DrawableTrapezoid::getBotLeft() const { return botLeft; }
/**
 * @brief Getter for the Color.
 * @return The Color.
 */
const cg3::Color& DrawableTrapezoid::getColor() const { return color; }

/**
 * @brief Generates a "random" Color.
 * @return the generated Color.
 */
const cg3::Color DrawableTrapezoid::randomColor() const {
    return cg3::Color(RANDOM_COLOR_BASE + (rand() % RANDOM_COLOR_OFFSET),
                      RANDOM_COLOR_BASE + (rand() % RANDOM_COLOR_OFFSET),
                      RANDOM_COLOR_BASE + (rand() % RANDOM_COLOR_OFFSET));
}

/**
 * @brief Calculates the intersection Point between a Segment and a line parallel to the Y axis.
 * @param s, the Segment
 * @param x, the X coordinate of the line parallel to the Y axis
 * @return the intersection Point.
 */
const cg3::Point2d DrawableTrapezoid::calculateIntersection(const cg3::Segment2d& s, const double& x) const {
    cg3::Point2d p1 = s.p1();
    cg3::Point2d p2 = s.p2();

    double m = (p2.y() - p1.y())/(p2.x() - p1.x());

    double y = m * (x - p1.x()) + p1.y();
    y = (static_cast<long long int>(y * ROUND))/ROUND;

    return cg3::Point2d(x, y);
}

/**
 * @brief Setter for the Color.
 * @param c, he Color.
 */
void DrawableTrapezoid::setColor(cg3::Color& c) { color = c; }
