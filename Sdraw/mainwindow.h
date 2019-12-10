#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphlibrary.h"
#include "tools.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void GetParament(QString x, QString y)
    {
        arg1=x;
        arg2=y;
    }
    void readText();
private slots:
    void on_actionLine_toggled(bool arg1);

    void on_actionLine_triggered();

    void on_actionDelete_triggered();

    void on_actionColor_triggered();

    void on_action_S_triggered();

    void on_action_O_triggered();

    void on_actionReadText_R_triggered();

    void on_actionSize_triggered();

    void on_actionCircle_triggered();

    void on_actionEllipse_triggered();

    void on_actionRectangle_triggered();

    void on_actionClip_triggered();

    void on_actionMove_triggered();

    void on_actionScale_triggered();

    void on_actionRotate_triggered();

    void on_actionReset_triggered();

    void on_actionChoose_by_area_triggered();

    void on_actionPolygon_triggered();

    void on_actionClear_triggered();

    void on_actionCurve_triggered();

    void on_actionAlgro_triggered();

private:
    Ui::MainWindow *ui;
    QString arg1;
    QString arg2;
};
#endif // MAINWINDOW_H
