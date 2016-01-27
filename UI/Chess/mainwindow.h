#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../viewmodel/viewmodel.h"
#include "../../model/model.h"
#include "../../musicmodel/music/widget.h"
#include "welcome.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QString>
#include <QMessageBox>
//#include <Windows.h>
#include <QtNetwork>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);
    void draw();
    bool checkEnd();  //check whether the game is over
    bool computerMove();

private slots:
    void on_actionExit_triggered();

    void on_actionNew_triggered();

    void on_actionRestart_triggered();

    void on_actionRegret_triggered();

    void on_actionMusicPlayer_triggered();

    void newConnect();

    void sendMessage();

    void readMessage();

private:
    Ui::MainWindow *ui;
    Widget* musicPlayer;
    QDialog dialog;
    int stateChosen;
    QHostAddress yourAddress;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QByteArray dataRead;
    QByteArray datasend;
    bool connected;
    quint16 blockSize;
    bool setSide;
    bool isChanged;
    short target;
    bool enableFlag;
    void sendOperation();
};

#endif // MAINWINDOW_H
