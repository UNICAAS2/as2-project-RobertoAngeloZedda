#include "trapezoidalmap.h"

/**
 * @brief TrapezoidalMap Constructor
 * @param boundingBox, first Trapezoid
 */
TrapezoidalMap::TrapezoidalMap(const Trapezoid& boundingBox) {
    trapezoids = std::vector<Trapezoid>();
    trapezoids.push_back(boundingBox);
    trapezoids[0].setDAGlink(0);

    freeSlotIndex = SIZE_MAX;
}

/**
 * @brief Adds a Trapezoid to the vector and returns the index in which it has been inserted
 * @param trapezoid, the Trapezoid to insert
 * @return The index in which the Trapezoid has been inserted
 */
size_t TrapezoidalMap::addTrapezoid(const Trapezoid& trapezoid) {
    if(freeSlotIndex == SIZE_MAX) {
        trapezoids.push_back(trapezoid);
        return trapezoids.size()-1;
    } else {
        updateTrapezoid(freeSlotIndex, trapezoid);
        size_t newIndex = freeSlotIndex;
        freeSlotIndex = SIZE_MAX;
        return newIndex;
    }
}

/**
 * @brief Replaces the Trapezoid located in the index position with a new one
 * @param index, index of the Trapezoid to replace
 * @param trapezoid, new Trapezoid
 */
void TrapezoidalMap::updateTrapezoid(const size_t& index, const Trapezoid& trapezoid) {
    trapezoids[index] = trapezoid;
}

/**
 * @brief Returns the Trapezoid located in the index position
 * @param index, index of the Trapezoid to return
 * @return the Trapezoid in the index position
 */
Trapezoid& TrapezoidalMap::getTrapezoid(const size_t& index) {
    return trapezoids[index];
}

/**
 * @brief Splits the Trapezoid in 4 new Trapezoids.
 *
 * The first Trapezoid, the left most one, will keep the same index
 * of the Trapezoid that is being replaced.
 *
 * All the neighbors will also be updated.
 * @param trpzToReplace, index of the Trapezoid to replace
 * @param segment, Segment to compute the spit around
 * @return a Vector containing the 4 indexes of the new Trapezoids
 */
const std::vector<size_t> TrapezoidalMap::split4(const size_t& trpzToReplace, const cg3::Segment2d& segment) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[trpzToReplace];

    /* Creation of the new 4 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), origin.getBot(), origin.getLeftP(), segment.p1());
    t1.setDAGlink(origin.getDAGlink());
    Trapezoid t2 = Trapezoid(origin.getTop(), segment, segment.p1(), segment.p2());
    Trapezoid t3 = Trapezoid(segment, origin.getBot(), segment.p1(), segment.p2());
    Trapezoid t4 = Trapezoid(origin.getTop(), origin.getBot(), segment.p2(), origin.getRightP());

    /* Indexes in the Trapezoids Vector of the new 4 Trapezoids.
     * The first one will replace the one that is being splitted */
    updateTrapezoid(trpzToReplace, t1);
    size_t t1Index = trpzToReplace;
    size_t t2Index = addTrapezoid(t2);
    size_t t3Index = addTrapezoid(t3);
    size_t t4Index = addTrapezoid(t4);

    /* Updating t1's neighbors */
    trapezoids[t1Index].setTopLeftNeighbor(origin.getTopLeftNeighbor());
    trapezoids[t1Index].setBotLeftNeighbor(origin.getBotLeftNeighbor());
    trapezoids[t1Index].setTopRightNeighbor(t2Index);
    trapezoids[t1Index].setBotRightNeighbor(t3Index);

    /* Updating t2's neighbors */
    trapezoids[t2Index].setTopLeftNeighbor(t1Index);
    trapezoids[t2Index].setTopRightNeighbor(t4Index);

    /* Updating t3's neighbors */
    trapezoids[t3Index].setBotLeftNeighbor(t1Index);
    trapezoids[t3Index].setBotRightNeighbor(t4Index);

    /* Updating t4's neighbors */
    trapezoids[t4Index].setTopLeftNeighbor(t2Index);
    trapezoids[t4Index].setBotLeftNeighbor(t3Index);
    trapezoids[t4Index].setTopRightNeighbor(origin.getTopRightNeighbor());
    trapezoids[t4Index].setBotRightNeighbor(origin.getBotRightNeighbor());

    /* Updating t4's neighbors' left neighbors */
    if(origin.getTopRightNeighbor() != SIZE_MAX)
        trapezoids[origin.getTopRightNeighbor()].setTopLeftNeighbor(t4Index);
    if(origin.getBotRightNeighbor() != SIZE_MAX)
        trapezoids[origin.getBotRightNeighbor()].setBotLeftNeighbor(t4Index);

    /* Returning the indexes of the edited and created Trapezoids */
    std::vector<size_t> createdTrapezoids;
    createdTrapezoids.push_back(t1Index);
    createdTrapezoids.push_back(t2Index);
    createdTrapezoids.push_back(t3Index);
    createdTrapezoids.push_back(t4Index);

    return createdTrapezoids;
}

