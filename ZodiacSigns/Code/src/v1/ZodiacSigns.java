package v1;
import java.text.SimpleDateFormat;
import java.text.ParseException;
import java.util.Date;
public class ZodiacSigns {
	private String sign;
	private Date startDate;
	private Date endDate;
	public ZodiacSigns(String sign, String startDate,String endDate) throws ParseException {
		SimpleDateFormat dateConversion = new SimpleDateFormat("MM/dd");
		this.sign = sign;
		this.startDate = dateConversion.parse(startDate);
		this.endDate = dateConversion.parse(endDate);
		
	}
	
	public String getSign() {
		return sign;
	}
	
	public void setSign(String sign) {
		this.sign = sign;
	}
	public Date getStartDate() {
		return startDate;
	}
	public void setStartDate(Date startDate) {
		this.startDate = startDate;
	}
	public Date getEndDate() {
		return endDate;
	}
	public void setEndDate(Date endDate) {
		this.endDate = endDate;
	}
	
	
}
