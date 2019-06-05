#ifndef CLASSIFICA_H
#define CLASSIFICA_H
#include <vector>
#include <fstream>
#include <QString>

//#include "giocatori.h"

#define FILEGIOCATORI "../CandyCrushGUI/FileDati/giocatori.dat"


using std::fstream;
using std::ifstream;
using std::ofstream;
using std::vector;

struct Giocatore
{
    int record = 0;
    int punteggio = 0;
    QString nome;
    bool operator< (const Giocatore &rhs)
    {
        return rhs.record>this->record;
    }
};

class Classifica
{
private:
    vector<Giocatore> Players;

public:
    Classifica();
    ~Classifica();
    int addPlayer(Giocatore player);
    void CaricaGiocatori();
    int EsisteGiocatore(QString NomeGioc);
    void SortClassifica();
    void SalvaGiocatori();
    vector<Giocatore> getClassifica(){return Players;}
    void AggiornaGiocatore(Giocatore &g);
    Giocatore getPlayer(size_t index);

};

#endif // CLASSIFICA_H
