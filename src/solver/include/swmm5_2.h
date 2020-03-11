

#ifndef SWMM52_H
#define SWMM52_H


#include "swmm5.h"

// Forward declaration
typedef struct TNodeStats SM_NodeStats;


#ifdef __cplusplus
extern "C" {
#endif


int DLLEXPORT swmm_getNodeStats(int index, SM_NodeStats *nodeStats);


#ifdef __cplusplus
}
#endif

#endif //SWMM52_H
