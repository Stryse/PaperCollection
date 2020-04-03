#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

static const std::string TPath = "../tests/";
namespace testf
{

    /* Checks each line of an output with expected result, and reports wrong lines, or
    reports if the expected number of lines are not equal to number of output lines */
    bool compareWithExpected(std::istream& inputSource,const std::string& expectedPath)
    {
        std::ifstream infileExpected(expectedPath);
        std::string sourceLine;
        std::string expctdLine;
        bool allMatches = true;
        int sourceCount = 0;
        int expectedCount = 0;

        std::getline(inputSource,sourceLine);
        std::getline(infileExpected,expctdLine);
        while(!inputSource.fail() || !infileExpected.fail())
        {
            if(!inputSource.fail() && !infileExpected.fail())
            {
                CHECK(sourceLine == expctdLine); // For additional info
                if(sourceLine != expctdLine)
                    allMatches = false;
            }

            if(!inputSource.fail())
            {
                ++sourceCount;
                std::getline(inputSource,sourceLine);
            }

            if(!infileExpected.fail())
            {
                ++expectedCount;
                std::getline(infileExpected,expctdLine);
            }
        }
        CHECK(sourceCount == expectedCount); // For additional info
        return allMatches;
    }

    void TEST_LIST_STUDENTS(const std::string& sourcePath, const std::string& expectedPath)
    {
        std::stringstream buffer;
        listStudents(TPath + sourcePath,buffer);
        CHECK(testf::compareWithExpected(buffer,TPath + expectedPath));
    }
}

TEST_CASE("Valami")
{
    testf::TEST_LIST_STUDENTS("Test01S.txt","Test01E.txt");
}

TEST_CASE("File Not exists")
{
    REQUIRE_THROWS_AS(listStudents("<>/*:nofile.txt"),StudentPaperDataEnor::Errors);
}