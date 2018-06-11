
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
		
		 System.out.println("Testing with manually created scheme of 'http' and 'https'");
		 
		 String[] schemes = {"http","https"};
	     UrlValidator urlValidator = new UrlValidator(schemes);
	     boolean valueOf=urlValidator.isValid("http://www.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.log");
	     System.out.println("testing if 'http://www.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.log' is valid:");
	     System.out.println(valueOf);
	       
	     valueOf=urlValidator.isValid(" ");
	     System.out.println("testing if ' ' is valid:"); 
	     System.out.println(valueOf);
	     
	     System.out.println("testing if 'ftp://www.logoworks.com' is valid:");   
	     valueOf=urlValidator.isValid("ftp://www.logoworks.com");
	     System.out.println(valueOf);
	     
	     valueOf=urlValidator.isValid("abcdefg");
	     System.out.println("testing if 'abcdefg' is valid:");   
	     System.out.println(valueOf);
	     
	     valueOf=urlValidator.isValid("%%%%%%");
	     System.out.println("testing if '%%%%%%' is valid:");  
	     System.out.println(valueOf);
	     
	     valueOf=urlValidator.isValid("http://www.good.com");
	     System.out.println("testing if 'http://www.good.com' is valid:");  
	     System.out.println(valueOf);
	     
	     valueOf=urlValidator.isValid("https://www.good.com");
	     System.out.println("testing if 'https://www.good.com' is valid:");  
	     System.out.println(valueOf);
	     
	     String[] schemes2 = {"http2","https2"};
	     System.out.println("Testing with manually created scheme of 'http2' and 'https2'");
	     UrlValidator urlValidator2 = new UrlValidator(schemes2);
	     
	     valueOf=urlValidator2.isValid("http2://www.good.com");
	     System.out.println("testing if 'http2://www.good.com' is valid:");  
	     System.out.println(valueOf);
	     
	     valueOf=urlValidator2.isValid("https2://www.good.com");
	     System.out.println("testing if 'https2://www.good.com' is valid:");  
	     System.out.println(valueOf);
	     
	     
	     valueOf=urlValidator2.isValid("~~~~~~~~~~~~~~~~~~~~~");
	     System.out.println("testing if '~~~~~~~~~~~~~~~~~~~~~' is valid:");  
	     System.out.println(valueOf);
	    
	     System.out.println("Testing with default scheme of 'http' and 'https'");
	     UrlValidator urlValidator4 = new UrlValidator();
	     
	     valueOf=urlValidator4.isValid("http://www.logoworks.com");
	     System.out.println("testing if 'http://www.logoworks.com' is valid:"); 
	     System.out.println(valueOf);
	     
	     valueOf=urlValidator4.isValidScheme("http");
	     System.out.println("testing if 'http' is a valid scheme"); 
	     System.out.println(valueOf);
	     
	     valueOf=urlValidator4.isValidScheme("HTTP");
	     System.out.println("testing if 'HTTP' is a valid scheme");
	     System.out.println(valueOf);
	     
	     valueOf=urlValidator4.isValidScheme(null);
	     System.out.println("testing if null is a valid scheme");
	     System.out.println(valueOf);
	     
	 }
	public void testRegexExpectedSuccess()
	{
		System.out.println("Starting Regex Tests: basic test 1");
		UrlValidator pathTest = new UrlValidator();
		boolean pathTestVal;
		int testCount=0;
		int passCount=0;
		int failCount=0;
		String[] passSet= {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "-", ".", "_", "~", ":", "?", "@", "!", "$", "&", "'", "(", ")", "*", "+", ",", ";", "=", "."};
		for (int index=0; index < passSet.length; index++)
		{
			String newPath="/" + passSet[index];
			pathTestVal=pathTest.isValidPath(newPath) ;
			if (pathTestVal)
			{
				passCount++;
			}
			else
			{
				failCount++;
				System.out.println("incorrectly rejected " + newPath);
				
			}
			testCount++;
			 
		}	
		System.out.println(passCount + " out of " + testCount + " correctly passed, " + failCount + " incorrectly failed.");
	}
	public void testTildeRegex()
	{
		System.out.println("Continuing regex tests: tilde tests");
		UrlValidator pathTest = new UrlValidator();
		boolean pathTestVal;
		int testCount=0;
		int passCount=0;
		int failCount=0;
		String[] passSet= {"A~", "B~", "C~", "D~", "E~", "F~", "G~", "H~", "I~", "J~", "K~", "L~", "M~", "N~", "O~", "P~", "Q~", "R~", "S~", "T~", "U~", "V~", "W~", "X~", "Y~", "Z~", "a~", "b~", "c~", "d~", "e~", "f~", "g~", "h~", "i~", "j~", "k~", "l~", "m~", "n~", "o~", "p~", "q~", "r~", "s~", "t~", "u~", "v~", "w~", "x~", "y~", "z~", "0~", "1~", "2~", "3~", "4~", "5~", "6~", "7~", "8~", "9~", "-~", ".~", "_~", "~~", ":~", "?~", "@~", "!~", "$~", "&~", "'~", "(~", ")~", "*~", "+~", ",~", ";~", "=~", ".~"};
		for (int index=0; index < passSet.length; index++)
		{
			String newPath="/" + passSet[index];
			pathTestVal=pathTest.isValidPath(newPath) ;
			if (pathTestVal)
			{
				passCount++;
			}
			else
			{
				failCount++;
				System.out.println("incorrectly rejected " + newPath);
				
			}
			testCount++;
			 
		}	
		System.out.println(passCount + " out of " + testCount + " correctly passed, " + failCount + " incorrectly failed.");
	}
	public void testTildeRegexTwo()
	{
		System.out.println("Continuing regex tests: tilde tests 2");
		UrlValidator pathTest = new UrlValidator();
		boolean pathTestVal;
		int testCount=0;
		int passCount=0;
		int failCount=0;
		String[] passSet= {"A~A", "B~A", "C~A", "D~A", "E~A", "F~A", "G~A", "H~A", "I~A", "J~A", "K~A", "L~A", "M~A", "N~A", "O~A", "P~A", "Q~A", "R~A", "S~A", "T~A", "U~A", "V~A", "W~A", "X~A", "Y~A", "Z~A", "a~A", "b~A", "c~A", "d~A", "e~A", "f~A", "g~A", "h~A", "i~A", "j~A", "k~A", "l~A", "m~A", "n~A", "o~A", "p~A", "q~A", "r~A", "s~A", "t~A", "u~A", "v~A", "w~A", "x~A", "y~A", "z~A", "0~A", "1~A", "2~A", "3~A", "4~A", "5~A", "6~A", "7~A", "8~A", "9~A", "-~A", ".~A", "_~A", "~A~A", ":~A", "?~A", "@~A", "!~A", "$~A", "&~A", "'~A", "(~A", ")~A", "*~A", "+~A",",~A", ";~A", "=~A", ".~A"};
		for (int index=0; index < passSet.length; index++)
		{
			String newPath="/" + passSet[index];
			pathTestVal=pathTest.isValidPath(newPath) ;
			if (pathTestVal)
			{
				passCount++;
			}
			else
			{
				failCount++;
				System.out.println("incorrectly rejected " + newPath);
				
			}
			testCount++;
			 
		}	
		System.out.println(passCount + " out of " + testCount + " correctly passed, " + failCount + " incorrectly failed.");
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
	public void testStringSizeOneExpectSuccess()
	{
		System.out.println("Starting String Size One Partition Tests: URL Valid Schemes, expect all Succeed, otherwise note");
		String[] schemes = {"a","b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
	    UrlValidator urlValidator = new UrlValidator(schemes);
	    boolean valueOf;
	    int correctCount=0;
	    int numTests=0;
	    for (int index=0; index < schemes.length; index++)
	    {
	    	valueOf=urlValidator.isValidScheme(schemes[index]);
	    	if (valueOf)
		    {
		    	correctCount++;
		    }
		    else
		    {
		    	System.out.println("'" + schemes[index] + "' incorrectly rejected as a valid scheme");
		    }
	    	numTests++;
	    	valueOf=urlValidator.isValidScheme(schemes[index].toUpperCase());
	    	if (valueOf)
		    {
		    	correctCount++;
		    }
		    else
		    {
		    	System.out.println("'" + schemes[index].toUpperCase() + "' incorrectly rejected as a valid scheme");
		    }
	    	numTests++;
	    	
	    }
	    System.out.println( correctCount +" out of " + numTests+ " tests correctly passed");
	}
	public void testNumericSchemesExpectFailures()
	{
		System.out.println("Starting Scheme Numeric Partition Tests: expect all fail else note");
		String[] schemes = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
	    UrlValidator urlValidator = new UrlValidator(schemes);
	    boolean valueOf;
	    int correctCount=0;
	    int numTests=0;
	    for (int index = 0; index < schemes.length; index++)
	    {
	    	
	    	System.out.println("Testing  " + schemes[index]);
	    	valueOf=urlValidator.isValidScheme(schemes[index]);
	    	if (!valueOf)
	    	{
	    		correctCount++;
	    	}
	    	else
	    	{
	    		System.out.println(schemes[index] + " incorrectly accepted as a valid scheme");
	    	}
	    	numTests++;
	    	
	    }
	    
	    System.out.println( correctCount +" out of " + numTests+ " tests correctly rejected");
	}
	/*public void testBigStringsExpectFailure()
	{
		System.out.println("Starting Scheme Large Wrong String Partition Tests: expect all fail else note"); 
		String[] schemes = {"a b c d e f g h i j k l m n o p q r s t u v w x y z", "0123456789", "!@#$%^&*()_+=-{}|:><.,", "A12B3C4D3F5G6"};
		 UrlValidator urlValidator = new UrlValidator(schemes);
		 boolean valueOf;
		 int correctCount=0;
		 int numTests=0;
		 for (int index = 0; index < schemes.length; index++)
		{
		   System.out.println("Testing  " + schemes[index]);
		  	valueOf=urlValidator.isValidScheme(schemes[index]);
		   	if (!valueOf)
	    	{
	    		correctCount++;		    	
	    	}
		   	else
		   	{
		   		System.out.println(schemes[index] + " incorrectly accepted as a valid scheme");
		   	}
	    	numTests++;
		    	
		 }
		 System.out.println( correctCount +" out of " + numTests+ " tests correctly rejected");		 
		 
		 
	}*/
	/*
	public void testYourFifthPartition()
	{
		System.out.println("Starting Fifth Partition Tests: URL Valid Authority, expect all succeed, otherwise note"); 
		UrlValidator urlValidator = new UrlValidator();
	    //boolean valueOf=urlValidator.isValidAuthority("plato.example.com:80");
	    //System.out.println(valueOf);
	    
	    int correctCount=0;
	    int numTests=0;
	    if (valueOf)
	    {
	    	correctCount++;
	    }
	    else
	    {
	    	System.out.println("'plato.example.com:80' incorrectly rejected as an invalid authority");
	    }
	    numTests++;
	    valueOf=urlValidator.isValidAuthority("12plato.example.com:80");
	    if (!valueOf)
	    {
	    	correctCount++;
	    }
	    else
	    {
	    	System.out.println("'12plato' incorrectly rejected as a valid scheme");
	    }
	    numTests++;
	
	    System.out.println( correctCount +" out of " + numTests+ " tests correctly passed");
 		
	}
	public void testYourSixthPartition()
	{
		System.out.println("Starting Sixth Partition Tests: URL Valid Authority, expect all fail, otherwise note"); 
		UrlValidator urlValidator = new UrlValidator();
	   
		boolean valueOf=urlValidator.isValidAuthority(".example.com:80");
	    int correctCount=0;
	    int numTests=0;
	    if (valueOf)
	    {
	    	correctCount++;
	    }
	    else
	    {
	    	System.out.println("'.example.com:80' incorrectly accepted as a valid authority");
	    }
	    System.out.println( correctCount +" out of " + numTests+ " tests correctly failed");
		
	}
	public void testYourSeventhPartition()
	{
		System.out.println("Starting Seventh Partition Tests: URL Valid Authority Single Letter, expect all fail"); 
		
		UrlValidator urlValidator = new UrlValidator();
	    int correctCount=0;
	    int numTests=0;
	    if (!urlValidator2.isValidAuthority("a.b.c:80"))
	    {
	    	correctCount++;
	    }
	    else
	    {
	    	System.out.println("'a.b.z:80' incorrectly accepted as a valid authority");
	    }
	    numTests++;
	    if (!urlValidator2.isValidAuthority("d.e.f:80"))
	    {
	    	correctCount++;
	    }
	    else
	    {
	    	System.out.println("'d.e.f:80' incorrectly accepted as a valid authority");
	    }
	    numTests++;
	    System.out.println( correctCount +" out of " + numTests+ " tests correctly failed");
	
	}
	*/
	/*public void testAuthorities()
	{
		//UrlValidator urlValidator = new UrlValidator();
		//String[] testUs= {"a.b.com", "pla"}
		
	}*/
	/*public void testAuthority()
	{
		UrlValidator urlValidator = new UrlValidator();
		String[] topPart= {"a","b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
		String[] middlePart = {"a","b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
		String[] bottomPartValid= {"com", "org", "gov", "edu", "abc"};
		int largestPort=65535;
		boolean valueOf;
		int testCounter=0;
		int correctCounter=0;
		for (int index=0; index < topPart.length-1; index++ )
		{
			for (int port=0; port <= largestPort; port++ )
			{
				for (int validBottom=0; validBottom < 5; validBottom++)
				{
					String newAuth=topPart[index]+"."+middlePart[index+1]+"."+bottomPartValid[validBottom]+":"+Integer.toString(port);
					valueOf=urlValidator.isValid(newAuth);
					
					if (valueOf)
					{
						correctCounter++;
					}	
					else
					{
						System.out.println(newAuth+ " was incorrectly rejected: " + valueOf);
					}
					testCounter++;
					
				}
				
			}
		}	
		System.out.println( correctCounter +" out of " + testCounter+ " tests correctly passed");	
	}*/
	/*public void testAuthorityInvalid()
	{
		UrlValidator urlValidator = new UrlValidator();
		String[] topPart= {"a","b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
		String[] middlePart = {"a","b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
		String[] bottomPartInvalid = {"bcd", "cde", "def", "efg", "fgh", "ghi", "hij", "ijk", "jkl", "klm", "lmn", "mno", "nop", "opq", "opq", "pqr", "qrs", "rst", "stu", "tuv", "uvw", "vwx","wxy", "xyz", "yza", "zab"};
		int largestPort=65535;
		boolean valueOf;
		int testCounter=0;
		int correctCounter=0;
		for (int index=0; index < topPart.length-1; index++ )
		{
			for (int port=0; port <= largestPort; port++ )
			{
				for (int invalidBottom=0; invalidBottom < 4; invalidBottom++)
				{
					String newAuth=topPart[index]+"."+middlePart[index+1]+"."+bottomPartInvalid[invalidBottom]+":"+Integer.toString(port);
					valueOf=urlValidator.isValid(newAuth);
					if (!valueOf)
					{
						correctCounter++;
					}	
					else
					{
						System.out.println(newAuth+ "was incorrectly accepted " + valueOf);
					}
					testCounter++;
					
				}
				
			}
		}	
		System.out.println( correctCounter +" out of " + testCounter+ " tests correctly passed");	
	}*/
	
	//You need to create more test cases for your Partitions if you need to 
	public void testIsValid()
	{
		System.out.println("Starting Programming Based Tests using a UrlCheck function"); 
		System.out.println("Testing with Default Schemes");
		UrlValidator validate = new UrlValidator();
		   
		   UrlCheck[] sampleUrls = {
				   new UrlCheck (validate, "http://www.google.com", true),
				   new UrlCheck (validate, "http://www.oregonstate.edu", true),
				   new UrlCheck (validate, "http://www.yahoo.com", true),
				   new UrlCheck (validate, "https:google.com", true),
				   new UrlCheck (validate, "http", false),
				   new UrlCheck (validate, "https:", false),
				   new UrlCheck (validate, "http!!!//www.google.com:", false),
				   new UrlCheck (validate, "http://www.bunny.com/~bunny", true),
				   new UrlCheck (validate, "http://www.bunny.com/bunny~", true),
				   new UrlCheck (validate, "http://www.bunny.com~/bunny", false),
				   new UrlCheck (validate, "http://www.bunny.com/bunny", true),
				   new UrlCheck (validate, "https", false),
				   new UrlCheck (validate, "http:", false),
				   new UrlCheck (validate, "https!!!//www.google.com:", false),
				   new UrlCheck (validate, "https://www.bunny.com/~bunny", true),
				   new UrlCheck (validate, "https://www.bunny.com/bunny~", true),
				   new UrlCheck (validate, "https://www.bunny.com~/bunny", false),
				   new UrlCheck (validate, "https://www.bunny.com/bunny", true),
				   
		   };
		  processUrls(sampleUrls);
		
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
