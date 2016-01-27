#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QDir>
#include <QUrl>
#include <QTime>
#include <QMenu>
#include <QCursor>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_openbtn_clicked();

    void on_playbtn_clicked();

    void on_previousbtn_clicked();
    
    void on_nextbtn_clicked();

    
    void on_modebtn_clicked();
    void currentOnce_slot();
    void currentLoop_slot();
    void loop_slot();
    void sequentially_slot();
    void random_slot();

    void on_volumeSlider_sliderMoved(int position);
    void volumeChanged_slot(int volume);

    void on_playSlider_sliderMoved(int position);

    void playTime_slot(qint64 finishTime);
    void currentTime_slot(qint64 position);

private:
    Ui::Widget *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playList;
};

#endif // WIDGET_H
