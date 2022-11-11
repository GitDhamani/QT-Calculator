#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

void NumPressed();
void MathNumPressed();
void clearALL();
void EqualsPressed();
void changesign();
void addmem();
void submem();
void recallmem();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
