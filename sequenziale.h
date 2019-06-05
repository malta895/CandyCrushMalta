#ifndef SEQUENZIALE_H
#define SEQUENZIALE_H

#include <fstream>
#include <algorithm>
#include <QString>
#include <vector>
#include <QDebug>
#include "gestiscicampo.h"

#define FILESEQ "../CandyCrushGUI/FileDati/sequenziale.dat"
#define FILEMOSSE "../CandyCrushGUI/FileDati/mosse.dat"
#define FILESALVATAGGIO "../CandyCrushGUI/FileDati/campo.dat"

struct Mossa
{
    int r;
    int c;
    int direzione;
};

class Sequenziale
{
private:
    CampoDaGioco CampoSequenziale = CampoDaGioco(false);
    CampoDaGioco CampoIniziale = CampoDaGioco(false);
    std::vector<Mossa> mosse;
public:
    Sequenziale();
    ~Sequenziale();
    std::vector<Mossa> restituisci_mosse(){return mosse;}
    char campo_gioco(int r,int c) {
        return CampoSequenziale.get_campo_gioco(r,c);
    }
    void esegui_mosse();
    void azzera_seq(){CampoSequenziale = CampoIniziale;}
    int LeggiMosse(QString nome_file);
    int SalvaCampo(QString nome_file);
    int LeggiSeq(QString nome_file);
};

#endif // SEQUENZIALE_H
