#include "finestragioco.h"
#include "ui_finestragioco.h"
#include "inserimento_nome.h"
#include "ui_inserimento_nome.h"
#include <QTimer>


FinestraGioco::FinestraGioco(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinestraGioco)
{
    ui->setupUi(this);
    sottofondo->setLoops(-1);//Il sottofondo viene eseguito in loop infinito
    sottofondo->play();
    ui->labelMosseRimaste->setText(QString::number(Mosse));
    ui->label_new_record->setVisible(false);//Nascondo il label nuovo record
    stampa_campo();
    ui->AreaGioco->setLayout(griglia);
    ui->AreaGioco->adjustSize();


    this->setMaximumSize(this->size());
    this->setMinimumSize(this->size());
}

FinestraGioco::~FinestraGioco()
{//devo cancellare con delete tutto ciò che ho creato dinamicamente
    for(int i=0;i<DIM;i++){
        for(int j=0;j<DIM;j++){
            delete mapper[i][j];
            delete bottone[i][j];
        }
    }
    delete sottofondo;
    delete esplosione;
    delete immagine_A;
    delete immagine_B;
    delete immagine_C;
    delete ui;
}

void FinestraGioco::cancella_prossima(){    
    if(Campo.CancellaUnaLettera()){//Continuo finchè ci sono lettere da cancellare
        QTimer::singleShot(80,this,SLOT(cancella_prossima()));
        player.punteggio = Campo.getPunteggio();
        ui->labelPunti->setText(QString::number(Campo.getPunteggio()));
        if(player.punteggio > player.record)//Nuovo record!
        {
            player.record = player.punteggio;
            ui->labelRecord->setText(QString::number(player.record));//aggiorno la grafica
            if(!is_new_player){//Nuovo record solo se il giocatore ha già giocato in precedenza
                ui->labelRecord->setStyleSheet("color: red");
                ui->label_new_record->setVisible(true);
            }
        }
        aggiorna_campo(true);
        esplosione->play();//suono esplosione
    }else{//Se non c'e' piu' niente da cancellare
        if(Campo.CiSonoSpazi()){//Finchè c'e da far cader roba
            Campo.Caduta_step_by_step();//la faccio cadere
            aggiorna_campo(false);
            int time = 150;
            if(!Campo.CiSonoSpazi()){
                time = 500;
                Campo.MarcaTris();
                aggiorna_campo(false);
            }
            QTimer::singleShot(time,this,SLOT(cancella_prossima()));//e richiamo la funzione
            return;//esco perchè se va avanti succede un casino
        }
        if(!Campo.CampoSenzaTris()){
            //Nel caso in cui la caduta ha causato altri tris ricomincio da capo
            Campo.MarcaTris();
            cancella_prossima();
        }else{//altrimenti finisce la Mosse
            Campo.MarcaGiaRiempite();
            Campo.Riempimento(DIM-1,DIM-1);
            aggiorna_campo(false);
            if(!Campo.CampoSenzaTris()){
                Campo.MarcaTris();
                aggiorna_campo(false);
                QTimer::singleShot(1000,this,SLOT(cancella_prossima()));
            }else{
                griglia->setEnabled(true);
                if(Mosse == 0) finePartita();
            }
        }
    }   
}




void FinestraGioco::finePartita(){
    isFinita = true;
    for(int r=0;r<DIM;r++){
        for(int c=0;c<DIM;c++){
            bottone[r][c]->setDisabled(true);
        }
    }
    player.punteggio = Campo.getPunteggio();
    if(player.punteggio > player.record)
        player.record = player.punteggio;
    classifica.AggiornaGiocatore(player);
    FinestraClassifica *fin_class = new FinestraClassifica;

    fin_class->exec();
}

