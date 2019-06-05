#ifndef INSERIMENTO_NOME_H
#define INSERIMENTO_NOME_H

#include <QDialog>

namespace Ui {
class inserimento_nome;
}

class inserimento_nome : public QDialog
{
    Q_OBJECT
private:
    Ui::inserimento_nome *ui;
    bool OK = false;
    QString nome;
public:
    explicit inserimento_nome(QWidget *parent = 0);
    bool isOK(){return OK;}
    QString getNome(){return nome;}
    ~inserimento_nome();
private slots:
    void on_buttonBox_accepted();



};

#endif // INSERIMENTO_NOME_H
