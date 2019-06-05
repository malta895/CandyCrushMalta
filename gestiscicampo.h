#ifndef GESTISCICAMPO_H
#define GESTISCICAMPO_H

#include <ctime>
#include <cstdlib>
#include <unistd.h>//Per lo sleep
#include <algorithm>
#include <QString>
//#include "finestragioco.h"

#define DIM 10

struct MossaInt
{
    int r;
    int c;
    int r1;
    int c1;
    int punti;
};

class CampoDaGioco
{
private:
    int ConteggioLettera[3] = {0,0,0};//Numero di lettere cancellate: 0 = numero di A, 1 = numero di B, 2 numero di C
    int Punteggio = 0;    
    bool da_riempire = true;//serve per capire se devo riempire il campo dopo la caduta(false in mossa intelligente)
    bool GiaRiempito[DIM][DIM];
    char CampoGioco[DIM][DIM];
    bool DaCancellare[DIM][DIM];
public:       
    CampoDaGioco() { }
    CampoDaGioco(bool riempi) {
        srand(time(0));
        AzzeraMatrici();
        if(riempi)
            Riempimento(DIM-1,DIM-1);
    }
    CampoDaGioco(char matrice[DIM][DIM])
    {
        srand(time(0));
        AzzeraMatrici();
        for(int i=0;i<DIM;++i){
            for(int j=0;j<DIM;++j)
                CampoGioco[i][j] = matrice[i][j];
        }
    }

    ~CampoDaGioco();
    char get_campo_gioco(int r, int c) {return CampoGioco[r][c];}
    bool is_da_cancellare(int r, int c) {return DaCancellare[r][c];}
    void set_da_cancellare(int r, int c, bool da_cancellare) {DaCancellare[r][c] = da_cancellare;}
    int scambia_e_gioca(int r, int c, int r1, int c1, bool gioca);
    bool ControllaLoop(int x, int y);
    bool CampoSenzaTris();
    bool ControlloTris(char c, int x, int y);
    bool CiSonoSpazi();
    char CarattereCasuale(int r, int c);
    void Riempimento(int r, int c);
    void AzzeraMatrici();
    MossaInt SimulaMosse();
    void CancellaLettere();
    void Caduta();
    bool CancellaUnaLettera();
    void MarcaTris();
    void MarcaGiaRiempite();
    void Caduta_step_by_step();
    int getPunteggio(){return Punteggio;}
    void setPunteggio(int p){Punteggio = p;}

};


#endif // GESTISCICAMPO_H

