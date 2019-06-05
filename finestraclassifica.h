#ifndef FINESTRACLASSIFICA_H
#define FINESTRACLASSIFICA_H

#include <QWidget>
#include <QDialog>
#include <QLabel>

#include "classifica.h"

namespace Ui {
class FinestraClassifica;
}

class FinestraClassifica : public QDialog
{
    Q_OBJECT


private:
    Ui::FinestraClassifica *ui;
    Classifica classif;
    Giocatore da_evidenziare;
    vector<QLabel*> label_classifica_v;

public:
    explicit FinestraClassifica(QWidget *parent = 0);
    FinestraClassifica(Classifica c) : classif(c) {}
    void set_evidenziato(Giocatore p) {da_evidenziare = p;}
    ~FinestraClassifica();

private slots:
    void on_chiudiClassifica_clicked();

};

#endif // FINESTRACLASSIFICA_H
