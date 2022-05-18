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

void TrapezoidalMap::updateTrapezoid(const size_t index, const Trapezoid& trapezoid) {
    trapezoids[index].~Trapezoid();
    trapezoids[index] = trapezoid;
}

void TrapezoidalMap::split4(const size_t trpzToReplace, const cg3::Segment2d& segment) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[trpzToReplace];

    /* Creation of the new 4 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), origin.getBot(), origin.getLeftP(), segment.p1());
    Trapezoid t2 = Trapezoid(origin.getTop(), segment, segment.p1(), segment.p2());
    Trapezoid t3 = Trapezoid(segment, origin.getBot(), segment.p1(), segment.p2());
    Trapezoid t4 = Trapezoid(origin.getTop(), origin.getBot(), segment.p2(), origin.getRightP());

    /* Indexes in the Trapezoids Vector of the new 4 Trapezoids.
     * The first one will replace the one that is being replaced */
    size_t t1Index = trpzToReplace;
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

    /* Updating t3's neighbors */
    t3.setBotLeftNeighbor(t1Index);
    t3.setBotRightNeighbor(t4Index);

    /* Updating t4's neighbors */
    t4.setTopLeftNeighbor(t2Index);
    t4.setBotLeftNeighbor(t3Index);
    t4.setTopRightNeighbor(origin.getTopRightNeighbor());
    t4.setBotRightNeighbor(origin.getBotRightNeighbor());

    /* Updating */
    updateTrapezoid(trpzToReplace, t1);
}

void TrapezoidalMap::split3Left(const size_t trpzToReplace, const cg3::Segment2d& segment) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[trpzToReplace];

    /* Creation of the new 3 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), origin.getBot(), origin.getLeftP(), segment.p1());
    Trapezoid t2 = Trapezoid(origin.getTop(), segment, segment.p1(), origin.getRightP());
    Trapezoid t3 = Trapezoid(segment, origin.getBot(), segment.p1(), origin.getRightP());

    /* Indexes in the Trapezoids Vector of the new 3 Trapezoids.
     * The first one will replace the one that is being splitted */
    size_t t1Index = trpzToReplace;
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

    /* Updating t3's neighbors */
    t3.setBotLeftNeighbor(t1Index);
    t3.setBotRightNeighbor(origin.getBotRightNeighbor());

    /* Updating */
    updateTrapezoid(trpzToReplace, t1);
}

void TrapezoidalMap::split2MergeTop(const size_t trpzToReplace, const cg3::Segment2d& segment, const size_t trpzToMerge, const size_t trpzNB) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[trpzToReplace];
    /* Reference of the Trapezoid that needs to be merged */
    Trapezoid merge = trapezoids[trpzToMerge];

    /* Creation of the new 2 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), segment, merge.getLeftP(), origin.getRightP());
    Trapezoid t2 = Trapezoid(segment, origin.getBot(), origin.getLeftP(), origin.getRightP());

    /* Updating t1's neighbors */
    t1.setTopLeftNeighbor(merge.getTopLeftNeighbor());
    t1.setBotLeftNeighbor(merge.getBotLeftNeighbor());

    /* Updating t2's neighbors */
    t2.setTopLeftNeighbor(trpzNB);

    /* Updating the left neighbors' neighbors */
    trapezoids[trpzNB].setTopRightNeighbor(trpzToReplace);

    /* Updating */
    updateTrapezoid(trpzToMerge, t1);
    updateTrapezoid(trpzToReplace, t2);
}

void TrapezoidalMap::split2MergeBot(const size_t trpzToReplace, const cg3::Segment2d& segment, const size_t trpzToMerge, const size_t trpzNB) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[trpzToReplace];
    /* Reference of the Trapezoid that needs to be merged */
    Trapezoid merge = trapezoids[trpzToMerge];

    /* Creation of the new 2 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), segment, origin.getLeftP(), origin.getRightP());
    Trapezoid t2 = Trapezoid(segment, origin.getBot(), merge.getLeftP(), origin.getRightP());

    /* Updating t1's neighbors */
    t1.setBotLeftNeighbor(trpzNB);

    /* Updating t2's neighbors */
    t2.setTopLeftNeighbor(merge.getTopLeftNeighbor());
    t2.setBotLeftNeighbor(merge.getBotLeftNeighbor());

    /* Updating the left neighbors' neighbors */
    trapezoids[trpzNB].setTopRightNeighbor(trpzToReplace);

    /* Updating */
    updateTrapezoid(trpzToReplace, t1);
    updateTrapezoid(trpzToMerge, t2);
}

/*
void TrapezoidalMap::split3Right(const size_t trpzToReplace, const cg3::Segment2d& segment, const size_t trpzToMerge, const size_t trpzNB) {
    Trapezoid origin = trapezoids[trapezoidToReplaceIndex];

    Trapezoid t1 = Trapezoid(origin.getTop(), segment, origin.getLeftP(), segment.p2());
    Trapezoid t2 = Trapezoid(segment, origin.getBot(), origin.getLeftP(), segment.p2());
    Trapezoid t3 = Trapezoid(origin.getTop(), origin.getBot(), segment.p2(), origin.getRightP());

    size_t t1Index = trapezoidToReplaceIndex;
    size_t t2Index = addTrapezoid(t2);
    size_t t3Index = addTrapezoid(t3);

    t1.setTopLeftNeighbor(origin.getTopLeftNeighbor());
    t1.setTopRightNeighbor(t3Index);
    t1.setBotLeftNeighbor(0);
    t1.setBotRightNeighbor(0);

    t2.setTopLeftNeighbor(0);
    t2.setTopRightNeighbor(0);
    t2.setBotLeftNeighbor(origin.getBotLeftNeighbor());
    t2.setBotRightNeighbor(t3Index);

    t3.setTopLeftNeighbor(t1Index);
    t3.setBotLeftNeighbor(t2Index);
    t3.setTopRightNeighbor(origin.getTopRightNeighbor());
    t3.setBotRightNeighbor(origin.getBotRightNeighbor());

    updateTrapezoid(trapezoidToReplaceIndex, t1);
}
*/
