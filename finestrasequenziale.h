#ifndef FINESTRASEQUENZIALE_H
#define FINESTRASEQUENZIALE_H

#include <QDialog>
#include "sequenziale.h"

namespace Ui {
class FinestraSequenziale;
}

class FinestraSequenziale : public QDialog
{
    Q_OBJECT
private:
    Ui::FinestraSequenziale *ui;
    Sequenziale seq;
    int codice_err_seq = -4;
    int codice_err_mosse = -4;

public:
    explicit FinestraSequenziale(QWidget *parent = 0);
    ~FinestraSequenziale();

private slots:
    void on_sfoglia_conf_iniziale_clicked();

    void on_sfoglia_mosse_clicked();


    void on_bottone_genera_campo_clicked();
};

#endif // FINESTRASEQUENZIALE_H
