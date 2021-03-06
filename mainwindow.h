#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bottoneGioca_clicked();

    void on_actionEsci_triggered();

    void on_pushButton_clicked();

    void on_bottone_sequenziale_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
