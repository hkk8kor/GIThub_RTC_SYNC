#include "RBSYS_UnsupportedHW.c"

#include "RBSYS_Config.h"

#include "TRBSYS_UnsupportedHW_Adaptor.h"

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  uint32 CallPrivate_RBSYS_getPRDNAME4MM6_PRDNAME2(void)
  {
      return RBSYS_uCProductName4MM6.DeviceID.prdname2;
  }
  
  uint32 CallPrivate_RBSYS_getPRDNAME4MM6_PRDNAME3(void)
  {
      return RBSYS_uCProductName4MM6.DeviceID.prdname3;
  }
  
  uint32 CallPrivate_RBSYS_getPRDNAME4MM6_PRDversion(void)
  {
      return RBSYS_uCProductName4MM6.DeviceID.version;
  }
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  uint32 CallPrivate_RBSYS_getPRDNAME4MM6_MIDR1(void)
  {
    return RBSYS_uCProductName4MM6.DeviceID.midr1;
  }

  uint32 CallPrivate_RBSYS_getPRDNAME4MM6_MIDR2(void)
  {
    return RBSYS_uCProductName4MM6.DeviceID.midr2;
  }
#endif

uint32 CallPrivate_RBSYS_getPRDNAME4MM6_CPUclock(void)
{
    return RBSYS_uCProductName4MM6.l_CpuClock;
}