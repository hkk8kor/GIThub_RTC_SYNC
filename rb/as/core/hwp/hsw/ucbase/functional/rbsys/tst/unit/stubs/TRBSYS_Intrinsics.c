#include "SwTest_Global.h"                      // for SWT functionality
#include "RBSYS_Config.h"

#include "TRBSYS_Intrinsics.h"
#include "TRBSYS_CpuInfo.h"
#include "RBSYS_BBFSW_StartupServices.h"
#include "TRBSYS_BBFSW_StartupServices.h"
#include "TRBSYS_uCRegisters.h"
#include "TRBSYS_uCReset.h"
#include "RBSYS_uCResetInfo.h"
#include "TRBSYS_SystemTimer.h"


void RBSYS_memory_changed(void){}
static uint32 TRBSYS_LinkPointer = 0;
uint32 RBSYS_getLinkPointer(void)
{
  return TRBSYS_LinkPointer;
}
static int ldl_w_cnt = 0;
int RBSYS_LDL_W(int *p)
{
  int result = 1;

  // RBSYS_LDL_W() twice required
  if(ldl_w_cnt >= 1)
  {
    result = 0;
  }

  ldl_w_cnt++;
  return result;
}
static int stc_w_cnt = 0;
int RBSYS_STC_W(int d, int *p)
{
  int result = 0;

  if ((*p != d) && (stc_w_cnt >= 1))
  {
    *p = d;
    result = 1;   //successful
  }

  stc_w_cnt++;
  return result;
}
void TRBSYS_setLinkPointer(int nLinkPointer)
{
  TRBSYS_LinkPointer = nLinkPointer;
}



static uint32 loop_counter = 0;
static boolean TRBSYS_AbortSnoozeLoop = FALSE;


void TRBSYS_SetAbortSnoozeLoop(void)
{
  TRBSYS_AbortSnoozeLoop = TRUE;
}

uint32 TRBSYS_GetSnoozeLoopCounter(void)
{
  return loop_counter;
}

void RBSYS_SNOOZE_LOOP(int cnt)
{
  loop_counter += cnt;

  if ((TRBSYS_AbortSnoozeLoop) && (loop_counter >= 5))
  {
    #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
      RBSYS_RESF = RBSYS_RESET_FLAG_SW_APPLICATION_0; //< set SW Application Reset
      TRBSYS_setBootblockRequest(RBSYS_SKIP_BOOTBLOCK);
      //< Is this akward behavior simulation even required anymore? uCReset.c has been instrumented meanwhile
    #endif
  }
}


static int TRBSYS_SYNCM_CNT = 0;
static int TRBSYS_SYNCP_CNT = 0;
static int TRBSYS_SYNCI_CNT = 0;

static uint32 TRBSYS_Snooze_Ctr = 0;

uint32 TRBSYS_GetSnoozeCounter(void)
{
  return TRBSYS_Snooze_Ctr;
}

