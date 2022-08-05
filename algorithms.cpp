#include "algorithms.h"

namespace Algorithms {
    /*size_t findPoint(cg3::Point2d& point, DAG& dag) {
        DAGnode currentNode = dag.getRoot();

        while(!currentNode  instanceof DAGnodeTrapezoid) {
            if(currentNode instanceof DAGnodePoint) {
                if(point.x() < currentNode.getValue().x())
                    currentNode = dag.getNode(currentNode.getLeft());
                else
                    currentNode = dag.getNode(currentNode.getRight());
            }
            if(currentNode instanceof DAGnodeSegment) {
                if(point is above currentNode.getValue())
                    currentNode = dag.getNode(currentNode.getLeft());
                else
                    currentNode = dag.getNode(currentNode.getRight());
            }
        }
    }*/

    std::vector<size_t> followSegment(cg3::Segment2d& segment, DAG& dag, TrapezoidalMap& tm, const size_t first) {
        std::vector<size_t> trapezoids;

        //trapezoids.push_back(findPoint(segment.p1(), dag));
        trapezoids.push_back(first);

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

    void updateTrapezoidalMapAndDAG(cg3::Segment2d& segment, std::vector<size_t>& trapezoids, DAG& dag, TrapezoidalMap& tm) {
        /* If the new Segment is contained inside a single Trapezoid,
         * that Trapezoid needs to be splitted in 4 */
        if(trapezoids.size() == 1) {
            tm.split4(trapezoids[0], segment);
        } else {
            /* A reference to the Trapezoid that is being replaced
             * is needed to know in which direction to merge */
            Trapezoid replacedTrapezoid = tm.getTrapezoid(trapezoids[0]);

            /* The first Trapezoid needs to be splitted in 3 (on the left) */
            std::vector<size_t> newTrpz = tm.split3(trapezoids[0], segment);

            /* Split in 2 with a Merge for every Trapezoid not in first nor in last position */
            for(size_t i=1; i<=trapezoids.size()-2; i++) {
                /* If the old Trapezoid's TOP right neighbor is the one that needs to be splitted */
                if(replacedTrapezoid.getTopRightNeighbor() == trapezoids[i]) {
                    /* New reference to the Trapezoid that is being replaced */
                    replacedTrapezoid = tm.getTrapezoid(trapezoids[i]);
                    newTrpz = tm.split2MergeTop(trapezoids[i], segment, newTrpz[newTrpz.size()-2], newTrpz[newTrpz.size()-1]);
                }
                /* If the old Trapezoid's BOT right neighbor is the one that needs to be splitted */
                else if(replacedTrapezoid.getBotRightNeighbor() == trapezoids[i]) {
                    /* New reference to the Trapezoid that is being replaced */
                    replacedTrapezoid = tm.getTrapezoid(trapezoids[i]);
                    newTrpz = tm.split2MergeBot(trapezoids[i], segment, newTrpz[newTrpz.size()-1], newTrpz[newTrpz.size()-2]);
                } else {
                    exit(EXIT_FAILURE);
                }
            }

            /* The last Trapezoid needs to be splitted in 3 with a merge (on the right) */
            if(replacedTrapezoid.getTopRightNeighbor() == trapezoids[trapezoids.size()-1]) {
                newTrpz = tm.split3MergeTop(trapezoids[trapezoids.size()-1], segment, newTrpz[newTrpz.size()-2], newTrpz[newTrpz.size()-1]);
            } else if(replacedTrapezoid.getBotRightNeighbor() == trapezoids[trapezoids.size()-1]) {
                newTrpz = tm.split3MergeBot(trapezoids[trapezoids.size()-1], segment, newTrpz[newTrpz.size()-1], newTrpz[newTrpz.size()-2]);
            } else {
                exit(EXIT_FAILURE);
            }
        }
    }
}
