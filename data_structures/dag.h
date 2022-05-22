#ifndef DAG_H
#define DAG_H

#import "dagnode.h"

class DAG {
    private:
        std::vector<DAGnode> nodes;
    public:
        DAG();
};

#endif // DAG_H
