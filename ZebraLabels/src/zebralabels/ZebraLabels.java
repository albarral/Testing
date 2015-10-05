package zebralabels;

/**
 *
 * @author albarral
 */

import org.apache.log4j.Logger;
import org.apache.log4j.xml.DOMConfigurator;

public class ZebraLabels 
{
    private final static Logger logger_ = Logger.getLogger(ZebraLabels.class);		
    private final static String appVersion_ = "1.0-JL";

    public static void main(String[] args) 
    {
      LabelCode oLabelCode = null;
      LabelPrinter oLabelPrinter = null;
     
        try 
        {
            String log4jconfig = System.getProperty("log4j.configuration");
            DOMConfigurator.configure(log4jconfig);
            
            logger_.info(">>>>>>>>>>>>");
            logger_.info("Starting ZebraLabels v" + appVersion_ + " ...");            
            
            //Read config file:
            String cfgFilePath = System.getProperty("app.cfgFilePath");
            logger_.info("Reading config file: " + cfgFilePath);
            logger_.info("Log4j config file: " + log4jconfig);
            
            ZebraConfigFile oConfigData = new ZebraConfigFile(cfgFilePath);

            LabelCode.setLabelFormat(oConfigData.getCodeX(), oConfigData.getCodeY(), oConfigData.getCodeH());
           
            oLabelCode = new LabelCode();
            oLabelCode.setPlaza(oConfigData.getPlazaNumber());            
            oLabelPrinter = new LabelPrinter(oConfigData.getPrinterName());      
            
            ControlGUI oControlGUI = new ControlGUI(oLabelCode, oLabelPrinter, oConfigData);
            
            //RPCServer oServer = new RPCServer(oConfigData.getServerPort(), oConfigData.getPrinterName());
            //oServer.launch();   
        }
        catch (Exception e) 
        {
            logger_.error("ERROR: Failed to start ZebraLabels - " + e.toString());
            System.exit (1);
        }
    }
    
//    private void shutdown()
    public static void shutdown()
    {
            logger_.info("ZebraLabels service shutdown requested...");
            System.exit(0);
    }
}
