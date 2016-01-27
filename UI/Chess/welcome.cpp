#include "welcome.h"
#include "QMessageBox"

Welcome::Welcome(QWidget *parent) : QDialog(parent)
{
    StateChosen=0;
    setFixedHeight(559);
    setFixedWidth(1019);

    PVPButton=new QPushButton(this);
    PVPButton->move(150, 130);
    PVPButton->setText(QObject::tr("联机对战"));

    PVEButton=new QPushButton(this);
    PVEButton->move(150, 170);
    PVEButton->setText(QObject::tr("人机对战"));

    Saber=new QLabel(this);
    Saber->setFixedHeight(559);
    Saber->setFixedWidth(1019);
    Saber->setPixmap(QPixmap::fromImage(*new QImage(":/res/WelcomeBackground.jpg")));

    PVEButton->raise();
    PVPButton->raise();
    connect(PVPButton, SIGNAL(clicked()), this, SLOT(PVPOnClicked()));
    connect(PVEButton, SIGNAL(clicked()), this, SLOT(PVEOnClicked()));
}

Welcome::~Welcome()
{
    delete PVPButton;
    delete PVEButton;
}

void Welcome::PVPOnClicked()
{
    IPConnect ip;
    ip.exec();
    if(ip.yourIP.isEmpty()==false)
    {
        yourIP=ip.yourIP;
        StateChosen=1;
        close();
    }
}

void Welcome::PVEOnClicked()
{
    StateChosen=2;
    close();
}

