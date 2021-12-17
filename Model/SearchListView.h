#ifndef SearchListView_H_
#define SearchListView_H_

#include <QWidget>
#include <QTableView>
#include <QHeaderView>

class SearchTableModel;
class SearchTableDelegate;
class SearchTableView : public QTableView
{
    Q_OBJECT
public:
    SearchTableView(QWidget* parent = nullptr);
    ~SearchTableView();

    void AddTableList(QList<QVariantList> var);
    void AddPlayListVar(bool isMV,int row);

public slots:
    void AllTableSetFalse();
signals:
    void OpenUrl(QString);
    void DoubleClickedSong(QString,QString,QString);
    void NowPlayerMusicName(QString);
    void MVClicked(QString,QString);
    void AddPlayList(bool,QVariantList var);
private:
    void View_Init();
    //model
    SearchTableModel* tableModel;
    //delegate
    SearchTableDelegate* tableDelegate;
};

#endif //SearchListView_H_
