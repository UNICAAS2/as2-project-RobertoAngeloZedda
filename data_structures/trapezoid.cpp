#include "trapezoid.h"

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

Trapezoid::Trapezoid(const cg3::Segment2d &top, const cg3::Segment2d &bot, const cg3::Point2d &leftP, const cg3::Point2d &rightP) {
    this->top = top;
    this->bot = bot;
    this->leftP = leftP;
    this->rightP = rightP;

    topLeftNeighbor = SIZE_MAX;
    topRightNeighbor = SIZE_MAX;
    botLeftNeighbor = SIZE_MAX;
    botRightNeighbor = SIZE_MAX;
}

Trapezoid::Trapezoid(const Trapezoid& trapezoid) {
    this->top = trapezoid.getTop();
    this->bot = trapezoid.getBot();
    this->leftP = trapezoid.getLeftP();
    this->rightP = trapezoid.getRightP();

    topLeftNeighbor = SIZE_MAX;
    topRightNeighbor = SIZE_MAX;
    botLeftNeighbor = SIZE_MAX;
    botRightNeighbor = SIZE_MAX;
}

Trapezoid::~Trapezoid() {
    top.~Segment();
    bot.~Segment();
    leftP.~Point2();
    rightP.~Point2();
}

void Trapezoid::setTop(const cg3::Segment2d& segment) { top = segment; }
void Trapezoid::setBot(const cg3::Segment2d& segment) { bot = segment; }
void Trapezoid::setLeftP(const cg3::Point2d& point) { leftP = point; }
void Trapezoid::setRightP(const cg3::Point2d& point) { rightP = point; }

void Trapezoid::setTopLeftNeighbor(const size_t trapezoid) { topLeftNeighbor = trapezoid; }
void Trapezoid::setTopRightNeighbor(const size_t trapezoid) { topRightNeighbor = trapezoid; }
void Trapezoid::setBotLeftNeighbor(const size_t trapezoid) { botLeftNeighbor = trapezoid; }
void Trapezoid::setBotRightNeighbor(const size_t trapezoid) { botRightNeighbor = trapezoid; }

const cg3::Segment2d& Trapezoid::getTop() const { return top; }
const cg3::Segment2d& Trapezoid::getBot() const { return bot; }
const cg3::Point2d& Trapezoid::getLeftP() const { return leftP; }
const cg3::Point2d& Trapezoid::getRightP() const { return rightP; }

size_t Trapezoid::getTopLeftNeighbor() const { return topLeftNeighbor; }
size_t Trapezoid::getTopRightNeighbor() const { return topRightNeighbor; }
size_t Trapezoid::getBotLeftNeighbor() const { return botLeftNeighbor; }
size_t Trapezoid::getBotRightNeighbor() const { return botRightNeighbor; }
