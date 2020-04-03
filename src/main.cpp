#include <iostream>
#include "student.h"
#include "schoolClass.h"

const char* filePath = "input.txt";


int main()
{
    // First Task
    try
    {   std::cout << "First Task" << std::endl;
        StudentPaperDataEnor t(filePath);
        for(t.first(); !t.end(); t.next())
        {
            if(t.current().hasMoreThan5kg)
            {
                std::cout << t.current().name << " " << t.current().className << std::endl;
            }
        }
    }
    catch(StudentPaperDataEnor::Errors& e)
    {
        switch (e)
        {
        case StudentPaperDataEnor::Errors::FILE_ERROR:
            std::cerr << "Could not open file: " << filePath << ".Exiting..." << std::endl; 
            break;

        case StudentPaperDataEnor::Errors::INVALID_VALUE_READ:
            std::cerr << "An invalid line has been read from input file" << std::endl;
            break;
             
        default:
            std::cerr << "Unhandled exception" << std::endl;
            break;
        }
    }
    

    try
    {
        SchoolClassEnor t(filePath);
        int c = 0;
        for(t.first(); !t.end(); t.next())
        {
            if(t.current())
                ++c;
        }
        std::cout << c << std::endl;
    }
    catch(StudentPaperDataEnor::Errors& e)
    {
        switch (e)
        {
        case StudentPaperDataEnor::Errors::FILE_ERROR:
            std::cerr << "Could not open file: " << filePath << ".Exiting..." << std::endl; 
            break;

        case StudentPaperDataEnor::Errors::INVALID_VALUE_READ:
            std::cerr << "An invalid line has been read from input file" << std::endl;
            break;
             
        default:
            std::cerr << "Unhandled exception" << std::endl;
            break;
        }
    }
    
    return 0;
}