

#include <stdlib.h>

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

// Local Functions
int *newIntArray(int n);


// Functions for working with date times
void DLLEXPORT sm_getElapsedTime(DateTime aDate, int **elapsedTime, int *length)
{
    // 0 days, 1 hrs, 2 mins, 3 secs
    DateTime x;

    int *temp = newIntArray(4);

    x = aDate - StartDateTime;
    if ( x > 0.0 ) {
        temp[0] = (int)x; // days
        datetime_decodeTime(x, &temp[1], &temp[2], &temp[3]);
    }

    *elapsedTime = temp;
    *length = 4;
}

void DLLEXPORT sm_getDateTime(double elapsedTime, DateTime *eDate)
// elapsedTime (decimal days)
{
    DateTime temp;
	// Convert from decimal days to milliseconds
    temp = getDateTime(elapsedTime*MSECperDAY);

    *eDate = temp;
}


int DLLEXPORT sm_getObjectIndex(SM_ObjectType type, const char *id, int *index)
{
    int idx, errorcode = 0;

    if (SolverState == CLOSED)
        errorcode = ERR_API_INPUTNOTOPEN;
    else
        idx = project_findObject(type, (char *)id);

    if (idx == -1)
        errorcode = ERR_API_OBJECT_INDEX;

    *index = idx;
	return errorcode;
}

int DLLEXPORT sm_getNodeResult(int index, SM_NodeResult resultType, double *result)
///
/// Input:   index = Index of desired ID
///          type = Result Type (SM_NodeResult)
/// Output:  result = result data desired (byref)
/// Return:  API Error
/// Purpose: Gets Node Simulated Value at Current Time
{
    int errcode = 0;

    // Check if Open
    if(SolverState == CLOSED)
        errcode = ERR_API_INPUTNOTOPEN;

    // Check if object index is within bounds
    else if (index < 0 || index >= Nobjects[NODE])
        errcode = ERR_API_OBJECT_INDEX;

    if (errcode == 0) {
        switch (resultType)
        {
        case TOTALINFLOW:
            *result = Node[index].inflow * UCF(FLOW);
            break;
        case TOTALOUTFLOW:
            *result = Node[index].outflow * UCF(FLOW);
            break;
        case LOSSES:
            *result = Node[index].losses * UCF(FLOW);
            break;
        case NODEVOL:
            *result = Node[index].newVolume * UCF(VOLUME);
            break;
        case NODEFLOOD:
            *result = Node[index].overflow * UCF(FLOW);
            break;
        case NODEDEPTH:
            *result = Node[index].newDepth * UCF(LENGTH);
            break;
        case NODEHEAD:
            *result = (Node[index].newDepth + Node[index].invertElev) * UCF(LENGTH);
            break;
        case LATINFLOW:
            *result = Node[index].newLatFlow * UCF(FLOW);
            break;
        default:
            result = NULL;
            errcode = ERR_API_OUTBOUNDS;

        }
    }

    return(errcode);
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

void DLLEXPORT sm_freeMemory(void *memory)
///
/// Helper function used to free memory allocated by API.
///
{
    free(memory);
}


int *newIntArray(int n)
{
    return (int *) calloc(n, sizeof(int));
}
