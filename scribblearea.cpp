/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sigin.h"
#include "login.h"
#include "welcom.h"
#include "ui_testmainwindow.h"
#include "scribblearea.h"

#include <QLabel>
#include <QMessageBox>
#include "scribblearea.h"

#include <QMouseEvent>
#include <QPainter>
#include <QtDebug>

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

//! [0]
ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
}
//! [0]

//! [1]
bool ScribbleArea::openImage(const QString &fileName)
//! [1] //! [2]
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}
//! [2]

//! [3]
bool ScribbleArea::saveImage(const QString &fileName, const char *fileFormat)
//! [3] //! [4]
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    }
    return false;
}
//! [4]

//! [5]
void ScribbleArea::setPenColor(const QColor &newColor)
//! [5] //! [6]
{
    myPenColor = newColor;
}
//! [6]

//! [7]
void ScribbleArea::setPenWidth(int newWidth)
//! [7] //! [8]
{
    myPenWidth = newWidth;
}
//! [8]

//! [9]
void ScribbleArea::clearImage()
//! [9] //! [10]
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}
//! [10]

//! [11]
void ScribbleArea::mousePressEvent(QMouseEvent *event)
//! [11] //! [12]
{
    qDebug() << "mousePressEvent";
    qDebug() << "x:" << event->x() << ",y:" << event->y();

    if (event->button() == Qt::LeftButton) {
        drawLineTo(event->pos());
        lastPoint = event->pos();
        scribbling = true;
    }else if (event->button() == Qt::RightButton){
        //ad_menu_2();
//        QPoint tep = lastPoint;
//        lastPoint = event->pos();
//        setPenWidth(10);
//        drawLineTo(event->pos());
//        //setPenWidth(1);
//        lastPoint = tep;
        drawPointAt(event->pos());
        add_right_click_menu();
    }

}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "mouseMoveEvent";
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "mouseRealseEvent";
    if (event->button() == Qt::LeftButton && scribbling) {
        qDebug() << "event->button left";
        drawLineTo(event->pos());
        scribbling = false;
    }else if (event->button() == Qt::RightButton){

    }
}

//! [12] //! [13]
void ScribbleArea::paintEvent(QPaintEvent *event)
//! [13] //! [14]
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}
//! [14]

//! [15]
void ScribbleArea::resizeEvent(QResizeEvent *event)
//! [15] //! [16]
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}
//! [16]

//! [17]
void ScribbleArea::drawLineTo(const QPoint &endPoint)
//! [17] //! [18]
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    painter.drawPoint(endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}
//! [18]

void ScribbleArea::drawPointAt(const QPoint &pos){
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, 5, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawPoint(pos);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update();
//    update(QRect())
//    update(QRect(lastPoint, endPoint).normalized()
//                                     .adjusted(-rad, -rad, +rad, +rad));
}

//! [19]
void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
//! [19] //! [20]
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
//! [20]

//! [21]
void ScribbleArea::print()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog printDialog(&printer, this);
//! [21] //! [22]
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
#endif // QT_CONFIG(printdialog)
}
//! [22]


void ScribbleArea::ad_menu_2(){
    static QMenu *menu = new (QMenu);
        menu->setTitle("自定义的菜单");
        static QList<QAction *> *list = nullptr ;
        if (list == nullptr) {
            list = new QList<QAction*>;
            list->append(new QAction(QIcon("icon.jpg"), "hello world ", this));

            list->append(new QAction(QIcon(), "hello  ", this));
            menu->setParent(this);

            auto action = new QAction(this);
            // 设置icon的图标
           // action->setIcon(QIcon(":/contentMenuEvent/Resources/icon.jpg"));
            //设置显示图标在icon 上
            action->setIconVisibleInMenu(true);
            action->setText("Qt积木笔记");
            // 同样处理 点击 信号. 跳转到 Qt积木笔记
            connect(action, SIGNAL(triggered(bool)), this, SLOT(QtjiMu()));
            // 将这个action append 到list
            list->append(action);
            menu->addActions(*list);

        }
        menu->exec(cursor().pos());
        menu->show();
}

void ScribbleArea::add_right_click_menu(){
    QMenu *pMenu = new QMenu(this);
    QAction *pNewTask = new QAction(tr("设为起点"), this);
    QAction *pEditTask = new QAction(tr("设为终点"), this);
    QAction *pDeleteTask = new QAction(tr("删除路线"), this);

//    QAction *pToolRenName = new QAction(tr("改名工具"), this);
//    QAction *pToolEdot = new QAction(tr("设置工具"), this);
//    QAction *pToolDelete = new QAction(tr("删除工具"), this);

    //1:新建任务 2:设置任务 3:删除任务 4:改名工具 5:设置工具 6:删除工具
    pNewTask->setData(1);
    pEditTask->setData(2);
    pDeleteTask ->setData(3);
//    pToolRenName->setData(4);
//    pToolEdot->setData(5);
//    pToolDelete ->setData(6);

    //把QAction对象添加到菜单上
    pMenu->addAction(pNewTask);
    pMenu->addAction(pEditTask);
    pMenu->addAction(pDeleteTask);
//    pMenu->addAction(pToolRenName);
//    pMenu->addAction(pToolEdot);
//    pMenu->addAction(pToolDelete);

    //连接鼠标右键点击信号
    connect(pNewTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pEditTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pDeleteTask, SIGNAL(triggered()), SLOT(onTaskBoxContextMenuEvent()));
//    connect(pToolRenName, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
//    connect(pToolEdot, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
//    connect(pToolDelete, SIGNAL(triggered()), SLOT(onTaskBoxContextMenuEvent()));

    //在鼠标右键点击的地方显示菜单
    pMenu->exec(cursor().pos());

    //释放内存
    QList<QAction*> list = pMenu->actions();
    foreach (QAction* pAction, list) delete pAction;
    delete pMenu;
}

void ScribbleArea::onTaskBoxContextMenuEvent()
{
    QAction *pEven = qobject_cast<QAction *>(this->sender()); //this->sender()就是发信号者 QAction

    //获取发送信息类型 1:新建任务 2:设置任务 3:删除任务 4:改名工具 5:设置工具 6:删除工具
    int iType = pEven->data().toInt();

    switch (iType)
    {
    case 1:
        QMessageBox::about(this, "tip", pEven->text());
        break;
    case 2:
        QMessageBox::about(this, "tip", pEven->text());
        break;
    case 3:
        QMessageBox::about(this, "tip", pEven->text());
        break;
    case 4:
        QMessageBox::about(this, "tip", pEven->text());
        break;
    case 5:
        QMessageBox::about(this, "tip", pEven->text());
        break;
    case 6:
        QMessageBox::about(this, "tip", pEven->text());
        break;
    default:
        break;
    }
}
