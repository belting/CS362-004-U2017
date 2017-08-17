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


    public void testManualTest() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        System.out.println(urlVal.isValid("http://www.amazon.com"));


    }


    public void testYourFirstPartition() {
        // Initialize URL validator
        UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        List<ResultPair> partitions = new ArrayList<>();
        partitions.add(new ResultPair("http://", true));
        partitions.add(new ResultPair("https://", true));
        partitions.add(new ResultPair("gopher://", true));
        partitions.add(new ResultPair("file://", true));
        partitions.add(new ResultPair("Imap://", true));
        partitions.add(new ResultPair("ipp://", true));
        partitions.add(new ResultPair("z39.50s://", true));
        partitions.add(new ResultPair("aaa://", true));
        partitions.add(new ResultPair("iris.beep://", true));
        partitions.add(new ResultPair("pkcs11://", true));
        partitions.add(new ResultPair("aaa", false));
        partitions.add(new ResultPair("http:", false));
        partitions.add(new ResultPair("http/", false));
        partitions.add(new ResultPair("http", false));
        partitions.add(new ResultPair("343sfa://", false));
        partitions.add(new ResultPair("!42Sd://", false));
        partitions.add(new ResultPair("0", false));
        partitions.add(new ResultPair("///", false));

        // Loop through all partitions
        partitions.forEach(partition -> {
            String url = String.format("%swww.google.com", partition.item);

            // Get expected and actual results
            boolean expected = partition.valid;
            boolean actual = urlValidator.isValid(url);

            // Print results
            if (expected == actual) {
                System.out.println("PASS " + url);
            } else {
                System.out.println("FAIL " + url);
            }
        });
    }

    public void testYourSecondPartition() {
        // Initialize URL validator
        UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        List<ResultPair> partitions = new ArrayList<>();
        partitions.add(new ResultPair("0.0.0.0", true));
        partitions.add(new ResultPair("somelink.com", true));
        partitions.add(new ResultPair("native.io", true));
        partitions.add(new ResultPair("reddit.com", true));
        partitions.add(new ResultPair("googlec.om", true));
        partitions.add(new ResultPair("supernova.org/", true));
        partitions.add(new ResultPair("nova.se", true));
        partitions.add(new ResultPair("www.fxyz.ru/", true));
        partitions.add(new ResultPair("255.255.255.255", true));
        partitions.add(new ResultPair("meg a.com", false));
        partitions.add(new ResultPair("a.b-.co", false));
        partitions.add(new ResultPair("test", false));
        partitions.add(new ResultPair("77", false));
        partitions.add(new ResultPair("256.256.256.256", false));
        partitions.add(new ResultPair(".255.255.255.255", false));
        partitions.add(new ResultPair("1.1.1.1..", false));
        partitions.add(new ResultPair("1.1.1.1.", false));
        partitions.add(new ResultPair("0", false));

        // Loop through all partitions
        partitions.forEach(partition -> {
            String url = String.format("http://%s:80", partition.item);

            // Get expected and actual results
            boolean expected = partition.valid;
            boolean actual = urlValidator.isValid(url);

            // Print results
            if (expected == actual) {
                System.out.println("PASS " + url);
            } else {
                System.out.println("FAIL " + url);
            }
        });
    }

    public void testYourThirdPartition() {
        // Initialize URL validator
        UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        List<ResultPair> partitions = new ArrayList<>();
        partitions.add(new ResultPair(":80", true));
        partitions.add(new ResultPair(":65535", true));
        partitions.add(new ResultPair(":0", true));
        partitions.add(new ResultPair(":012345", true));
        partitions.add(new ResultPair(":123456", false));
        partitions.add(new ResultPair(":65536", false));
        partitions.add(new ResultPair(":65636", false));
        partitions.add(new ResultPair("80", false));
        partitions.add(new ResultPair(":21AD", false));

        // Loop through all partitions
        partitions.forEach(partition -> {
            String url = String.format("http://www.google.com%s", partition.item);

            // Get expected and actual results
            boolean expected = partition.valid;
            boolean actual = urlValidator.isValid(url);

            // Print results
            if (expected == actual) {
                System.out.println("PASS " + url);
            } else {
                System.out.println("FAIL " + url);
            }
        });
    }

    public void testYourFourthPartition() {
        // Initialize URL validator
        UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        List<ResultPair> partitions = new ArrayList<>();
        partitions.add(new ResultPair("/", true));
        partitions.add(new ResultPair("/path", true));
        partitions.add(new ResultPair("/1234", true));
        partitions.add(new ResultPair("/k1234", true));
        partitions.add(new ResultPair("#Q$%%", false));
        partitions.add(new ResultPair("/path???/file name", false));
        partitions.add(new ResultPair("\\filename", false));
        partitions.add(new ResultPair("\\host/path/file", false));

        // Loop through all partitions
        partitions.forEach(partition -> {
            String url = String.format("http://www.google.com:80%s", partition.item);

            // Get expected and actual results
            boolean expected = partition.valid;
            boolean actual = urlValidator.isValid(url);

            // Print results
            if (expected == actual) {
                System.out.println("PASS " + url);
            } else {
                System.out.println("FAIL " + url);
            }
        });
    }

    public void testYourFifthPartition() {
        // Initialize URL validator
        UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        List<ResultPair> partitions = new ArrayList<>();
        partitions.add(new ResultPair("", true));
        partitions.add(new ResultPair("?value=", true));
        partitions.add(new ResultPair("?value=something&value2", true));

        // Loop through all partitions
        partitions.forEach(partition -> {
            String url = String.format("http://www.google.com:80/%s", partition.item);

            // Get expected and actual results
            boolean expected = partition.valid;
            boolean actual = urlValidator.isValid(url);

            // Print results
            if (expected == actual) {
                System.out.println("PASS " + url);
            } else {
                System.out.println("FAIL " + url);
            }
        });
    }


    public void testIsValid() {
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

    public void testAnyOtherUnitTest() {

    }
    /**
     * Create set of tests by taking the testUrlXXX arrays and
     * running through all possible permutations of their combinations.
     *
     * @param testObjects Used to create a url.
     */


}
