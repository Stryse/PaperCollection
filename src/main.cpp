#include <iostream>
#include "student.h"

const char* filePath = "input.txt";


int main()
{
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
        
        default:
            std::cerr << "Unhandled exception" << std::endl;
            break;
        }
    }
    
    return 0;
}