void RBSYS_snooze(void)
{
  TRBSYS_Snooze_Ctr++;

  //value is slowly increasing to check behavior during while loop
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
    STM0CNT2 += TRBSYS_SNOOZE_LOOP_TICKS;
  #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) ||(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    TPTMPE0TPTM0UCNT1 += TRBSYS_SNOOZE_LOOP_TICKS;
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    TRBSYS_RealtimeTickCtrAddTicks(TRBSYS_SNOOZE_LOOP_TICKS);
  #endif
}

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  static unsigned int TRBSYS_SystemRegister[REG_ID_MAX][SEL_ID_MAX][RB_NUM_CORES] = {
    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      [0][0]  [0] = 0x00000000,
      [1][0]  [0] = 0x00000020,
      [2][0]  [0] = 0x00006ece,
      [3][0]  [0] = 0x00000020,
      [5][0]  [0] = 0x00000029,
      [6][0]  [0] = 0x00000000,
      [7][0]  [0] = 0x00000000,
      [8][0]  [0] = 0x00000000,
      [9][0]  [0] = 0x00000000,
      [10][0] [0] = 0x00000000,
      [11][0] [0] = 0x00000000,
      [13][0] [0] = 0x00000000,
      [14][0] [0] = 0x00000000,
      [16][0] [0] = 0x00000000,
      [17][0] [0] = 0x00000000,
      [20][0] [0] = 0x00000000,
      [28][0] [0] = 0x00000000,
      [29][0] [0] = 0x00000000,
      [31][0] [0] = 0x00000000,
      [0][1]  [0] = 0x00020004,
      [2][1]  [0] = 0x00000000,
      [3][1]  [0] = 0x00000000,
      [4][1]  [0] = 0x00000000,
      [5][1]  [0] = 0x80000000,
      [6][1]  [0] = 0x05800714,
      [11][1] [0] = 0x00000000,
      [12][1] [0] = 0x00000000,
      [0][2]  [0] = 0x00018000,
      [6][2]  [0] = 0x00000000,
      [7][2]  [0] = 0x00000000,
      [8][2]  [0] = 0x00000000,
      [7][1]  [0] = 0x00000000,
      [10][2] [0] = 0x00000000,
      [11][2] [0] = 0x00000000,
      [12][2] [0] = 0x00000000,
      [13][2] [0] = 0x00000000,
      [0][5]  [0] = 0x00000000,
      [1][5]  [0] = 0x00000000,
      [4][5]  [0] = 0x00000000,
      [5][5]  [0] = 0x00000010,
      [8][5]  [0] = 0x00000000,
      [9][5]  [0] = 0x00000000,
      [10][5] [0] = 0x00000000,
      [11][5] [0] = 0x00000000,
      [0][6]  [0] = 0x00000000,
      [1][6]  [0] = 0x00000000,
      [2][6]  [0] = 0x00000000,
      [4][6]  [0] = 0x00000000,
      [5][6]  [0] = 0x00000000,
      [6][6]  [0] = 0x00000000,
      [8][6]  [0] = 0x00000000,
      [9][6]  [0] = 0x00000000,
      [10][6] [0] = 0x00000000,
      [12][6] [0] = 0x00000000,
      [13][6] [0] = 0x00000000,
      [14][6] [0] = 0x00000000,
      [16][6] [0] = 0x00000000,
      [17][6] [0] = 0x00000000,
      [18][6] [0] = 0x00000000,
      [20][6] [0] = 0x00000000,
      [21][6] [0] = 0x00000000,
      [22][6] [0] = 0x00000000,
      [24][6] [0] = 0x00000000,
      [25][6] [0] = 0x00000000,
      [26][6] [0] = 0x00000000,
      [28][6] [0] = 0x00000000,
      [29][6] [0] = 0x00000000,
      [30][6] [0] = 0x00000000,
      [0][7]  [0] = 0x00000000,
      [1][7]  [0] = 0x00000000,
      [2][7]  [0] = 0x00000000,
      [4][7]  [0] = 0x00000000,
      [5][7]  [0] = 0x00000000,
      [6][7]  [0] = 0x00000000,
      [8][7]  [0] = 0x00000000,
      [9][7]  [0] = 0x00000000,
      [10][7] [0] = 0x00000000,
      [12][7] [0] = 0x00000000,
      [13][7] [0] = 0x00000000,
      [14][7] [0] = 0x00000000,
      [16][7] [0] = 0x00000000,
      [17][7] [0] = 0x00000000,
      [18][7] [0] = 0x00000000,
      [20][7] [0] = 0x00000000,
      [21][7] [0] = 0x00000000,
      [22][7] [0] = 0x00000000,
      [24][7] [0] = 0x00000000,
      [25][7] [0] = 0x00000000,
      [26][7] [0] = 0x00000000,
      [28][7] [0] = 0x00000000,
      [29][7] [0] = 0x00000000,
      [30][7] [0] = 0x00000000,
      [16][4] [0] = 0x00000000,
      [17][4] [0] = 0x00000001,
      [18][4] [0] = 0x00000000,
      [19][4] [0] = 0x00000000,
      [24][4] [0] = 0x00030003,
      [26][4] [0] = 0x00011084,
      [28][4] [0] = 0x00000000,
      [24][13][0] = 0x00000001,
      #if( RBFS_MCORE == RBFS_MCORE_ON )
        [0][0]  [1] = 0x00000000,
        [1][0]  [1] = 0x00000020,
        [2][0]  [1] = 0x0000c8ba,
        [3][0]  [1] = 0x00000020,
        [5][0]  [1] = 0x00000028,
        [6][0]  [1] = 0x00000000,
        [7][0]  [1] = 0x00000000,
        [8][0]  [1] = 0x00000000,
        [9][0]  [1] = 0x00000000,
        [10][0] [1] = 0x00000000,
        [11][0] [1] = 0x00000000,
        [13][0] [1] = 0x00000000,
        [14][0] [1] = 0x00000000,
        [16][0] [1] = 0x00000000,
        [17][0] [1] = 0x00000000,
        [20][0] [1] = 0x00000000,
        [28][0] [1] = 0x00000000,
        [29][0] [1] = 0x00000000,
        [31][0] [1] = 0x00000000,
        [0][1]  [1] = 0x00020004,
        [2][1]  [1] = 0x00000000,
        [3][1]  [1] = 0x00000000,
        [4][1]  [1] = 0x00000000,
        [5][1]  [1] = 0x80000000,
        [6][1]  [1] = 0x05800714,
        [11][1] [1] = 0x00000000,
        [12][1] [1] = 0x00000000,
        [0][2]  [1] = 0x00028000,
        [6][2]  [1] = 0x00000000,
        [7][2]  [1] = 0x00000000,
        [8][2]  [1] = 0x00000000,
        [7][1]  [1] = 0x00000000,
        [10][2] [1] = 0x00000000,
        [11][2] [1] = 0x00000000,
        [12][2] [1] = 0x00000000,
        [13][2] [1] = 0x00000000,
        [0][5]  [1] = 0x00000000,
        [1][5]  [1] = 0x00000000,
        [4][5]  [1] = 0x00000000,
        [5][5]  [1] = 0x00000010,
        [8][5]  [1] = 0x00000000,
        [9][5]  [1] = 0x00000000,
        [10][5] [1] = 0x00000000,
        [11][5] [1] = 0x00000000,
        [0][6]  [1] = 0x00000000,
        [1][6]  [1] = 0x00000000,
        [2][6]  [1] = 0x00000000,
        [4][6]  [1] = 0x00000000,
        [5][6]  [1] = 0x00000000,
        [6][6]  [1] = 0x00000000,
        [8][6]  [1] = 0x00000000,
        [9][6]  [1] = 0x00000000,
        [10][6] [1] = 0x00000000,
        [12][6] [1] = 0x00000000,
        [13][6] [1] = 0x00000000,
        [14][6] [1] = 0x00000000,
        [16][6] [1] = 0x00000000,
        [17][6] [1] = 0x00000000,
        [18][6] [1] = 0x00000000,
        [20][6] [1] = 0x00000000,
        [21][6] [1] = 0x00000000,
        [22][6] [1] = 0x00000000,
        [24][6] [1] = 0x00000000,
        [25][6] [1] = 0x00000000,
        [26][6] [1] = 0x00000000,
        [28][6] [1] = 0x00000000,
        [29][6] [1] = 0x00000000,
        [30][6] [1] = 0x00000000,
        [0][7]  [1] = 0x00000000,
        [1][7]  [1] = 0x00000000,
        [2][7]  [1] = 0x00000000,
        [4][7]  [1] = 0x00000000,
        [5][7]  [1] = 0x00000000,
        [6][7]  [1] = 0x00000000,
        [8][7]  [1] = 0x00000000,
        [9][7]  [1] = 0x00000000,
        [10][7] [1] = 0x00000000,
        [12][7] [1] = 0x00000000,
        [13][7] [1] = 0x00000000,
        [14][7] [1] = 0x00000000,
        [16][7] [1] = 0x00000000,
        [17][7] [1] = 0x00000000,
        [18][7] [1] = 0x00000000,
        [20][7] [1] = 0x00000000,
        [21][7] [1] = 0x00000000,
        [22][7] [1] = 0x00000000,
        [24][7] [1] = 0x00000000,
        [25][7] [1] = 0x00000000,
        [26][7] [1] = 0x00000000,
        [28][7] [1] = 0x00000000,
        [29][7] [1] = 0x00000000,
        [30][7] [1] = 0x00000000,
        [16][4] [1] = 0x00000000,
        [17][4] [1] = 0x00000000,
        [18][4] [1] = 0x00000000,
        [19][4] [1] = 0x00000000,
        [24][4] [1] = 0x00030003,
        [26][4] [1] = 0x00011084,
        [28][4] [1] = 0x00000000,
        [24][13][1] = 0x00000001,
      #endif
    #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      [0][0]   [0] = 0x0000cfb6,
      [1][0]   [0] = 0x00000020,
      [2][0]   [0] = 0xf90100b0,
      [3][0]   [0] = 0x00000020,
      [5][0]   [0] = 0x00000021,
      [6][0]   [0] = 0x00000000,
      [7][0]   [0] = 0x00000000,
      [8][0]   [0] = 0x00000000,
      [9][0]   [0] = 0x00000000,
      [10][0]  [0] = 0x00000000,
      [13][0]  [0] = 0x00000000,
      [14][0]  [0] = 0x00000000,
      [16][0]  [0] = 0x00000000,
      [17][0]  [0] = 0x00000000,
      [20][0]  [0] = 0x00000000,
      [21][0]  [0] = 0x00000020,
      [28][0]  [0] = 0x00000000,
      [29][0]  [0] = 0x00000000,
      [0][1]   [0] = 0x00000000,
      [1][1]   [0] = 0xffffffff,
      [2][1]   [0] = 0x00000000,
      [3][1]   [0] = 0x00000001,
      [4][1]   [0] = 0x00000000,
      [5][1]   [0] = 0x00000000,
      [6][1]   [0] = 0x07840700,
      [8][1]   [0] = 0x00000000,
      [11][1]  [0] = 0x00000000,
      [12][1]  [0] = 0x00000000,
      [0][2]   [0] = 0x00000000,
      [1][2]   [0] = 0x00000000,
      [6][2]   [0] = 0x00000000,
      [8][2]   [0] = 0x00000000,
      [15][2]  [0] = 0x00000000,
      [16][2]  [0] = 0x0000ffff,
      [17][2]  [0] = 0x00000000,
      [18][2]  [0] = 0x00000000,
      [10][2]  [0] = 0x00000000,
      [12][2]  [0] = 0x00000000,
      [13][2]  [0] = 0x000f0000,
      [14][2]  [0] = 0x00000010,
      [6][10]  [0] = 0x00000000,
      [8][10]  [0] = 0x00000000,
      [9][10]  [0] = 0x00000000,
      [10][10] [0] = 0x00000000,
      [12][10] [0] = 0x00000000,
      [13][10] [0] = 0x00000000,
      [0][5]   [0] = 0x00000000,
      [2][5]   [0] = 0x0002001f,
      [8][5]   [0] = 0x00000000,
      [9][5]   [0] = 0x00000000,
      [10][5]  [0] = 0x00000000,
      [11][5]  [0] = 0x00000000,
      [12][5]  [0] = 0x00000000,
      [16][5]  [0] = 0x00000000,
      [20][5]  [0] = 0x00000000,
      [21][5]  [0] = 0x00000000,
      [22][5]  [0] = 0x00000000,
      [24][5]  [0] = 0x00000000,
      [25][5]  [0] = 0x00000000,
      [26][5]  [0] = 0x00000000,
      [27][5]  [0] = 0x00000000,
      [28][5]  [0] = 0x00000000,
      [29][5]  [0] = 0x00000000,
      [30][5]  [0] = 0x00000000,
      [31][5]  [0] = 0x00000000,
      [16][4]  [0] = 0x00000000,
      [17][4]  [0] = 0x00000000,
      [18][4]  [0] = 0x00000000,
      [19][4]  [0] = 0x00000000,
      [24][4]  [0] = 0x00010003,
      [26][4]  [0] = 0x00001044,
      [28][4]  [0] = 0x00000000,
      [0][11]  [0] = 0x00000000,
      [1][11]  [0] = 0x00000000,
      [2][11]  [0] = 0x00000000,
      [8][11]  [0] = 0x00000000,
      [16][11] [0] = 0x00000000,
      [17][11] [0] = 0x00000000,
      [18][11] [0] = 0x00000000,
      [19][11] [0] = 0x00000000,
      [20][11] [0] = 0x00000000,
      [21][11] [0] = 0x00000000,
      [22][11] [0] = 0x00000000,
      [23][11] [0] = 0x00000000,
      [0][12]  [0] = 0x00000000,
      [1][12]  [0] = 0x00000000,
      [5][12]  [0] = 0x00000001,
      [8][12]  [0] = 0x00000001,
      [24][13] [0] = 0x00000101,

      #if( RBFS_MCORE == RBFS_MCORE_ON )
        [0][0]   [1] = 0x00000000,
        [1][0]   [1] = 0x00000020,
        [2][0]   [1] = 0xf90200b0,
        [3][0]   [1] = 0x00000020,
        [5][0]   [1] = 0x00000020,
        [6][0]   [1] = 0x00000000,
        [7][0]   [1] = 0x00000000,
        [8][0]   [1] = 0x00000000,
        [9][0]   [1] = 0x00000000,
        [10][0]  [1] = 0x00000000,
        [13][0]  [1] = 0x00000000,
        [14][0]  [1] = 0x00000000,
        [16][0]  [1] = 0xdbf6bb71,
        [17][0]  [1] = 0x00000000,
        [20][0]  [1] = 0x00000000,
        [21][0]  [1] = 0x00000020,
        [28][0]  [1] = 0xdfffdfeb,
        [29][0]  [1] = 0xf94de6bb,
        [0][1]   [1] = 0x00000001,
        [1][1]   [1] = 0xffffffff,
        [2][1]   [1] = 0x00000000,
        [3][1]   [1] = 0x6fffdc03,
        [4][1]   [1] = 0x3beea200,
        [5][1]   [1] = 0x00000000,
        [6][1]   [1] = 0x07840700,
        [8][1]   [1] = 0x00000000,
        [11][1]  [1] = 0x00000000,
        [12][1]  [1] = 0x00000000,
        [0][2]   [1] = 0x00000001,
        [1][2]   [1] = 0x00000001,
        [6][2]   [1] = 0x772f7b55,
        [8][2]   [1] = 0xf0140e1a,
        [15][2]  [1] = 0x00000000,
        [16][2]  [1] = 0x0000ffff,
        [17][2]  [1] = 0x00000000,
        [18][2]  [1] = 0x0ede1e20,
        [10][2]  [1] = 0x00000000,
        [12][2]  [1] = 0x00000000,
        [13][2]  [1] = 0x000f0000,
        [14][2]  [1] = 0x00000010,
        [6][10]  [1] = 0x00000000,
        [8][10]  [1] = 0x00000000,
        [9][10]  [1] = 0x00000000,
        [10][10] [1] = 0x00000000,
        [12][10] [1] = 0x00000000,
        [13][10] [1] = 0x00000000,
        [0][5]   [1] = 0x00000000,
        [2][5]   [1] = 0x0002001f,
        [8][5]   [1] = 0x00000000,
        [9][5]   [1] = 0x00000000,
        [10][5]  [1] = 0x00000000,
        [11][5]  [1] = 0x00000000,
        [12][5]  [1] = 0x00000000,
        [16][5]  [1] = 0x00000000,
        [20][5]  [1] = 0x00000000,
        [21][5]  [1] = 0x00000000,
        [22][5]  [1] = 0x00000000,
        [24][5]  [1] = 0x0000001e,
        [25][5]  [1] = 0x00000013,
        [26][5]  [1] = 0x00000010,
        [27][5]  [1] = 0x00000018,
        [28][5]  [1] = 0x00000016,
        [29][5]  [1] = 0x0000001f,
        [30][5]  [1] = 0x0000000f,
        [31][5]  [1] = 0x00000001,
        [16][4]  [1] = 0x04d3b034,
        [17][4]  [1] = 0x00153e00,
        [18][4]  [1] = 0xfffbfffb,
        [19][4]  [1] = 0x7fefd4cb,
        [24][4]  [1] = 0x00010003,
        [26][4]  [1] = 0x00001044,
        [28][4]  [1] = 0x48002fe0,
        [0][11]  [1] = 0x00000000,
        [1][11]  [1] = 0x00000000,
        [2][11]  [1] = 0x00000000,
        [8][11]  [1] = 0x00000000,
        [16][11] [1] = 0x00000000,
        [17][11] [1] = 0x00000000,
        [18][11] [1] = 0x00000000,
        [19][11] [1] = 0x00000000,
        [20][11] [1] = 0x00000000,
        [21][11] [1] = 0x00000000,
        [22][11] [1] = 0x00000000,
        [23][11] [1] = 0x00000000,
        [0][12]  [1] = 0x00000000,
        [1][12]  [1] = 0x00000000,
        [5][12]  [1] = 0x00000001,
        [8][12]  [1] = 0x00000001,
        [24][13] [1] = 0x00000101,
      #endif
    #endif
  };
