package zebralabels;

/**
 *
 * @author albarral
 */

import javax.print.Doc;
import javax.print.DocFlavor;
import javax.print.DocPrintJob;
import javax.print.PrintException;
import javax.print.PrintService;
import javax.print.PrintServiceLookup;
import javax.print.SimpleDoc;
import javax.print.attribute.*;
import javax.print.attribute.PrintServiceAttribute;
import javax.print.attribute.standard.PrinterName;
import javax.print.attribute.standard.PrinterState;
import javax.print.attribute.standard.QueuedJobCount;
import org.apache.log4j.Logger;

public class LabelPrinter 
{
    private final static Logger logger_ = Logger.getLogger(LabelPrinter.class);
    private PrintService psZebra;
    private String sPrinterName;

    LabelPrinter (String printerName)            
{
    sPrinterName = printerName;
}
     
// Search for Zebra printer
public int findZebra() 
{
     logger_.info("Buscando servicio de impresión ...");

    psZebra = null;
    String sPrinterName = null;
    PrintService[] services = PrintServiceLookup.lookupPrintServices(null, null);

    for (int i = 0; i < services.length; i++) 
    {
        PrintServiceAttribute attr = services[i].getAttribute(PrinterName.class);
        sPrinterName = ((PrinterName) attr).getValue();
        logger_.debug(sPrinterName);

        if (sPrinterName.contains(this.sPrinterName)) 
        {
            psZebra = services[i];
            logger_.info("Ok!");
            break;
        }
    }

    if (psZebra != null) 
    {
			return 0;
    }
    else
    {
         logger_.error("Servicio de impresión para Zebra no encontrado!");
        return -1;
    }
}

    
// Launch printing job
public void printCode(String sCode, int i) 
{
    try 
    {           
			 DocPrintJob job = psZebra.createPrintJob();

			 byte[] byteCode = sCode.getBytes();

			 DocFlavor flavor = DocFlavor.BYTE_ARRAY.AUTOSENSE;
			 Doc doc = new SimpleDoc(byteCode, flavor, null);

			 job.print(doc, null);
			 logger_.info("etiqueta " + i);
    } 
    catch (PrintException e) 
    {
         logger_.error("Error de impresión:");
        e.printStackTrace();  
    }    
}

public int checkPendingJobs()
{
	int jobs;

	if (psZebra == null)
		return -1;

	PrintServiceAttribute att = psZebra.getAttribute(QueuedJobCount.class);

	if (att == null)
	{
		jobs = -1;
		logger_.warn("jobs queu could not be read!");
	}
	else
	{
		String queu = att.toString();
		jobs = Integer.parseInt(queu);
		logger_.debug("cola = " + queu);
	}

	return jobs;
}

private void checkState(PrintService pService)
{
		String sState;
		PrintServiceAttribute attr = pService.getAttribute(PrinterState.class);

		if (attr == null)
		{
			logger_.warn("state =  null");
		}
		else
		{
			sState = ((PrinterState) attr).toString();
			logger_.debug("state = " + sState);
		}
}

private void checkAttributes(PrintService pService)
{
		AttributeSet attributes = pService.getAttributes();

		for (Attribute att : attributes.toArray())
		{
			String name = att.getName();
			String value = attributes.get(att.getClass()).toString();

			logger_.info(name + " " + value);
		}
}

}
