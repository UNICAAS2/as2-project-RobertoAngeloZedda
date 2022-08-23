#include "drawabletrapezoidalmap.h"

DrawableTrapezoidalMap::DrawableTrapezoidalMap(const cg3::Point2d botLeft, const cg3::Point2d topRight):
    TrapezoidalMap(botLeft, topRight)
{
    srand(time(0));

    selectedTrapezoid = SIZE_MAX;
    updateColors();
}

void DrawableTrapezoidalMap::updateColors() {
    while(colors.size() < getTrapezoids().size())
        colors.push_back(randomColor());
}

void DrawableTrapezoidalMap::draw() const {
    std::vector<Trapezoid> tm = getTrapezoids();

    for(size_t i=0; i<tm.size(); i++) {
        if(i != getFreeSlotIndex()) {
            Trapezoid t = tm[i];

            cg3::Point2d p1 = aaa(t.getTop(), t.getLeftP().x());
            cg3::Point2d p2 = aaa(t.getTop(), t.getRightP().x());
            cg3::Point2d p3 = aaa(t.getBot(), t.getRightP().x());
            cg3::Point2d p4 = aaa(t.getBot(), t.getLeftP().x());

            Trapezoid boundingBox = getBoundingBox();
            cg3::Color segmentColor = cg3::Color(0,0,0);
            cg3::Color trapezoidColor;

            if(i == selectedTrapezoid)
                trapezoidColor = cg3::Color(255, 0, 0);
            else
                trapezoidColor = colors[i];

            if(p1 == p4) {
                cg3::opengl::drawTriangle2(p1, p2, p3, trapezoidColor, 1, true);

                if(p2.x() != boundingBox.getRightP().x())
                    cg3::opengl::drawLine2(p2, p3, segmentColor, 3);
            } else if(p2 == p3) {
                cg3::opengl::drawTriangle2(p1, p2, p4, trapezoidColor, 1, true);

                if(p1.x() != boundingBox.getLeftP().x())
                    cg3::opengl::drawLine2(p1, p4, segmentColor, 3);
            } else {
                cg3::opengl::drawQuad2(p1, p2, p3, p4, trapezoidColor, 1, true);

                if(p1.x() != boundingBox.getLeftP().x())
                    cg3::opengl::drawLine2(p1, p4, segmentColor, 3);
                if(p2.x() != boundingBox.getRightP().x())
                    cg3::opengl::drawLine2(p2, p3, segmentColor, 3);
            }
        }
    }
}

cg3::Point3d DrawableTrapezoidalMap::sceneCenter() const
{
    const cg3::BoundingBox2& boundingBox = cg3::BoundingBox2();
    return cg3::Point3d(boundingBox.center().x(), boundingBox.center().y(), 0);
}

double DrawableTrapezoidalMap::sceneRadius() const
{
    const cg3::BoundingBox2& boundingBox = cg3::BoundingBox2();
    return boundingBox.diag();
}

const cg3::Color DrawableTrapezoidalMap::randomColor() const {
    return cg3::Color(140 + (rand()%75),
                      140 + (rand()%75),
                      140 + (rand()%75));
}

cg3::Point2d DrawableTrapezoidalMap::aaa(cg3::Segment2d s, double x) const {
    cg3::Point2d p1 = s.p1();
    cg3::Point2d p2 = s.p2();

    double m = (p2.y() - p1.y())/(p2.x() - p1.x());

    return cg3::Point2d(x, m * (x - p1.x()) + p1.y());
}

void DrawableTrapezoidalMap::setSelectedTrapezoid(size_t index) {
    selectedTrapezoid = index;
}

void DrawableTrapezoidalMap::clear() {
    TrapezoidalMap::clear();

    selectedTrapezoid = SIZE_MAX;

    cg3::Color bbColor = colors[0];
    colors.clear();
    colors.push_back(bbColor);
}
