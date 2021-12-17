#ifndef SearchHeadListView_H_
#define SearchHeadListView_H_

#include <QWidget>
#include <QTableView>
#include <QHeaderView>

class SearchHeadTableModel;
class SearchHeadTableDelegate;
class SearchHeadTableView : public QTableView
{
    Q_OBJECT
public:
    SearchHeadTableView(QWidget* parent = nullptr);
    ~SearchHeadTableView();

public slots:
    void AllTableSetFalse();
signals:
    void OpenUrl(QString);
private:
    void View_Init();
    //model
    SearchHeadTableModel* tableModel;
    //delegate
    SearchHeadTableDelegate* tableDelegate;
};

#endif //SearchHeadListView_H_
