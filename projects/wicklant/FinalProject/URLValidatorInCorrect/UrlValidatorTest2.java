import junit.framework.TestCase;
//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!
public class UrlValidatorTest extends TestCase 
{
	public UrlValidatorTest(String testName) 
	{
		super(testName);
	}
	/* Function for adding an item to a string array
	    * http://grails.asia/how-to-add-element-to-string-array-in-java 
	    */
	public static String[] add(String[] original, String newUrl)
	{
       int currentSize = original.length;
	   int newSize = currentSize + 1;
	   String[] temp = new String[ newSize ];
	   for (int i=0; i < currentSize; i++)
	   {
	        temp[i] = original [i];
	   }
	   temp[newSize- 1] = newUrl;
	   return temp;   
	}
	/* Function to iterate through urls and determine whether the 
	    * isValid function and urlValidator produces the expected outcome.
	    * If the results are as expected, url is added to list of 
	    * successful/passed tests. If not as expected, url is added to list
	    * of failed tests
	    */
	  public void processUrls (UrlCheck[] sampleUrls)
	  {
		   String[] urlsPassed = {};
		   String[] urlsFailed = {};
		   
		   for (int index = 0; index < sampleUrls.length; index++)
		   {
			   if (sampleUrls[index].Comparison() == true)
				  urlsPassed = add(urlsPassed, sampleUrls[index].url);
			   else
				   urlsFailed = add(urlsFailed, sampleUrls[index].url);
		   };
		   System.out.println("Tests Passed:");
		   for (String element: urlsPassed)
		   {
			   System.out.println(element);
		   }
		   System.out.println("\nTests Failed:");
		   for (String element: urlsFailed)
		   {
			   System.out.println(element);
		   }
	   }
	 
