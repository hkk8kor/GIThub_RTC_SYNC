using System;
using System.Xml;
using System.Collections.Generic;
using System.Linq;
using DDB = com.bosch.Diamant.Diagnosis;
using DPP = com.bosch.Diamant.Plugins;
using GeneralLib;

public class DDL_PRJ
{

  public DDL_PRJ() { }
  public DDL_PRJ(CN.CALC_FAILURE_WORD fw, DiamantInterface ddb)
  {
        var dtc = ddb.getDTC(fw); 
		DTC_SIGNIFICANCE = ddb.DTCSignificance(dtc);
		NODE_HWSHUTDOWN_MMP = ddb.HWShutdownMMP(fw, ddb.m_Ddb);
		IMUSTATUS_MMP = ddb.getIMUStatus(fw, ddb.m_Ddb);
		IMUSTATUS_SPEC_FORCE = ddb.getIMUSpecForce(fw, ddb.m_Ddb);
		IMUSTATUS_RATE = ddb.getIMUStatusRate(fw, ddb.m_Ddb);
    // Project specific DDL data

  }
   
  
  	    public string DTC_SIGNIFICANCE { get; set; }
  	    public string NODE_HWSHUTDOWN_MMP { get; set; }
  	    public string IMUSTATUS_MMP { get; set; }
  	    public string IMUSTATUS_SPEC_FORCE { get; set;}
  	    public string IMUSTATUS_RATE { get; set;}

}

public partial class DiamantInterface
{
	
	public string DTCSignificance(CN.CALC_DTC dtc)
    {    
        var dtcAttributesValues = GetDtcAttribute(dtc);
        
        if (dtcAttributesValues != null)
        {
            return Tool.ReturnValidStr(dtcAttributesValues.EventSignificance, "-");
        }
        return "-";
    }
    
    public string HWShutdownMMP(CN.CALC_FAILURE_WORD fw, CN.DIAGNOSIS calcDDB)
    {
        var NodeName = getNode(fw);
        string HWShutdown = Tool.ReadKeyListValue(NodeName.KEYLIST, "HWShutdown", "NoHWShutdown");
        if (null != NodeName)
        {
            if (HWShutdown == "FailsafeActuation")
            {
                 return "NoHWShutdown";
            }
            else
            {
               return Tool.ReadKeyListValue(NodeName.KEYLIST, "HWShutdown");

            }
        }
        
        return "NoHWShutdown";
        
    }
   
    public string getIMUStatus(CN.CALC_FAILURE_WORD fw, CN.DIAGNOSIS calcDDB)
    {
        var NodeName = getNode(fw);
        
        if (NodeName.NAME == "Node_uC")
        {
           return "Not Applicable";
        }
        if (NodeName.NAME == "Node_Ecu")
        {
           return "Error_Permanent";
        }
        if (NodeName.NAME == "Node_uCMemoryGuard")
        {
           return "Error_Permanent";
        }
        if ((NodeName.NAME == "Node_MMP_SyncError") || (NodeName.NAME == "Node_MMP_ReInitError"))
        {
           return "Error_Permanent";
        }
       if (NodeName.NAME ==  "Node_MMP_Nvm_SigChnMonContents")
        {
           return "Error_Permanent";
        }
        if (NodeName.NAME == "Node_MMP_SignalChain" )
        {
           return "Error_Permanent";
        }     
        else
        {
           return "Operational";
        }   
           
    }
    
