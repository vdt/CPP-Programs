/*
 * GUI_QPDownloader.java
 *
 */

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Component;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.JScrollPane;
import javax.swing.JPanel;
import javax.swing.JTable;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.AbstractButton;
import javax.swing.table.TableCellRenderer;
import java.util.Vector;
import java.util.ArrayList;

class CheckBoxRenderer extends JCheckBox implements TableCellRenderer, ItemListener {
    public CheckBoxRenderer(Object course) {
		super((String)course);
		addItemListener(this);
    }
	
      public void itemStateChanged(ItemEvent itemEvent) {
        AbstractButton abstractButton = (AbstractButton)itemEvent.getSource();
        int state = itemEvent.getStateChange();
        if (state == ItemEvent.SELECTED) {
			//do stuff
        }
	  }
    
	public Component getTableCellRendererComponent(
                            JTable table, Object status,
                            boolean isSelected, boolean hasFocus,
                            int row, int column) {
        if(!(Boolean)status){
			setEnabled(false);
		}
        return this;
    }
}

public class GUI_QPDownloader extends JFrame{
    JButton dl_btn = new JButton("Download Selected");
	JTable table;
	
    public GUI_QPDownloader(String name) {
        super(name);
        //setResizable(false);
    }

    public void addComponentsToPane(final Container pane) {

		Object[] columnNames;
		Object[][] data;
	
		QPDownloader qpdown = new QPDownloader();
		columnNames = new String[qpdown.seasonPagesInfo.size()];
		int i=-1;
		for(SeasonPage sp: qpdown.seasonPagesInfo){
			columnNames[++i] = sp.toString();
		}
		//columnNames = 		(qpdown.seasonPagesInfo).toArray(columnNames);
		System.out.println(SeasonPage.courses.size()+" "+qpdown.seasonPagesInfo.size());
		data = new Boolean[SeasonPage.courses.size()][qpdown.seasonPagesInfo.size()];
		
		final ArrayList v = new ArrayList(SeasonPage.courses);
		table = new JTable(data, columnNames){
			public TableCellRenderer getCellRenderer(int row, int column) {
				return new CheckBoxRenderer(v.get(row));
			}
		};
		table.setFillsViewportHeight(true);

		int r=-1;
		for(String course: SeasonPage.courses){//for each course or row
			int c = -1;	++r;
			//System.out.println(course);
			for(SeasonPage season: qpdown.seasonPagesInfo){//for each season or col
				//if course  exits in season.coursesInfo.name then add JCheckBox
				boolean exists = false;
				for(CourseInfo ci: season.coursesInfo){
					if((ci.name).equals(course)){
						exists = true;
						break;
					}
				}
				if(exists){
					data[r][++c]=new Boolean(true);
				}else{
					data[r][++c]=new Boolean(false);
				}
			}
		}

		
		//controls
        JPanel controls = new JPanel();
		dl_btn.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
				//do stuff
            }
        });
        controls.add(dl_btn);
		
		pane.setLayout(new BorderLayout());
        pane.add(table.getTableHeader(), BorderLayout.PAGE_START);
        pane.add(new JScrollPane(table), BorderLayout.CENTER);
        pane.add(controls, BorderLayout.SOUTH);
    }

	public static void main(String[] args){
        /* Use an appropriate Look and Feel */
        try {
            UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
            //UIManager.setLookAndFeel("javax.swing.plaf.metal.MetalLookAndFeel");
        } catch (UnsupportedLookAndFeelException ex) {
            ex.printStackTrace();
        } catch (IllegalAccessException ex) {
            ex.printStackTrace();
        } catch (InstantiationException ex) {
            ex.printStackTrace();
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }
        /* Turn off metal's use of bold fonts */
        UIManager.put("swing.boldMetal", Boolean.FALSE);
        
        //Schedule a job for the event dispatch thread:
        //creating and showing this application's GUI.
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
				//Create and set up the window.
				GUI_QPDownloader frame = new GUI_QPDownloader("TU QPDownloader");
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				//Set up the content pane.
				frame.addComponentsToPane(frame.getContentPane());
				//Display the window.
				frame.pack();
				frame.setVisible(true);
            }
        });
	}
}