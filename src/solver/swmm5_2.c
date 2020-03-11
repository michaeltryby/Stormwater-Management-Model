

// Public Includes
#include "swmm5_2.h"

// Private Includes
#include "error.h"
#include "objects.h"
#define EXTERN extern
#include "globals.h"


// Imported from stats.c
EXTERN void stats_getNodeStat(int index, TNodeStats *nodeStats);


int DLLEXPORT swmm_getNodeStats(int index, SM_NodeStats *nodeStats)
/// Output:  Node Stats Structure (SM_NodeStats)
/// Return:  API Error
/// Purpose: Gets Node Stats and Converts Units
{
    int errorcode = 0;

    switch(State)
    {
    case CLOSED:
        errorcode = ERR_API_INPUTNOTOPEN;
        break;
    case STARTED:
        errorcode = ERR_API_SIM_NRUNNING;
        break;
    default:
        if (index < 0 || index >= Nobjects[NODE])
            errorcode = ERR_API_OBJECT_INDEX;
    }

    if (!errorcode)
        stats_getNodeStat(index, (TNodeStats *)nodeStats);

    return errorcode;
}
