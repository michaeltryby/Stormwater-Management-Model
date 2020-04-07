

#ifndef SWMM52_H
#define SWMM52_H


#include "swmm5.h"
#include "swmm_types.h"


#ifdef __cplusplus
extern "C" {
#endif

// Functions for working with DateTimes
void DLLEXPORT sm_getElapsedTime(DateTime aDate, int **elapsedTime, int *length);

void DLLEXPORT sm_getDateTime(double elapsedMsec, DateTime *eDate);


int DLLEXPORT sm_getObjectIndex(SM_ObjectType type, const char *id, int *index);

int DLLEXPORT sm_getNodeResult(int index, SM_NodeResult resultType, double *result);

int DLLEXPORT sm_getNodeStats(int index, SM_NodeStats *nodeStats);


void DLLEXPORT sm_freeMemory(void *memory);

#ifdef __cplusplus
}
#endif

#endif //SWMM52_H