void FinestraGioco::passa_posizione(int rc)
{
    if(griglia->isEnabled()){//Se provo a giocare mentre la griglia e' disattiva, ovvero quando e' in corso un timer per la caduta o il cancellamento, non succede nulla
        Coordinate CoordPrec;
        if(!prima_volta)
            CoordPrec = CoordAtt;
        CoordAtt.y = rc / 10;//Mi ricavo la riga
        CoordAtt.x = rc % 10;//Mi ricavo la colonna
        if(!prima_volta){
            if(CoordAtt.x-CoordPrec.x > 1 || CoordAtt.x-CoordPrec.x < -1 || CoordAtt.y-CoordPrec.y > 1 || CoordAtt.y-CoordPrec.y < -1){
                //Se il Giocatore prova a scambiare caramelle non adiacenti fra di loro rimetto le variabili a posto e esco dalla funzione
                CoordAtt = CoordPrec;
                return;
            }                       
            //std::swap(Campo.CampoGioco[CoordPrec.y][CoordPrec.x],Campo.CampoGioco[CoordAtt.y][CoordAtt.x]);
            Campo.scambia_e_gioca(CoordPrec.y,CoordPrec.x,CoordAtt.y,CoordAtt.x,false);
           if(!(CoordAtt.x == CoordPrec.x && CoordAtt.y == CoordPrec.y)){//Decremento il contatore delle mosse solo se non ho cliccato due volte sullo stesso simbolo
               Mosse--;
               ui->labelMosseRimaste->setText(QString::number(Mosse));//Aggiorno sulla grafica il numero di mosse rimaste
            }
            if(!Campo.CampoSenzaTris()){//Se ci sono dei tris li faccio saltare
                griglia->setEnabled(false);//Setto la griglia a disabled sia per evitare un cambio di dimensione dei bottoni quando viene loro rimossa l'icona, sia per capire se devo ignorare il click su di essi
                Campo.MarcaTris();
                aggiorna_campo(false);
                QTimer::singleShot(1000,this,SLOT(cancella_prossima()));
            }else{//altrimenti aggiorno semplicemente il campo da gioco
                aggiorna_campo(false);
                if(Mosse == 0) finePartita();
            }
        }else{//Se ho cliccato una caramella soltanto evidenzio le caramelle con cui posso scambiarla
            for(int r=-1; r<=1; ++r){
                for(int c=-1; c<=1; ++c){
                    if(CoordAtt.y+r < DIM && CoordAtt.y+r >= 0 && CoordAtt.x+c < DIM && CoordAtt.x+c >=0)
                        bottone[CoordAtt.y+r][CoordAtt.x+c]->setStyleSheet("background-color: red");//Evideonzio in rosso le caramelle verso cui posso spostare
                }
            }
            bottone[CoordAtt.y][CoordAtt.x]->setStyleSheet("background-color: blue");//e in blu la caramella selezionata
        }
        prima_volta = !prima_volta;
    }
}


void FinestraGioco::aggiorna_campo(bool after_boom){
//Confronta la matrice di gioco con quella grafica e sistema le immagini con le lettere corrispondenti
    for(int r=0;r<DIM;++r){
        for(int c=0;c<DIM;++c){
            bottone[r][c]->setStyleSheet("background-color:black");//Riporto il background dei pulsanti al valore predefinito
            switch (Campo.get_campo_gioco(r,c)) {
            case 'A':
                if(Campo.is_da_cancellare(r,c))//Evidenzio eventuali tris
                    bottone[r][c]->setStyleSheet("background-color: red");
                bottone[r][c]->setIcon(*immagine_A);
                break;
            case 'B':
                if(Campo.is_da_cancellare(r,c))
                    bottone[r][c]->setStyleSheet("background-color: green");
               bottone[r][c]->setIcon(*immagine_B);
                break;
            case 'C':
                if(Campo.is_da_cancellare(r,c))
                    bottone[r][c]->setStyleSheet("background-color: blue");
                bottone[r][c]->setIcon(*immagine_C);
                break;
            case ' ':
                if(after_boom && Campo.is_da_cancellare(r,c)){
                    bottone[r][c]->setIcon(QIcon(*boom));//Mostro l'immagine dell'esplosione
                    Campo.set_da_cancellare(r,c,false);//contrassegno la caramella esplosa come non appartenente a un tris
                }else{
                    bottone[r][c]->setIcon(QIcon());//tolgo l'immagine dalla caramella esplosa
                }
                    break;
            }
        }
    }
}

