//-----------------------------------------------------------------------------
//   swmm5.h
//
//   Project: EPA SWMM5
//   Version: 5.1
//   Date:    03/24/14  (Build 5.1.001)
//            08/01/16  (Build 5.1.011)
//   Author:  L. Rossman
//
//   Prototypes for SWMM5 functions exported to swmm5.dll.
//
//-----------------------------------------------------------------------------

#ifndef SWMM5_H
#define SWMM5_H

#include "swmm_solver_export.h"


typedef enum {
    OPENED,
    STARTED,
    STEPPING,
    COMPLETED,
    ENDED,
    CLOSED
} TSolverState;

extern TSolverState SolverState;


#ifdef __cplusplus
extern "C" {
#endif


int  DLLEXPORT   swmm_run(const char *f1, const char *f2, const char *f3);
int  DLLEXPORT   swmm_open(const char *f1, const char *f2, const char *f3);
int  DLLEXPORT   swmm_start(int saveFlag);
int  DLLEXPORT   swmm_step(double *elapsedTime);
int  DLLEXPORT   swmm_end(void);
int  DLLEXPORT   swmm_report(void);
int  DLLEXPORT   swmm_getMassBalErr(float *runoffErr, float *flowErr, float *qualErr);
int  DLLEXPORT   swmm_close(void);
int  DLLEXPORT   swmm_getVersion(void);
int  DLLEXPORT   swmm_getError(char *errMsg, int msgLen);
int  DLLEXPORT   swmm_getWarnings(void);


#ifdef __cplusplus
}
#endif

#endif //SWMM5_H
