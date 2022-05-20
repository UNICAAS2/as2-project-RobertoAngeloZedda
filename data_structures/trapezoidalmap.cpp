#include "trapezoidalmap.h"

TrapezoidalMap::TrapezoidalMap(const Trapezoid& boundingBox) {
    trapezoids = std::vector<Trapezoid>();
    trapezoids.push_back(boundingBox);
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

const Trapezoid& TrapezoidalMap::getTrapezoid(const size_t index) const {
    return trapezoids[index];
}

const std::vector<size_t> TrapezoidalMap::split4(const size_t trpzToReplace, const cg3::Segment2d& segment) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[trpzToReplace];

    /* Creation of the new 4 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), origin.getBot(), origin.getLeftP(), segment.p1());
    Trapezoid t2 = Trapezoid(origin.getTop(), segment, segment.p1(), segment.p2());
    Trapezoid t3 = Trapezoid(segment, origin.getBot(), segment.p1(), segment.p2());
    Trapezoid t4 = Trapezoid(origin.getTop(), origin.getBot(), segment.p2(), origin.getRightP());

    /* Indexes in the Trapezoids Vector of the new 4 Trapezoids.
     * The first one will replace the one that is being splitted */
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

    /* Updating t4's neighbors' left neighbors */
    if(t4.getTopRightNeighbor() != SIZE_MAX)
        trapezoids[t4.getTopRightNeighbor()].setTopLeftNeighbor(t4Index);
    if(t4.getBotRightNeighbor() != SIZE_MAX)
        trapezoids[t4.getBotRightNeighbor()].setBotLeftNeighbor(t4Index);

    /* Updating the Vector */
    updateTrapezoid(trpzToReplace, t1);

    /* Returning the indexes of the edited and created Trapezoids */
    std::vector<size_t> createdTrapezoids;// = std::vector<size_t>();
    createdTrapezoids.push_back(t1Index);
    createdTrapezoids.push_back(t2Index);
    createdTrapezoids.push_back(t3Index);
    createdTrapezoids.push_back(t4Index);

    return createdTrapezoids;
}

const std::vector<size_t> TrapezoidalMap::split3(const size_t trpzToReplace, const cg3::Segment2d& segment) {
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

    /* Updating the Vector */
    updateTrapezoid(trpzToReplace, t1);

    /* Returning the indexes of the edited and created Trapezoids */
    std::vector<size_t> createdTrapezoids = std::vector<size_t>();
    createdTrapezoids.push_back(t1Index);
    createdTrapezoids.push_back(t2Index);
    createdTrapezoids.push_back(t3Index);

    return createdTrapezoids;
}

const std::vector<size_t> TrapezoidalMap::split2MergeTop(const size_t trpzToReplace, const cg3::Segment2d& segment, const size_t trpzToMerge, const size_t trpzNB) {
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
    t2.setBotLeftNeighbor(origin.getBotLeftNeighbor());

    /* Updating the left neighbors' neighbors */
    trapezoids[trpzNB].setTopRightNeighbor(trpzToReplace);

    /* Updating the Vector */
    updateTrapezoid(trpzToMerge, t1);
    updateTrapezoid(trpzToReplace, t2);

    /* Returning the indexes of the edited Trapezoids */
    std::vector<size_t> createdTrapezoids = std::vector<size_t>();
    createdTrapezoids.push_back(trpzToMerge);
    createdTrapezoids.push_back(trpzToReplace);

    return createdTrapezoids;
}

const std::vector<size_t> TrapezoidalMap::split2MergeBot(const size_t trpzToReplace, const cg3::Segment2d& segment, const size_t trpzToMerge, const size_t trpzNB) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[trpzToReplace];
    /* Reference of the Trapezoid that needs to be merged */
    Trapezoid merge = trapezoids[trpzToMerge];

    /* Creation of the new 2 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), segment, origin.getLeftP(), origin.getRightP());
    Trapezoid t2 = Trapezoid(segment, origin.getBot(), merge.getLeftP(), origin.getRightP());

    /* Updating t1's neighbors */
    t1.setTopLeftNeighbor(origin.getTopLeftNeighbor());
    t1.setBotLeftNeighbor(trpzNB);

    /* Updating t2's neighbors */
    t2.setTopLeftNeighbor(merge.getTopLeftNeighbor());
    t2.setBotLeftNeighbor(merge.getBotLeftNeighbor());

    /* Updating the left neighbors' neighbors */
    trapezoids[trpzNB].setBotRightNeighbor(trpzToReplace);

    /* Updating the Vector */
    updateTrapezoid(trpzToReplace, t1);
    updateTrapezoid(trpzToMerge, t2);

    /* Returning the indexes of the edited Trapezoids */
    std::vector<size_t> createdTrapezoids = std::vector<size_t>();
    createdTrapezoids.push_back(trpzToReplace);
    createdTrapezoids.push_back(trpzToMerge);

    return createdTrapezoids;
}

