#include "finestrasequenziale.h"
#include "ui_finestrasequenziale.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

FinestraSequenziale::FinestraSequenziale(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinestraSequenziale)
{
    ui->setupUi(this);
    this->setMaximumSize(this->size());
    this->setMinimumSize(this->size());
}

FinestraSequenziale::~FinestraSequenziale()
{
    delete ui;
}

void FinestraSequenziale::on_sfoglia_conf_iniziale_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,tr("Apri file"), FILESEQ, tr("Any file (*.*)"));
    codice_err_seq = seq.LeggiSeq(file_name);
    QString testo;
    switch(codice_err_seq)
    {
    case 0:
        testo += QChar(' ');
        testo += QChar(' ');
        for(int i=0;i<DIM;++i)
        {
            testo += QString::number(i);
            if(i!=DIM-1) testo += QChar(' ');
        }
        testo += QChar('\n');
        for(int r=0;r<DIM;r++){
            testo += QString::number(r);
            testo += QChar(' ');
            for(int c=0;c<DIM;c++){
                testo += QChar::fromLatin1(seq.campo_gioco(r,c));
                //qDebug() << seq.campo_gioco(r,c);
                if(c!=DIM-1)
                    testo += QChar(' ');
            }
            testo += QChar('\n');
        }
        ui->text_campo_iniziale->setText(testo);
        if(codice_err_mosse == 0)
            ui->bottone_genera_campo->setEnabled(true);
        break;
    case -1:
        QMessageBox::critical(this,"File non valido!","Il file selezionato è vuoto o non esiste!");
        break;
    case -2:
        QMessageBox::critical(this,"File non valido!","Il campo da gioco nel file contiene tris!");
        break;
    case -3:
        QMessageBox::critical(this,"File non valido!","Il campo da gioco nel file non è valido!");
        break;
    }
}

void FinestraSequenziale::on_sfoglia_mosse_clicked()
{
    QString file_mosse;
    file_mosse = QFileDialog::getOpenFileName(this,tr("Apri file"), FILESEQ, tr("Any file (*.*)"));
    codice_err_mosse = seq.LeggiMosse(file_mosse);
    QString testo_mosse;
    std::vector<Mossa> mosse;
    switch (codice_err_mosse) {
    case 0:
        mosse = seq.restituisci_mosse();
        for(size_t i = 0; i < mosse.size(); ++i)
        {
            testo_mosse += "Sposto la lettera in riga ";
            testo_mosse += QString::number(mosse.at(i).r);
            testo_mosse += " colonna ";
            testo_mosse += QString::number(mosse.at(i).c);
            switch (mosse.at(i).direzione)
            {
            case 1://sopra
                testo_mosse += " verso l'alto.";
                break;
            case 2://sotto
                testo_mosse += " verso il basso.";
                break;
            case 3://destra
                testo_mosse += " verso destra.";
                break;
            case 4://sinistra
                testo_mosse += " verso sinistra.";
                break;
            case 5://diagonale alto destra
                testo_mosse += " in alto a destra.";
                break;
            case 6://diagonale alto sinistra
                testo_mosse += " in alto a sinistra.";
                break;
            case 7://diagonale basso destra
                testo_mosse += " in basso a destra.";
                break;
            case 8://diagonale basso sinistra
                testo_mosse += " in basso a sinistra.";
            }
            testo_mosse += '\n';
        }
        ui->text_mosse->setText(testo_mosse);
        if(codice_err_seq == 0)
            ui->bottone_genera_campo->setEnabled(true);
        break;
    case -1:
        QMessageBox::critical(this,"File non valido!","Il file selezionato è vuoto o non esiste!");
        break;
    case -2:
        QMessageBox::critical(this,"File non valido!","Il file selezionato non è valido!");
        break;
    }

}

void FinestraSequenziale::on_bottone_genera_campo_clicked()
{
    seq.esegui_mosse();
    QString testo;
    testo += QChar(' ');
    testo += QChar(' ');
    for(int i=0;i<DIM;++i)
    {
        testo += QString::number(i);
        if(i!=DIM-1) testo += QChar(' ');
    }
    testo += QChar('\n');
    for(int r=0;r<DIM;r++){
        testo += QString::number(r);
        testo += QChar(' ');
        for(int c=0;c<DIM;c++){
            testo += QChar::fromLatin1(seq.campo_gioco(r,c));
            if(c!=DIM-1)
                testo += QChar(' ');
        }
        testo += QChar('\n');
    }
    ui->text_campo_finale->setText(testo);
    int salva = QMessageBox::question(this,"Salvare in un file?","Si desidera salvare la configurazione di gioco ottenuta in un file?",QMessageBox::Yes, QMessageBox::No);
    if(salva == QMessageBox::Yes)
    {
        QString percorso_da_salvare;
        percorso_da_salvare = QFileDialog::getSaveFileName(this,tr("Salva file"), FILESALVATAGGIO, tr("Any file (*.*)"));
        seq.SalvaCampo(percorso_da_salvare);
    }
    seq.azzera_seq();
}
