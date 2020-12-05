#include "painterarea.h"

class PainterAreaData : public QSharedData
{
public:

};

PainterArea::PainterArea() : data(new PainterAreaData)
{

}

PainterArea::PainterArea(const PainterArea &rhs) : data(rhs.data)
{

}

PainterArea &PainterArea::operator=(const PainterArea &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

PainterArea::~PainterArea()
{

}