    public string getIMUSpecForce(CN.CALC_FAILURE_WORD fw, CN.DIAGNOSIS calcDDB)
    {
        var NodeName = getNode(fw);
        var ddb = new DiamantInterface(calcDDB);
        var dtc = ddb.getDTC(fw);
        var FW_NAME = ddb.FWName(fw); 
        var FW_list = new List<string>();
        var DTC_NAME = ddb.DTCName(dtc);  
        
        FW_list.Add(ddb.FWName(fw));
                      
        if (NodeName.NAME == "Node_uC")
        {
           return "Not Applicable";
        }
        if (DTC_NAME == "NOTASSIGNED")
        {
            return "valid";
        }
        
        if((NodeName.NAME == "Node_MMP_Nvm_SigChnMonContents") || (NodeName.NAME == "Node_MMP_SignalChain") || 
        (NodeName.NAME == "Node_MMP_SyncError") || (NodeName.NAME == "Node_MMP_ReInitError"))
        {
            return "Error_Permananent";
        }
 
        if((NodeName.NAME == "Node_MMP_CommunicationFailure") || (NodeName.NAME == "Node_MMP_SignalChainMonitors"))
        {
            var rate = FW_list.Contains("RBL_AmbientTemperatureFault");
            if(rate)
            {
                 return "Error_Temperature"; 
            }
            else
            {
                 return "Error_Sporadic";
            }
        }
        
        if((NodeName.NAME == "Node_MMP_SensorModuleError"))
        {
            var temp = FW_list.Any(i => i.Contains("RBL_TemperatureRangeExceeded_"));
            if(temp)
            {
                return "Error_Temperature";    
            }
        }
        
        // MechOverload DTC's with the FW RBL_MechOverload_Smux_Accx are set to Sporadic
        // and RBL_MechOverload_Smux_Ratex are set to Valid
        
        if ((DTC_NAME == "Imu_MechOverload"))
        {
            var rate = FW_list.Any(i => (i.Contains("_Rate1") || i.Contains("Smu1_Acc") || i.Contains("Smu2_Acc")));
            if(rate)
            {
                return "valid" ;
            }
            else
            {
                return "Error_Overload" ;
            }
        }
        
        // MechOverload DTC's with the FW RBL_ChannelInvalid_Smux_Accx are set to Permananent/Sporadic
        // and RBL_ChannelInvalid_Smux_Ratex are set to Valid
        
        if ((DTC_NAME == "Imu_SignalInvalid"))
        {
            var rate = FW_list.Any(i => (i.Contains("_Rate1") || i.Contains("Smu1_Acc") || i.Contains("Smu2_Acc")));
            if(rate)
            {
                return "valid" ;
            }
            else
            {
                return "Error_Permananent" +"/" + "Error_Sporadic" ;
            }
        }       
        
        else
        {
            return "valid";
        }
    }
    
    public string getIMUStatusRate(CN.CALC_FAILURE_WORD fw, CN.DIAGNOSIS calcDDB)
    {
        var NodeName = getNode(fw);
        var ddb = new DiamantInterface(calcDDB);
        var dtc = ddb.getDTC(fw);
        var FW_NAME = ddb.FWName(fw); 
        var FW_list = new List<string>();
        var DTC_NAME = ddb.DTCName(dtc);
        
        FW_list.Add(ddb.FWName(fw));
        
        if (NodeName.NAME == "Node_uC")
        {
           return "Not Applicable";
        }
        
        if (DTC_NAME == "NOTASSIGNED")
        {
            return "valid";
        }

        if((NodeName.NAME == "Node_MMP_Nvm_SigChnMonContents") || (NodeName.NAME == "Node_MMP_SignalChain") ||
         (NodeName.NAME == "Node_MMP_SyncError") || (NodeName.NAME == "Node_MMP_ReInitError") )
        {
                return "Error_Permananent";
        }
        
        if((NodeName.NAME == "Node_MMP_CommunicationFailure") || (NodeName.NAME == "Node_MMP_SignalChainMonitors"))
        {
            var rate = FW_list.Contains("RBL_AmbientTemperatureFault");
            if(rate)
            {
                 return "Error_Temperature"; 
            }
            else
            {
                 return "Error_Sporadic";
            }
        }
        
        if((NodeName.NAME == "Node_MMP_SensorModuleError"))
        {
            var temp = FW_list.Any(i => i.Contains("RBL_TemperatureRangeExceeded_"));
            if(temp)
            {
                return "Error_Temperature";    
            }
        }
    
        // MechOverload DTC's with the FW RBL_MechOverload_Smux_Accx are set to Valid
        // and RBL_MechOverload_Smux_Ratex are set to Sporadic
        
        if ((DTC_NAME == "Imu_MechOverload"))
        {
            var rate = FW_list.Any(i => i.Contains("_Rate1"));
            if(rate)
            {
                return "Error_Overload" ;
            }
            else
            {
                return "valid" ;
            }
        }
        
        // MechOverload DTC's with the FW RBL_ChannelInvalid_Smux_Accx are set to Valid
        // and RBL_ChannelInvalid_Smux_Ratex are set to Permananent/Sporadic
        
        if ((DTC_NAME == "Imu_SignalInvalid"))
        {
            var rate = FW_list.Any(i => i.Contains("_Rate1"));
            if(rate)
            {
                return "Error_Permananent" + "/" + "Error_Sporadic" ;
            }
            else
            {
                return "valid" ;
            }
        }          
        else
        {
            return "valid";
        }
    }

  // Project specific methods

}
