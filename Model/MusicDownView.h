#ifndef MUSIC_DOWN_VIEW_H_
#define MUSIC_DOWN_VIEW_H_

#include <QWidget>
#include <QTableView>

class MusicDownTableModel;
class MusicDownTableDelegate;
class MusicDownTableView : public QTableView
{
    Q_OBJECT
public:
    MusicDownTableView(QWidget* parent = nullptr);
    ~MusicDownTableView();

    void AddListData(QVariantList);

protected:
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void SlotUpdateProgress(QString,qint64,qint64);
    void SendData(QString);

public slots:
    void AllTableSetFalse();
signals:
    void OpenUrl(QString);
    void SendDownEndData(QVariantList);
private:
    void View_Init();
    //model
    MusicDownTableModel* tableModel;
    //delegate
    MusicDownTableDelegate* tableDelegate;
};


#endif //MUSIC_DOWN_VIEW_H_
