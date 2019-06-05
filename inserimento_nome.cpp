#include "inserimento_nome.h"
#include "ui_inserimento_nome.h"
#include "finestragioco.h"
#include "ui_finestragioco.h"
#include <QMessageBox>
inserimento_nome::inserimento_nome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inserimento_nome)
{
    ui->setupUi(this);
    this->setMaximumSize(this->size());
    this->setMinimumSize(this->size());
}

inserimento_nome::~inserimento_nome()
{
    delete ui;
}

void inserimento_nome::on_buttonBox_accepted()
{
    if(ui->lineEditNome->text() == NULL){
        QMessageBox::critical(this,"Errore!","Inserire un nome valido!");
    }else{
        nome = ui->lineEditNome->text();
        OK = true;
        FinestraGioco *finestra = new FinestraGioco(0);
        finestra->setPlayer(nome);
        this->close();
        this->destroy();
        this->deleteLater();
        finestra->show();
    }
}
