#include <gtest/gtest.h>
#include "mymap.h"

using namespace std;

// milestone 1 tests 
// ssulta24
// default constructor Test and size Test
TEST(mymap, defaultConstructor) {

    // create a mymap
    mymap<int, int> m; 

    // check if the size is 0
    EXPECT_EQ(m.Size(), 0);

}

// ssulta24
// put Test and size Test
TEST(mymap, put) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.Size(), 3);

}

// ssulta24
// get Test
TEST(mymap, get) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.get(1), 1);
    EXPECT_EQ(m.get(2), 2);
    EXPECT_EQ(m.get(3), 3);
    EXPECT_EQ(m.get(4), 0);

}

// ssulta24
// contains Test
TEST(mymap, containsKey) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.contains(1), true);
    EXPECT_EQ(m.contains(2), true);
    EXPECT_EQ(m.contains(3), true);
    EXPECT_EQ(m.contains(4), false);

}

// ssulta24
// toString Test
TEST(mymap, tostr) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {3, 2, 1};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    string sol = "key: 1 value: 1\nkey: 2 value: 2\nkey: 3 value: 3\n";
    EXPECT_EQ(sol, m.toString());

}

// ssulta24
// operator[] Test
TEST(mymap, operator) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m[1], 1);
    EXPECT_EQ(m[2], 2);
    EXPECT_EQ(m[3], 3);
    EXPECT_EQ(m[4], 0);

}

// ssulta24
// stress test combining all the tests above 
TEST(mymap, stressTest) {

    // create a mymap
    mymap<int, int> m; 

    vector< int > arr;

    for (int i = 0; i < 10000; i++) {
        int num = rand() % 10000;
        // append num to arr 
        arr.push_back(num);
        m.put(i, num);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m[i], arr[i]);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m.contains(i), true);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m.get(i), arr[i]);
    }

    EXPECT_EQ(m.Size(), 10000);

}

// TO DO: write lots of tests here.
