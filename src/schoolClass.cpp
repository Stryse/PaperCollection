#include "schoolClass.h"

SchoolClassEnor::SchoolClassEnor(const std::string &fname)
    : _y(fname)
{
}

void SchoolClassEnor::next()
{
    if(!(_end = (_y.end())))
    {
        _act = true;
        std::string currClassName = _y.current().className;
        for (; !_y.end() && _y.current().className == currClassName; _y.next())
        {
            if (!_y.current().hasMoreThan5kg)
                _act = false;
        }
    }
}