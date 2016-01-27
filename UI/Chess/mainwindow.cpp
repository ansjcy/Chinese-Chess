#include "mainwindow.h"
#include "ui_mainwindow.h"
bool flag=true;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    musicPlayer=new Widget;
    connected=false;
    setSide=true;   //red
    isChanged=false;
    enableFlag=true;
    tcpServer=new QTcpServer(this);
    tcpSocket=new QTcpSocket(this);

    Welcome w;
    w.exec();
    stateChosen=w.GetStateChosen();
    ViewModel::ChosenMode(stateChosen);
    if(stateChosen!=0)
    {
        if(stateChosen==1)
        {
            yourAddress=QHostAddress(w.yourIP);
            if(!tcpServer->listen(QHostAddress::Any,6666))
            {
                close();
            }
            connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));
            connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
            QPushButton connectButton(&dialog);
            dialog.setFixedHeight(60);
            dialog.setFixedWidth(200);
            connectButton.setText(QObject::tr("连接"));
            connectButton.setFixedHeight(30);
            connectButton.setFixedWidth(100);
            connectButton.move(50,15);
            connect(&connectButton,SIGNAL(clicked()),this,SLOT(newConnect()));
            dialog.exec();
        }
        move(width()/2,0);
        ui->setupUi(this);
        show();
        draw();
        if(stateChosen==1)
        {
            ui->actionRegret->setEnabled(false);
            ui->actionRestart->setEnabled(false);
        }
        else
        {
            ui->actionRegret->setEnabled(true);
            ui->actionRestart->setEnabled(true);
        }
    }
    else
    {
        this->~MainWindow();
        exit(1);
    }
}

void MainWindow::newConnect()
{
    blockSize=0;
    tcpSocket->abort();
    connected=true;
    tcpSocket->connectToHost(yourAddress,6666);
}

void MainWindow::sendMessage()
{
    if(connected==false)
    {
        QByteArray block;
        QDataStream out(&block,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);
        out<<(quint16) 0;
        if(setSide==true)
        {
            out<<tr("Red");
        }
        else
        {
            out<<tr("Black");
        }
        out.device()->seek(0);
        out<<(quint16)(block.size()-sizeof(quint16));
        QTcpSocket *clientConnection=tcpServer->nextPendingConnection();
        connect(clientConnection,SIGNAL(disconnected()),clientConnection,SLOT(deleteLater()));
        clientConnection->write(block);
        clientConnection->disconnectFromHost();
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("连接成功"),QObject::tr("确定"));
        connected=true;
        if(setSide==true)
            newConnect();
        dialog.close();
    }
    if(connected==true&&setSide==false&&flag)
    {
        flag=false;
        dialog.close();
        newConnect();
    }
}

void MainWindow::sendOperation()
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out<<(quint16) 0;
    QString data(QString::number(ViewModel::mD->getLastMove()));
    out<<data;
    isChanged = false;
    out.device()->seek(0);
    out<<(quint16)(block.size()-sizeof(quint16));
    ViewModel::legal=false;
    QTcpSocket *clientConnection=tcpServer->nextPendingConnection();
    do{
        connect(clientConnection,SIGNAL(disconnected()),clientConnection,SLOT(deleteLater()));
        clientConnection->write(block);
        clientConnection->disconnectFromHost();
    }while(clientConnection=tcpServer->nextPendingConnection());
    newConnect();
}

void MainWindow::readMessage()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_6);
    if(blockSize==0)
    {
        if(tcpSocket->bytesAvailable()<(int)sizeof(quint16))
            return;
        in>>blockSize;
    }
    if(tcpSocket->bytesAvailable() < blockSize) return;
    QString message;
    in>>message;
    if(message=="Red")
    {
        setSide=false;
        enableFlag=false;
    }
    else if(message=="Black")
    {
        setSide=true;
        enableFlag=true;
    }
    else if(enableFlag == false)
    {
        enableFlag=true;
        ViewModel::legal=false;
        int startPos=message.toInt()%100;
        int endPos=message.toInt()/100;
        ViewModel::mD->MovementsExectionDistributer(startPos, endPos, ViewModel::turns);
        ViewModel::turns=!ViewModel::turns;
        draw();
        checkEnd();
    }
}

