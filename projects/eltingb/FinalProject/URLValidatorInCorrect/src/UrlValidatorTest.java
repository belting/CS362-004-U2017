/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;

import java.util.ArrayList;
import java.util.List;


/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
   }
   
   
   public void testIsValid()
   {
       // Initialize URL validator
       UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       // Initialize URL parts
       List<ResultPair> schemes = new ArrayList<>();
       schemes.add(new ResultPair("http://", true));
       schemes.add(new ResultPair("http:/", false));
       schemes.add(new ResultPair("http:", false));
       schemes.add(new ResultPair("http", false));
       schemes.add(new ResultPair("https://", true));
       schemes.add(new ResultPair("ftp://", true));
       schemes.add(new ResultPair("smtp://", true));
       schemes.add(new ResultPair("123://", false));

       List<ResultPair> authorities = new ArrayList<>();
       authorities.add(new ResultPair("www.yahoo.com", true));
       authorities.add(new ResultPair("yahoo.com", true));
       authorities.add(new ResultPair("yahoo.co", true));
       authorities.add(new ResultPair("123.123.123.123", true));
       authorities.add(new ResultPair("256.256.256.256", false));
       authorities.add(new ResultPair(".123.123.123.123", false));
       authorities.add(new ResultPair("123.123.123.123.", false));
       authorities.add(new ResultPair("123.123.123", false));
       authorities.add(new ResultPair("123.com", true));
       authorities.add(new ResultPair(".com", false));

       List<ResultPair> ports = new ArrayList<>();
       ports.add(new ResultPair(":80", true));
       ports.add(new ResultPair(":12345", true));
       ports.add(new ResultPair(":", false));
       ports.add(new ResultPair("", true));

       List<ResultPair> paths = new ArrayList<>();
       paths.add(new ResultPair("/", true));
       paths.add(new ResultPair("/one", true));
       paths.add(new ResultPair("/one/", true));
       paths.add(new ResultPair("/one/two", true));
       paths.add(new ResultPair("/one/two/", true));
       paths.add(new ResultPair("", true));
       paths.add(new ResultPair("/..", false));

       List<ResultPair> queries = new ArrayList<>();
       queries.add(new ResultPair("", true));
       queries.add(new ResultPair("?", true));
       queries.add(new ResultPair("?one", true));
       queries.add(new ResultPair("?one=two", true));
       queries.add(new ResultPair("?one=two&three=4", true));

       // Loop through all combinations of URL parts
       schemes.forEach(scheme -> {
           authorities.forEach(authority -> {
               ports.forEach(port -> {
                   paths.forEach(path -> {
                       queries.forEach(query -> {
                           // Build URL
                           String url = String.format("%s%s%s%s%s", scheme.item, authority.item, port.item, path.item, query.item);

                           // Get expected and actual results
                           boolean expected = scheme.valid && authority.valid && port.valid && path.valid && query.valid;
                           boolean actual = urlValidator.isValid(url);

                           // Perform assertion
                           //assertEquals(url, expected, actual);

                           // Print results
                           if (expected == actual) {
                               System.out.println("PASS " + url);
                           } else {
                               System.out.println("FAIL " + url);
                           }
                       });
                   });
               });
           });
       });
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
