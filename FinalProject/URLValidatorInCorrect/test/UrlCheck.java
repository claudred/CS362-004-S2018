/* UrlCheck is a based off ResultPair and utilized with our testing
 * to collect the errors we find while running our tests
 */
public class UrlCheck {
	public String url;
	public boolean expectedResult;
	
	public UrlCheck(String url, boolean expectedResult) {
		this.url = url;
		this.expectedResult = expectedResult;
	}
}

/*public class UrlCheck {
    public String url;
    public boolean expected;
    public boolean actual;

    public UrlCheck(UrlValidator validate, String url, boolean expected) {
    	this.url = url;
       this.expected = expected;
	   try {
		   this.actual = validate.isValid(url);
	   } catch (Throwable err) {
		   System.out.println("ERROR for " + url + "= " + err.getMessage());
	   }
       //this.actual = validate.isValid(url);
    }
    
    public String UrlCompareResults() {
       	System.out.println(this.url);
       	if (this.expected == this.actual) {
       		return "Result is as expected";	
       	}
       	else {
       		return "Result not expected";
       	}
       }
    public boolean Comparison() {
    	if(this.expected == this.actual)
    		return true;
    	else
    		return false;
    }
 }*/
