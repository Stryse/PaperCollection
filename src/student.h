#ifndef STUDENT__H
#define STUDENT__H

#include <string>
#include <fstream>

struct Contribution
{
    std::string name;
    std::string className;
    std::string data;
};

struct StudentPaperData
{
    std::string name;
    std::string className;
    bool hasMoreThan5kg;
};

enum class Status { norm, abnorm };

struct StudentPaperDataEnor
{
    public:
            enum class Errors { FILE_ERROR };

            StudentPaperDataEnor(const std::string& fname);
            ~StudentPaperDataEnor();
            void first() { read(); next(); }
            void next();
            StudentPaperData current() const { return _act; }
            bool end() const { return _end; }

    private:
            std::ifstream _x;
            Status _sx;
            Contribution _dx;
            StudentPaperData _act;
            bool _end;


            void read();
            static bool isClassName(const std::string& str);
};
#endif