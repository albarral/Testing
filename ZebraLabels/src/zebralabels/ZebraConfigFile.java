package zebralabels;

import java.io.File;
import java.io.IOException;
import util.ConfigFile;

/**
 *
 * @author albarral
 */

public class ZebraConfigFile extends ConfigFile
{
    private int rpcPort;
    private String sPlazaNumber;
    private String sPrinterName;
    private int sBarcodeX;   // dots
    private int sBarcodeY;   // dots
    private int sBarcodeH;   // dots

    public ZebraConfigFile(String cfgFilePath) throws Exception
    {
        super (cfgFilePath);
    }

    public ZebraConfigFile(File cfgFile) throws IOException, ConfigException, Exception
    {
        super (cfgFile);
    }

    protected void readInParameters() throws ConfigException
    {
        rpcPort = super.getIntParam("rpc.server.port");
        sPlazaNumber = super.getStringParam("plaza.number");
        sPrinterName = super.getStringParam("printer.service.name");
        sBarcodeX = super.getIntParam("barcode.xpos");
        sBarcodeY = super.getIntParam("barcode.ypos");
        sBarcodeH = super.getIntParam("barcode.height");
    }

    public int getServerPort()
    {
        return rpcPort;        
    }
    
    public String getPlazaNumber()
    {
        return  sPlazaNumber;
    }

    public String getPrinterName()
    {
        return sPrinterName;
    }

    public int getCodeX()
    {
        return sBarcodeX;
    }

    public int getCodeY()
    {
        return sBarcodeY;
    }

    public int getCodeH()
    {
        return sBarcodeH;
    }
};