/**
 * @brief Splits the Trapezoid in 3 new Trapezoids around a Segment starting inside the original Trapezoid.
 *
 * The first Trapezoid, the left most one, will keep the same index
 * of the Trapezoid that is being replaced.
 *
 * The neighbors will also be updated.
 * @param trpzToReplace, index of the Trapezoid to replace
 * @param segment, Segment to compute the spit around
 * @return a Vector containing the 3 indexes of the new Trapezoids
 */
const std::vector<size_t> TrapezoidalMap::split3L(const size_t& trpzToReplace, const cg3::Segment2d& segment) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[trpzToReplace];

    /* Creation of the new 3 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), origin.getBot(), origin.getLeftP(), segment.p1());
    t1.setDAGlink(origin.getDAGlink());
    Trapezoid t2 = Trapezoid(origin.getTop(), segment, segment.p1(), origin.getRightP());
    Trapezoid t3 = Trapezoid(segment, origin.getBot(), segment.p1(), origin.getRightP());

    /* Indexes in the Trapezoids Vector of the new 3 Trapezoids.
     * The first one will replace the one that is being splitted */
    updateTrapezoid(trpzToReplace, t1);
    size_t t1Index = trpzToReplace;
    size_t t2Index = addTrapezoid(t2);
    size_t t3Index = addTrapezoid(t3);

    /* Updating t1's neighbors */
    trapezoids[t1Index].setTopLeftNeighbor(origin.getTopLeftNeighbor());
    trapezoids[t1Index].setBotLeftNeighbor(origin.getBotLeftNeighbor());
    trapezoids[t1Index].setTopRightNeighbor(t2Index);
    trapezoids[t1Index].setBotRightNeighbor(t3Index);

    /* Updating t2's neighbors */
    trapezoids[t2Index].setTopLeftNeighbor(t1Index);
    trapezoids[t2Index].setTopRightNeighbor(origin.getTopRightNeighbor());

    /* Updating t3's neighbors */
    trapezoids[t3Index].setBotLeftNeighbor(t1Index);
    trapezoids[t3Index].setBotRightNeighbor(origin.getBotRightNeighbor());

    /* Updating the right neighbors' neighbors */
    if(origin.getTopRightNeighbor() != SIZE_MAX)
        trapezoids[origin.getTopRightNeighbor()].setTopLeftNeighbor(t2Index);
    if(origin.getBotRightNeighbor() != SIZE_MAX)
        trapezoids[origin.getBotRightNeighbor()].setBotLeftNeighbor(t3Index);

    /* Returning the indexes of the edited and created Trapezoids */
    std::vector<size_t> createdTrapezoids = std::vector<size_t>();
    createdTrapezoids.push_back(t1Index);
    createdTrapezoids.push_back(t2Index);
    createdTrapezoids.push_back(t3Index);

    return createdTrapezoids;
}

