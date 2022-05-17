#include "trapezoidalmap.h"

TrapezoidalMap::TrapezoidalMap() {
    trapezoids = std::vector<Trapezoid>();
}

TrapezoidalMap::~TrapezoidalMap() {
    trapezoids.~vector();
}

size_t TrapezoidalMap::addTrapezoid(const Trapezoid& trapezoid) {
    trapezoids.push_back(trapezoid);
    return trapezoids.size();
}

void TrapezoidalMap::updateTrapezoid(const int index, const Trapezoid& trapezoid) {
    trapezoids[index].~Trapezoid();
    trapezoids[index] = trapezoid;
}

void TrapezoidalMap::split4(const int index, cg3::Segment2d& segment) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[index];

    /* Creation of the new 4 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), origin.getBot(), origin.getLeftP(), segment.p1());
    Trapezoid t2 = Trapezoid(origin.getTop(), segment, segment.p1(), segment.p2());
    Trapezoid t3 = Trapezoid(segment, origin.getBot(), segment.p1(), segment.p2());
    Trapezoid t4 = Trapezoid(origin.getTop(), origin.getBot(), segment.p2(), origin.getRightP());

    /* Indexes in the Trapezoids Vector of the new 4 Trapezoids.
     * The first one will replace the one that is being replaced */
    size_t t1Index = index;
    size_t t2Index = addTrapezoid(t2);
    size_t t3Index = addTrapezoid(t3);
    size_t t4Index = addTrapezoid(t4);

    /* Updating t1's neighbors */
    t1.setTopLeftNeighbor(origin.getTopLeftNeighbor());
    t1.setBotLeftNeighbor(origin.getBotLeftNeighbor());
    t1.setTopRightNeighbor(t2Index);
    t1.setBotRightNeighbor(t3Index);

    /* Updating t2's neighbors */
    t2.setTopLeftNeighbor(t1Index);
    t2.setTopRightNeighbor(t4Index);
    t2.setBotLeftNeighbor(0);
    t2.setBotRightNeighbor(0);

    /* Updating t3's neighbors */
    t3.setTopLeftNeighbor(0);
    t3.setTopRightNeighbor(0);
    t3.setBotLeftNeighbor(t1Index);
    t3.setBotRightNeighbor(t4Index);

    /* Updating t4's neighbors */
    t4.setTopLeftNeighbor(t2Index);
    t4.setBotLeftNeighbor(t3Index);
    t4.setTopRightNeighbor(origin.getTopRightNeighbor());
    t4.setBotRightNeighbor(origin.getBotRightNeighbor());

    /* Updating */
    updateTrapezoid(index, t1);
}

void TrapezoidalMap::split3Left(const int index, cg3::Segment2d& segment) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[index];

    /* Creation of the new 3 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), origin.getBot(), origin.getLeftP(), segment.p1());
    Trapezoid t2 = Trapezoid(origin.getTop(), segment, segment.p1(), origin.getRightP());
    Trapezoid t3 = Trapezoid(segment, origin.getBot(), segment.p1(), origin.getRightP());

    /* Indexes in the Trapezoids Vector of the new 3 Trapezoids.
     * The first one will replace the one that is being replaced */
    size_t t1Index = index;
    size_t t2Index = addTrapezoid(t2);
    size_t t3Index = addTrapezoid(t3);

    /* Updating t1's neighbors */
    t1.setTopLeftNeighbor(origin.getTopLeftNeighbor());
    t1.setBotLeftNeighbor(origin.getBotLeftNeighbor());
    t1.setTopRightNeighbor(t2Index);
    t1.setBotRightNeighbor(t3Index);

    /* Updating t2's neighbors */
    t2.setTopLeftNeighbor(t1Index);
    t2.setTopRightNeighbor(origin.getTopRightNeighbor());
    t2.setBotLeftNeighbor(0);
    t2.setBotRightNeighbor(0);

    /* Updating t3's neighbors */
    t3.setTopLeftNeighbor(0);
    t3.setTopRightNeighbor(0);
    t3.setBotLeftNeighbor(t1Index);
    t3.setBotRightNeighbor(origin.getBotRightNeighbor());

    /* Updating */
    updateTrapezoid(index, t1);
}

void TrapezoidalMap::split3Right(const int index, cg3::Segment2d& segment) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[index];

    /* Creation of the new 3 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), segment, origin.getLeftP(), segment.p2());
    Trapezoid t2 = Trapezoid(segment, origin.getBot(), origin.getLeftP(), segment.p2());
    Trapezoid t3 = Trapezoid(origin.getTop(), origin.getBot(), segment.p2(), origin.getRightP());

    /* Indexes in the Trapezoids Vector of the new 3 Trapezoids.
     * The first one will replace the one that is being replaced */
    size_t t1Index = index;
    size_t t2Index = addTrapezoid(t2);
    size_t t3Index = addTrapezoid(t3);

    /* Updating t1's neighbors */
    t1.setTopLeftNeighbor(origin.getTopLeftNeighbor());
    t1.setTopRightNeighbor(t3Index);
    t1.setBotLeftNeighbor(0);
    t1.setBotRightNeighbor(0);

    /* Updating t2's neighbors */
    t2.setTopLeftNeighbor(0);
    t2.setTopRightNeighbor(0);
    t2.setBotLeftNeighbor(origin.getBotLeftNeighbor());
    t2.setBotRightNeighbor(t3Index);

    /* Updating t1's neighbors */
    t3.setTopLeftNeighbor(t1Index);
    t3.setBotLeftNeighbor(t2Index);
    t3.setTopRightNeighbor(origin.getTopRightNeighbor());
    t3.setBotRightNeighbor(origin.getBotRightNeighbor());


    /* Updating */
    updateTrapezoid(index, t1);
}

void TrapezoidalMap::split2(const int index, cg3::Segment2d& segment) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[index];

    /* Creation of the new 2 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), segment, origin.getLeftP(), origin.getRightP());
    Trapezoid t2 = Trapezoid(segment, origin.getBot(), origin.getLeftP(), origin.getRightP());

    /* Indexes in the Trapezoids Vector of the new 2 Trapezoids.
     * The first one will replace the one that is being replaced */
    size_t t1Index = index;
    size_t t2Index = addTrapezoid(t2);

    /* Updating t1's neighbors */
    t1.setTopLeftNeighbor(origin.getTopLeftNeighbor());
    t1.setTopRightNeighbor(origin.getTopRightNeighbor());
    t1.setBotLeftNeighbor(0);
    t1.setBotRightNeighbor(0);

    /* Updating t2's neighbors */
    t2.setTopLeftNeighbor(0);
    t2.setTopRightNeighbor(0);
    t2.setBotLeftNeighbor(origin.getBotLeftNeighbor());
    t2.setBotRightNeighbor(origin.getBotRightNeighbor());

    /* Updating */
    updateTrapezoid(index, t1);
}
