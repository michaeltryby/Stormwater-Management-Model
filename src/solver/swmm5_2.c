

// Public Includes
#include "swmm5_2.h"

// Private Includes
#include "error.h"
#include "objects.h"
#include "funcs.h"
#define EXTERN extern
#include "globals.h"


// Imported from swmm5.c
EXTERN TSolverState SolverState;

// Imported from stats.c
EXTERN void stats_getNodeStat(int index, TNodeStats *nodeStats);

int DLLEXPORT sm_getObjectIndex(SM_ObjectType type, const char *id, int *index)
{
    int errorcode = 0;
	int idx = project_findObject(type, (char *)id);

	if (idx == -1) {
        index = NULL;
        errorcode = ERR_API_OBJECT_INDEX;
	} else
        *index = idx;

	return errorcode;
}

int DLLEXPORT sm_getNodeStats(int index, SM_NodeStats *nodeStats)
/// Output:  Node Stats Structure (SM_NodeStats)
/// Return:  API Error
/// Purpose: Gets Node Stats and Converts Units
{
    int errorcode = 0;

    switch(SolverState)
    {
    case COMPLETED:
        if (index < 0 || index >= Nobjects[NODE])
            errorcode = ERR_API_OBJECT_INDEX;
        break;
    case CLOSED:
        errorcode = ERR_API_INPUTNOTOPEN;
        break;
    case STEPPING:
        errorcode = ERR_API_SIM_NRUNNING;
        break;
    }

    if (!errorcode)
        stats_getNodeStat(index, (TNodeStats *)nodeStats);

    return errorcode;
}