void FinestraGioco::stampa_campo(){
    int caramellaIndex = 0;
    for(int r=0;r<DIM;++r){
        for(int c=0;c<DIM;++c){
            mapper[r][c] = new QSignalMapper(this);
            bottone[r][c] = new QPushButton(this);            
            bottone[r][c]->setStyleSheet("background-color: black");
            bottone[r][c]->setGeometry(c,r,65,65);
            switch (Campo.get_campo_gioco(r,c)) {//In base a che lettera trovo nella matrice scelgo la caramella
            case 'A':
                bottone[r][c]->setIcon(*immagine_A);
                break;
            case 'B':
                bottone[r][c]->setIcon(*immagine_B);
                break;
            case 'C':
                bottone[r][c]->setIcon(*immagine_C);
                break;
            default:
                QMessageBox::critical(this,"Errore!","Si e' verificato un errore nella generazione del campo da gioco!");
                break;
            }
            bottone[r][c]->setIconSize(bottone[r][c]->size());
            connect(bottone[r][c],SIGNAL(clicked()),mapper[r][c],SLOT(map()));
            mapper[r][c]->setMapping(bottone[r][c],caramellaIndex);//serve per prendere i valore intero che rappresenta l'indice della posizione della caramella
            connect(mapper[r][c],SIGNAL(mapped(int)),this,SLOT(passa_posizione(int)));
            griglia->addWidget(bottone[r][c],r,c);            
            caramellaIndex++;
        }
    }    
}


void FinestraGioco::setPlayer(QString nome)
{
    player.nome = nome;
    int index = classifica.EsisteGiocatore(player.nome);
    if(index != -1)
    {
        player = classifica.getPlayer(index);
        is_new_player = false;
    }else
    {
        player.record = 0;
        classifica.addPlayer(player);
        is_new_player = true;
    }
    ui->labelRecord->setText(QString::number(player.record));
    ui->labelNome->setText(player.nome);
}



void FinestraGioco::on_actionEsci_triggered()
{
    QMessageBox esci;
    int ans = 0;
    if(!isFinita)
        ans = esci.warning(this,"Uscita","Una partita e' in corso, sei sicuro di voler uscire? Il punteggio non sarà salvato!","Esci","Annulla");
    if(ans == 0){
        this->close();
        this->destroy();
        this->deleteLater();
    }
}

void FinestraGioco::on_actionMossa_intelligiente_triggered()
{
    MossaInt m = Campo.SimulaMosse();
    QString txt = "Sposto ";
    txt += QString::number(m.r);
    txt += " ";
    txt += QString::number(m.c);
    txt += " in ";
    txt += QString::number(m.r1);
    txt += " ";
    txt += QString::number(m.c1);
    //txt += " per fare punti ";
    //txt += QString::number(m.punti);
    QMessageBox::about(this,"Mossa intelligente!!", txt);
    bottone[m.r][m.c]->setStyleSheet("background-color: red");
    bottone[m.r1][m.c1]->setStyleSheet("background-color: red");

}

void FinestraGioco::on_actionNuova_partita_triggered()
{
    int ans = 0;
    if(!isFinita)
        ans = QMessageBox::question(this,"Vuoi interrompere?","Sei sicuro di voler interrompere la partita in corso per iniziarne una nuova? Il punteggio non sarà salvato.",QMessageBox::Yes,QMessageBox::No);
    if(ans == QMessageBox::Yes || isFinita)
    {
        inserimento_nome new_nome(this);
        new_nome.exec();
        if(new_nome.isOK())
        {
            this->close();
            this->destroy();
            this->deleteLater();
        }
    }
}
