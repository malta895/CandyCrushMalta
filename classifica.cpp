#include "classifica.h"
#include <algorithm>
#include "math.h"

Classifica::Classifica()
{
    CaricaGiocatori();
}

Classifica::~Classifica()
{

}

using std::ios;

void Classifica::CaricaGiocatori(){//Legge dal file la lista dei giocatori e le inserisce in un vettore
    ifstream FileGiocatore(FILEGIOCATORI,ios::in);
    if(FileGiocatore){
        enum in_lettura {punteggioo,nomee};
        in_lettura leggendo = nomee;
        Giocatore PlayerAtt;
        QString nomeAtt;
        int recordAtt = 0;
        char car;
        while(!FileGiocatore.eof()){//Riempio il vettore con le info contenute nel file
            FileGiocatore >> car;
            switch (car) {
            case ';':
                if(!nomeAtt.isEmpty()){
                    PlayerAtt.nome = nomeAtt;
                    PlayerAtt.record = recordAtt;
                    Players.push_back(PlayerAtt);//lo salvo nel vettore
                    nomeAtt.clear();//cancello i dati temporanei
                    recordAtt = 0;
                }
                leggendo = nomee;
                break;
            case ',':
                leggendo = punteggioo;
                break;
            default:
                switch (leggendo) {
                case nomee:
                    nomeAtt += QChar::fromLatin1(car);
                    break;
                case punteggioo:
                    recordAtt = (recordAtt * 10) + (car - '0');
                    break;
                }
                break;
            }
        }
        if(Players.size()>0)
            SortClassifica();//Riordino la Classifica
    } else { //create classifica if doesn't exist
      FileGiocatore.close();
      ofstream new_file;
      new_file(FILEGICATORI, ios::out);
      new_file.close()
    }
    FileGiocatore.close();
}

void Classifica::SortClassifica(){

            std::sort(Players.begin(),Players.end());

}

int Classifica::EsisteGiocatore(QString NomeGioc){//Se il Giocatore esiste ritorna l'indice in cui si trova nel vettore, altrimenti ritorna -1
    for(size_t i=0;i<Players.size();i++){
        if(Players.at(i).nome == NomeGioc)
           return i;
    }
    return -1;
}


int Classifica::addPlayer(Giocatore player){//Aggiungo il Giocatore attuale alla lista degli altri o aggiorno i dati del Giocatore già esistente e salvo nel file
    int index = EsisteGiocatore(player.nome);
    if(index != -1){
        Players.at(index) = player;        
    }else{
       Players.push_back(player);
    }
    SortClassifica();
    SalvaGiocatori();
    return EsisteGiocatore(player.nome);
}


void Classifica::SalvaGiocatori(){
    SortClassifica();
    ofstream FileGioc(FILEGIOCATORI,ios::out | ios::trunc);//Apre in scrittura il file e ne cancella il contenuto
    for(size_t i=0;i<Players.size();i++)//e scrive nel file i punteggi leggendoli dal vettore
        FileGioc << Players.at(i).nome.toStdString() << ',' << Players.at(i).record << ';';//separati da punti e virgola
    FileGioc.close();
}

void Classifica::AggiornaGiocatore(Giocatore &g)
{
    int index = EsisteGiocatore(g.nome);
    if(index != -1)
    {
        if(g.punteggio > Players.at(index).record)
        {
            Players.at(index) = g;
        }
    }else
    {
        g.record = g.punteggio;
        addPlayer(g);
    }
    SortClassifica();
    SalvaGiocatori();
}

Giocatore Classifica::getPlayer(size_t index)
{
    for(size_t i = 0; i<Players.size(); i++)
    {
        if(i == index) return Players.at(index);
    }
    return Giocatore();
}

