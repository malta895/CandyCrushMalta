#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "finestraclassifica.h"
#include "ui_finestraclassifica.h"
#include "inserimento_nome.h"
#include "ui_inserimento_nome.h"
#include "sequenziale.h"
#include "finestrasequenziale.h"
#include "ui_finestrasequenziale.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMaximumSize(this->size());
    this->setMinimumSize(this->size());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bottoneGioca_clicked()
{
    inserimento_nome *nickname_dialog = new inserimento_nome(0);
    nickname_dialog->exec();
    if(nickname_dialog->isOK()){
        this->close();
        this->destroy(true,true);
    }
}

void MainWindow::on_actionEsci_triggered()
{
    this->close();
    this->destroy();
    this->deleteLater();
}

void MainWindow::on_pushButton_clicked()
{    
    FinestraClassifica *fin_classifica = new FinestraClassifica;
    fin_classifica->exec();
  }

void MainWindow::on_bottone_sequenziale_clicked()
{

    FinestraSequenziale *f= new FinestraSequenziale(0);
    f->exec();
}
