#include "algorithms.h"

namespace Algorithms {
    /**
     * @brief Finds the Trapezoid containing a Point using the DAG
     * @param point, the Point
     * @param dag, the DAG
     * @param point2, the second Point used in case the first one overlaps with one already used
     * @return returns the index (inside the TrapezoidalMap) of the Trapezoid containing the Point.
     */
    size_t findPoint(const cg3::Point2d& point, DAG& dag, const cg3::Point2d& point2) {
        DAGnode currentNode = dag.getRoot();

        while(!currentNode.isTrapezoidNode()) {
            if(currentNode.isPointNode()) {
                if(point.x() < currentNode.getPointValue().x())
                    currentNode = dag.getNode(currentNode.getLeft());
                else
                    currentNode = dag.getNode(currentNode.getRight());
            }
            if(currentNode.isSegmentNode()) {
                if(point != currentNode.getSegmentValue().p1()) {
                    if(isPointOnTheRight(currentNode.getSegmentValue(), point))
                        currentNode = dag.getNode(currentNode.getLeft());
                    else
                        currentNode = dag.getNode(currentNode.getRight());
                } else {
                    if(isPointOnTheRight(currentNode.getSegmentValue(), point2))
                        currentNode = dag.getNode(currentNode.getLeft());
                    else
                        currentNode = dag.getNode(currentNode.getRight());
                }
            }
        }

        return currentNode.getTrapezoidValue();
    }

    /**
     * @brief finds all the Trapzeoids in which a Segment lies.
     * @param segment, the Segment
     * @param dag, the DAG
     * @param tm, the Trapezoidal Map
     * @return a vector containing the indexes of the Trapezoids in which the segment lies (from left to right)
     */
    std::vector<size_t> followSegment(const cg3::Segment2d& segment, DAG& dag, TrapezoidalMap& tm) {
        std::vector<size_t> trapezoids;

        cg3::Point2d firstPoint = segment.p1();
        cg3::Point2d secondPoint = segment.p2();
        trapezoids.push_back(Algorithms::findPoint(firstPoint, dag, secondPoint));

        /* As long as the Trapezoid we are analyzing does not contain
         * the right endpoint of the Segment
         *      if the rightmost point of the Trapezoid lies
         *      on the RIGHT of the Segment
         *          the BOT-right neighbor can be added to the Vector
         *      if the rightmost point of the Trapezoid lies
         *      on the LEFT of the Segment
         *          the TOP-right neighbor can be added to the Vector */
        int j = 0;
        while(segment.p2().x() > tm.getTrapezoid(trapezoids[j]).getRightP().x()) {
            if(isPointOnTheRight(segment ,tm.getTrapezoid(trapezoids[j]).getRightP()))
                trapezoids.push_back(tm.getTrapezoid(trapezoids[j]).getBotRightNeighbor());
            else
                trapezoids.push_back(tm.getTrapezoid(trapezoids[j]).getTopRightNeighbor());
            j++;
        }

        return trapezoids;
    }