/**
 * @brief Splits the Trapezoid in 2 new Trapezoids around a Segment.
 *
 * The first Trapezoid, the upper one, will keep the same index
 * of the Trapezoid that is being replaced.
 *
 * The neighbors will also be updated.
 * @param trpzToReplace, index of the Trapezoid to replace
 * @param segment, Segment to compute the spit around
 * @param trpzPrevSplitTop, index of the left neighbor Trapezoid from a previous split (above the segment).
 * @param trpzPrevSplitBot, index of the left neighbor Trapezoid from a previous split (under the segment).
 * @return a Vector containing the 3 indexes of the new Trapezoids
 */
const std::vector<size_t> TrapezoidalMap::split2(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                                 const size_t& trpzPrevSplitTop, const size_t& trpzPrevSplitBot) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[trpzToReplace];

    /* Creation of the new 2 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), segment, origin.getLeftP(), origin.getRightP());
    t1.setDAGlink(origin.getDAGlink());
    Trapezoid t2 = Trapezoid(segment, origin.getBot(), origin.getLeftP(), origin.getRightP());

    /* Updating the Vector */
    updateTrapezoid(trpzToReplace, t1);
    size_t t1Index = trpzToReplace;
    size_t t2Index = addTrapezoid(t2);

    /* Updating t1's neighbors */
    trapezoids[t1Index].setTopLeftNeighbor(origin.getTopLeftNeighbor());
    trapezoids[t1Index].setTopRightNeighbor(origin.getTopRightNeighbor());
    trapezoids[t1Index].setBotLeftNeighbor(trpzPrevSplitTop);

    /* Updating t2's neighbors */
    trapezoids[t2Index].setTopLeftNeighbor(trpzPrevSplitBot);
    trapezoids[t2Index].setBotLeftNeighbor(origin.getBotLeftNeighbor());
    trapezoids[t2Index].setBotRightNeighbor(origin.getBotRightNeighbor());

    /* Updating the left neighbors' neighbors */
    if(trpzPrevSplitTop != SIZE_MAX)
        trapezoids[trpzPrevSplitTop].setBotRightNeighbor(t1Index);
    if(trpzPrevSplitBot != SIZE_MAX)
        trapezoids[trpzPrevSplitBot].setTopRightNeighbor(t2Index);

    if(origin.getBotLeftNeighbor() != SIZE_MAX)
        trapezoids[origin.getBotLeftNeighbor()].setBotRightNeighbor(t2Index);

    /* Updating the right neighbor's neigbors */
    if(origin.getBotRightNeighbor() != SIZE_MAX)
        trapezoids[origin.getBotRightNeighbor()].setBotLeftNeighbor(t2Index);

    /* Returning the indexes of the edited Trapezoids */
    std::vector<size_t> createdTrapezoids = std::vector<size_t>();
    createdTrapezoids.push_back(t1Index);
    createdTrapezoids.push_back(t2Index);

    return createdTrapezoids;
}

/**
 * @brief Splits the Trapezoid in 3 new Trapezoids around a Segment ending inside the original Trapezoid.
 *
 * The third Trapezoid, the right most one, will keep the same index
 * of the Trapezoid that is being replaced.
 *
 * The neighbors will also be updated.
 * @param trpzToReplace, index of the Trapezoid to replace
 * @param segment, Segment to compute the spit around
 * @param trpzPrevSplitTop, index of the left neighbor Trapezoid from a previous split (above the segment).
 * @param trpzPrevSplitBot, index of the left neighbor Trapezoid from a previous split (under the segment).
 * @return a Vector containing the 3 indexes of the new Trapezoids
 */
