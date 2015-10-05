package zebralabels;

import java.util.Date;
import java.text.SimpleDateFormat;
import org.apache.log4j.Logger;

public class PrintHandler
{
    private static String sPrinterName;
    private final static Logger logger_ = Logger.getLogger(PrintHandler.class);
 
    public static void setPrinter (String printerName)            
    {
        sPrinterName = printerName;
        logger_.info("Impresora de etiquetas: " + sPrinterName);
    }

    public Integer PrintLabel(String sSeal, String sTime, String sCollector, String sShift)
    {
        int ret; 
        int nLabels = 1; 
        
        logger_.info("");
        logger_.info("PrintLabel ... ");
        logger_.info("Bolsa: " + sSeal);
        logger_.info("Hora: " + sTime);
        logger_.info("Cobrador: " + sCollector);
        logger_.info("Turno: " + sShift);
                
        try
        {
            LabelPrinter oLabelPrinter = new LabelPrinter(sPrinterName);
            LabelCode oLabelCode = new LabelCode();

            // transform date format to label form
            SimpleDateFormat dateFormat = new SimpleDateFormat ("yyyyMMddHHmmss");        
            Date date = dateFormat.parse(sTime);
            String sDate = oLabelCode.getDateString(date);

            if (oLabelPrinter.findZebra() == 0) 
            {
                logger_.info("Lanzando impresión ...");

                oLabelCode.addField("Cobrador: "+sCollector);
                oLabelCode.addField("Fecha: "+sDate);
                oLabelCode.addField("Turno: "+sShift);
                oLabelCode.addCode(sSeal);
                String sZPL = oLabelCode.buildZPLCommand();

								int jobs1 = oLabelPrinter.checkPendingJobs();

                for (int i = 0; i < nLabels; i++) 
                {
                    oLabelPrinter.printCode(sZPL, i + 1);
                }

								// We wait for 2 seconds to check if the printer is processing jobs
								// (workaround: I was not able to get the printer state)
								waitForSeconds(2);
								int jobs2 = oLabelPrinter.checkPendingJobs();																 
								int processed = jobs1 + nLabels - jobs2;								
								if (processed > 0)
								{
									logger_.info("Impresión OK!");
									ret = 0;									
								}
								else
								{
									logger_.error("La impresora no está imprimiendo!");
									ret = -1;									
								}
            }
            else 
            {
                logger_.error("Impresora no encontrada!");
                ret = -1;
            }
        }                  
        catch (Exception e) 
        {
             logger_.error("Impresión no realizada! - " + e.toString());
            ret = -1;
        }
                
        return (ret);
    }

		// this function waits for the specified seconds
		private void waitForSeconds(int delay_secs)
		{
			try
			{
				Thread.sleep(1000*delay_secs);
			}
			catch (InterruptedException ex)
			{
				Thread.currentThread().interrupt();
			}
		}

}