#endif

TRBSYS_Callback_t TRBSYS_SYNCM_Callback = NULL;
void RBSYS_SYNCM(void)
{
  if(TRBSYS_SYNCM_Callback != NULL)
  {
    TRBSYS_SYNCM_Callback();
  }
  TRBSYS_SYNCM_CNT++;
}

void RBSYS_SYNCP(void)
{
  TRBSYS_SYNCP_CNT++;
}

void RBSYS_SYNCI(void)
{
  TRBSYS_SYNCI_CNT++;
}

static uint32 trbsys_Intrinsics_CurrentRegisterSetIndex = 0;
void TRBSYS_Intrinsics_SetRegisterSetIndex(uint32 coreRegisterSetIndex)
{
  trbsys_Intrinsics_CurrentRegisterSetIndex = coreRegisterSetIndex;
}

static inline uint32 TRBSYS_Intrinsics_GetRegisterSetIndex(void)
{
  return trbsys_Intrinsics_CurrentRegisterSetIndex;
}



#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

  uint32 TRBSYS_GetSystemRegister(int regID, int selID)
  {
    return TRBSYS_SystemRegister[regID][selID][TRBSYS_Intrinsics_GetRegisterSetIndex()];
  }

#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  uint32 TRBSYS_GetSystemRegister(uint32 coproc, uint32 opcode1, uint32 CRn, uint32 CRm, uint32 opcode2)
  {
    return TRBSYS_SystemRegister_STMStellar[opcode1][CRn][CRm][opcode2][TRBSYS_Intrinsics_GetRegisterSetIndex()];
  }
  uint64 TRBSYS_GetSystemRegister64(uint32 coproc, uint32 opcode, uint32 CRm)
  {
    return TRBSYS_SystemRegister_STMStellar[opcode][0][CRm][0][TRBSYS_Intrinsics_GetRegisterSetIndex()];
  }

#endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  static int TRBSYS_STSR_CNT = 0;
  unsigned int RBSYS_STSR(int regID, int selID)
  {
    if ((regID == 24) && (selID == 4) && (TRBSYS_STSR_CNT == 10))
    {
      // required to leave while loop inside RBSYS_invalidateInstructionCache
      TRBSYS_SystemRegister[regID][selID][TRBSYS_Intrinsics_GetRegisterSetIndex()] &= 0xFFFFFEFFu;
    }

    TRBSYS_STSR_CNT++;

    return TRBSYS_SystemRegister[regID][selID][TRBSYS_Intrinsics_GetRegisterSetIndex()];
  }

  void RBSYS_LDSR(int regID, int selID, unsigned int val)
  {
    TRBSYS_SystemRegister[regID][selID][TRBSYS_Intrinsics_GetRegisterSetIndex()] = val;
  }


  static bool TRBSYS_SET1_OVERWRITE_ZFLAG = FALSE;
  static int TRBSYS_SET1OVERWRITE_ZFLAG_VALUE = 0;
  void RBSYS_SET1(volatile char *addr, int bitnum)
  {
    uint32 zFlag = !(*addr & (1 << bitnum));
    if(TRBSYS_SET1_OVERWRITE_ZFLAG)
    {
      zFlag = TRBSYS_SET1OVERWRITE_ZFLAG_VALUE;
    }
    *addr |= 1 << bitnum;
    TRBSYS_SystemRegister[5][0][TRBSYS_Intrinsics_GetRegisterSetIndex()] = (TRBSYS_SystemRegister[5][0][TRBSYS_Intrinsics_GetRegisterSetIndex()] & (~1)) | zFlag;
  }

  void RBSYS_CLR1(volatile char *addr, int bitnum)
  {
    uint32 zFlag = !(*addr & (1 << bitnum));
    *addr &= ~(1 << bitnum);
    TRBSYS_SystemRegister[5][0][TRBSYS_Intrinsics_GetRegisterSetIndex()] = (TRBSYS_SystemRegister[5][0][TRBSYS_Intrinsics_GetRegisterSetIndex()] & (~1)) | zFlag;
  }

  void TRBSYS_SET1_Overwrite_ZFlag(int value)
  {
    TRBSYS_SET1OVERWRITE_ZFLAG_VALUE = value;
    TRBSYS_SET1_OVERWRITE_ZFLAG = TRUE;
  }


  /* helper functions */
  int TRBSYS_Get_SYNCM_CNT(void)
  {
    return TRBSYS_SYNCM_CNT;
  }

  int TRBSYS_Get_SYNCP_CNT(void)
  {
    return TRBSYS_SYNCP_CNT;
  }

  int TRBSYS_Get_SYNCI_CNT(void)
  {
    return TRBSYS_SYNCI_CNT;
  }

  void TRBSYS_Clear_SYNCP_CNT(void)
  {
    TRBSYS_SYNCP_CNT = 0;
  }
#endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

  void TRBSYS_SetSystemRegister(int regID, int selID, unsigned int val)
  {
    TRBSYS_SystemRegister[regID][selID][TRBSYS_Intrinsics_GetRegisterSetIndex()] = val;
  }

#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  void TRBSYS_SetSystemRegister(uint32 coproc, uint32 opcode1, uint32 val, uint32 CRn, uint32 CRm, uint32 opcode2)
  {
    TRBSYS_SystemRegister_STMStellar[opcode1][CRn][CRm][opcode2][TRBSYS_Intrinsics_GetRegisterSetIndex()] = val;
  }
  void TRBSYS_SetSystemRegister64(uint32 coproc, uint32 opcode, uint64 val64, uint32 CRm)
  {
    TRBSYS_SystemRegister_STMStellar[opcode][0][CRm][0][TRBSYS_Intrinsics_GetRegisterSetIndex()] = val64;
  }

#endif


void RBSYS_DI(void)
{

}

void RBSYS_EI(void)
{

}


uint64 TRBSYS_SystemRegister_STMStellar[OPCODE1_MAX][CRN_MAX][CRM_MAX][OPCODE2_MAX][RB_NUM_CORES] = {
  /*[15]*/[0][0][0][5][0] = 0, /* Core0 -> MPIDR -> MPIDR.Aff1 = 0, MPIDR.Aff0 = 0 */
  #if( RBFS_MCORE == RBFS_MCORE_ON )
    /*[15]*/[0][0][0][5][1] = 1, /* Core0 -> MPIDR -> MPIDR.Aff1 = 0, MPIDR.Aff0 = 1 */
  #endif
};