const std::vector<size_t> TrapezoidalMap::split3R(const size_t& trpzToReplace, const cg3::Segment2d& segment,
                                                         const size_t& trpzPrevSplitTop, const size_t& trpzPrevSplitBot) {
    /* Reference of the Trapezoid that needs to be splitted */
    Trapezoid origin = trapezoids[trpzToReplace];

    /* Creation of the new 3 Trapezoids */
    Trapezoid t1 = Trapezoid(origin.getTop(), segment, origin.getLeftP(), segment.p2());
    Trapezoid t2 = Trapezoid(segment, origin.getBot(), origin.getLeftP(), segment.p2());
    Trapezoid t3 = Trapezoid(origin.getTop(), origin.getBot(), segment.p2(), origin.getRightP());
    t3.setDAGlink(origin.getDAGlink());

    /* Indexes in the Trapezoids Vector of the new 3 Trapezoids
     * The third one will replace the one that is being splitted */
    size_t t1Index = addTrapezoid(t1);
    size_t t2Index = addTrapezoid(t2);
    updateTrapezoid(trpzToReplace, t3);
    size_t t3Index = trpzToReplace;;

    /* Updating t1's neighbors */
    trapezoids[t1Index].setTopLeftNeighbor(origin.getTopLeftNeighbor());
    trapezoids[t1Index].setBotLeftNeighbor(trpzPrevSplitTop);
    trapezoids[t1Index].setTopRightNeighbor(t3Index);

    /* Updating t2's neighbors */
    trapezoids[t2Index].setTopLeftNeighbor(trpzPrevSplitBot);
    trapezoids[t2Index].setBotLeftNeighbor(origin.getBotLeftNeighbor());
    trapezoids[t2Index].setBotRightNeighbor(t3Index);

    /* Updating t3's neighbors */
    trapezoids[t3Index].setTopLeftNeighbor(t1Index);
    trapezoids[t3Index].setBotLeftNeighbor(t2Index);
    trapezoids[t3Index].setTopRightNeighbor(origin.getTopRightNeighbor());
    trapezoids[t3Index].setBotRightNeighbor(origin.getBotRightNeighbor());

    /* Updating the left neighbors' neighbors */
    if(trpzPrevSplitTop != SIZE_MAX)
        trapezoids[trpzPrevSplitTop].setBotRightNeighbor(t1Index);
    if(trpzPrevSplitBot != SIZE_MAX)
        trapezoids[trpzPrevSplitBot].setTopRightNeighbor(t2Index);

    if(origin.getTopLeftNeighbor() != SIZE_MAX)
        trapezoids[origin.getTopLeftNeighbor()].setTopRightNeighbor(t1Index);
    if(origin.getBotLeftNeighbor() != SIZE_MAX)
        trapezoids[origin.getBotLeftNeighbor()].setBotRightNeighbor(t2Index);

    /* Returning the indexes of the edited and created Trapezoids */
    std::vector<size_t> createdTrapezoids = std::vector<size_t>();
    createdTrapezoids.push_back(t1Index);
    createdTrapezoids.push_back(t2Index);
    createdTrapezoids.push_back(t3Index);

    return createdTrapezoids;
}
/**
 * @brief Merges two Trapezoids.
 *
 * The left trapezoid will be updated inside the map.
 * The right trapezoid will be considered as deleted.
 *
 * The neighbors will also be updated.
 * @param leftTrpzIndex, index of the left Trapezoid to merge
 * @param rightTrpzIndex, index of the right Trapezoid to merge
 */
void TrapezoidalMap::merge(size_t leftTrpzIndex, size_t rightTrpzIndex) {
    Trapezoid t2 = trapezoids[rightTrpzIndex];

    /* "Deleting" the right Trapezoid */
    freeSlotIndex = rightTrpzIndex;

    /* Updating the right point and the right nighbors */
    trapezoids[leftTrpzIndex].setRightP(t2.getRightP());

    trapezoids[leftTrpzIndex].setTopRightNeighbor(t2.getTopRightNeighbor());
    trapezoids[leftTrpzIndex].setBotRightNeighbor(t2.getBotRightNeighbor());

    /* Updating neighbors' neighbors */
    if(trapezoids[leftTrpzIndex].getTopRightNeighbor() != SIZE_MAX)
        trapezoids[trapezoids[leftTrpzIndex].getTopRightNeighbor()].setTopLeftNeighbor(leftTrpzIndex);
    if(trapezoids[leftTrpzIndex].getBotRightNeighbor() != SIZE_MAX)
        trapezoids[trapezoids[leftTrpzIndex].getBotRightNeighbor()].setBotLeftNeighbor(leftTrpzIndex);
}