const std::vector<size_t> TrapezoidalMap::split3MergeTop(const size_t trpzToReplace, const cg3::Segment2d& segment, const size_t trpzToMerge, const size_t trpzNB) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[trpzToReplace];
    /* Reference of the Trapezoid that needs to be merged */
    Trapezoid merge = trapezoids[trpzToMerge];

    /* Creation of the new 3 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), segment, merge.getLeftP(), segment.p2());
    Trapezoid t2 = Trapezoid(segment, origin.getBot(), origin.getLeftP(), segment.p2());
    Trapezoid t3 = Trapezoid(origin.getTop(), origin.getBot(), segment.p2(), origin.getRightP());

    /* Indexes in the Trapezoids Vector of the new 3 Trapezoids
     * The first one will replace the one that is being merged
     * The third one will replace the one that is being splitted */
    size_t t1Index = trpzToMerge;
    size_t t2Index = addTrapezoid(t2);
    size_t t3Index = trpzToReplace;;

    /* Updating t1's neighbors */
    t1.setTopLeftNeighbor(merge.getTopLeftNeighbor());
    t1.setBotLeftNeighbor(merge.getBotLeftNeighbor());
    t1.setTopRightNeighbor(t3Index);

    /* Updating t2's neighbors */
    t2.setTopLeftNeighbor(trpzNB);
    t2.setBotLeftNeighbor(origin.getBotLeftNeighbor());
    t2.setBotRightNeighbor(t3Index);

    /* Updating t3's neighbors */
    t3.setTopLeftNeighbor(t1Index);
    t3.setBotLeftNeighbor(t2Index);
    t3.setTopRightNeighbor(origin.getTopRightNeighbor());
    t3.setBotRightNeighbor(origin.getBotRightNeighbor());

    /* Updating the left neighbors' neighbors */
    trapezoids[trpzNB].setTopRightNeighbor(t2Index);

    /* Updating the Vector */
    updateTrapezoid(trpzToMerge, t1);
    updateTrapezoid(trpzToReplace, t3);

    /* Returning the indexes of the edited and created Trapezoids */
    std::vector<size_t> createdTrapezoids = std::vector<size_t>();
    createdTrapezoids.push_back(t1Index);
    createdTrapezoids.push_back(t2Index);
    createdTrapezoids.push_back(t3Index);

    return createdTrapezoids;
}

const std::vector<size_t> TrapezoidalMap::split3MergeBot(const size_t trpzToReplace, const cg3::Segment2d& segment, const size_t trpzToMerge, const size_t trpzNB) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[trpzToReplace];
    /* Reference of the Trapezoid that needs to be merged */
    Trapezoid merge = trapezoids[trpzToMerge];

    /* Creation of the new 3 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), segment, origin.getLeftP(), segment.p2());
    Trapezoid t2 = Trapezoid(segment, origin.getBot(), merge.getLeftP(), segment.p2());
    Trapezoid t3 = Trapezoid(origin.getTop(), origin.getBot(), segment.p2(), origin.getRightP());

    /* Indexes in the Trapezoids Vector of the new 3 Trapezoids
     * The second one will replace the one that is being merged
     * The third one will replace the one that is being splitted */
    size_t t1Index = addTrapezoid(t1);
    size_t t2Index = trpzToMerge;
    size_t t3Index = trpzToReplace;;

    /* Updating t1's neighbors */
    t1.setTopLeftNeighbor(origin.getTopLeftNeighbor());
    t1.setBotLeftNeighbor(trpzNB);
    t1.setTopRightNeighbor(t3Index);

    /* Updating t2's neighbors */
    t2.setTopLeftNeighbor(merge.getTopLeftNeighbor());
    t2.setBotLeftNeighbor(merge.getBotLeftNeighbor());
    t2.setBotRightNeighbor(t3Index);

    /* Updating t3's neighbors */
    t3.setTopLeftNeighbor(t1Index);
    t3.setBotLeftNeighbor(t2Index);
    t3.setTopRightNeighbor(origin.getTopRightNeighbor());
    t3.setBotRightNeighbor(origin.getBotRightNeighbor());

    /* Updating the left neighbors' neighbors */
    trapezoids[trpzNB].setBotRightNeighbor(t1Index);

    /* Updating the Vector */
    updateTrapezoid(trpzToMerge, t2);
    updateTrapezoid(trpzToReplace, t3);

    /* Returning the indexes of the edited and created Trapezoids */
    std::vector<size_t> createdTrapezoids = std::vector<size_t>();
    createdTrapezoids.push_back(t1Index);
    createdTrapezoids.push_back(t2Index);
    createdTrapezoids.push_back(t3Index);

    return createdTrapezoids;
}
