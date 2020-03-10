

// Public Includes
#include "swmm5.h"
#include "swmm5_2.h"

#include "error.h"
#define EXTERN extern
#include "globals.h"

// Imported from swmm5.c
EXTERN int IsOpenFlag;
EXTERN int IsStartedFlag;
// Imported from stats.c
EXTERN void stats_getNodeStat(int index, TNodeStats *nodeStats);


int DLLEXPORT swmm_getNodeStats(int index, TNodeStats *nodeStats)
///
/// Output:  Node Stats Structure (SM_NodeStats)
/// Return:  API Error
/// Purpose: Gets Node Stats and Converts Units
{
    int errorcode = 0;

    // Check if Open
    if (IsOpenFlag == FALSE)
        errorcode = ERR_API_INPUTNOTOPEN;

    // Check if Simulation is Running
    else if (IsStartedFlag == FALSE)
        errorcode = ERR_API_SIM_NRUNNING;

    // Check if object index is within bounds
    else if (index < 0 || index >= Nobjects[NODE])
        errorcode = ERR_API_OBJECT_INDEX;

    else
        stats_getNodeStat(index, nodeStats);

    return errorcode;
}
