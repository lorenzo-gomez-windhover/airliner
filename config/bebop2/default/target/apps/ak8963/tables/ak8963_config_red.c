/*
** Pragmas
*/

/*
** Include Files
*/
#include "cfe_tbl_filedef.h"
#include "ak8963_tbldefs.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/
static OS_USED CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    /* Content format: ObjName[64], TblName[38], Desc[32], TgtFileName[20], ObjSize
    **    ObjName - variable name of config table, e.g., CI_ConfigDefTbl[]
    **    TblName - app's table name, e.g., CI.CONFIG_TBL, where CI is the same app name
    **              used in cfe_es_startup.scr, and CI_defConfigTbl is the same table
    **              name passed in to CFE_TBL_Register()
    **    Desc - description of table in string format
    **    TgtFileName[20] - table file name, compiled as .tbl file extension
    **    ObjSize - size of the entire table
    */

    "AK8963_ConfigTbl", "AK8963.CONFIG_TBL", "AK8963 default config table",
    "ak8963_config.tbl", (sizeof(AK8963_ConfigTbl_t))
};

/*
** External Global Variables
*/

/*
** Global Variables
*/

/* Default AK8963 config table data */
AK8963_ConfigTbl_t AK8963_ConfigTbl =
{
        /* User calibration params */
        /* MagXScale */
        0.976245760917663574f,
        /* MagYScale */
        0.988125443458557129f,
        /* MagZScale */
        1.038563847541809082f,
        /* MagXOffset */
        0.076581671833992004f,
        /* MagYOffset */
        -0.027957385405898094f,
        /* MagZOffset */
        0.254844546318054199f
};

/*
** Local Variables
*/

/*
** Function Prototypes
*/

/*
** Function Definitions
*/

/*=======================================================================================
** End of file ak8963_config.c
**=====================================================================================*/
    