uint32 RBSYS_MRC(uint32 coproc, uint32 opcode1, uint32 CRn, uint32 CRm, uint32 opcode2)
{
  return TRBSYS_SystemRegister_STMStellar[opcode1][CRn][CRm][opcode2][TRBSYS_Intrinsics_GetRegisterSetIndex()];
}

uint32 RBSYS_MRRC(uint32 coproc, uint32 opcode, uint32 CRm)
{
  return TRBSYS_SystemRegister_STMStellar[opcode][0][CRm][0][TRBSYS_Intrinsics_GetRegisterSetIndex()];
}


TRBSYS_SystemRegister_WriteAccess TRBSYS_SystemRegister_STMStellar_WriteAccesses[4000] = {0};
uint32 TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx = 0;

void RBSYS_MCR(uint32 coproc, uint32 opcode1, uint32 val, uint32 CRn, uint32 CRm, uint32 opcode2)
{
  TRBSYS_SystemRegister_STMStellar[opcode1][CRn][CRm][opcode2][TRBSYS_Intrinsics_GetRegisterSetIndex()] = val;

  TRBSYS_SystemRegister_STMStellar_WriteAccesses[TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx].coproc   = coproc;
  TRBSYS_SystemRegister_STMStellar_WriteAccesses[TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx].opcode1  = opcode1;
  TRBSYS_SystemRegister_STMStellar_WriteAccesses[TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx].val      = val;
  TRBSYS_SystemRegister_STMStellar_WriteAccesses[TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx].CRn      = CRn;
  TRBSYS_SystemRegister_STMStellar_WriteAccesses[TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx].CRm      = CRm;
  TRBSYS_SystemRegister_STMStellar_WriteAccesses[TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx].opcode2  = opcode2;

  TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx++;
}