	public void testManualTest()
	{
		 
		System.out.println("Starting Manual Tests");
		
		 
		 String[] schemes = {"http","https"};
	     UrlValidator urlValidator = new UrlValidator(schemes);
	     boolean valueOf=urlValidator.isValid("http://www.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.log");
	     System.out.println(valueOf);
	     valueOf=urlValidator.isValid(" ");
	     System.out.println(valueOf);
	     valueOf=urlValidator.isValid("ftp://www.logoworks.com");
	     System.out.println(valueOf);
	     valueOf=urlValidator.isValid("abcdefg");
	     System.out.println(valueOf);
	     valueOf=urlValidator.isValid("%%%%%%");
	     System.out.println(valueOf);
	     String[] schemes2 = {"http2","https2"};
	     UrlValidator urlValidator2 = new UrlValidator(schemes2);
	     valueOf=urlValidator2.isValid("http://ww.logoworks");
	     System.out.println(valueOf);
	     valueOf=urlValidator2.isValid("http2://www.logoworks.com");
	     System.out.println(valueOf);
	     valueOf=urlValidator2.isValid("~~~~~~~~~~~~~~~~~~~~~");
	     System.out.println(valueOf);
	    
	    
	     UrlValidator urlValidator4 = new UrlValidator();
	     valueOf=urlValidator4.isValid("http://www.logoworks.com");
	     System.out.println(valueOf);
	     
	     valueOf=urlValidator4.isValidScheme("http");
	     System.out.println(valueOf);
	     
	     valueOf=urlValidator4.isValidScheme("HTTP");
	     System.out.println(valueOf);
	     
	     valueOf=urlValidator4.isValidScheme(null);
	     System.out.println(valueOf);
	     
	     System.out.println("Testing with Default Schemes");
		   UrlValidator validate = new UrlValidator();
		   
		   UrlCheck[] sampleUrls = {
				   new UrlCheck (validate, "http://www.google.com", true),
				   new UrlCheck (validate, "http://www.oregonstate.edu", true),
				   new UrlCheck (validate, "http://www.yahoo.com", true),
				   new UrlCheck (validate, "https:google.com", true)
				   
		   };
		  processUrls(sampleUrls);
	 }
	public void testYourFirstPartition()   
	{
		System.out.println("Starting First Partition Tests: Regex expected to fail");
		//You can use this function to implement your First Partition testing
		System.out.println("Starting First Partition Tests: Regex");
		UrlValidator UrlValidator5 = new UrlValidator();
		boolean valueOf2 =UrlValidator5.isValidPath("ab~~cd");
		int correctCount=0;
		int numTests=0;
		if (!valueOf2) 
		{
			 correctCount++;
		 }
		else
		{
			System.out.println("'ab~~cd' incorrectly passed");
		}
		numTests++;
		valueOf2 = UrlValidator5.isValidPath("abcd");
		if (!valueOf2) 
		{
			 correctCount++;
		}
		else
		{
			System.out.println("'abcd' incorrectly passed");
		}
		numTests++;
		valueOf2 =UrlValidator5.isValidPath("www.something.com");
		if (!valueOf2) 
		{
			 correctCount++;
		 }
		 else
		 {
			 System.out.println("'www.something.com' incorrectly passed");
		 }	
		numTests++;
		 valueOf2 =UrlValidator5.isValidPath("http:\\");
		 if (!valueOf2) 
		 {
				 correctCount++;
		 }
		 else
		 {
			 System.out.println("'http:\\' incorrectly passed");
		 }	
		 numTests++;
		valueOf2 =UrlValidator5.isValidPath("~/bunny");
		if (!valueOf2) 
		{
			correctCount++;
		}
		else 
		{
			 System.out.println("'~/bunny' incorrectly passed");
		}	
		numTests++;
		valueOf2 =UrlValidator5.isValidPath("//////");
		if (!valueOf2) 
		{
			 correctCount++;
		 }
		else 
		{
			System.out.println("'//////' incorrectly passsed");
		}
		numTests++;
		System.out.println( correctCount +" out of " + numTests+ " tests correctly failed");
		
		//You can use this function to implement your First Partition testing	   
	}
	public void testYourSecondPartition()
	{
		System.out.println("Starting Second Partition Tests: Regex; expected to pass"); 
		//You can use this function to implement your Second Partition testing	
		UrlValidator UrlValidator6 = new UrlValidator();
		boolean valueOf2 =UrlValidator6.isValidPath("/bunny");
		int correctCount=0;
		int numTests=0;
		
		if (valueOf2) 
		{
		 correctCount++;
		 }
		else 
		{
			System.out.println("'/bunny' incorrectly failed");
		}	
		numTests++;
		 valueOf2 =UrlValidator6.isValidPath("/~bunny");
		 if (valueOf2) 
		 {
			 correctCount++;
		 }
		 else 
		{
			System.out.println("'/~bunny' incorrectly failed");
		}
		 numTests++;
		valueOf2 =UrlValidator6.isValidPath("/bunny~");
		if (valueOf2) 
		{
			 correctCount++;
		 }
		else 
		{
			System.out.println("'/bunny~' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/bunny!");
		if (valueOf2) 
		{
			 correctCount++;
		 }
		else 
		{
			System.out.println("'/bunny!' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/bunny****");
		if (valueOf2) 
		{
			 correctCount++;
		 }
		else 
		{
			System.out.println("'/bunny*****' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/bunnybbbb4444$$$$$");
		if (valueOf2) 
		{
			 correctCount++;
		}
		else 
		{
			System.out.println("'/bunnybbbb4444$$$$$' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/@@@@@");
		if (valueOf2) 
		{
			 correctCount++;
		}
		
		else 
		{
			System.out.println("'/@@@@@@' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/*****");
		if (valueOf2) 
		{
			 correctCount++;
		}
		
		else 
		{
			System.out.println("'/****' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/&&&&&");
		if (valueOf2) 
		{
			 correctCount++;
		}
		else 
		{
			System.out.println("'/&&&&&' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/asdfgggg_222____");
		if (valueOf2) 
		{
			 correctCount++;
		}
		else 
		{
			System.out.println("'/asdfgggg_222____' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/asdf~gggg_222____");
		if (valueOf2) 
		{
			 correctCount++;
		}
		else 
		{
			System.out.println("'/asdf~gggg_222____' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/$+=-01245");
		if (valueOf2) 
		{
			 correctCount++;
		}
		else 
		{
			System.out.println("'/$+=-01245' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/$+=-~01245");
		if (valueOf2) 
		{
			 correctCount++;
		}
		else 
		{
			System.out.println("'/$+=-~01245' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/~");
		if (valueOf2) 
		{
			 correctCount++;
		}
		else 
		{
			System.out.println("'/~' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/");
		if (valueOf2) 
		{
			 correctCount++;
		}
		else 
		{
			System.out.println("'/' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("");
		if (valueOf2) 
		{
			 correctCount++;
		}
		else 
		{
			System.out.println("'' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/asdf?");
		if (valueOf2) 
		{
			 correctCount++;
		}
		else 
		{
			System.out.println("'/asdf?' incorrectly failed");
		}
		numTests++;
		valueOf2 =UrlValidator6.isValidPath("/asdf?$");
		if (valueOf2) 
		{
			 correctCount++;
		}
		else 
		{
			System.out.println("'/asdf?$' incorrectly failed");
		}
		numTests++;
		System.out.println( correctCount +" out of " + numTests+ " tests correctly passed");
			
	}
	public void testYourThirdPartition()
	{
		System.out.println("Starting Third Partition Tests: URL Valid Schemes, expect all pass, otherwise note"); 
		String[] schemes = {"http","https"};
	    UrlValidator urlValidator = new UrlValidator(schemes);
	    boolean valueOf=urlValidator.isValidScheme("HTTP");
	    int correctCount=0;
	    int numTests=0;
	    if (valueOf)
	    {
	    	correctCount++;
	    }
	    else
	    {
	    	System.out.println("'HTTP' incorrectly rejected as a valid scheme");
	    }
	    numTests++;
	    valueOf=urlValidator.isValidScheme("http");
	    if (valueOf)
	    {
	    	correctCount++;
	    }
	    else
	    {
	    	System.out.println("'http' incorrectly rejected as a valid scheme");
	    }
	    numTests++;
	    valueOf=urlValidator.isValidScheme("https");
	    if (valueOf)
	    {
	    	correctCount++;
	    }
	    else
	    {
	    	System.out.println("'https' incorrectly rejected as a valid scheme");
	    }
	    numTests++;
	    valueOf=urlValidator.isValidScheme("HTTPS");
	    if (valueOf)
	    {
	    	correctCount++;
	    }
	    else
	    {
	    	System.out.println("'HTTPS' incorrectly rejected as a valid scheme");
	    }
	    numTests++;
	    System.out.println( correctCount +" out of " + numTests+ " tests correctly passed");
	    
	    
	}
	public void testYourFourthPartition()
	{
		System.out.println("Starting Fourth Partition Tests: URL Valid Schemes, expect all fail, otherwise note"); 
		String[] schemes = {"httpX","httpsX"};
	    UrlValidator urlValidator = new UrlValidator(schemes);
	    boolean valueOf=urlValidator.isValidScheme("HTTP");
	    int correctCount=0;
	    int numTests=0;
	    if (!valueOf)
	    {
	    	correctCount++;
	    }
	    else
	    {
	    	System.out.println("'HTTP' incorrectly rejected as a valid scheme");
	    }
	    numTests++;
	    valueOf=urlValidator.isValidScheme("http");
	    if (!valueOf)
	    {
	    	correctCount++;
	    }
	    else
	    {
	    	System.out.println("'http' incorrectly rejected as a valid scheme");
	    }
	    numTests++;
	    valueOf=urlValidator.isValidScheme("https");
	    if (!valueOf)
	    {
	    	correctCount++;
	    }
	    else
	    {
	    	System.out.println("'https' incorrectly rejected as a valid scheme");
	    }
	    numTests++;
	    valueOf=urlValidator.isValidScheme("HTTPS");
	    if (!valueOf)
	    {
	    	correctCount++;
	    }
	    else
	    {
	    	System.out.println("'HTTPS' incorrectly rejected as a valid scheme");
	    }
	    numTests++;
	    System.out.println( correctCount +" out of " + numTests+ " tests correctly failed");
	    
	    
	}
	//You need to create more test cases for your Partitions if you need to 
	public void testIsValid()
	{
		System.out.println("Starting Programming Based Tests"); 
		
		//You can use this function for programming based testing
	}
	public void firstTests()
	{
		System.out.println("Hello, World");
    }	
	public static void main(String[] argv) 
	{
	 
		 UrlValidatorTest myTest = new UrlValidatorTest("myTest");
		 myTest.firstTests();

	}

}
