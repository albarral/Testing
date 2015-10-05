package zebralabels;

import java.util.Date;
import java.util.Vector;
import java.text.SimpleDateFormat;

/**
 *
 * @author albarral
 */

public class LabelCode 
{
    private static String zplLabelStart;
    private static String zplLabelEnd;    
    private static String zplTextFormat;
    private static String zplCodeFormat;
    private static int fieldX;
    private static int fieldY0;
    private static int fieldH;
    private String zplCommand;
    private Vector<String> vecFields;
    private String sCode;
    int counter;
    String sPlaza;    
    SimpleDateFormat dateFormat;
    
    LabelCode ()            
    {
        counter = 0;
        //dateFormat = new SimpleDateFormat ("yyMMddHHmmss");   // 12 characters                      
        dateFormat = new SimpleDateFormat ("dd-MM-yyyy HH:mm:ss");
        vecFields = new Vector<String>();
        sCode = "";
    }

    public static void setLabelFormat (int xpos, int ypos, int codeHeight)            
    {
        // label format
        zplLabelStart = "^XA";
        zplLabelEnd = "^XZ";
        fieldX = xpos;
        fieldY0 = ypos;
        fieldH = codeHeight;        
        zplCodeFormat = "^BY2^B3N,N,"+Integer.toString(codeHeight)+",Y,N";         // Code 11 bar code (ZPL guide pag. 17)
        zplTextFormat = "^ADN,18,10";        // just text
    }

    public void addField(String sText) 
    {
        vecFields.add(sText);
    }
    
    public void addCode(String sText) 
    {
        sCode = sText;
    }

    public String buildZPLCommand() 
    {        
        zplCommand = zplLabelStart;
        
        // build fields from vector         
        int fieldY = fieldY0;
        for (int i = 0; i < vecFields.size(); i++)
        {
            zplCommand += buildZPLField(fieldY, 0, vecFields.get(i));
            // prepare for new line
            fieldY += fieldH;
        }
        
        if (!sCode.isEmpty())
        {
            zplCommand += buildZPLField(fieldY, 1, sCode);            
        }
        
        zplCommand += zplLabelEnd;              
  
        return (zplCommand);
    }
    
    
    private String buildZPLField(int fieldY, int type, String data) 
    {
        String zplFieldPos = "^FO"+Integer.toString(fieldX)+","+Integer.toString(fieldY);
        
        String zplFieldFormat = "";
        switch (type)
        {
            // text 
            case 0:
                zplFieldFormat = zplTextFormat; 
                break;
            case 1:
                zplFieldFormat = zplCodeFormat; 
                break;
                
        }
        String zplFieldData = "^FD"+data+"^FS";            
        String zplField = zplFieldPos+zplFieldFormat+zplFieldData;
        
        return (zplField);
    }
    
    
    public void setPlaza(String plaza)
    {
        sPlaza = plaza;
    }

    public String obtainBagCode() 
    {
        counter++;
        if (counter == 100)
            counter = 0;

        String sCounter = String.format("%02d", counter);
        
        // utilizar fecha para crear nuevo codigo 
        Date dateNow = new Date();
        String sBagCode = sPlaza+dateFormat.format (dateNow)+sCounter;                
        System.out.println("Codigo = " + sBagCode);
         
        return (sBagCode);
    }

    public String getDateString(Date date) 
    {
        return (dateFormat.format (date));
    }

}
