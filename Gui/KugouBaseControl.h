#ifndef _KUGOU_BASE_CONTROL_H_
#define _KUGOU_BASE_CONTROL_H_

#include <QWidget>

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QDoubleSpinBox;
class KugouBaseControl : public QWidget
{
    Q_OBJECT
public:
    KugouBaseControl(QWidget* parent = nullptr);
    KugouBaseControl();
    ~KugouBaseControl();

protected:
    QPushButton* Get_Button(QString text = "",QString Icon = "",QString ToolText = "",int width = 0,int height = 0,int IconWidth = 16,int IconHeight = 16,QString style = "");
    QLabel* Get_Label(QString text = "",int Width = 0,int height = 0,QString style = "",Qt::Alignment Align = Qt::AlignVCenter | Qt::AlignHCenter);
    QHBoxLayout* Get_HLayout(int left = 0,int right = 0,int top = 0,int bottom = 0,int Spaceing = 0);
    QVBoxLayout* Get_VLayout(int left = 0,int right = 0,int top = 0,int bottom = 0,int Spaceing = 0);
};


#endif //_KUGOU_BASE_CONTROL_H_
