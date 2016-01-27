#ifndef IPCONNECT_H
#define IPCONNECT_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QtNetwork>
#include <QHostInfo>
#include <QHostAddress>

class IPConnect:public QDialog
{
    Q_OBJECT
public:
    explicit IPConnect(QWidget *parent=0);
    ~IPConnect();
    QString yourIP;

private:
    QString hostIP;
    QLabel *currentIP;
    QLineEdit *inputIP;
    QLabel *inputIPText;
    QPushButton *commit;

signals:

private slots:
    void CommitOnClick();

public slots:

};

#endif // IPCONNECT_H
