#ifndef WELCOM_H
#define WELCOM_H

#include <QWidget>

namespace Ui {
class Welcom;
}

class Welcom : public QWidget
{
    Q_OBJECT

public:
    explicit Welcom(QWidget *parent = nullptr);
    ~Welcom();

private:
    Ui::Welcom *ui;

private slots:
    void on_sigin_buttom_clicked();

    void on_login_button_clicked();
};

#endif // WELCOM_H
