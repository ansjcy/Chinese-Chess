#include "ipconnect.h"

IPConnect::IPConnect(QWidget *parent):QDialog(parent)
{
    QString localHostName=QHostInfo::localHostName();
    QHostInfo info=QHostInfo::fromName(localHostName);

    foreach(QHostAddress address,info.addresses()) //get ipv4 address
    {
        if(address.protocol()==QAbstractSocket::IPv4Protocol)
            hostIP=address.toString();
    }

    setFixedHeight(90);
    setFixedWidth(260);

    currentIP=new QLabel(this);
    currentIP->move(10,5);
    currentIP->setText(QObject::tr("当前IP:")+hostIP);

    inputIPText=new QLabel(this);
    inputIPText->move(10,30);
    inputIPText->setText(QObject::tr("对方IP: "));

    inputIP= new QLineEdit(this);
    inputIP->move(65,27);

    commit=new QPushButton(this);
    commit->move(100,60);
    commit->setText(tr("确认"));
    connect(commit,SIGNAL(clicked()),this,SLOT(CommitOnClick()));
}

IPConnect::~IPConnect()
{
    delete currentIP;
    delete inputIP;
    delete inputIPText;
    delete commit;
}

void IPConnect::CommitOnClick()
{
    yourIP=inputIP->text();
    close();
}


