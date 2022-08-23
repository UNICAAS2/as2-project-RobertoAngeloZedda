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
        /* Set of trapezoids (indexes) as result of a split operation */
        std::vector<size_t> newTrpz;

        /* A reference to the Trapezoid that is being replaced
         * is needed to know in which direction to merge
         * and to perform the update of the DAG */
        Trapezoid replacedTrapezoid;

        /* If the new Segment is contained inside a single Trapezoid */
        if(trapezoids.size() == 1) {
            replacedTrapezoid = tm.getTrapezoid(trapezoids[0]);

            if(replacedTrapezoid.getLeftP() == segment.p1()) {
                if(replacedTrapezoid.getRightP() == segment.p2()) {
                    newTrpz = tm.split2(trapezoids[0], segment, SIZE_MAX, SIZE_MAX);
                    dag.split2(tm, segment, replacedTrapezoid.getDAGlink(), newTrpz);
                }
                else {
                    newTrpz = tm.split3R(trapezoids[0], segment, SIZE_MAX, SIZE_MAX);
                    dag.split3R(tm, segment, replacedTrapezoid.getDAGlink(), newTrpz);
                }
            }
            else if (replacedTrapezoid.getRightP() == segment.p2()) {
                newTrpz = tm.split3L(trapezoids[0], segment);
                dag.split3L(tm, segment, replacedTrapezoid.getDAGlink(), newTrpz);
            }
            else {
                newTrpz = tm.split4(trapezoids[0], segment);
                dag.split4(tm, segment, replacedTrapezoid.getDAGlink(), newTrpz);
            }
        } else {
        /* If the new Segment is contained inside multiple Trapezoids */

            /* Handling first Trapezoid*/
            replacedTrapezoid = tm.getTrapezoid(trapezoids[0]);

            if (replacedTrapezoid.getLeftP() == segment.p1()) {
                newTrpz = tm.split2(trapezoids[0], segment, SIZE_MAX, SIZE_MAX);
                dag.split2(tm, segment, replacedTrapezoid.getDAGlink(), newTrpz);
            }
            else {
                newTrpz = tm.split3L(trapezoids[0], segment);
                dag.split3L(tm, segment, replacedTrapezoid.getDAGlink(), newTrpz);
            }

            bool mergeFlag;
            size_t trpzToMerge;

            /* Handling Trapezoid not in first nor in last position */
            for(size_t i=1; i<=trapezoids.size()-2; i++) {

                mergeFlag = replacedTrapezoid.getTopRightNeighbor() == trapezoids[i];

                replacedTrapezoid = tm.getTrapezoid(trapezoids[i]);

                newTrpz = tm.split2(trapezoids[i], segment, newTrpz[newTrpz.size()-2], newTrpz[newTrpz.size()-1]);

                if(mergeFlag) {
                    trpzToMerge = tm.getTrapezoid(newTrpz[0]).getBotLeftNeighbor();
                    tm.merge(trpzToMerge, newTrpz[0]);
                    newTrpz[0] = trpzToMerge;
                }
                else {
                    trpzToMerge = tm.getTrapezoid(newTrpz[1]).getTopLeftNeighbor();
                    tm.merge(trpzToMerge, newTrpz[1]);
                    newTrpz[1] = trpzToMerge;
                }

                dag.split2(tm, segment, replacedTrapezoid.getDAGlink(), newTrpz);
            }

            /* Handling the last Trapezoid */
            mergeFlag = replacedTrapezoid.getTopRightNeighbor() == trapezoids[trapezoids.size()-1];

            replacedTrapezoid = tm.getTrapezoid(trapezoids[trapezoids.size()-1]);

            if(replacedTrapezoid.getRightP() == segment.p2())
                newTrpz = tm.split2(trapezoids[trapezoids.size()-1], segment, newTrpz[newTrpz.size()-2], newTrpz[newTrpz.size()-1]);
            else
                newTrpz = tm.split3R(trapezoids[trapezoids.size()-1], segment, newTrpz[newTrpz.size()-2], newTrpz[newTrpz.size()-1]);

            if(mergeFlag) {
                trpzToMerge = tm.getTrapezoid(newTrpz[0]).getBotLeftNeighbor();
                tm.merge(trpzToMerge, newTrpz[0]);
                newTrpz[0] = trpzToMerge;
            }
            else {
                trpzToMerge = tm.getTrapezoid(newTrpz[1]).getTopLeftNeighbor();
                tm.merge(trpzToMerge, newTrpz[1]);
                newTrpz[1] = trpzToMerge;
            }

            if(replacedTrapezoid.getRightP() == segment.p2())
                dag.split2(tm, segment, replacedTrapezoid.getDAGlink(), newTrpz);
            else
                dag.split3R(tm, segment, replacedTrapezoid.getDAGlink(), newTrpz);
        }
    }
}
