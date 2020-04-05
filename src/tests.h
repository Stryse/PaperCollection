#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace test
{
static const std::string TPath = "../tests/";

/* Checks each line of an output with expected result, and reports wrong lines, or
    reports if the expected number of lines are not equal to number of output lines */
bool compareWithExpected(std::istream &inputSource, const std::string &expectedPath)
{
    std::ifstream infileExpected(expectedPath);
    std::string sourceLine;
    std::string expctdLine;
    bool allMatches = true;
    int sourceCount = 0;
    int expectedCount = 0;

    std::getline(inputSource, sourceLine);
    std::getline(infileExpected, expctdLine);
    while (!inputSource.fail() || !infileExpected.fail())
    {
        if (!inputSource.fail() && !infileExpected.fail())
        {
            CHECK(sourceLine == expctdLine); // For additional info
            if (sourceLine != expctdLine)
                allMatches = false;
        }

        if (!inputSource.fail())
        {
            ++sourceCount;
            std::getline(inputSource, sourceLine);
        }

        if (!infileExpected.fail())
        {
            ++expectedCount;
            std::getline(infileExpected, expctdLine);
        }
    }
    CHECK(sourceCount == expectedCount); // For additional info
    return allMatches;
}

void TEST_LIST_STUDENTS(const std::string &sourcePath, const std::string &expectedPath)
{
    std::stringstream buffer;
    listStudents(test::TPath + sourcePath, buffer);
    CHECK(test::compareWithExpected(buffer, test::TPath + expectedPath));
}

void TEST_COUNT_CLASSES(const std::string &sourcePath, int expectedResult)
{
    CHECK(countClasses(test::TPath + sourcePath) == expectedResult);
}

} // namespace test

//================TEST CASES================//
            /// ListStudent Tests ///

TEST_CASE("File Not exists")
{
    REQUIRE_THROWS_AS(listStudents("<>/*:nofile.txt"), StudentPaperDataEnor::Errors);
}

TEST_CASE("Empty File - NO Students", "Test00S.txt; Test00E.txt")
{
    test::TEST_LIST_STUDENTS("Test00S.txt", "Test00E.txt");
}

TEST_CASE("One Student")
{
    SECTION("No Result", "Test01S.txt; Test01E.txt")
    {
        test::TEST_LIST_STUDENTS("Test01S.txt", "Test01E.txt");
    }

    SECTION("1 result", "Test02S.txt; Test02E.txt")
    {
        test::TEST_LIST_STUDENTS("Test02S.txt", "Test02E.txt");
    }
}

TEST_CASE("Two Students")
{
    SECTION("No Result","Test03S.txt; Test03E.txt")
    {
        test::TEST_LIST_STUDENTS("Test03S.txt","Test03E.txt");
    }
    SECTION("1 result","Test04S.txt; Test04E.txt")
    {
        test::TEST_LIST_STUDENTS("Test04S.txt","Test04E.txt");
    }
    SECTION("2 (multiple) results","Test05S.txt; Test05E.txt")
    {
        test::TEST_LIST_STUDENTS("Test05S.txt","Test05E.txt");
    }
}

TEST_CASE("Four Students - Result position test")
{
    SECTION("Result at beginning","Test06S.txt; Test06E.txt")
    {
        test::TEST_LIST_STUDENTS("Test06S.txt","Test06E.txt");
    }

    SECTION("Result in the middle","Test07S.txt; Test07E.txt")
    {
        test::TEST_LIST_STUDENTS("Test07S.txt","Test07E.txt");
    }

    SECTION("Result at the end","Test08S.txt; Test08E.txt")
    {
        test::TEST_LIST_STUDENTS("Test08S.txt","Test08E.txt");
    }
}


    /// countClasses Tests ///

TEST_CASE("File Not exists 2")
{
    REQUIRE_THROWS_AS(countClasses("<>/*:nofile.txt"), StudentPaperDataEnor::Errors);
}

TEST_CASE("Empty File","Test09S.txt")
{
    test::TEST_COUNT_CLASSES("Test09S.txt",0);
}

TEST_CASE("One class")
{
    SECTION("1 student - 0 result","Test10S.txt")
    {
        test::TEST_COUNT_CLASSES("Test10S.txt",0);
    }
    SECTION("1 student - 1 result","Test11S.txt")
    {
        test::TEST_COUNT_CLASSES("Test11S.txt",1);
    }
    SECTION("2 (multiple students) - 0 result (none fulfills)","Test12S.txt")
    {
        test::TEST_COUNT_CLASSES("Test12S.txt",0);
    }
    SECTION("2 (multiple students) - 0 results (one fulfills)","Test13S.txt")
    {
        test::TEST_COUNT_CLASSES("Test13S.txt",0);
    }
    SECTION("2 (multiple students) - 1 result", "Test14S.txt")
    {
        test::TEST_COUNT_CLASSES("Test14S.txt",1);
    }
}

TEST_CASE("Two classes")
{
    SECTION("Multiple students - 0 result","Test15S.txt")
    {
        test::TEST_COUNT_CLASSES("Test15S.txt",0);
    }

    SECTION("Multiple students - 1 result","Test16S.txt")
    {
        test::TEST_COUNT_CLASSES("Test16S.txt",1);
    }

    SECTION("Multiple students - 2 result","Test17S.txt")
    {
        test::TEST_COUNT_CLASSES("Test17S.txt",2);
    }
}

TEST_CASE("Test student with multiple contributions")
{
    SECTION("None of them checks","TestMUL1.txt")
    {
        test::TEST_COUNT_CLASSES("TestMUL1.txt",0);
    }

    SECTION("First Checks","TestMUL2.txt")
    {
        test::TEST_COUNT_CLASSES("TestMUL2.txt",1);
    }

    SECTION("Second Checks","TestMUL3.txt")
    {
        test::TEST_COUNT_CLASSES("TestMUL3.txt",1);
    }

    SECTION("Third Checks","TestMUL4.txt")
    {   
        test::TEST_COUNT_CLASSES("TestMUL4.txt",1);
    }
}