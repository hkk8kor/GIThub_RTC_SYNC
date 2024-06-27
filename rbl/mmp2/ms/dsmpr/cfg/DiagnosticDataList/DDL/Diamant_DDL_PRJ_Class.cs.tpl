using System;
using System.Xml;
using System.Collections.Generic;
using DDB = com.bosch.Diamant.Diagnosis;
using DPP = com.bosch.Diamant.Plugins;

public class DDL_PRJ
{
    public DDL_PRJ() { }
    public DDL_PRJ(CN.CALC_FAILURE_WORD fw, DiamantInterface ddb)

    {
        // Project specific DDL data
        CUS_DATA1 = ddb.CusData1(fw);
        CUS_DATA2 = ddb.CusData2(fw, calcDDB);
        CUS_DATA3 = ddb.CusData3(ddb.getDTC(fw, calcDDB));
        CUS_DATA4 = ddb.CusData4(ddb.getDTC(fw, calcDDB), calcDDB);
    }

    public string CUS_DATA1 { get; set; }
    public string CUS_DATA2 { get; set; }
    public string CUS_DATA3 { get; set; }
    public string CUS_DATA4 { get; set; }
}

public partial class DDBAccess
{
    // Project specific methods

    public string CusData1(CN.CALC_FAILURE_WORD fw)
    {
        Ctx.IO.ConsoleWrite("info", "CusData1"); // Used for debugging. Accepted values - error, info, warning
        return "CusData1";
    }
    public string CusData2(CN.CALC_FAILURE_WORD fw, CN.DIAGNOSIS calcDDB)
    {
        return "CusData2";
    }
    public string CusData3(CN.CALC_DTC dtc)
    {
        return "CusData3";
    }
    public string CusData4(CN.CALC_DTC dtc, CN.DIAGNOSIS calcDDB)
    {
        return "CusData4";
    }
}