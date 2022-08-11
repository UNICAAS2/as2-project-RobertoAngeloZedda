#include "trapezoid.h"

/**
 * @brief Trapezoid basic Constructor
 */
Trapezoid::Trapezoid() {
    top = cg3::Segment2d(cg3::Point2d(0, 0), cg3::Point2d(0, 0));
    bot = cg3::Segment2d(cg3::Point2d(0, 0), cg3::Point2d(0, 0));
    leftP = cg3::Point2d(0, 0);
    rightP = cg3::Point2d(0, 0);

    topLeftNeighbor = SIZE_MAX;
    topRightNeighbor = SIZE_MAX;
    botLeftNeighbor = SIZE_MAX;
    botRightNeighbor = SIZE_MAX;
}

/**
 * @brief Trapezoid Constructor
 * @param top, Segment delimiting the upper boundary
 * @param bot, Segment delimiting the lower boundary
 * @param leftP, Point delimiting the left boundary
 * @param rightP, Point delimiting the right boundary
 */
Trapezoid::Trapezoid(const cg3::Segment2d &top, const cg3::Segment2d &bot,
                     const cg3::Point2d &leftP, const cg3::Point2d &rightP) {
    this->top = top;
    this->bot = bot;
    this->leftP = leftP;
    this->rightP = rightP;

    topLeftNeighbor = SIZE_MAX;
    topRightNeighbor = SIZE_MAX;
    botLeftNeighbor = SIZE_MAX;
    botRightNeighbor = SIZE_MAX;
}

/**
 * @brief Setter for the top segment
 * @param segment, the new top segment
 */
void Trapezoid::setTop(const cg3::Segment2d& segment) { top = segment; }
/**
 * @brief Setter for the bot segment
 * @param segment, the new bot segment
 */
void Trapezoid::setBot(const cg3::Segment2d& segment) { bot = segment; }
/**
 * @brief Setter for the left point
 * @param point, the new left point
 */
void Trapezoid::setLeftP(const cg3::Point2d& point) { leftP = point; }
/**
 * @brief Setter for the right point
 * @param point, the new right point
 */
void Trapezoid::setRightP(const cg3::Point2d& point) { rightP = point; }

/**
 * @brief Setter for the top left neighbor
 * @param trapezoid, index of the new top left neighbor
 */
void Trapezoid::setTopLeftNeighbor(const size_t& trapezoid) {
    topLeftNeighbor = trapezoid;
}
/**
 * @brief Setter for the top right neighbor
 * @param trapezoid, index of the new top right neighbor
 */
void Trapezoid::setTopRightNeighbor(const size_t& trapezoid) {
    topRightNeighbor = trapezoid;
}
/**
 * @brief Setter for the bot left neighbor
 * @param trapezoid, index of the new bot left neighbor
 */
void Trapezoid::setBotLeftNeighbor(const size_t& trapezoid) {
    botLeftNeighbor = trapezoid;
}
/**
 * @brief Setter for the bot right neighbor
 * @param trapezoid, index of the new bot right neighbor
 */
void Trapezoid::setBotRightNeighbor(const size_t& trapezoid) {
    botRightNeighbor = trapezoid;
}

/**
 * @brief Getter for the top segment
 * @return The top segment
 */
const cg3::Segment2d& Trapezoid::getTop() const { return top; }
/**
 * @brief Getter for the bot segment
 * @return The bot segment
 */
const cg3::Segment2d& Trapezoid::getBot() const { return bot; }
/**
 * @brief Getter for the left point
 * @return The left point
 */
const cg3::Point2d& Trapezoid::getLeftP() const { return leftP; }
/**
 * @brief Getter for the right point
 * @return The right point
 */
const cg3::Point2d& Trapezoid::getRightP() const { return rightP; }


/**
 * @brief Getter for the top left neighbor
 * @return the index of the top left neighbor
 */
size_t Trapezoid::getTopLeftNeighbor() const { return topLeftNeighbor; }
/**
 * @brief Getter for the top right neighbor
 * @return the index of the top right neighbor
 */
size_t Trapezoid::getTopRightNeighbor() const { return topRightNeighbor; }
/**
 * @brief Getter for the bot left neighbor
 * @return the index of the bot left neighbor
 */
size_t Trapezoid::getBotLeftNeighbor() const { return botLeftNeighbor; }
/**
 * @brief Getter for the bot right neighbor
 * @return the index of the bot right neighbor
 */
size_t Trapezoid::getBotRightNeighbor() const { return botRightNeighbor; }

/**
 * @brief Setter for the DAG link
 * @param nodeIndex, the index of the DAGnode inside the DAG that represents this Trapezoid
 */
void Trapezoid::setDAGlink(const size_t& nodeIndex) { DAGlink = nodeIndex; }

/**
 * @brief Getter for the DAG link
 * @return the index of the DAGnode inside the DAG that represents this Trapezoid
 */
size_t Trapezoid::getDAGlink() const { return DAGlink; }
