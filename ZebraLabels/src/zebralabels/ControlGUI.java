package zebralabels;

/**
 *
 * @author albarral
 */

import java.awt.*; 
import java.awt.event.*;
import javax.swing.*;

public class ControlGUI extends JFrame implements ActionListener
{
    private LabelCode mLabelCode;
    private LabelPrinter mLabelPrinter;
    private int numLabels; 
    // widgets
    private JPanel panelH;
    private JPanel panelV;
    private JLabel labelPlaza;
    private JButton buttonPrint;  
    private JLabel labelSelect;
    private JRadioButton radio1;
    private JRadioButton radio2;
    private JRadioButton radio3;
    private JRadioButton radio4;
    private static String sLabels1 = "1";
    private static String sLabels2 = "5";
    private static String sLabels3 = "10";
    private static String sLabels4 = "20";
  
  // the constructor
  ControlGUI (LabelCode oLabelCode, LabelPrinter oLabelPrinter, ZebraConfigFile oLabelConfigFile)   
  {
    super ("ZebraLabels - Impresión de etiquetas de liquidación"); 
 
    mLabelCode = oLabelCode;    
    mLabelPrinter = oLabelPrinter;
    numLabels = 1;
    
    int x=100;
    int y=100;
    int w=500;
    int h=400;
    int w2=200;
    int h2=380;
    int wb=150;
    int hb=100;
    int gap = 30;
        
    panelH = new JPanel();
    panelH.setLayout(new BoxLayout(panelH, BoxLayout.X_AXIS));

    panelV = new JPanel();
    panelV.setLayout(new BoxLayout(panelV, BoxLayout.Y_AXIS));
    panelV.setSize(w2, h2);

    labelPlaza = new JLabel("RUTA 160 - ESTACIÓN "+oLabelConfigFile.getPlazaNumber());
    labelPlaza.setAlignmentX(Component.CENTER_ALIGNMENT);

    buttonPrint = new JButton("Imprimir etiquetas");            
    buttonPrint.setSize(wb, hb);
    buttonPrint.setAlignmentX(Component.CENTER_ALIGNMENT);
    buttonPrint.requestFocus();
    
    labelSelect = new JLabel("Número de etiquetas a imprimir:");
    labelSelect.setAlignmentX(Component.CENTER_ALIGNMENT);
            
    radio1 = new JRadioButton(sLabels1);
    radio2 = new JRadioButton(sLabels2);
    radio3 = new JRadioButton(sLabels3);
    radio4 = new JRadioButton(sLabels4);
    radio1.setActionCommand(sLabels1);
    radio2.setActionCommand(sLabels2);
    radio3.setActionCommand(sLabels3);    
    radio4.setActionCommand(sLabels4);
    radio1.setMnemonic(KeyEvent.VK_1);
    radio2.setMnemonic(KeyEvent.VK_5);
    radio3.setMnemonic(KeyEvent.VK_0);
    radio4.setMnemonic(KeyEvent.VK_2);
    radio1.setAlignmentX(Component.CENTER_ALIGNMENT);
    radio2.setAlignmentX(Component.CENTER_ALIGNMENT);
    radio3.setAlignmentX(Component.CENTER_ALIGNMENT);
    radio4.setAlignmentX(Component.CENTER_ALIGNMENT);
    radio1.setSelected(true);
    ButtonGroup group = new ButtonGroup();
    group.add(radio1);
    group.add(radio2);
    group.add(radio3);
    group.add(radio4);

    // register button listeners
    buttonPrint.addActionListener(this);   
    radio1.addActionListener(this);   
    radio2.addActionListener(this);   
    radio3.addActionListener(this);   
    radio4.addActionListener(this);   

    panelV.add(labelPlaza); 
    panelV.add(Box.createRigidArea(new Dimension(0,gap)));
    panelV.add(buttonPrint); 
    panelV.add(Box.createRigidArea(new Dimension(0,gap)));
    panelV.add(labelSelect);
    panelV.add(Box.createRigidArea(new Dimension(0,gap)));
    panelV.add(radio1);
    panelV.add(radio2);
    panelV.add(radio3);
    panelV.add(radio4);
        
    panelH.add(Box.createHorizontalGlue());
    panelH.add(panelV);
    panelH.add(Box.createHorizontalGlue());
    
    setContentPane(panelH);

    UIManager.put("Button.defaultButtonFollowsFocus", Boolean.TRUE);
    
    setLocation(x,y);
    setSize(w,h);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);    
    setVisible(true); // make frame visible
  }
  
  // event handler
  public void actionPerformed(ActionEvent event)
  {
    Object source = event.getSource();
    if (source == buttonPrint)
    {               
        System.out.println("Buscar impresora ...");
        if (mLabelPrinter.findZebra() == 0)
        {
            System.out.println();
            System.out.println("Imprimir "+numLabels+" etiquetas ...");

            for (int i=0; i<numLabels; i++)
            {
                String sCode = mLabelCode.obtainBagCode();
                mLabelCode.addField(sCode);
                String sZPL = mLabelCode.buildZPLCommand();
                mLabelPrinter.printCode (sZPL, i+1);
            }
            
            System.out.println();
            System.out.println("Impresion finalizada!");            
        }
    }
    else 
    {
        numLabels = Integer.parseInt(event.getActionCommand());
        System.out.println("Num. etiquetas = " + numLabels);
        buttonPrint.requestFocus();
    }
                        
  }
  
}