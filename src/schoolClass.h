#ifndef SCHOOL_CLASS__H
#define SCHOOL_CLASS__H

#include <fstream>
#include "student.h"

class SchoolClassEnor
{
    public:
            SchoolClassEnor(const std::string& fname);
            void first() { _y.first(); next(); };
            void next();
            bool current() const { return _act; }
            bool end() const { return _end; }
    private:
            StudentPaperDataEnor _y;
            Status _sy;
            StudentPaperData _dy;
            bool _act;
            bool _end;
};
#endif