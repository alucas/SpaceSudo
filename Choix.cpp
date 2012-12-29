////////////////////////////////////////////////
//                                            //
// Auteur : Heero                             //
// D�but du projet : 04/07/08                 //
// Derni�re modification : 25/07/08           //
// Biblioth�que : Qt 4.4                      //
//                                            //
// Information : Classe Choix                 //
// Description : Fen�tre secondaire qui       //
//   s'affiche lorsque l'on clique (ou appuis //
//   sur Entrer, en mode clavier) sur une     //
//   case de la fen�tre principale, elle      //
//   contient la liste des plan�tes que l'on  //
//   peut mettre dans cette case.             //
//                                            //
////////////////////////////////////////////////

#include "Choix.h"

////////////////////////////////////////////////
//               CONSTRUCTEURS                //
////////////////////////////////////////////////

Choix::Choix(Bouton **boutons, QPixmap **images, QWidget *parent):QWidget(parent){

    setModeClavier(false);
    setModeClavierPos(0);

    // Cr�ation du Widget conteneur.
    m_fenetre = new QWidget(this);
    m_fenetre->setObjectName("choix");

    // Cr�ation d'une QGridLayout, avec une marge de 10px et aucun espace entre les cases.
    m_layout = new QGridLayout();
    m_layout->setContentsMargins(10, 10, 10, 5);
    m_layout->setSpacing(0);
    m_layout->setRowMinimumHeight(3, 5);

    for(int i=0; i<10; i++){
        m_boutons[i] = new Bouton(images, 0, i);
        m_boutons[i]->setFixedSize(40, 40);
        if(i==0){ // Si c'est le bouton 0 on le place � une position sp�ciale.
            m_layout->addWidget(m_boutons[i], 4, 1);
        }else{ // Sinon on les placent � la suite.
            m_layout->addWidget(m_boutons[i], (i-(i-1)%3)/3, (i-1)%3);
        }

        connect(m_boutons[i], SIGNAL(clicked(int, int)), this, SLOT(close()));
        connect(m_boutons[i], SIGNAL(clicked(int, int)), this, SLOT(slotSendAtributs(int, int)));
    }
    // Affichage de ma QGridLayout dans la fenetre.
    m_fenetre->setLayout(m_layout);
}

////////////////////////////////////////////////
//                   SLOTS                    //
////////////////////////////////////////////////

void Choix::slotSendAtributs(int numero, int valeur){
    emit signalFermerFenetre(numero, valeur);
}

////////////////////////////////////////////////
//                 ACCESSEURS                 //
////////////////////////////////////////////////

bool Choix::getModeClavier() const{
    return m_modeClavier;
}
int Choix::getModeClavierPos() const{
    return m_modeClavierPos;
}

////////////////////////////////////////////////
//                 MUTATEURS                  //
////////////////////////////////////////////////

void Choix::setModeClavier(bool mode){
    m_modeClavier = mode;
}
void Choix::setModeClavierPos(int pos){
    m_modeClavierPos = pos;
}

////////////////////////////////////////////////
//                 METHODES                   //
////////////////////////////////////////////////

void Choix::update(int numero, int valeur, Bouton **boutons, bool filtrer, bool afficherValeur, bool modeClavier){
    bool tab_libre[10] = {true, true, true, true, true, true, true, true, true, true};
    if(filtrer){
        // V�rification lignes.
        int num = numero-(numero%9);
        for(int i=0; i<9; i++){
            if(num != numero){
                tab_libre[boutons[num]->getValeur()] = false;
            }
            num++;
        }
        // V�rification colones.
        num = numero%9;
        for(int i=0; i<9; i++){
            if(num != numero){
                tab_libre[boutons[num]->getValeur()] = false;
            }
            num += 9;
        }
        // V�rification zones.
        num = (numero-(numero%3))-(((numero-(numero%9))/9)%3)*9;
        for(int i=0; i<9; i++){
            if(num != numero){
                tab_libre[boutons[num]->getValeur()] = false;
            }
            if(i%3 == 2){
                num += 7;
            }else{
                num++;
            }
        }
    }
    m_boutons[0]->setNumero(numero);
    for(int i=1; i<10; i++){
        // Si cette plan�te peut etre plac� dans cette case, on l'affiche, sinon on la cache.
        m_boutons[i]->showLabel(0, tab_libre[i]);
        m_boutons[i]->showLabel(3, tab_libre[i] and afficherValeur);
        m_boutons[i]->setFixe(!tab_libre[i]);
        m_boutons[i]->setNumero(numero);
    }

    if(modeClavier){
        // Initialisation du mode clavier si le mode clavier de la fen�tre principale est activ�.
        m_boutons[getModeClavierPos()]->showLabel(2, false);
        setModeClavier(true);
        setModeClavierPos(valeur);
        m_boutons[valeur]->showLabel(2, true);
    }else{
        // Sinon on le d�sactive au cas ou il etait activ� au dernier affichage de cette fen�tre.
        setModeClavier(false);
        m_boutons[getModeClavierPos()]->showLabel(2, false);
    }
}
void Choix::afficherValeur(bool valeur){
    for(int i=1; i<10; i++){
        m_boutons[i]->showLabel(3, valeur);
    }
}
void Choix::keyPressEvent(QKeyEvent *event){
    int pos = getModeClavierPos();
    if(event->key() == Qt::Key_Return){ // Si l'utilisateur appuis sur la touche Entrer et que le mode clavier est activ� on �met le signal de validation.
        if(getModeClavier()){
            emit signalFermerFenetre(m_boutons[pos]->getNumero(), m_boutons[pos]->getValeur());
            close();
        }
    }
    // Si une touche directionelle est apuy�e.
    if(event->key() == Qt::Key_Right or event->key() == Qt::Key_Left or event->key() == Qt::Key_Up or event->key() == Qt::Key_Down){
        if(!getModeClavier()){
            // Si le mode clavier est d�sactiv� alors on l'initialise.
            m_boutons[pos]->showLabel(2, false);
            m_boutons[0]->showLabel(2, true);
            setModeClavier(true);
            setModeClavierPos(0);
        }else{
            // On cache la marque de s�l�ction du precedent bouton.
            m_boutons[pos]->showLabel(2, false);

            // On cherche la position du prochain bouton non fixe dans la direction choisie.
            if(event->key() == Qt::Key_Right){  // Touche droite.
                do{
                    pos++;
                    if(pos>9){
                        pos -= 10;
                    }
                }while(m_boutons[pos]->getFixe() == true);
            }
            if(event->key() == Qt::Key_Left){ // Touche gauche.
                do{
                    pos--;
                    if(pos<0){
                        pos += 10;
                    }
                }while(m_boutons[pos]->getFixe() == true);
            }
            if(event->key() == Qt::Key_Up){ // Touche haut.
                do{
                    if(pos == 0 or pos == 1){
                        pos += 8;
                    }else if(pos == 3){
                        pos = 0;
                    }else if(pos == 2){
                        pos = 7;
                    }else{
                        pos -= 3;
                    }
                }while(m_boutons[pos]->getFixe() == true);
            }
            if(event->key() == Qt::Key_Down){ // Touche bas.
                do{
                    if(pos == 7){
                        pos = 2;
                    }else if(pos == 8 or pos == 9){
                        pos  -= 8;
                    }else{
                        pos += 3;
                    }
                }while(m_boutons[pos]->getFixe() == true);
            }

            // On affiche la marque de s�l�ction.
            m_boutons[pos]->showLabel(2, true);
            setModeClavierPos(pos);
        }
    }
}