void RBSYS_MCRR(uint32 coproc, uint32 opcode, uint64 val64, uint32 CRm)
{
  TRBSYS_SystemRegister_STMStellar[opcode][0][CRm][0][TRBSYS_Intrinsics_GetRegisterSetIndex()] = val64;

  TRBSYS_SystemRegister_STMStellar_WriteAccesses[TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx].coproc   = coproc;
  TRBSYS_SystemRegister_STMStellar_WriteAccesses[TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx].opcode1  = opcode;
  TRBSYS_SystemRegister_STMStellar_WriteAccesses[TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx].val      = val64;
  TRBSYS_SystemRegister_STMStellar_WriteAccesses[TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx].CRn      = 0;
  TRBSYS_SystemRegister_STMStellar_WriteAccesses[TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx].CRm      = CRm;
  TRBSYS_SystemRegister_STMStellar_WriteAccesses[TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx].opcode2  = 0;

  TRBSYS_SystemRegister_STMStellar_WriteAccesses_Idx++;
}

static uint32 TRBSYS_VirtualMachineSpecialRegisters_STMStellar[20];
void RBSYS_VMSR(uint32 regnum, uint32 val) {
  TRBSYS_VirtualMachineSpecialRegisters_STMStellar[regnum] = val;
}

static uint32 TRBSYS_DSB_Cnt = 0;
void RBSYS_DSB(void){ TRBSYS_DSB_Cnt++; }
uint32 TRBSYS_Get_DSB_Cnt(void)
{
  return TRBSYS_DSB_Cnt;
}

static uint32 TRBSYS_ISB_Cnt = 0;
void RBSYS_ISB(void){TRBSYS_ISB_Cnt++; }
uint32 TRBSYS_Get_ISB_Cnt(void)
{
  return TRBSYS_ISB_Cnt;
}

int RBSYS_LDREX(const int* addr)
{
  return 0;
}

int RBSYS_STREX(int value, int* addr)
{
  return 0;
}

void RBSYS_HVC(int code)
{

}

void RBSYS_CLREX(void){}