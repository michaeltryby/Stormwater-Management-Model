

#ifndef SWMM52_H
#define SWMM52_H


#include "swmm5.h"
#include "swmm_types.h"


#ifdef __cplusplus
extern "C" {
#endif


int DLLEXPORT sm_getObjectIndex(SM_ObjectType type, const char *id, int *index);

int DLLEXPORT sm_getNodeStats(int index, SM_NodeStats *nodeStats);


#ifdef __cplusplus
}
#endif

#endif //SWMM52_H
