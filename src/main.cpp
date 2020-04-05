#include <iostream>
#include "student.h"
#include "schoolClass.h"

void listStudents(const std::string& filePath, std::ostream& stream = std::cout);
int countClasses(const std::string& filePath);
void handleSPaperDataEnorError(const StudentPaperDataEnor::Errors& e, const std::string& filePath);

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    std::cout << "Please enter the name of the input file: ";
    std::string filePath;
    std::cin >> filePath;
    // First Task
    try
    {
        std::cout << "==============First Task===============" << std::endl;
        listStudents(filePath);
    }
    catch (const StudentPaperDataEnor::Errors &e)
    {
        handleSPaperDataEnorError(e,filePath);
    }

    // Second Task
    try
    {
        std::cout << "==============Second Task==============" << std::endl;
        std::cout << "Result: "<< countClasses(filePath) << " classes." << std::endl;  
    }
    catch (const StudentPaperDataEnor::Errors &e)
    {
        handleSPaperDataEnorError(e,filePath);
    }
    
    return 0;
}

#else
#include "tests.h"
#endif

void listStudents(const std::string& filePath, std::ostream& stream)
{
    StudentPaperDataEnor t(filePath);
    for (t.first(); !t.end(); t.next())
    {
        if (t.current().hasMoreThan5kg)
        {
            stream << t.current().name << " " << t.current().className << std::endl;
        }
    }
}

int countClasses(const std::string& filePath)
{
    SchoolClassEnor t(filePath);
    int c = 0;
    for (t.first(); !t.end(); t.next())
    {
        if (t.current())
            ++c;
    }
    return c;
}

void handleSPaperDataEnorError(const StudentPaperDataEnor::Errors& e, const std::string& filePath)
{
    switch (e)
    {
    case StudentPaperDataEnor::Errors::FILE_ERROR:
        std::cerr << "Could not open file: \"" << filePath << "\" Exiting..." << std::endl;
        break;
    default:
        std::cerr << "Unhandled exception" << std::endl;
        break;
    }
}