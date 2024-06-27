using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DPP = com.bosch.Diamant.Plugins;

namespace DiagDocu10
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var debugger = DPP.Debug.PluginDebugger.Create(
                @"C:\MTC10Tools\DiamantPro\V3_4_r1623",
                @"E:\ISW\Dev\ISWDevSB\HWRef",
                "--RELAXED", @"--READSPLITTER=Gen\EV7133xD5EDxMCxEMUxAPBxEPSW\make\Cfg_DBFiles_GenMake.csv",
                @"--IMPORTUSEDFLAGS=Gen\EV7133xD5EDxMCxEMUxAPBxEPSW\src_out\diamantpro\diamantpro_fwused.pp"))
            {
                debugger.ExecutePlugin<Plugin>();
            }
        }
    }
}
