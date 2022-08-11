#include "algorithms.h"

namespace Algorithms {
    size_t findPoint(cg3::Point2d& point, DAG& dag) {
        DAGnode currentNode = dag.getRoot();

        while(!currentNode.isTrapezoidNode()) {
            if(currentNode.isPointNode()) {
                if(point.x() < currentNode.getPointValue().x())
                    currentNode = dag.getNode(currentNode.getLeft());
                else
                    currentNode = dag.getNode(currentNode.getRight());
            }
            if(currentNode.isSegmentNode()) {
                if(isPointOnTheRight(currentNode.getSegmentValue(), point))
                    currentNode = dag.getNode(currentNode.getLeft());
                else
                    currentNode = dag.getNode(currentNode.getRight());
            }
        }

        return currentNode.getTrapezoidValue();
    }

    std::vector<size_t> followSegment(cg3::Segment2d& segment, DAG& dag, TrapezoidalMap& tm) {
        std::vector<size_t> trapezoids;

        cg3::Point2d firstPoint = segment.p1();
        trapezoids.push_back(Algorithms::findPoint(firstPoint, dag));

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
        std::vector<size_t> newTrpz;

        /* If the new Segment is contained inside a single Trapezoid,
         * that Trapezoid needs to be splitted in 4 */
        if(trapezoids.size() == 1) {
            newTrpz = tm.split4(trapezoids[0], segment);
            DAGsplit4(dag, tm, segment, newTrpz[0], newTrpz[1], newTrpz[2], newTrpz[3]);
        } else {
            /* A reference to the Trapezoid that is being replaced
             * is needed to know in which direction to merge */
            Trapezoid replacedTrapezoid = tm.getTrapezoid(trapezoids[0]);

            /* The first Trapezoid needs to be splitted in 3 (on the left) */
            newTrpz = tm.split3(trapezoids[0], segment);
            DAGsplit3Left(dag, tm, segment, newTrpz[0], newTrpz[1], newTrpz[2]);

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
                DAGsplit2(dag, tm, segment, newTrpz[0], newTrpz[1], i);
            }

            /* The last Trapezoid needs to be splitted in 3 with a merge (on the right) */
            if(replacedTrapezoid.getTopRightNeighbor() == trapezoids[trapezoids.size()-1]) {
                newTrpz = tm.split3MergeTop(trapezoids[trapezoids.size()-1], segment, newTrpz[newTrpz.size()-2], newTrpz[newTrpz.size()-1]);
            } else if(replacedTrapezoid.getBotRightNeighbor() == trapezoids[trapezoids.size()-1]) {
                newTrpz = tm.split3MergeBot(trapezoids[trapezoids.size()-1], segment, newTrpz[newTrpz.size()-1], newTrpz[newTrpz.size()-2]);
            } else {
                exit(EXIT_FAILURE);
            }
            DAGsplit3Right(dag, tm, segment, newTrpz[0], newTrpz[1], newTrpz[2]);
        }
    }

    void DAGsplit4(DAG& dag, TrapezoidalMap& tm, cg3::Segment2d s, size_t t1, size_t t2, size_t t3, size_t t4) {
        size_t n1 = dag.updateNode(DAGnode(s.p1()), tm.getTrapezoid(t1).getDAGlink());

        size_t n2 = dag.addLeftChild(DAGnode(t1), n1);
        size_t n3 = dag.addRightChild(DAGnode(s.p2()), n1);

        size_t n4 = dag.addLeftChild(DAGnode(s), n3);
        size_t n5 = dag.addRightChild(DAGnode(t4), n3);

        size_t n6 = dag.addLeftChild(DAGnode(t2), n4);
        size_t n7 = dag.addRightChild(DAGnode(t3), n4);

        tm.getTrapezoid(t1).setDAGlink(n2);
        tm.getTrapezoid(t2).setDAGlink(n6);
        tm.getTrapezoid(t3).setDAGlink(n7);
        tm.getTrapezoid(t4).setDAGlink(n5);
    }

    void DAGsplit3Left(DAG& dag, TrapezoidalMap& tm, cg3::Segment2d s, size_t t1, size_t t2, size_t t3) {
        size_t n1 = dag.updateNode(DAGnode(s.p1()), tm.getTrapezoid(t1).getDAGlink());

        size_t n2 = dag.addLeftChild(DAGnode(t1), n1);
        size_t n3 = dag.addRightChild(DAGnode(s), n1);

        size_t n4 = dag.addLeftChild(DAGnode(t2), n3);
        size_t n5 = dag.addRightChild(DAGnode(t3), n3);

        tm.getTrapezoid(t1).setDAGlink(n2);
        tm.getTrapezoid(t2).setDAGlink(n4);
        tm.getTrapezoid(t3).setDAGlink(n5);
    }

    void DAGsplit3Right(DAG& dag, TrapezoidalMap& tm, cg3::Segment2d s, size_t t1, size_t t2, size_t t3) {
        size_t n1 = dag.updateNode(DAGnode(s.p1()), tm.getTrapezoid(t3).getDAGlink());

        size_t n2 = dag.addLeftChild(DAGnode(s), n1);
        size_t n3 = dag.addRightChild(DAGnode(t3), n1);

        size_t n4, n5;
        if(tm.getTrapezoid(t1).getDAGlink() == SIZE_MAX)
            n4 = dag.addLeftChild(DAGnode(t1), n2);
        else {
            n4 = tm.getTrapezoid(t1).getDAGlink();
            dag.getNode(n2).setLeft(n4);
        }
        if(tm.getTrapezoid(t2).getDAGlink() == SIZE_MAX)
            n5 = dag.addRightChild(DAGnode(t2), n2);
        else {
            n5 = tm.getTrapezoid(t2).getDAGlink();
            dag.getNode(n2).setRight(n5);
        }

        tm.getTrapezoid(t1).setDAGlink(n4);
        tm.getTrapezoid(t2).setDAGlink(n5);
        tm.getTrapezoid(t3).setDAGlink(n3);
    }

    void DAGsplit2(DAG& dag, TrapezoidalMap& tm, cg3::Segment2d s, size_t t1, size_t t2, size_t tOrigin) {
        size_t n1 = dag.updateNode(DAGnode(s), tm.getTrapezoid(tOrigin).getDAGlink());

        size_t n2 = tm.getTrapezoid(t1).getDAGlink();
        dag.getNode(n1).setLeft(n2);
        size_t n3 = tm.getTrapezoid(t2).getDAGlink();
        dag.getNode(n1).setLeft(n3);

        tm.getTrapezoid(t1).setDAGlink(n2);
        tm.getTrapezoid(t2).setDAGlink(n3);
    }
}
