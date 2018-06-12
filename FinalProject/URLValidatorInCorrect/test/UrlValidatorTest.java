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
	public void printTest(boolean result, String query) 
	{
        if (result == true) {
            System.out.println('"' + query + '"' + " is VALID");
        } else {
            System.out.println('"' + query + '"' + " is INVALID");
        }
    }
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
	public static void printResult(String url, boolean actual, boolean expected)
	{
		if(actual == true)
			System.out.println("\"" + url + "\"" + " is true, should be " + expected);
		else if(actual == false)
			System.out.println("\"" + url + "\"" + " is false, should be " + expected);
		
	};
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
	public void testValidUrls()
	{
			System.out.println("Manual Url Valid Tests");
			UrlValidator urlValidator = new UrlValidator();
			String[] validUrls = {"http://norse.horse.edu:999","http://home.net.net:800","http://home.net.net:80","http://hhh.google.org","http://www.google.org","http://www.google.com", "https://www.google.com", "https://www.google.com:80", "https://www.facebook.com/~myProfile", "file://test1/file"};
			String[] invalidUrls= {"http://net.near.nor:888","http://net.near.nor:80","www.nice.net","abc.dox.com","abc.obf.com:199","https://wag.wig.gof/~absc/dddf","asdf://asdf.sss.ddd:88","123.123.123:80","http://hhh.google.ddd:900", "http://test1/file"};
			boolean valueOf;
			int correctCount = 0;
			int wrongCount= 0;
			for (int index=0; index < validUrls.length; index++)
			{
				valueOf=urlValidator.isValid(validUrls[index]);
				if (!valueOf)
				{
					System.out.println(validUrls[index] + " failed");
					wrongCount++;
				}
				else
				{
					
					correctCount++;
				}
				
			}
			System.out.println(correctCount + " passed " + wrongCount + " failed " );
			wrongCount=0;
			correctCount=0;
			for (int index=0; index < invalidUrls.length; index++)
			{
				valueOf=urlValidator.isValid(invalidUrls[index]);
				if (valueOf)
				{
					System.out.println(validUrls[index] + " passed");
					wrongCount++;
				}
				else
				{
					
					correctCount++;
				}
				
			}
			System.out.println(correctCount + " passed " + wrongCount + " failed " );
			
	} 
	/* Various schemes tested using 'google.com' as the path since manual testing showed this was valid */
	public void testSchemePartition()
	{
		//Default schemes: "http", "ftp", "https"
		System.out.println("SCHEME PARTITION");
		System.out.println("Testing default schemes with isValidScheme()");
		UrlValidator defaultScheme = new UrlValidator();
		printResult("http://", defaultScheme.isValid("http://google.com"), true);
		printResult("https://", defaultScheme.isValid("https://google.com"), true);
		printResult("ftp://", defaultScheme.isValid("fpt://google.com"), true); 
		printResult("ht3p://", defaultScheme.isValid("ht3p://google.com"), false); 
		printResult("://", defaultScheme.isValid("://google.com"), false); 
	
		System.out.println("Testing manual schemes with isValidScheme()");
		System.out.println("Manual schemes 'ht3p://', 'file://', 'http://'");
		String[] ourSchemes = {"ht3p://","file://", "http://"};
	    UrlValidator manualSchemes = new UrlValidator(ourSchemes);
		printResult("http://", manualSchemes.isValid("http://google.com"), true); 
		printResult("https://", manualSchemes.isValid("https://google.com"), false); 
		printResult("file://", manualSchemes.isValid("file://google.com"), true); 
		printResult("ht3p://", manualSchemes.isValid("ht3p://google.com"), true); 
		printResult("://", manualSchemes.isValid("://google.com"), false); 
	     
		System.out.println("Testing ALLOW_ALL_SCHEMES with isValidScheme()");
		UrlValidator allSchemes = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES); 
		try {
			printResult("http://", allSchemes.isValid("http://google.com"), true); 
		} catch (Throwable err) {
			   System.out.println("ERROR with " + "http://" + err.getMessage());
		   }
		try {
			printResult("https://", allSchemes.isValid("https://google.com"), true); 
		} catch (Throwable err) {
			   System.out.println("ERROR with " + "https:// " + err.getMessage());
		   }
		try {
			printResult("ftp://", allSchemes.isValid("ftp://google.com"), true); 
		} catch (Throwable err) {
			   System.out.println("ERROR with " + "ftp:// " + err.getMessage());
		   }
		try {
			printResult("ht3p://", allSchemes.isValid("ht3p://google.com"), true);  
		} catch (Throwable err) {
			   System.out.println("ERROR with " + "ht3p:// " + err.getMessage());
		   }
		try {
			printResult("://", allSchemes.isValid("://google.com"), false);   
		} catch (Throwable err) {
			   System.out.println("ERROR with " + ":// " + err.getMessage());
		   }
		try {
			printResult("", allSchemes.isValid("google.com"), false);   
		} catch (Throwable err) {
			   System.out.println("ERROR with " + " " + err.getMessage());
		   }
	}
	
	/* Various authorities using 'http://' as this was seen to be valid from schemePartition */
	public void testAuthorityPartition()
	{
		UrlValidator authorityTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		System.out.println("AUTHORITY PARTITION");
		System.out.println("Testing valid authorities");
		printResult("www.google.com", authorityTest.isValid("http://www.google.com"), true);
		printResult("google.com", authorityTest.isValid("http://google.com"), true);
		printResult("oregonstate.edu", authorityTest.isValid("http://oregonstate.edu"), true);
		printResult("123.122.123.124", authorityTest.isValid("http://123.122.123.124"), true);
		printResult("255.255.255.255", authorityTest.isValid("http://255.255.255.255"), true); //boundary case
		printResult("0.0.0.0", authorityTest.isValid("http://0.0.0.0"), true); //boundary case
		
		System.out.println("Testing invalid authorities");
		printResult("google.", authorityTest.isValid("http://google."), false);
		printResult("google", authorityTest.isValid("http://google"), false);
		printResult("google.00", authorityTest.isValid("http://google.00"), false);
		printResult(".com", authorityTest.isValid("http://.com"), false);
		printResult("", authorityTest.isValid("http://"), false);
	}
	
	/* Using http://google.com as we know this is a valid scheme and authority */
	public void testPortPartition()
	{
		UrlValidator portTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		System.out.println("PORT PARTITION");
		System.out.println("Testing valid ports");
		printResult("", portTest.isValid("http://google.com"), true);
		printResult(":80", portTest.isValid("http://google.com:80"), true);
		printResult(":25", portTest.isValid("http://google.com:25"), true);
		printResult(":7315", portTest.isValid("http://google.com:7315"), true);
		printResult(":65535", portTest.isValid("http://google.com:65535"), true); //boundary case

		System.out.println("Testing invalid ports");
		printResult(":65536", portTest.isValid("http://google.com:65536"), false); 
		printResult(":-1", portTest.isValid("http://google.com:-1"), false);
		printResult(":abc3", portTest.isValid("http://google.com:abc3"), false);
		printResult(":154.2", portTest.isValid("http://google.com:154.2"), false);
	}
	
	/* Using http://www.google.com as we know this is a valid scheme, authority, and port (null) */
	public void testPathPartition()
	{
		UrlValidator pathTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		System.out.println("PATH PARTITION");
		System.out.println("Testing valid paths");
		printResult("", pathTest.isValid("http://google.com"), true);
		printResult("/path", pathTest.isValid("http://google.com/path"), true);
		printResult("/path/to/file", pathTest.isValid("http://google.com/path/to/file"), true);
		printResult("/path/", pathTest.isValid("http://google.com/path/"), true);
		printResult("/path~/", pathTest.isValid("http://google.com/path~/"), true);
		printResult("/path!/", pathTest.isValid("http://google.com/path!/"), true);
		printResult("/path$/", pathTest.isValid("http://google.com/path$/"), true);
		printResult("/path^/", pathTest.isValid("http://google.com/path^/"), true);
		printResult("/path&/", pathTest.isValid("http://google.com/path&/"), true);
		
		System.out.println("Testing invalid paths");
		printResult("//path", pathTest.isValid("http://google.com//path"), false);
		printResult("/path//to/file", pathTest.isValid("http://google.com/path//to/file"), false);
		printResult("/../", pathTest.isValid("http://google.com/../"), false);
	}
	/* Using http://www.google.com/path as we know this is a valid scheme, authority, and port (null), and path */
	public void testQueryPartition()
	{
		UrlValidator queryTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		System.out.println("QUERY PARTITION");
		System.out.println("Testing valid queries");
		printResult("", queryTest.isValid("http://google.com/path"), true);
		printResult("?foo=bar", queryTest.isValid("http://google.com/path?foo=bar"), true);
		printResult("?foo=bar&bar=baz", queryTest.isValid("http://google.com/path?foo=bar&bar=baz"), true);
		printResult("?", queryTest.isValid("http://google.com/path?"), true);
		
		System.out.println("Testing invalid queries");
		printResult("//foo%", queryTest.isValid("http://google.com/path//foo%"), false);
	}
	/*Print out strings of size one, all should succeed if the source code is correct, else indicates a problem. */
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
	/*All should fail if source code is correct, else indicates a problem*/
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
	/*All should succeed if source code is correct, else indicates a problem*/
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
		/*This is a continuation of tests after an issue with the tilde regex is recognized; all of these should pass but given the bug we thingk we have found we expec them to fail. */
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
		/*A second partition of regex tilde tests: This is a continuation of tests after an issue with the tilde regex is recognized; all of these should pass but given the bug we thingk we have found we expec them to fail. */
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
		public void testQueryPartOne() {
			// a null query should be a valid query
			UrlValidator urlVal = new UrlValidator();
			boolean valid = false;
			int passedTests = 0, failedTests = 0;

			System.out.println("Testing string with length 0 (null). Test expected to be valid");
			valid = urlVal.isValidQuery("");
			printTest(valid, "");
			if (valid == true) {
				passedTests++;
			} else {
				failedTests++;
			}
			System.out.println("Expected 1 passed test: ACTUAL PASSED = " + passedTests);
			System.out.println("Expected 0 failed tests: ACTUAL FAILED = " + failedTests);

		}

		public void testQueryPartTwo() {
			//partition for testing strings of length 1
			UrlValidator urlVal = new UrlValidator();
			boolean valid = false;
			int passedTests = 0, failedTests = 0;

			System.out.println("Testing valid queries of length 1. Tests expected to be valid");

			for (int i = 33; i < 127; i++) {
				String query = String.valueOf((char) i);
				valid = urlVal.isValidQuery(query);
				printTest(valid, query);
				if (valid == true) {
					passedTests++;
				} else {
					failedTests++;
				}
			}

			System.out.println("Testing invalid queries of length 1. Tests expected to be invalid");

			valid = urlVal.isValidQuery(" ");
			printTest(valid, " ");
			if (valid == false) {
				passedTests++;
			} else {
				failedTests++;
			}
			System.out.println("Expected 95 passed test: ACTUAL PASSED = " + passedTests);
			System.out.println("Expected 0 failed tests: ACTUAL FAILED = " + failedTests);
		}

		public void testQueryPartThree() {
			//partition for testing strings > 1 in length
			UrlValidator urlVal = new UrlValidator();
			boolean valid = false;
			int passedTests = 0, failedTests = 0;
			String[] queries = { "?action=view", "action=view", "$!@#$%^&*()_+-=[]}{|\\':;,<.>/?",
					"abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "1234567890", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890$!@#$%^&*()_+-=[]}{|\\':;,<.>/?" };

			//testing valid queries, should result in valid
			System.out.println("Testing valid queries of length > 1. Tests expected to be valid");
			for (int i = 0; i < queries.length; i++) {
				valid = urlVal.isValidQuery(queries[i]);
				printTest(valid, queries[i]);
				if (valid == true) {
					passedTests++;
				} else {
					failedTests++;
				}
			}

			//testing invalid queries, should be invalid
			System.out.println("Testing invalid queries of length > 1. Tests expected to be invalid");
			String[] invalidQueries = { "?action = view", " ? a c t i o n = v i e w", "action= view", " action=view",
					"                  ", "action =view" };

			for (int i = 0; i < invalidQueries.length; i++) {
				valid = urlVal.isValidQuery(invalidQueries[i]);
				printTest(valid, invalidQueries[i]);
				if (valid == false) {
					passedTests++;
				} else {
					failedTests++;
				}
			}
			System.out.println("Expected 13 passed test: ACTUAL PASSED = " + passedTests);
			System.out.println("Expected 0 failed tests: ACTUAL FAILED = " + failedTests);
	}
	/* testIsValid is a programming based testing suite.  It takes the 5 components
	 * (scheme, authority, port, path, and query) and generates urls that are then 
	 * tested with isValid to determine if the url is valid or invalid.  Results are
	 * displayed at the end and user can choose to display all urls of certain results 
	 * (ie all invalid urls that were true instead of false).  The user can also display
	 * all error messages. 
	 */
	public void testIsValid()
	{
		System.out.println("PROGRAMMING BASED TESTS"); 
		
		/* From RFC 3986 URI Generic Syntax -
		 * Schemes may include characters beginning with a letter
		 * and then followed by letters, digits, '+', '.', and/or '-'
		 * scheme      = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
		 *  https://tools.ietf.org/html/rfc3986 Section 3.1
		 *  Schemes should end with ://.  Null scheme should be valid 
		 */
		UrlCheck[] schemes = {
				new UrlCheck("http://", true),
				new UrlCheck("https://", true),
				new UrlCheck("ftp://", true),
				new UrlCheck("ht3p://", true),
				new UrlCheck("3http://", false),
				new UrlCheck("h%p://", false),
				new UrlCheck("://", false),
				new UrlCheck("http:", false),
				new UrlCheck("http/", false)		
		};
		
		/* Authority component is preceded by a '//'.  It is terminated
		 * by '/', '?', or '#'.  
		 * authority   = [ userinfo "@" ] host [ ":" port ]
		 * For this urlvalidator, port is not included in the authority.
		 * The host is composed of IP literal address or registered name.
		 * https://tools.ietf.org/html/rfc3986 Secton 3.2
		 */
		UrlCheck[] authority = {
				new UrlCheck("www.google.com", true),
				new UrlCheck("google.com", true),
				new UrlCheck("oregonstate.edu", true),
				new UrlCheck("123.122.123.124", true),
				new UrlCheck("255.255.255.255", true),
				new UrlCheck("google.", false),
				new UrlCheck("google", false),
				new UrlCheck("google.00", false),
				new UrlCheck(".com", false),
				new UrlCheck("", false)
		};
		
		/* Port component should begin with a single colon ':'.  
		 * It should be a decimal number
		 * port        = *DIGIT
		 * https://tools.ietf.org/html/rfc3986 Section 3.2.3
		 */
		UrlCheck[] port = {
				new UrlCheck("", true),
				new UrlCheck(":80", true),
				new UrlCheck(":25", true),
				new UrlCheck(":7315", true),
				new UrlCheck(":65535", true),
				new UrlCheck(":65536", false),
				new UrlCheck(":-1", false),
				new UrlCheck(":abc3", false),
				new UrlCheck(":154.2", false),
		};
		
		/* Path should begin with a '/' or be null.  It is terminated
		 * by a '?', '#', or end of URI. Cannot begin with '//' if URI
		 * contains authority component. 
		 * https://tools.ietf.org/html/rfc3986 Section 3.3 
		 */
		UrlCheck[] path = {
				new UrlCheck("", true),
				new UrlCheck("/path", true),
				new UrlCheck("/path/to/file", true),
				new UrlCheck("//path", false),
				new UrlCheck("/path//to/file", false),
				new UrlCheck("/../", false)
		};
		
		/* Query component should begin with a '?' and end with '#' or 
		 * end of URI.
		 * query       = *( pchar / "/" / "?" )
		 * https://tools.ietf.org/html/rfc3986 Section 3.4
		 */
		UrlCheck[] query = {
				new UrlCheck("?foo=bar", true),
				new UrlCheck("", true),
				new UrlCheck("?foo=bar&bar=baz", true),
				new UrlCheck("?", true),
				new UrlCheck("//foo%", false)
		};
		
		String[] validUrlsPassed = {};
		String[] invalidUrlsPassed = {};
		String[] validUrlsFailed = {};
		String[] invalidUrlsFailed = {};
		String[] Errors = {};
		
		String urlToTest;
		int totalTests = 0;
		boolean actual = false;
		boolean expected = true;
		
		for (int s = 0; s < schemes.length; s++)
		   {
			for(int a = 0; a < authority.length; a++)
			{
				for(int p = 0; p < port.length; p++)
				{
					for(int t = 0; t < path.length; t++)
					{
						for(int q = 0; q < query.length; q++)
						{
							urlToTest = schemes[s].url + authority[a].url + port[p].url + path[t].url + query[q].url;
							totalTests++;
							if(schemes[s].expectedResult == true && authority[a].expectedResult == true && port[p].expectedResult == true && path[t].expectedResult == true && query[q].expectedResult == true) {
								expected = true;
							}
							else
								expected = false;
							
							UrlValidator validate = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
							
							try {
								actual = validate.isValid(urlToTest);
							} catch (Throwable err) {
								   String error = "ERROR for " + urlToTest + "= " + err.getMessage();
								   Errors = add(Errors, error);
							   }
							
							if ( expected == true)
							   {
								   if (actual == true)
									   validUrlsPassed = add(validUrlsPassed, urlToTest);
								   else
									   validUrlsFailed = add(validUrlsFailed, urlToTest);
							   }
							   else if (expected == false)
							   {
								   if (actual == false)
									   invalidUrlsFailed = add(invalidUrlsFailed, urlToTest);
								   else
									   invalidUrlsPassed = add(invalidUrlsPassed, urlToTest);  
							   }
					}
				}
			}
		   }
		}
		System.out.println("Total Tests: " + totalTests);
		
		System.out.println("\n" + validUrlsPassed.length + "urls expected true and were true");
		//Uncomment to display all valid urls that passed
		/*System.out.println("Valid Url Tests Passed:");
		   for (String element: validUrlsPassed)
		   {
			   System.out.println(element);
		   }*/
		System.out.println("\n" + validUrlsFailed.length + " urls expected true and were false");
		System.out.println("\nValid Url Tests Failed:");
		for (String element: validUrlsFailed)
		{
			System.out.println(element);
		}
		
		System.out.println("\n" + invalidUrlsFailed.length + " urls expected false and were false");
		//Uncomment to display all invalid urls that failed
		/*System.out.println("\nInvalid Url Tests Failed:");
		for (String element: invalidUrlsFailed)
		{
			System.out.println(element);
		}*/
		
		System.out.println("\n" + invalidUrlsPassed.length + " urls expected false and were true");
		System.out.println("\nInvalid Url Tests Passed:");
		for (String element: invalidUrlsPassed)
		{
			System.out.println(element);
		}
		   
		System.out.println("\n" + Errors.length + " errors caught");
		
		//Uncomment to display all error messages caught
		/*System.out.println("\nErrors caught:");
		for (String element: Errors)
		{
			System.out.println(element);
		}*/
	
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
