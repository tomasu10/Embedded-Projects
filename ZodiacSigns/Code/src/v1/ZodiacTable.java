package v1;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
public class ZodiacTable {
	private ArrayList<ZodiacSigns> zodiacArray = new ArrayList<ZodiacSigns>();
	
	public ZodiacTable() throws ParseException{
		ZodiacSigns Aries = new ZodiacSigns("Aries","03/21","04/19");
		ZodiacSigns Taurus = new ZodiacSigns("Taurus","04/20","05/20");
		ZodiacSigns Gemini = new ZodiacSigns("Gemini","05/21","06/20");
		ZodiacSigns Cancer = new ZodiacSigns("Cancer","06/21","07/22");
		ZodiacSigns Leo = new ZodiacSigns("Leo","07/23","08/22");
		ZodiacSigns Virgo = new ZodiacSigns("Virgo","08/23","09/22");
		ZodiacSigns Libra = new ZodiacSigns("Libra","09/23","10/22");
		ZodiacSigns Scorpio = new ZodiacSigns("Scorpio","10/23","11/21");
		ZodiacSigns Sagittarius = new ZodiacSigns("Sagittarius","11/22","12/21");
		ZodiacSigns Capricorn1 = new ZodiacSigns("Capricorn","12/22","12/31");
		ZodiacSigns Capricorn2 = new ZodiacSigns("Capricorn","01/01","01/19");
		ZodiacSigns Aquarius = new ZodiacSigns("Aquarius","01/20","02/18");
		ZodiacSigns Pisces = new ZodiacSigns("Pisces","02/19","03/20");
		zodiacArray.add(Aries);
		zodiacArray.add(Taurus);
		zodiacArray.add(Gemini);
		zodiacArray.add(Cancer);
		zodiacArray.add(Leo);
		zodiacArray.add(Virgo);
		zodiacArray.add(Libra);
		zodiacArray.add(Scorpio);
		zodiacArray.add(Sagittarius);
		zodiacArray.add(Capricorn1);
		zodiacArray.add(Capricorn2);
		zodiacArray.add(Aquarius);
		zodiacArray.add(Pisces);
		
	}
	
	public String determineSign(Date birthdate) {
		if(birthdate != null)
		{
		ZodiacSigns userSign = null;
		for(int i=0; i<zodiacArray.size();++i){
			ZodiacSigns checkedSign = zodiacArray.get(i);
			if(checkedSign.getStartDate().compareTo(birthdate)<=0 && checkedSign.getEndDate().compareTo(birthdate)>=0){
				userSign = checkedSign;
			}
		}
		return userSign.getSign();
		}
		else{
			return "Invalid Entry";
		}
	}
	
	
	protected static Date getBirthdate(String birthdateString){
		SimpleDateFormat signConversion = new SimpleDateFormat("MM/dd");
		signConversion.setLenient(false);
		try{
			Date stringDate = signConversion.parse(birthdateString);	
			return stringDate;
		}
		catch(ParseException e){
			return null;
			
		}
	}
}