    /**
     * @brief Updates the Trapezoidal Map and the DAG when a new Segment is added
     * @param segment, the added Segment
     * @param trapezoids, a Vector containing the indexes of the Trapezoids crossed by the Segement (from left to right)
     * @param dag, the DAG
     * @param tm, the Trapezoidal Map
     */
    void updateTrapezoidalMapAndDAG(const cg3::Segment2d& segment, std::vector<size_t>& trapezoids, DAG& dag, TrapezoidalMap& tm) {
        /* A reference to the Trapezoid that is being replaced,
         * It is needed to know in which direction to merge
         * and to perform the update of the DAG */
        Trapezoid replacedTrapezoid;

        std::array<size_t, 2> newTrapezoids2;
        std::array<size_t, 3> newTrapezoids3;
        std::array<size_t, 4> newTrapezoids4;

        /* If the new Segment is contained inside a single Trapezoid */
        if(trapezoids.size() == 1) {
            replacedTrapezoid = tm.getTrapezoid(trapezoids[0]);

            if(replacedTrapezoid.getLeftP() == segment.p1()) {
                if(replacedTrapezoid.getRightP() == segment.p2()) {
                    newTrapezoids2 = tm.split2(trapezoids[0], segment, SIZE_MAX, SIZE_MAX);
                    dag.split2(tm, segment, replacedTrapezoid.getDAGlink(), newTrapezoids2);
                }
                else {
                    newTrapezoids3 = tm.split3R(trapezoids[0], segment, SIZE_MAX, SIZE_MAX);
                    dag.split3R(tm, segment, replacedTrapezoid.getDAGlink(), newTrapezoids3);
                }
            }
            else if (replacedTrapezoid.getRightP() == segment.p2()) {
                newTrapezoids3 = tm.split3L(trapezoids[0], segment);
                dag.split3L(tm, segment, replacedTrapezoid.getDAGlink(), newTrapezoids3);
            }
            else {
                newTrapezoids4 = tm.split4(trapezoids[0], segment);
                dag.split4(tm, segment, replacedTrapezoid.getDAGlink(), newTrapezoids4);
            }
        } else {
        /* If the new Segment is contained inside multiple Trapezoids */

            /* Handling first Trapezoid*/
            replacedTrapezoid = tm.getTrapezoid(trapezoids[0]);

            /* References for merging and setting neighbors */
            size_t trapezoidFromPrevSplitTop;
            size_t trapezoidFromPrevSplitBot;

            if (replacedTrapezoid.getLeftP() == segment.p1()) {
                newTrapezoids2 = tm.split2(trapezoids[0], segment, SIZE_MAX, SIZE_MAX);

                dag.split2(tm, segment, replacedTrapezoid.getDAGlink(), newTrapezoids2);

                trapezoidFromPrevSplitTop = newTrapezoids2[0];
                trapezoidFromPrevSplitBot = newTrapezoids2[1];
            }
            else {
                newTrapezoids3 = tm.split3L(trapezoids[0], segment);

                dag.split3L(tm, segment, replacedTrapezoid.getDAGlink(), newTrapezoids3);

                trapezoidFromPrevSplitTop = newTrapezoids3[1];
                trapezoidFromPrevSplitBot = newTrapezoids3[2];
            }

            bool mergeFlag;
            size_t trapezoidToMerge;

            /* Handling Trapezoid not in first nor in last position */
            for(size_t i=1; i<=trapezoids.size()-2; i++) {

                mergeFlag = replacedTrapezoid.getTopRightNeighbor() == trapezoids[i];

                replacedTrapezoid = tm.getTrapezoid(trapezoids[i]);

                newTrapezoids2 = tm.split2(trapezoids[i], segment, trapezoidFromPrevSplitTop, trapezoidFromPrevSplitBot);

                if(mergeFlag) {
                    trapezoidToMerge = tm.getTrapezoid(newTrapezoids2[0]).getBotLeftNeighbor();
                    tm.merge(trapezoidToMerge, newTrapezoids2[0]);
                    newTrapezoids2[0] = trapezoidToMerge;
                }
                else {
                    trapezoidToMerge = tm.getTrapezoid(newTrapezoids2[1]).getTopLeftNeighbor();
                    tm.merge(trapezoidToMerge, newTrapezoids2[1]);
                    newTrapezoids2[1] = trapezoidToMerge;
                }

                dag.split2(tm, segment, replacedTrapezoid.getDAGlink(), newTrapezoids2);

                trapezoidFromPrevSplitTop = newTrapezoids2[0];
                trapezoidFromPrevSplitBot = newTrapezoids2[1];
            }

            /* Handling the last Trapezoid */
            mergeFlag = replacedTrapezoid.getTopRightNeighbor() == trapezoids[trapezoids.size()-1];

            replacedTrapezoid = tm.getTrapezoid(trapezoids[trapezoids.size()-1]);

            if(replacedTrapezoid.getRightP() == segment.p2()) {
                newTrapezoids2 = tm.split2(trapezoids[trapezoids.size()-1], segment,
                                           trapezoidFromPrevSplitTop, trapezoidFromPrevSplitBot);

                if(mergeFlag) {
                    trapezoidToMerge = tm.getTrapezoid(newTrapezoids2[0]).getBotLeftNeighbor();
                    tm.merge(trapezoidToMerge, newTrapezoids2[0]);
                    newTrapezoids2[0] = trapezoidToMerge;
                }
                else {
                    trapezoidToMerge = tm.getTrapezoid(newTrapezoids2[1]).getTopLeftNeighbor();
                    tm.merge(trapezoidToMerge, newTrapezoids2[1]);
                    newTrapezoids2[1] = trapezoidToMerge;
                }

                dag.split2(tm, segment, replacedTrapezoid.getDAGlink(), newTrapezoids2);
            } else {
                newTrapezoids3 = tm.split3R(trapezoids[trapezoids.size()-1], segment,
                                      trapezoidFromPrevSplitTop, trapezoidFromPrevSplitBot);

                if(mergeFlag) {
                    trapezoidToMerge = tm.getTrapezoid(newTrapezoids3[0]).getBotLeftNeighbor();
                    tm.merge(trapezoidToMerge, newTrapezoids3[0]);
                    newTrapezoids3[0] = trapezoidToMerge;
                }
                else {
                    trapezoidToMerge = tm.getTrapezoid(newTrapezoids3[1]).getTopLeftNeighbor();
                    tm.merge(trapezoidToMerge, newTrapezoids3[1]);
                    newTrapezoids3[1] = trapezoidToMerge;
                }

                dag.split3R(tm, segment, replacedTrapezoid.getDAGlink(), newTrapezoids3);
            }
        }
    }
}
