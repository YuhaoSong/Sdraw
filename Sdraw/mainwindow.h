#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphlibrary.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
