#ifndef FINESTRAGIOCO_H
#define FINESTRAGIOCO_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QMessageBox>
#include <QWidget>
#include <QGridLayout>
#include <QSound>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSignalMapper>
#include <QTimer>//Al posto dello sleep
#include <string>
#include <QIcon>
#include <QDebug>
#include <QString>
#include <QResource>
#include <QDir>



#include "gestiscicampo.h"
#include "finestraclassifica.h"
//#include "ui_finestraClassifica.h"


#define CARAMELLA_ROSSA ":/immagini/granata_rossa.png"
#define CARAMELLA_VERDE ":/immagini/granata_verde.png"
#define CARAMELLA_BLU ":/immagini/granata_blu.png"
#define ESPLOSIONE ":/immagini/maxresdefault.png"

#define MOSSE_MAX 5

namespace Ui {
class FinestraGioco;
}


class FinestraGioco : public QMainWindow
{
     Q_OBJECT
private:
    Ui::FinestraGioco *ui;
    QGridLayout *griglia = new QGridLayout(this);
    QPushButton *bottone[DIM][DIM];
    QSound *esplosione = new QSound(":/suoni/sparo.wav",this);
    QSound *sottofondo = new QSound(":/suoni/sottofondo.wav",this);
    QIcon *immagine_A = new QIcon(CARAMELLA_ROSSA);
    QIcon *immagine_B = new QIcon(CARAMELLA_VERDE);
    QIcon *immagine_C = new QIcon(CARAMELLA_BLU);
    QIcon *boom = new QIcon(ESPLOSIONE);
    QSignalMapper *mapper[DIM][DIM];
    struct Coordinate{
        int x = 0;
        int y = 0;
    } CoordAtt;
    bool prima_volta = true;
    bool isFinita = false;
    CampoDaGioco Campo = CampoDaGioco(true);
    int Mosse = MOSSE_MAX;
    Classifica classifica;
    Giocatore player;
    bool is_new_player;
    bool gioco_in_corso = false;
private slots:
    void on_actionEsci_triggered();

    void on_actionMossa_intelligiente_triggered();

    void on_actionNuova_partita_triggered();

signals:
    void clicked(int &rc);

public:
    explicit FinestraGioco(QWidget *parent = 0);
    void stampa_campo();
    void aggiorna_campo(bool after_boom);
    QString seleziona_caramella(bool isCentrale, int r, int c);
    void setPlayer(QString nome);
    ~FinestraGioco();

public slots:
    void passa_posizione(int rc);
    void cancella_prossima();//è uno slot perchè lo chiamo con un QTimer
    void finePartita();
};



#endif // FINESTRAGIOCO_H
