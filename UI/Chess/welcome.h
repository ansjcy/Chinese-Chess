#ifndef WELCOME_H
#define WELCOME_H

#include "ipconnect.h"
#include <QDialog>
#include <QPushButton>
#include <QLabel>

class Welcome : public QDialog
{
    Q_OBJECT
public:
    explicit Welcome(QWidget *parent = 0);
    ~Welcome();
    short GetStateChosen()
    {
        return StateChosen;
    };
    QString yourIP;

private:
    QPushButton *PVEButton;
    QPushButton *PVPButton;
    QLabel *Saber;
    short StateChosen;

signals:

private slots:
    void PVPOnClicked();
    void PVEOnClicked();

public slots:
};

#endif // WELCOME_H
