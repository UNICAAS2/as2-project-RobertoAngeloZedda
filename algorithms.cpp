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

    /*std::vector<size_t> followSegment(cg3::Segment2d& segment, DAG& dag, TrapezoidalMap& tm) {
        std::vector<size_t> trapezoids = std::vector<size_t>();

        trapezoids.push_back(findPoint(segment.p1(), dag));

        int j = 0;
        while(segment.p2().x > tm.getTrapezoid(trapezoids[j]).getRightP().x()) {
            if(tm.getTrapezoid(trapezoids[j]).getRightP().x() is above segment)
                trapezoids.push_back(tm.getTrapezoid(trapezoids[j]).getBotRightNeighbor());
            else
                trapezoids.push_back(tm.getTrapezoid(trapezoids[j]).getTopRightNeighbor());
            j++;
        }

        return trapezoids;
    }*/

    void updateTrapezoidalMapAndDAG(cg3::Segment2d& segment, std::vector<size_t>& trapezoids, DAG& dag, TrapezoidalMap& tm) {
        if(trapezoids.size() == 1) {
            tm.split4(trapezoids[0], segment);
        } else {
            std::vector<size_t> newTrpz = tm.split3(trapezoids[0], segment);

            for(size_t i=1; i<trapezoids.size()-2; i++) {
                if(tm.getTrapezoid(newTrpz[newTrpz.size()-2]).getTopRightNeighbor() == trapezoids[i]) {
                    newTrpz = tm.split2MergeBot(trapezoids[i], segment, newTrpz[newTrpz.size()-2], newTrpz[newTrpz.size()-1]);
                } else {
                    newTrpz = tm.split2MergeBot(trapezoids[i], segment, newTrpz[newTrpz.size()-1], newTrpz[newTrpz.size()-2]);
                }
            }

            if(tm.getTrapezoid(newTrpz[newTrpz.size()-2]).getTopRightNeighbor() == trapezoids[trapezoids.size()-1]) {
                newTrpz = tm.split2MergeBot(trapezoids[trapezoids.size()-1], segment, newTrpz[newTrpz.size()-3], newTrpz[newTrpz.size()-2]);
            } else {
                newTrpz = tm.split2MergeBot(trapezoids[trapezoids.size()-1], segment, newTrpz[newTrpz.size()-2], newTrpz[newTrpz.size()-3]);
            }
        }
    }
}
