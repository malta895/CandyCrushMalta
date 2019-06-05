#include "sequenziale.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Sequenziale::Sequenziale()
{

}

Sequenziale::~Sequenziale()
{

}

using namespace std;

int Sequenziale::LeggiSeq(QString nome_file){
    /* Codici errore:
     * -1: file non esistente o non accessibile
     * -2: il campo da gioco nel file contiene tris
     * -3: sintassi del file errata
     */
    QFile file_seq(nome_file);//apro il file
    if (!file_seq.open(QIODevice::ReadOnly | QIODevice::Text))//Apro il file in sola lettura verificando se esiste
        return -1;//se non esiste ritorno -1
    QTextStream stream_file(&file_seq);
    QChar car;
    int r=0, c=0;
    char matrice[DIM][DIM];
    while(!stream_file.atEnd())
    {
        stream_file >> car;
        switch(car.toLatin1())
        {
        case ';':
            c=0;
            r++;
            if(r>DIM)
            {
                file_seq.close();
                return -3;
            }
            break;
        case ',':
            c++;
            if(c>DIM)
            {
                file_seq.close();
                return -3;
            }
            break;
        default:
            if(car.toLatin1() >= 'A' && car.toLatin1() <= 'C')
            {
                matrice[r][c] = car.toLatin1();
                qDebug() << matrice[r][c];
            }else{
                file_seq.close();
                return -3;
            }
            break;
        }
    }
    CampoDaGioco CampoSeq(matrice);
    CampoSequenziale = CampoSeq;
    CampoIniziale = CampoSequenziale;
    if(!CampoSequenziale.CampoSenzaTris())
    {
        file_seq.close();
        return -2;
    }
    file_seq.close();
    return 0;
}

int Sequenziale::LeggiMosse(QString nome_file)
{
    /*Codici errore:
     * -1: file non esistente o non accessibile
     * -2: sintassi file non valida
     */
    QFile file_mosse(nome_file);
    if (!file_mosse.open(QIODevice::ReadOnly | QIODevice::Text))//file non esistente o non accessibile
        return -1;
    QTextStream stream_file(&file_mosse);
    QChar carattere;
    Mossa mossa_attuale;
    int cnt = 0;//se e' 0 leggo la riga, 1 la colonna, 2 la direzione
    char car = 0;
    while(!stream_file.atEnd())
    {
        stream_file >> carattere;
        //qDebug() << carattere;
        car = carattere.toLatin1();
        switch (car) {
        case '\n':
            break;
        case ',':
            ++cnt;
            break;
        case ';':
            mosse.push_back(mossa_attuale);
            cnt=0;
            break;
        default:
            int num = car - '0';
            if(num >= 0 && num < DIM)
            {
                switch (cnt) {
                case 0:
                    mossa_attuale.r = num;
                    break;
                case 1:
                    mossa_attuale.c = num;
                    break;
                case 2:
                    if(num >= 0 && num <= 8)
                        mossa_attuale.direzione = num;
                    else
                    {
                        qDebug() << "direzione non valida";
                        return -2;
                    }
                    break;
                default:
                    qDebug() << "sintassi errata";
                    return -2;
                }
            }else
            {
                qDebug() << "Troppe righe/colonne";
                qDebug() << carattere;
                return -2;
            }
            break;
        }
    }
    return 0;
}

void Sequenziale::esegui_mosse()
{
    int x,y;
    for(size_t i = 0; i < mosse.size(); ++i)
    {
        y = mosse.at(i).r;
        x = mosse.at(i).c;
        switch (mosse.at(i).direzione)
        {
        case 1://sopra
            if(y-1>=0)
                CampoSequenziale.scambia_e_gioca(y,x,y-1,x,true);
                //swap(CampoSequenziale.CampoGioco[y][x],CampoSequenziale.CampoGioco[y-1][x]);
            break;
        case 2://sotto
            if(y+1<DIM)
                CampoSequenziale.scambia_e_gioca(y,x,y+1,x,true);
                //swap(CampoSequenziale.CampoGioco[y][x],CampoSequenziale.CampoGioco[y+1][x]);
            break;
        case 3://destra
            if(x+1<DIM)
                CampoSequenziale.scambia_e_gioca(y,x,y,x+1,true);
                //swap(CampoSequenziale.CampoGioco[y][x],CampoSequenziale.CampoGioco[y][x+1]);
            break;
        case 4://sinistra
            if(x-1>=0)
                CampoSequenziale.scambia_e_gioca(y,x,y,x-1,true);
                //swap(CampoSequenziale.CampoGioco[y][x],CampoSequenziale.CampoGioco[y][x-1]);
            break;
        case 5://diagonale alto destra
            if(y-1>=0 && x+1<DIM)
                CampoSequenziale.scambia_e_gioca(y,x,y-1,x+1,true);
                //swap(CampoSequenziale.CampoGioco[y][x],CampoSequenziale.CampoGioco[y-1][x+1]);
            break;
        case 6://diagonale alto sinistra
            if(y-1>=0 && x-1>=0)
                CampoSequenziale.scambia_e_gioca(y,x,y-1,x-1,true);
                //swap(CampoSequenziale.CampoGioco[y][x],CampoSequenziale.CampoGioco[y-1][x-1]);
            break;
        case 7://diagonale basso destra
            if(y+1<DIM && x+1<DIM)
                CampoSequenziale.scambia_e_gioca(y,x,y+1,x+1,true);
                //swap(CampoSequenziale.CampoGioco[y][x],CampoSequenziale.CampoGioco[y+1][x+1]);
            break;
        case 8://diagonale basso sinistra
            if(y+1<DIM && x-1>=0)
                CampoSequenziale.scambia_e_gioca(y,x,y+1,x-1,true);
                //swap(CampoSequenziale.CampoGioco[y][x],CampoSequenziale.CampoGioco[y+1][x-1]);
            break;
        }
        //CampoSequenziale.CancellaLettere();
    }
}



int Sequenziale::SalvaCampo(QString nome_file){
    QFile file_out(nome_file);
    if (!file_out.open(QIODevice::WriteOnly | QIODevice::Text))//Apro il file in scrittura
        return -1;
    QTextStream stream_campo_out(&file_out);
    for(int i=0;i<DIM;++i){
        for(int j=0;j<DIM;++j){
           stream_campo_out << CampoSequenziale.get_campo_gioco(i,j);
           if(j<DIM-1) stream_campo_out << ',';
        }
        stream_campo_out << ';';
    }
    file_out.close();
    return 0;
}
