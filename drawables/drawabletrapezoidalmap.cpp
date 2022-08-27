#include "drawabletrapezoidalmap.h"

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
    /* For the random generation of colors */
    srand(time(0));

    /* Creating the DrawableTrapezoid for the boundingbox */
    drawableTrapezoids.push_back(DrawableTrapezoid(getTrapezoid(0)));

    selectedTrapezoid = SIZE_MAX;
}

void DrawableTrapezoidalMap::draw() const {
    /* For each Trapezoid */
    for(size_t i=0; i<drawableTrapezoids.size(); i++) {
        /* If its not the deleted one */
        if(i != getFreeSlotIndex()) {
            Trapezoid boundingBox = getBoundingBox();

            /* References to the effective points of the Trapezoid */
            cg3::Point2d p1 = drawableTrapezoids[i].getTopLeft();
            cg3::Point2d p2 = drawableTrapezoids[i].getTopRight();
            cg3::Point2d p3 = drawableTrapezoids[i].getBotRight();
            cg3::Point2d p4 = drawableTrapezoids[i].getBotLeft();

            /* Define the Trapezoid color based of if it's selected or not */
            cg3::Color trapezoidColor;
            if(i == selectedTrapezoid)
                trapezoidColor = selectedTrapezoidColor;
            else
                trapezoidColor = drawableTrapezoids[i].getColor();

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
 * @brief Sets the index of the selected Trapezoid.
 * @param index, the index
 */
void DrawableTrapezoidalMap::setSelectedTrapezoid(size_t index) {
    assert(index >= 0 && index < getTrapezoidalMapSize());
    selectedTrapezoid = index;
}

/**
 * @brief Splits the Trapezoid in 4 new Trapezoids and updates the DrawableTrapezoid Vector.
 *
 * The first Trapezoid, the left most one, will keep the same index
 * of the Trapezoid that is being replaced.
 *
 * All the neighbors will also be updated.
 * @param trpzToReplace, index of the Trapezoid to replace
 * @param segment, Segment to compute the spit around
 * @return an Array containing the 4 indexes of the new Trapezoids
 */
const std::array<size_t, 4> DrawableTrapezoidalMap::split4(const size_t& trpzToReplace, const cg3::Segment2d& segment) {
    std::array<size_t, 4> newTrapezoidsIndexes = TrapezoidalMap::split4(trpzToReplace, segment);

    size_t t1i = newTrapezoidsIndexes[0];
    size_t t2i = newTrapezoidsIndexes[1];
    size_t t3i = newTrapezoidsIndexes[2];
    size_t t4i = newTrapezoidsIndexes[3];

    drawableTrapezoids[t1i] = DrawableTrapezoid(getTrapezoid(t1i));

    /* Handling the case in which a "deleted" trapezoid has been updated */
    if(t2i >= drawableTrapezoids.size())
        drawableTrapezoids.push_back(DrawableTrapezoid(getTrapezoid(t2i)));
    else
        drawableTrapezoids[t2i] = DrawableTrapezoid(getTrapezoid(t2i));

    drawableTrapezoids.push_back(DrawableTrapezoid(getTrapezoid(t3i)));
    drawableTrapezoids.push_back(DrawableTrapezoid(getTrapezoid(t4i)));

    return newTrapezoidsIndexes;
}

/**
 * @brief Splits the Trapezoid in 3 new Trapezoids around a Segment starting inside the original Trapezoid and updates the DrawableTrapezoid Vector.
 *
 * The first Trapezoid, the left most one, will keep the same index
 * of the Trapezoid that is being replaced.
 *
 * The neighbors will also be updated.
 * @param trpzToReplace, index of the Trapezoid to replace
 * @param segment, Segment to compute the spit around
 * @return an Array containing the 3 indexes of the new Trapezoids
 */
const std::array<size_t, 3> DrawableTrapezoidalMap::split3L(const size_t& trpzToReplace, const cg3::Segment2d& segment) {
    std::array<size_t, 3> newTrapezoidsIndexes = TrapezoidalMap::split3L(trpzToReplace, segment);

    size_t t1i = newTrapezoidsIndexes[0];
    size_t t2i = newTrapezoidsIndexes[1];
    size_t t3i = newTrapezoidsIndexes[2];

    drawableTrapezoids[t1i] = DrawableTrapezoid(getTrapezoid(t1i));

    /* Handling the case in which a "deleted" trapezoid has been updated */
    if(t2i >= drawableTrapezoids.size())
        drawableTrapezoids.push_back(DrawableTrapezoid(getTrapezoid(t2i)));
    else
        drawableTrapezoids[t2i] = DrawableTrapezoid(getTrapezoid(t2i));

    drawableTrapezoids.push_back(DrawableTrapezoid(getTrapezoid(t3i)));

    return newTrapezoidsIndexes;
}

/**
 * @brief Splits the Trapezoid in 2 new Trapezoids around a Segment and updates the DrawableTrapezoid Vector.
 *
 * The first Trapezoid, the upper one, will keep the same index
 * of the Trapezoid that is being replaced.
 *
 * The neighbors will also be updated.
 * @param trpzToReplace, index of the Trapezoid to replace
 * @param segment, Segment to compute the spit around
 * @param trpzPrevSplitTop, index of the left neighbor Trapezoid from a previous split (above the segment).
 * @param trpzPrevSplitBot, index of the left neighbor Trapezoid from a previous split (under the segment).
 * @return an Array containing the 3 indexes of the new Trapezoids
 */
const std::array<size_t, 2> DrawableTrapezoidalMap::split2(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                                           const size_t& trpzPrevSplitTop, const size_t& trpzPrevSplitBot) {
    std::array<size_t, 2> newTrapezoidsIndexes = TrapezoidalMap::split2(trpzToReplace, segment, trpzPrevSplitTop, trpzPrevSplitBot);

    size_t t1i = newTrapezoidsIndexes[0];
    size_t t2i = newTrapezoidsIndexes[1];

    drawableTrapezoids[t1i] = DrawableTrapezoid(getTrapezoid(t1i));

    /* Handling the case in which a "deleted" trapezoid has been updated */
    if(t2i >= drawableTrapezoids.size())
        drawableTrapezoids.push_back(DrawableTrapezoid(getTrapezoid(t2i)));
    else
        drawableTrapezoids[t2i] = DrawableTrapezoid(getTrapezoid(t2i));

    return newTrapezoidsIndexes;
}

/**
 * @brief Splits the Trapezoid in 3 new Trapezoids around a Segment ending inside the original Trapezoid and updates the DrawableTrapezoid Vector.
 *
 * The third Trapezoid, the right most one, will keep the same index
 * of the Trapezoid that is being replaced.
 *
 * The neighbors will also be updated.
 * @param trpzToReplace, index of the Trapezoid to replace
 * @param segment, Segment to compute the spit around
 * @param trpzPrevSplitTop, index of the left neighbor Trapezoid from a previous split (above the segment).
 * @param trpzPrevSplitBot, index of the left neighbor Trapezoid from a previous split (under the segment).
 * @return an Array containing the 3 indexes of the new Trapezoids
 */
const std::array<size_t, 3> DrawableTrapezoidalMap::split3R(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                                            const size_t& trpzPrevSplitTop, const size_t& trpzPrevSplitBot) {
    std::array<size_t, 3> newTrapezoidsIndexes = TrapezoidalMap::split3R(trpzToReplace, segment, trpzPrevSplitTop, trpzPrevSplitBot);

    size_t t1i = newTrapezoidsIndexes[0];
    size_t t2i = newTrapezoidsIndexes[1];
    size_t t3i = newTrapezoidsIndexes[2];

    /* Handling the case in which a "deleted" trapezoid has been updated */
    if(t1i >= drawableTrapezoids.size())
        drawableTrapezoids.push_back(DrawableTrapezoid(getTrapezoid(t1i)));
    else
        drawableTrapezoids[t1i] = DrawableTrapezoid(getTrapezoid(t1i));

    drawableTrapezoids.push_back(DrawableTrapezoid(getTrapezoid(t2i)));
    drawableTrapezoids[t3i] = DrawableTrapezoid(getTrapezoid(t3i));

    return newTrapezoidsIndexes;
}

/**
 * @brief Merges two Trapezoids and updates the DrawableTrapezoid Vector.
 *
 * The left trapezoid will be updated inside the map.
 * The right trapezoid will be considered as deleted.
 *
 * The neighbors will also be updated.
 * @param leftTrpzIndex, index of the left Trapezoid to merge
 * @param rightTrpzIndex, index of the right Trapezoid to merge
 */
void DrawableTrapezoidalMap::merge(const size_t& leftTrpzIndex, const size_t& rightTrpzIndex) {
    TrapezoidalMap::merge(leftTrpzIndex, rightTrpzIndex);

    drawableTrapezoids[leftTrpzIndex] = DrawableTrapezoid(getTrapezoid(leftTrpzIndex));
}

/**
 * @brief Clears the DrawableTrapezoidalMap restoring the original Trapezoid.
 */
void DrawableTrapezoidalMap::clear() {
    selectedTrapezoid = SIZE_MAX;

    /* Keeps the same color in case the Trapezoidal map was empty */
    if(getTrapezoidalMapSize() == 1) {
        TrapezoidalMap::clear();

        cg3::Color bbColor = drawableTrapezoids[0].getColor();
        drawableTrapezoids.clear();

        drawableTrapezoids.push_back(DrawableTrapezoid(getTrapezoid(0)));
        drawableTrapezoids[0].setColor(bbColor);
    } else {
        TrapezoidalMap::clear();
        drawableTrapezoids.clear();
        drawableTrapezoids.push_back(DrawableTrapezoid(getTrapezoid(0)));
    }
}
