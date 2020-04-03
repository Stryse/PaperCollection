#include "student.h"
#include <sstream>
#include <cstdlib>
#include <iostream>

StudentPaperDataEnor::StudentPaperDataEnor(const std::string& fname)
        :_x(fname)
{
    if(_x.fail())
        throw StudentPaperDataEnor::Errors::FILE_ERROR;
}

StudentPaperDataEnor::~StudentPaperDataEnor()
{
    _x.close();
}

void StudentPaperDataEnor::read()
{
    std::string line;
    std::getline(_x,line);
    _sx = (!_x.fail() && line != "") ? Status::norm : Status::abnorm;
    if(_sx == Status::norm)
    {
        std::istringstream iss(line);
        std::ostringstream oss;
        std::string tmp;
        for(iss >> tmp; !isClassName(tmp) && (_sx = (!iss.fail()) ? Status::norm : Status::abnorm) == Status::norm; iss >> tmp)
        {
            oss << tmp << " ";
        }

        if(_sx == Status::norm)
        {
            _dx.name = oss.str();
            _dx.name.pop_back(); // Trimming name
            _dx.className = tmp;
            std::getline(iss.ignore(),_dx.data); // Trimming and reading to data
        }
    }
}

void StudentPaperDataEnor::next()
{
    if(!(_end = (_sx == Status::abnorm)))
    {
        _act.name = _dx.name;
        _act.className = _dx.className;
        std::istringstream ss(_dx.data);

        bool exist = false;
        std::string date;
        double weight;

        while(ss >> date >> weight && !exist)
        {
            if(weight > 5)
            {
                exist = true;
            }
        }
        _act.hasMoreThan5kg = exist;
        read();
    }
}

bool StudentPaperDataEnor::isClassName(const std::string& str)
{
    char fstChar[] = { str.c_str()[0], '\0'}; // Null terminated for std::atoi
    return std::atoi(fstChar) >= 1 && std::atoi(fstChar) <= 4;
}