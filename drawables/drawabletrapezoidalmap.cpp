#include "drawabletrapezoidalmap.h"

#define RANDOM_COLOR_BASE 140
#define RANDOM_COLOR_OFFSET 75

/**
 * @brief DrawableTrapezoidalMap Constructor
 * @param botLeft, bot left point of the bounding box
 * @param topRight, top right point of the bounding box
 */
DrawableTrapezoidalMap::DrawableTrapezoidalMap(const cg3::Point2d& botLeft, const cg3::Point2d& topRight):
    TrapezoidalMap(botLeft, topRight),
    selectedTrapezoidColor(255, 0, 0),
    segmentColor(0, 0, 0)
{
    srand(time(0));

    selectedTrapezoid = SIZE_MAX;
    updateColors();
}

/**
 * @brief Generates a Color for every Trapezoids that doesnt have one already.
 */
void DrawableTrapezoidalMap::updateColors() {
    while(colors.size() < getTrapezoidalMapSize())
        colors.push_back(randomColor());
}

void DrawableTrapezoidalMap::draw() const {
    /* For each Trapezoid */
    for(size_t i=0; i<getTrapezoidalMapSize(); i++) {
        /* If its not the deleted one */
        if(i != getFreeSlotIndex()) {
            Trapezoid t = getTrapezoid(i);
            Trapezoid boundingBox = getBoundingBox();

            /* Calculate the effective points of the Trapezoid */
            cg3::Point2d p1 = calculateIntersection(t.getTop(), t.getLeftP().x());
            cg3::Point2d p2 = calculateIntersection(t.getTop(), t.getRightP().x());
            cg3::Point2d p3 = calculateIntersection(t.getBot(), t.getRightP().x());
            cg3::Point2d p4 = calculateIntersection(t.getBot(), t.getLeftP().x());

            /* Define the Trapezoid color based of if it's selected or not */
            cg3::Color trapezoidColor;
            if(i == selectedTrapezoid)
                trapezoidColor = selectedTrapezoidColor;
            else
                trapezoidColor = colors[i];

            /* In case it is a Tringale */
            if(p1 == p4) {
                cg3::opengl::drawTriangle2(p1, p2, p3, trapezoidColor, 1, true);

                /* Draw its vertical boundaries if they dont overlap with the bounding box */
                if(p2.x() != boundingBox.getRightP().x())
                    cg3::opengl::drawLine2(p2, p3, segmentColor, 3);
            } else if(p2 == p3) {
                cg3::opengl::drawTriangle2(p1, p2, p4, trapezoidColor, 1, true);

                /* Draw its vertical boundaries if they dont overlap with the bounding box */
                if(p1.x() != boundingBox.getLeftP().x())
                    cg3::opengl::drawLine2(p1, p4, segmentColor, 3);
            /* In case it is a Quadrangle */
            } else {
                cg3::opengl::drawQuad2(p1, p2, p3, p4, trapezoidColor, 1, true);

                /* Draw its vertical boundaries if they dont overlap with the bounding box */
                if(p1.x() != boundingBox.getLeftP().x())
                    cg3::opengl::drawLine2(p1, p4, segmentColor, 3);
                if(p2.x() != boundingBox.getRightP().x())
                    cg3::opengl::drawLine2(p2, p3, segmentColor, 3);
            }
        }
    }
}

cg3::Point3d DrawableTrapezoidalMap::sceneCenter() const {
    const cg3::BoundingBox2& boundingBox = cg3::BoundingBox2();
    return cg3::Point3d(boundingBox.center().x(), boundingBox.center().y(), 0);
}

double DrawableTrapezoidalMap::sceneRadius() const {
    const cg3::BoundingBox2& boundingBox = cg3::BoundingBox2();
    return boundingBox.diag();
}

/**
 * @brief Generates a "random" Color.
 * @return the generated Color.
 */
const cg3::Color DrawableTrapezoidalMap::randomColor() const {
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
const cg3::Point2d DrawableTrapezoidalMap::calculateIntersection(const cg3::Segment2d& s, const double& x) const {
    cg3::Point2d p1 = s.p1();
    cg3::Point2d p2 = s.p2();

    double m = (p2.y() - p1.y())/(p2.x() - p1.x());

    return cg3::Point2d(x, m * (x - p1.x()) + p1.y());
}

/**
 * @brief Sets the index of the selected Trapezoid.
 * @param index, the index
 */
void DrawableTrapezoidalMap::setSelectedTrapezoid(size_t index) {
    assert(index >= 0 && index < getTrapezoidalMapSize());
    selectedTrapezoid = index;
}

/**
 * @brief Clears the DrawableTrapezoidalMap restoring the original Trapezoid.
 */
void DrawableTrapezoidalMap::clear() {
    TrapezoidalMap::clear();

    selectedTrapezoid = SIZE_MAX;

    /* Keeps the same color in case the Trapezoidal map was empty */
    cg3::Color bbColor;
    if(colors.size() == 1)
        bbColor = colors[0];
    else
        bbColor = randomColor();

    colors.clear();
    colors.push_back(bbColor);
}
