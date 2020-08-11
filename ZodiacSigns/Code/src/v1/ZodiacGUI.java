package v1;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.ParseException;
import java.util.Date;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.border.LineBorder;
import javax.swing.border.TitledBorder;
import javax.swing.JPanel;

public class ZodiacGUI extends JFrame {
	JLabel dateInputLabel = new JLabel("Enter your birthday date MM/DD/YYYY format:");
	JTextField dateInput = new JTextField(10);
	JTextField zodiacOutput = new JTextField(10);
	JFrame personality = new JFrame();
	JLabel oldImage = new JLabel(new ImageIcon("DefaultProfilePic.jpg"));
	
	
	
public ZodiacGUI() {
	setupFrame();
	buildGUI();
	addTextListener();
	initiatePersonalityGUI();
}

private void setupFrame() {
	 this.setLocation(1000, 500);
	 this.setSize(400, 150);
	 this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	 this.setTitle("What's your Sign?");
	 this.setBackground(Color.DARK_GRAY);
	 this.getContentPane().setLayout(new BoxLayout(this.getContentPane(),BoxLayout.Y_AXIS));
	 this.setVisible(true);
}

private void buildGUI() {
	 zodiacOutput.setEditable(false);
	 JPanel topPanel = new JPanel();
	 topPanel.setLayout(new BoxLayout(topPanel,BoxLayout.X_AXIS));
	 topPanel.setBorder(new TitledBorder("Input Zodiac Sign"));
	 topPanel.add(dateInputLabel);
	 topPanel.add(dateInput);
	 topPanel.setBackground(new Color(250,230,230));
	 
	 JPanel zodiacPanel = new JPanel();
	 zodiacPanel.setBorder(new TitledBorder("Your Zodiac Sign"));
	 zodiacPanel.add(zodiacOutput);
	 zodiacPanel.setBackground(new Color(250,200,200));
	 
	 JPanel bottomPanel = new JPanel();
	 JPanel greyPanel1 = new JPanel();
	 JPanel greyPanel2 = new JPanel();
	 greyPanel1.setBackground(Color.DARK_GRAY);
	 greyPanel2.setBackground(Color.DARK_GRAY);
	 bottomPanel.setLayout(new BoxLayout(bottomPanel,BoxLayout.X_AXIS));
	 bottomPanel.add(greyPanel1);
	 bottomPanel.add(zodiacPanel);
	 bottomPanel.add(greyPanel2);
	 
	 JPanel projectContainer = new JPanel();
	 projectContainer.setBackground(Color.DARK_GRAY);
	 projectContainer.setBorder(new LineBorder(Color.DARK_GRAY,5));
	 projectContainer.add(topPanel);
	 
	 
	 this.add(projectContainer);
	 this.add(bottomPanel);
}
public void initiatePersonalityGUI() {
	personality.add(oldImage);
}

public void loadPersonality(String sign) {
	ImageIcon pic;
	switch(sign) {
	case "Aries":
			pic = new ImageIcon("Aries.png");
		break;
	case "Taurus":
			pic = new ImageIcon("Taurus.png");
		break;
	case "Gemini":
			pic = new ImageIcon("Gemini.png");
		break;
	case "Cancer":
			pic = new ImageIcon("Cancer.png");
		break;
	case "Leo":
			pic = new ImageIcon("Leo.png");
		break;
	case "Virgo":
			pic = new ImageIcon("Virgo.png");
		break;
	case "Libra":
			pic = new ImageIcon("Libra.png");
		break;
	case "Scorpio":
			pic = new ImageIcon("Scorpio.png");
		break;
	case "Sagittarius":
			pic = new ImageIcon("Sagittarius.png");
		break;
	case "Capricorn":
			pic = new ImageIcon("Capricorn.png");
		break;
	case "Aquarius":
		pic = new ImageIcon("Aquarius.png");
		break;
	case "Pisces":
			pic = new ImageIcon("Pisces.png");
		break;
	default:
			pic = new ImageIcon("DefaultProfilePic.jpg");
	}
	JLabel newImage = new JLabel(pic);
	personality.remove(oldImage);
	personality.add(newImage);
	oldImage = newImage;
	personality.setDefaultCloseOperation
	         (JFrame.EXIT_ON_CLOSE);
	  personality.pack();
	  personality.setVisible(true);
}
private class TextListener implements ActionListener{

	@Override
	public void actionPerformed(ActionEvent arg0) {
		String text = dateInput.getText();
		Date birthday = ZodiacTable.getBirthdate(text);
		try{
			ZodiacTable zodiac = new ZodiacTable();
			String sign = zodiac.determineSign(birthday);
			loadPersonality(sign);
			zodiacOutput.setText(sign);
		}
		catch(ParseException e){
			JOptionPane.showMessageDialog(null, "Error");
		}
		catch(NullPointerException n){
			JOptionPane.showMessageDialog(null, "Invalid Format");
		}
		}
		
	}
public void addTextListener(){
	dateInput.addActionListener(new TextListener());
}		
	
}
