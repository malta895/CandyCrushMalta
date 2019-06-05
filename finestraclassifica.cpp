#include "finestraclassifica.h"
#include "ui_finestraclassifica.h"

#include <QLabel>
#include <QMessageBox>


FinestraClassifica::FinestraClassifica(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinestraClassifica)
{    
    ui->setupUi(this);

    this->setMaximumSize(this->size());
    this->setMinimumSize(this->size());


    vector<Giocatore> Players = classif.getClassifica();
    QString testo_nome;
    QString testo_record;    
    for(int i = Players.size()-1; i>=0; --i)
    {
        QLabel *label_classifica_nome = new QLabel(this);
        QLabel *label_classifica_record = new QLabel(this);
        label_classifica_v.push_back(label_classifica_nome);//Salvo i puntatori in un vettore per poter fare il delete alla fine
        label_classifica_v.push_back(label_classifica_record);
        testo_nome += QString::number(Players.size()-i);//posizione in classifica
        testo_nome += ". ";
        testo_nome += Players.at(i).nome;
        testo_record += QString::number(Players.at(i).record);
        label_classifica_nome->setText(testo_nome);
        label_classifica_record->setText(testo_record);
        ui->layout_classifica_nome->addWidget(label_classifica_nome);
        ui->layout_classifica_record->addWidget(label_classifica_record);
        label_classifica_nome->setAlignment(Qt::AlignLeading);
        label_classifica_record->setAlignment(Qt::AlignLeading);
        testo_nome.clear();
        testo_record.clear();
    }
}

FinestraClassifica::~FinestraClassifica()
{
    for(size_t i = 0; i < label_classifica_v.size(); i++)
        delete label_classifica_v[i];
    delete ui;
}

void FinestraClassifica::on_chiudiClassifica_clicked()
{
    this->close();
    this->destroy();
}
