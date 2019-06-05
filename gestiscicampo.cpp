#include "gestiscicampo.h"
#include <vector>
#define VALOREA 10
#define VALOREB 20
#define VALOREC 30

int CampoDaGioco::scambia_e_gioca(int r, int c, int r1, int c1, bool gioca)
{
    if(r>=0 && r1 >=0 && r < DIM && r1 < DIM && c>=0 && c1 >=0 && c < DIM && c1 <DIM)
        std::swap(CampoGioco[r][c],CampoGioco[r1][c1]);
    else
        return -1;
    if(gioca)
        CancellaLettere();
    return 0;
}

//Restituisce vero se mi trovo nel caso in cui qualsiasi lettera metto provoca un tris
bool CampoDaGioco::ControllaLoop(int x, int y){
    if(ControlloTris('A',x,y) && ControlloTris('B',x,y) && ControlloTris('C',x,y))
        return true;
    return false;
}


//Riempie la matrice di spazi
void CampoDaGioco::AzzeraMatrici(){//Azzero tutte le matrici
    for(int i=0;i<DIM;++i){
        for(int j=0;j<DIM;++j){            
            CampoGioco[i][j] = ' ';
            DaCancellare[i][j] = false;
            GiaRiempito[i][j] = false;
        }
    }
}

/*Restituisce: 'A' 'B' o 'C' se va bene soltanto una delle lettere
oppure una a caso di quelle che van bene
*/
char CampoDaGioco::CarattereCasuale(int r, int c){
    std::vector<char> car_poss;
    for(char car = 'A';car<='C';++car){
        if(!ControlloTris(car,c,r))
            car_poss.push_back(car);
    }
    if(!car_poss.empty())
        return car_poss[rand() % car_poss.size()];

    //Se la funzione non termina prima di questo punto significa che sono in un caso in cui qualsiasi lettera metto fa un tris
    //perciò proverò a sostituire le lettere intorno, partendo dalle più vicine, con altre lettere che non provocano tris, finche non arrivo a una situazione valida
    int max = 1;//variabile che indica la posizione più lontana da cui parto a sostituire le lettere della matrice
    while(true){
        for(int r1 = -max;r1 <= max && ControllaLoop(c,r);++r1){
            for(int c1 = -max;c1 <= max && ControllaLoop(c,r);++c1){
                if(c+c1 >= 0 && c+c1 < DIM && r+r1 >= 0 && r+r1 < DIM){//Verifico di non uscire dalla matrice
                    if(!GiaRiempito[r+r1][c+c1]){//Non posso modificare caratteri appartenenti a una configurazione di gioco precedente
                        char iniziale = CampoGioco[r+r1][c+c1];
                        for(char car='A';car<='C';++car){//Sostituisco ogni lettera con un'altra che vada bene e che non sia uguale a quella iniziale
                            if(!ControlloTris(car,c+c1,r+r1) && car != iniziale  && CampoGioco[r+r1][c+c1] != ' '){
                                CampoGioco[r+r1][c+c1] = car;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if(!ControllaLoop(c,r)) break;
        ++max;//Incremento il contatore per andare a modificare lettere ancora più lontane nel caso in cui modificare quelle subito dopo non basta
        if(max > DIM-1){
            return rand() % 3 + 'A';//se il ciclo è andato in loop ritorno un carattere qualsiasi e poi cancellerò il tris che andrà a causare
        }

    }
    return CarattereCasuale(r,c);
}


//Riempie il campo con lettere casuali
void CampoDaGioco::Riempimento(int r, int c){
    if(!GiaRiempito[r][c]){//Procedo solo se non tocco le lettere che ci sono già
        CampoGioco[r][c] = CarattereCasuale(r,c);
    }
    //StampaCampo(CampoGioco,true);
    if (c-1 >= 0) Riempimento(r,c-1);//Se non ho finito la riga fai il carattere successivo
    if (c == 0 && r-1 >= 0){
        Riempimento(r-1,DIM-1);//altrimenti passa alla riga successiva
    }
}

// Ritorna vero se ci sono spazi con sopra altre lettere, ovvero quando non tutte le lettere sono "cadute"
bool CampoDaGioco::CiSonoSpazi(){
    for(int i = DIM-1; i-1 >= 0; --i){
        for(int j = DIM-1; j >= 0; --j){
            if((CampoGioco[i-1][j] >= 'A' && CampoGioco[i-1][j] <= 'C') && CampoGioco[i][j] == ' ' && i-1>=0)
                return true;
        }
    }
    return false;
}


//Controllo se vi sono tre o più lettere uguali, in tal caso restituisce vero e la direzione di tali lettere
bool CampoDaGioco::ControlloTris(char c, int x, int y){//c è il carattere da cercare, x e y le coordinate di inizio
    if(c >= 'A' && c <= 'C'){
        if(x >= 0 && y >= 0 && x < DIM && y < DIM){//Se le coordinate sono all'interno dei limiti della matrice
            //ORIZZONTALE
            if((c == CampoGioco[y][x-1] && c == CampoGioco[y][x-2] && x-2>=0) || (c == CampoGioco[y][x+1] && c == CampoGioco[y][x+2]  && x+2<DIM) || (c == CampoGioco[y][x-1] && c == CampoGioco[y][x+1]  && x-1>=0 && x+1<DIM))
                return true;
            //VERTICALE
            if((c == CampoGioco[y-1][x] && c == CampoGioco[y-2][x] && y-2>=0) || (c == CampoGioco[y+1][x] && c == CampoGioco[y+2][x]  && y+2<DIM) || (c == CampoGioco[y-1][x] && c == CampoGioco[y+1][x]  &&y-1>=0&&y+1<DIM))
                return true;
            //DIAGONALE ALTO DX/BASSO SX
            if((c == CampoGioco[y-1][x-1] && c == CampoGioco[y-2][x-2] && y-2>=0&&x-2>=0) || (c == CampoGioco[y+1][x+1] && c == CampoGioco[y+2][x+2]  &&y+2<DIM && x+2<DIM) || (c == CampoGioco[y-1][x-1] && c == CampoGioco[y+1][x+1]  && x-1>=0 && y-1>=0 && y+1<DIM && x+1<DIM))
                return true;
            //DIAGONALE ALTO DX/BASSO SX
            if((c == CampoGioco[y-1][x+1] && c == CampoGioco[y-2][x+2] &&y-2>=0&&x+2<DIM) || (c == CampoGioco[y+1][x-1] && c == CampoGioco[y+2][x-2]  &&y+2<DIM&&x-2>=0) || (c == CampoGioco[y-1][x+1] && c == CampoGioco[y+1][x-1]  &&y-1>=0&&y+1<DIM&&x+1<DIM&&x-1>=0))
                return true;
        }
    }
    return false;
}

void CampoDaGioco::MarcaTris(){
    for(int r=0;r<DIM;r++){
        for(int c=0;c<DIM;c++)
            DaCancellare[r][c] = ControlloTris(CampoGioco[r][c],c,r);
            //MarcaTris(c,r,CampoGioco[r][c]);
    }
}


bool CampoDaGioco::CancellaUnaLettera(){
    for(int r=0; r<DIM; r++){
        for(int c=0; c<DIM; c++){
            if(DaCancellare[r][c]){
                switch (CampoGioco[r][c]) {
                case 'A':
                    Punteggio += VALOREA;
                    break;
                case 'B':
                    Punteggio += VALOREB;
                    break;
                case 'C':
                    Punteggio += VALOREC;
                    break;
                default:
                    break;
                }
                CampoGioco[r][c] = ' ';                
                return true;
            }
        }
    }
    return false;
}

void CampoDaGioco::MarcaGiaRiempite(){
            for(int i=0;i<DIM;++i){
                for(int j=0;j<DIM;++j){
                    GiaRiempito[i][j] = CampoGioco[i][j] != ' ';
                }
            }
}

//Cancello tutti i tris
void CampoDaGioco::CancellaLettere(){
    if(!CampoSenzaTris()){
    MarcaTris();
        for(int i = 0; i < DIM; ++i){
            for(int j=0;j<DIM;++j){
                if(DaCancellare[i][j] && CampoGioco[i][j] >= 'A' && CampoGioco[i][j] <= 'C'){//Mi assicuro che sto cancellando una lettera e non uno spazio senno sbaglio il conteggio dei punti
                    ++ConteggioLettera[CampoGioco[i][j]-'A'];//Aggiungo un punto alla lettera cancellata
                    switch (CampoGioco[i][j]) {
                    case 'A':
                        Punteggio += VALOREA;
                        break;
                    case 'B':
                        Punteggio += VALOREB;
                        break;
                    case 'C':
                        Punteggio += VALOREC;
                        break;
                    default:
                        break;
                    }
                    //Beep((CampoGioco[i][j]-'A')*50 + 450,20
                    CampoGioco[i][j] = ' ';
                }
                DaCancellare[i][j] = false;//Rimetto a posto la matrice per evitare di togliere lettere di troppo
            }
        }
    }
    Caduta();
}

void CampoDaGioco::Caduta_step_by_step(){
    for(int i = 0; i<DIM;++i){//Rimetto a posto la matrice della caduta altrimenti cancello dei simboli in più
        for(int j=0;j<DIM;++j)
            DaCancellare[i][j] = false;
    }
    if(CiSonoSpazi()){
        for(int i = DIM-1; i > 0; --i){//Scorro la matrice dal basso verso l'alto alla ricerca di spazi
            for(int j = DIM-1; j >= 0; --j){
                if(CampoGioco[i][j] == ' '){//Se c'è uno spazio
                    int k = 1;
                    while(CampoGioco[i-k][j] == ' ' && i-k > 0) ++k;//Con il contatore k capisco quanti spazi ci sono sopra
                    if(CampoGioco[i-k][j] != ' '){
                    CampoGioco[i][j] = CampoGioco[i-k][j];//Sostituisco lo spazio trovato con la lettera che si trova sopra
                    CampoGioco[i-k][j] = ' ';//e metto uno spazio al posto di quella lettera
                    break;
                    }
                }
            }
        }
    }
}


//Sposta verso il basso le lettere con spazi sotto di esse finchè ogni lettera ha un'altra lettera o la fine della matrice sotto di essa
void CampoDaGioco::Caduta(){
    for(int i = 0; i<DIM;++i){//Rimetto a posto la matrice della caduta altrimenti cancello dei simboli in più
        for(int j=0;j<DIM;++j)
            DaCancellare[i][j] = false;
    }
    while(CiSonoSpazi()){//Va avanti a far scendere le lettere finchè non ci sono più spazi in mezzo al campo
        for(int i = DIM-1; i > 0; --i){//Scorro la matrice dal basso verso l'alto alla ricerca di spazi
            for(int j = DIM-1; j >= 0; --j){
                if(CampoGioco[i][j] == ' '){//Se c'è uno spazio
                    int k = 1;
                    while(CampoGioco[i-k][j] == ' ' && i-k > 0) ++k;//Con il contatore k capisco quanti spazi ci sono sopra
                    if(CampoGioco[i-k][j] != ' '){
                    CampoGioco[i][j] = CampoGioco[i-k][j];//Sostituisco lo spazio trovato con la lettera che si trova sopra
                    CampoGioco[i-k][j] = ' ';//e metto uno spazio al posto di quella lettera
                    }
                }
            }
        }
    }
    if(!CampoSenzaTris()) CancellaLettere();//Se ci sono ancora dei tris li cancello
    else if(da_riempire){//Altrimenti riempio gli spazi rimasti con lettere casuali
        MarcaGiaRiempite();
        Riempimento(DIM-1,DIM-1);
        if(!CampoSenzaTris()) CancellaLettere();//Se ci sono ancora dei tris (caso limite) li cancello
    }
}

bool CampoDaGioco::CampoSenzaTris(){//Questa funzione ritorna vero se il campo è privo di tris, altrimenti ritorna falso
    for(int i = 0; i < DIM; ++i){
        for(int j = 0; j < DIM; ++j){
            if(ControlloTris(CampoGioco[i][j],j,i)){
                return false;
            }
        }
    }
    return true;
}


//Funzione che simula le mosse in modo "intelligente"
MossaInt CampoDaGioco::SimulaMosse(){
    CampoDaGioco CampoInt = *this;
    CampoInt.da_riempire = true;
    CampoInt.setPunteggio(0);
    int pnt = 0;
    int riga = 0, colonna = 0, rigaN = 0, colonnaN = 0;
    for(int r = 0; r<DIM;r++){
        for(int c=0; c<DIM; c++){
            for(int r1 = -1; r1<=1;r1++){
                for(int c1 = -1; c1<=1; c1++){
                    if(r+r1>=0 && r+r1<DIM && c+c1 >= 0 && c+c1<DIM){
                        CampoInt.scambia_e_gioca(r,c,r+r1,c+c1,true);
                        if(CampoInt.getPunteggio() > pnt){
                            pnt = CampoInt.getPunteggio();
                            riga = r;
                            colonna = c;
                            rigaN = r+r1;
                            colonnaN = c+c1;
                        }
                        CampoInt = *this;
                        CampoInt.da_riempire = true;
                    }
                }
            }
        }
    }
    MossaInt mossa;
    mossa.r = riga;
    mossa.c = colonna;
    mossa.r1 = rigaN;
    mossa.c1 = colonnaN;
    mossa.punti = pnt;
    return mossa;
}


CampoDaGioco::~CampoDaGioco(){

}
