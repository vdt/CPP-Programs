import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
/*
public class TT_GUI{
public static void main(String[] args){
        EventQueue.invokeLater(new Runnable()
        {
                public void run(){
                        myFrame frame=new myFrame();
                        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                        frame.setVisible(true);
                }
        });
}
}*/
class TT_GUI extends JFrame{

//to set title call to JFrame constructor

        TT_GUI(){
		super("Administrator Screen");
                setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
		setVisible(true);

		Container TTPanel = getContentPane();
		TTPanel.setLayout(new BorderLayout());
		page1rowA Trow = new page1rowA("Teachers: ", new String[] {
                        "Prateek Bhatia",
                        "Ajay Kumar",
                        "Varinder Singh"});
		JPanel TPanel = Trow.getPanel();
		TTPanel.add(TPanel);

		page1rowA Crow = new page1rowA("Courses: ", new String[] {
			"Computer Architecture",
			"Operating Systems"});
		JPanel CPanel = Crow.getPanel();
		TPanel.setBounds(25,25,300,40);

		CPanel.setBounds(25,75,300,40);
		TTPanel.add(CPanel);
//                add(TTPanel, BorderLayout.WEST);//adds TTPanel to the frame
//                Action1 InsertAction = new Action1();//                myCBox.addActionListener(actionTaker);              
//                btnTEdit.addActionListener(InsertAction);
        }
	public static void main(String[] args)
	{
		TT_GUI myFrame = new TT_GUI();
		myFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
        private static final int DEFAULT_WIDTH  = 400;
        private static final int DEFAULT_HEIGHT = 400;
                
}
/*class Action1 implements ActionListener{
        public void actionPerformed(ActionEvent event)
	{
		
                System.out.println("Event generated(comboBox)");
		String input1 = tf1.getText();
                        
                String input2= tf2.getText();
		myCBox.addItem(input1+" "+input2);
	}
}*/
class page1rowA{

	page1rowA(String LabelName,String[] CBoxOptions){
		
                JLabel myLabel = new JLabel(LabelName);
                JComboBox myCBox=new JComboBox(CBoxOptions);
		JPanel myInnerPanel = new JPanel();
		tf1 = new JTextField("input1..");
		tf2 = new JTextField("input2..");
		JButton btnTEdit = new JButton("Insert");//Insert Delete

                myInnerPanel.add(tf1);//add tf1 to myInnerPanel
                myInnerPanel.add(tf2);//add tf2 to myInnerPanel
                myInnerPanel.add(btnTEdit);//add btnTEdit to myInnerPanel			

                outerPanel.add(myLabel);//add faceLabel to TTPanel
                outerPanel.add(myCBox);//add faceCBox to TTPanel 
		outerPanel.add(myInnerPanel);//add inner panel to TTPanel
		
		
	}
	public JPanel getPanel(){
		return(outerPanel);
	}
//        private JComboBox myCBox;
	private JPanel outerPanel;
	public JTextField tf1;
	public JTextField tf2;
}
/*class rowFormat{
        public rowFormat(String name, String[] dropDownOptions){



//                ActionListener listener = new Dummy();

                //construct components///////////////
                JLabel faceLabel = new JLabel(name+": ");
		
                face=new JComboBox(dropDownOptions);

                face.addActionListener(new ActionListener(){
                        public void actionPerformed(ActionEvent event){
                        System.out.println("Event generated(comboBox)");
                        }
                });              //////////////////
	}               
        private JComboBox face;
}
*/