void MainWindow::draw()
{
    int PixelX=0;
    int PixelY=0;
    int i=0;

    for (i=16; i<48; i++)
    {
        ViewModel::ArrayToPixel(i,stateChosen,setSide);
        PixelX=ViewModel::GetPixelX();
        PixelY=ViewModel::GetPixelY();
        switch(i)
        {
            case 16:
                ui->RedGen->move(PixelX,PixelY);
                break;
            case 17:
                ui->RedServant->move(PixelX,PixelY);
                break;
            case 18:
                ui->RedServant_2->move(PixelX,PixelY);
                break;
            case 19:
                ui->RedAdvisor->move(PixelX,PixelY);
                break;
            case 20:
                ui->RedAdvisor_2->move(PixelX,PixelY);
                break;
            case 21:
                ui->RedHorse->move(PixelX,PixelY);
                break;
            case 22:
                ui->RedHorse_2->move(PixelX,PixelY);
                break;
            case 23:
                ui->RedCar->move(PixelX,PixelY);
                break;
            case 24:
                ui->RedCar_2->move(PixelX,PixelY);
                break;
            case 25:
                ui->RedCannon->move(PixelX,PixelY);
                break;
            case 26:
                ui->RedCannon_2->move(PixelX,PixelY);
                break;
            case 27:
                ui->RedSoldier->move(PixelX,PixelY);
                break;
            case 28:
                ui->RedSoldier_2->move(PixelX,PixelY);
                break;
            case 29:
                ui->RedSoldier_3->move(PixelX,PixelY);
                break;
            case 30:
                ui->RedSoldier_4->move(PixelX,PixelY);
                break;
            case 31:
                ui->RedSoldier_5->move(PixelX,PixelY);
                break;
            case 32:
                ui->BlackGen->move(PixelX,PixelY);
                break;
            case 33:
                ui->BlackServant->move(PixelX,PixelY);
                break;
            case 34:
                ui->BlackServant_2->move(PixelX,PixelY);
                break;
            case 35:
                ui->BlackAdvisor->move(PixelX,PixelY);
                break;
            case 36:
                ui->BlackAdvisor_2->move(PixelX,PixelY);
                break;
            case 37:
                ui->BlackHorse->move(PixelX,PixelY);
                break;
            case 38:
                ui->BlackHorse_2->move(PixelX,PixelY);
                break;
            case 39:
                ui->BlackCar->move(PixelX,PixelY);
                break;
            case 40:
                ui->BlackCar_2->move(PixelX,PixelY);
                break;
            case 41:
                ui->BlackCannon->move(PixelX,PixelY);
                break;
            case 42:
                ui->BlackCannon_2->move(PixelX,PixelY);
                break;
            case 43:
                ui->BlackSoldier->move(PixelX,PixelY);
                break;
            case 44:
                ui->BlackSoldier_2->move(PixelX,PixelY);
                break;
            case 45:
                ui->BlackSoldier_3->move(PixelX,PixelY);
                break;
            case 46:
                ui->BlackSoldier_4->move(PixelX,PixelY);
                break;
            case 47:
                ui->BlackSoldier_5->move(PixelX,PixelY);
                break;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete musicPlayer;
    delete tcpServer;
    delete tcpSocket;
}

void MainWindow::on_actionNew_triggered()
{
    hide();

    Welcome w;
    w.exec();
    if(w.GetStateChosen()==0)
        close();
    else
    {
        if(stateChosen==1)
        {
            connected=false;
            setSide=true;   //red
            isChanged=false;
            enableFlag=true;
            flag=true;
            ui->actionRegret->setEnabled(false);
            ui->actionRestart->setEnabled(false);
            delete tcpServer;
            delete tcpSocket;
            tcpServer=new QTcpServer(this);
            tcpSocket=new QTcpSocket(this);
            yourAddress=QHostAddress(w.yourIP);
            if(!tcpServer->listen(QHostAddress::Any,6666))
            {
                close();
            }
            connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));
            connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
            QPushButton connectButton(&dialog);
            dialog.setFixedHeight(60);
            dialog.setFixedWidth(200);
            connectButton.setText(QObject::tr("连接"));
            connectButton.setFixedHeight(30);
            connectButton.setFixedWidth(100);
            connectButton.move(50,15);
            connect(&connectButton,SIGNAL(clicked()),this,SLOT(newConnect()));
            dialog.exec();
        }
        else
        {
             ui->actionRegret->setEnabled(true);
             ui->actionRestart->setEnabled(true);
        }
        ViewModel::Restart();
        stateChosen=w.GetStateChosen();
        ViewModel::ChosenMode(stateChosen);
        ui->blue1->move(-999,-999);
        ui->blue2->move(-999,-999);
        ui->chosen->move(-999,-999);
        draw();
        show();
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

bool MainWindow::checkEnd()
{
    if(ViewModel::mD->isEnd(ViewModel::turns)==true)
    {
        if(ViewModel::turns==false)
        {
            if(QMessageBox::information(this,"REDWIN","RED WIN!","Restart","Exit")==1)
                close();
        }
        else
        {
            if(QMessageBox::information(this,"BLACKWIN","BLACK WIN!","Restart","Exit")==1)
                close();
        }
        ViewModel::Restart();
        ui->blue1->move(-999,-999);
        ui->blue2->move(-999,-999);
        ui->chosen->move(-999,-999);
        draw();
        return true;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        ViewModel::PixelToArray(event->pos().x(),event->pos().y(),stateChosen,enableFlag,setSide);
        ViewModel::ChosenToPixel();
        if(ViewModel::turns==true)
            ui->statusBar->showMessage(QObject::tr("等待红方走棋"));
        else
            ui->statusBar->showMessage(QObject::tr("等待黑方走棋"));
        ui->chosen->move(ViewModel::chosenX,ViewModel::chosenY);

        if(ViewModel::legal==true)
        {
            draw();
            isChanged=true;

            if(stateChosen==2)
            {
                if(checkEnd())
                    return;
                computerMove();
                if(checkEnd())
                    return;
                ui->statusBar->showMessage(QObject::tr("等待红方走棋"));
            }
            else
            {
                //sendMessage();
                sendOperation();
                if(checkEnd())
                    return;
                enableFlag=false;
            }
        }
        else if(ViewModel::alarm() && !ViewModel::StartOrEnd)
            QMessageBox::information(this,"!!!",QObject::tr("要死了！"),"OK");
    }
}

bool MainWindow::computerMove()
{
    ui->statusBar->showMessage(QObject::tr("等待黑方走棋"));
    ViewModel::mD->MovementsExectionDistributer(0,0,0);
    ViewModel::turns=true;
    ViewModel::legal=false;
    draw();
    target=ViewModel::mD->getLastMove();
    short tempX1,tempX2,tempY1,tempY2;
    tempX1=target/1000;
    tempY1=(target%1000)/100;
    tempX2=(target%100)/10;
    tempY2=target%10;
    int blueX1,blueY1,blueX2,blueY2;
    blueX1=40+tempY1*63;
    blueY1=10+tempX1*63;
    blueX2=40+tempY2*63;
    blueY2=10+tempX2*63;
    ui->blue1->move(blueX1,blueY1);
    ui->blue2->move(blueX2,blueY2);
    return true;
}

void MainWindow::on_actionRestart_triggered()
{
    ViewModel::Restart();
    ui->blue1->move(-999,-999);
    ui->blue2->move(-999,-999);
    ui->chosen->move(-999,-999);
    draw();
}

void MainWindow::on_actionRegret_triggered()
{
    if(ViewModel::mD->regret()==true)
    {
        ViewModel::turns=!ViewModel::turns;
        draw();
        if(stateChosen==2)
        {
            ViewModel::mD->regret();
            ViewModel::turns=!ViewModel::turns;
            draw();
        }
        if(ViewModel::turns==true)
            ui->statusBar->showMessage(QObject::tr("等待红方走棋"));
        else
            ui->statusBar->showMessage(QObject::tr("等待黑方走棋"));
    }
}

void MainWindow::on_actionMusicPlayer_triggered()
{
    musicPlayer->show();
}

