


#ifndef SWMM_TYPES_H
#define SWMM_TYPES_H


typedef enum {
    GAGE,           /**< Rain gage */
    SUBCATCH,       /**< Subcatchment */
    NODE,           /**< Conveyance system node */
    LINK,           /**< Conveyance system link */
    POLLUT,         /**< Pollutant */
    LANDUSE,        /**< Land use category */
    TIMEPATTERN,    /**< Dry weather flow time pattern */
    CURVE,          /**< Generic table of values */
    TSERIES,        /**< Generic time series of values */
    CONTROL,        /**< Conveyance system control rules */
    TRANSECT,       /**< Irregular channel cross-section */
    AQUIFER,        /**< Groundwater aquifer */
    UNITHYD,        /**< RDII unit hydrograph */
    SNOWMELT,       /**< Snowmelt parameter set */
    SHAPE,          /**< Custom conduit shape */
    LID,            /**< LID treatment units */
    MAX_OBJ_TYPES
} SM_ObjectType;


typedef double DateTime;

typedef struct {
   double        avgDepth;
   double        maxDepth;
   DateTime      maxDepthDate;
   double        maxRptDepth;
   double        volFlooded;
   double        timeFlooded;
   double        timeSurcharged;
   double        timeCourantCritical;
   double        totLatFlow;
   double        maxLatFlow;
   double        maxInflow;
   double        maxOverflow;
   double        maxPondedVol;
   DateTime      maxInflowDate;
   DateTime      maxOverflowDate;
} SM_NodeStats;


#endif //SWMM_TYPES
