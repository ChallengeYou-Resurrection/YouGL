#ifndef CYLEVEL_H
#define CYLEVEL_H

#include <string>

struct CYLevelHeader
{
    std::string name;
    std::string author;
    std::string date;

    float version;
    int levels;
};

class CYLevel
{
public:
    CYLevelHeader m_header;

private:
};

#endif // CYLEVEL_H
