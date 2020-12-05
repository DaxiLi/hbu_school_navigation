#ifndef PAINTERAREA_H
#define PAINTERAREA_H

#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class PainterAreaData;

class PainterArea
{
    Q_OBJECT
public:
    PainterArea();
    PainterArea(const PainterArea &);
    PainterArea &operator=(const PainterArea &);
    ~PainterArea();

private:
    QSharedDataPointer<PainterAreaData> data;
};

#endif // PAINTERAREA_H
