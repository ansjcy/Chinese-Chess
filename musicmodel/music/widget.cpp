#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->
    ui->volumeSlider->setRange(0,100);
    this->setAutoFillBackground(true);
    QPalette palette;

    QPixmap pixmap("../../musicmodel/music/pic.jpg");
    qreal width =  pixmap.width();
    qreal height = pixmap.height();
    pixmap = pixmap.scaled(width/5.1,height/5.1,Qt::KeepAspectRatio);
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);
    player = new QMediaPlayer(this);
    playList = new QMediaPlaylist(this);
    player->setPlaylist(playList);

    connect(player,SIGNAL(volumeChanged(int)),this,SLOT(volumeChanged_slot(int)));
    player->setVolume(50);

    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(playTime_slot(qint64)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(currentTime_slot(qint64)));

}

Widget::~Widget()
{
    delete ui;
}

/***************************
 * open music file
 ***************************/
void Widget::on_openbtn_clicked()
{
    QStringList fileName = QFileDialog::getOpenFileNames(this,QObject::tr("open the music you wanna play"),QDir::homePath(),QObject::tr("music(*.mp3)"));
    if(fileName.count() > 0){
        foreach (QString fileItem, fileName) {
            if(!fileItem.isEmpty()){
                playList->addMedia(QUrl::fromLocalFile(fileItem));
            }
        }
        playList->setCurrentIndex(0);
    }

}
/***************************
 * play and pause the music
 ***************************/
void Widget::on_playbtn_clicked()
{
    if(ui->playbtn->isChecked()){
        //ui->playbtn->setText(QObject::tr("pause"));
        QIcon pauseIcon("../../pic/pause.ico");
        ui->playbtn->setIcon(pauseIcon);
        player->play();
    }
    else{
        //ui->playbtn->setText(QObject::tr("play"));
        QIcon playIcon("../../pic/play.ico");
        ui->playbtn->setIcon(playIcon);
        player->pause();
    }
}
/***************************
 * choose previous and next
 * song in the play list
 ***************************/
void Widget::on_previousbtn_clicked()
{
    playList->previous();
}

void Widget::on_nextbtn_clicked()
{
    playList->next();
}

void Widget::on_modebtn_clicked()
{
    QMenu menu;
    menu.addAction(QObject::tr("this song once"),this,SLOT(currentOnce_slot()));
    menu.addAction(QObject::tr("this song loop"),this,SLOT(currentLoop_slot()));
    menu.addAction(QObject::tr("all songs loop"),this,SLOT(loop_slot()));
    menu.addAction(QObject::tr("play  directly"),this,SLOT(sequentially_slot()));
    menu.addAction(QObject::tr("play  randomly"),this,SLOT(random_slot()));
    menu.exec(QCursor::pos());
}
void Widget::currentOnce_slot()
{
    playList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}
void Widget::currentLoop_slot()
{
    playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
}
void Widget::sequentially_slot()
{
    playList->setPlaybackMode(QMediaPlaylist::Sequential);
}
void Widget::loop_slot()
{
    playList->setPlaybackMode(QMediaPlaylist::Loop);
}
void Widget::random_slot()
{
    playList->setPlaybackMode(QMediaPlaylist::Random);
}
/***************************
 * volume
 ***************************/
void Widget::on_volumeSlider_sliderMoved(int position)
{
     player->setVolume(position);
}
void Widget::volumeChanged_slot(int volume)
{
    player->setVolume(volume);
    ui->volumeSlider->setValue(volume);
}



void Widget::on_playSlider_sliderMoved(int position)
{
    QTime time(0,position/60000,position/1000%60);
    ui->current->setText(time.toString(QObject::tr("mm:ss")));
    player->setPosition(position);
}

void Widget::playTime_slot(qint64 finishTime)
{
    QTime playFinishTime(0,finishTime/60000,finishTime/1000%60);
    ui->total->setText(playFinishTime.toString(QObject::tr("mm:ss")));
    ui->playSlider->setMaximum(finishTime);
}
void Widget::currentTime_slot(qint64 position)
{
    QTime playCurrentTime(0,position/60000,position/1000%60);
    ui->current->setText(playCurrentTime.toString(QObject::tr("mm:ss")));
    ui->playSlider->setValue(position);
}
