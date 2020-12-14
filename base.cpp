#include <QString>
#include <QWidget>
#include <QPropertyAnimation>

void widgetShake(QWidget *pWidget, int nRange)
{
    const int nX = pWidget->x();
    const int nY = pWidget->y();
    QPropertyAnimation *pAnimation = new QPropertyAnimation(pWidget,"geometry");
    pAnimation->setEasingCurve(QEasingCurve::InOutSine);
    pAnimation->setDuration(300);
    pAnimation->setStartValue(QRect(QPoint(nX,nY),pWidget->size()));

    int nShakeCount = 25; //抖动次数
    double nStep = 1.0/nShakeCount;
    pAnimation->setKeyValueAt(nStep,QRect(QPoint(nX,nY),pWidget->size()));
    for(int i = 1; i < nShakeCount; i++){
        nRange = i%2 ? -nRange : nRange;
        pAnimation->setKeyValueAt(nStep*i,QRect(QPoint(nX + nRange,nY),pWidget->size()));
       // pAnimation->setKeyValueAt(nStep*i,QRect(QPoint(nX - nRange,nY),pWidget->size()));
        //pAnimation->setEndValue(QRect(QPoint(nX - nRange,nY),pWidget->size()));
    }
   // pAnimation->setKeyValueAt(nStep,QRect(QPoint(nX,nY),pWidget->size()));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);

}

bool check_string(QString S){
    foreach(QChar c,S){
        if ( (c >= '0' && c <= '9') ||
             (c >= 'A' && c <= 'Z') ||
             (c >= 'a' && c <= 'z') ||
             c == '_'){
        }else {
            return false;
        }
    }
    return true;
}
bool check_username(QString S){
    if (S.length() > 20){
        return false;
    }
    return true;
}
