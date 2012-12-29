////////////////////////////////////////////////
//                                            //
// Auteur : Heero                             //
// Début du projet : 04/07/08                 //
// Dernière modification : 25/07/08           //
// Bibliothèque : Qt 4.4                      //
//                                            //
// Information : Classe Solution              //
// Description : Fenêtre secondaire qui       //
//   sert à afficher la solution de la grille //
//                                            //
////////////////////////////////////////////////


#include "Solution.h"


////////////////////////////////////////////////
//               CONSTRUCTEURS                //
////////////////////////////////////////////////

Solution::Solution(QWidget *parent):QWidget(parent){
    m_fenetre = new QWidget(this);

    m_layout = new QGridLayout();
    m_layout->setContentsMargins(10,10,10,10);
    m_layout->setSpacing(0);
    m_layout->setColumnMinimumWidth(3, 10); // Espace
    m_layout->setColumnMinimumWidth(7, 10); // entre
    m_layout->setRowMinimumHeight(3, 10);   // les
    m_layout->setRowMinimumHeight(7, 10);   // zones

    int curseur = 0;
    for(int i=0; i<11; i++){
        for(int o=0; o<11; o++){
            if(o != 3 && o != 7 && i != 3 && i != 7){ // cases qui servent d'espaceurs.
                m_boutons[curseur] = new QLabel();
                m_boutons[curseur]->setFixedSize(20, 20);

                m_layout->addWidget(m_boutons[curseur], i, o);

                curseur++;
            }
        }
    }

    m_bouton = new QPushButton("Fermer");
    connect(m_bouton, SIGNAL(clicked()), this, SLOT(close()));
    m_layout->addWidget(m_bouton, 11, 0, 1, 11);

    m_fenetre->setLayout(m_layout);
}

////////////////////////////////////////////////
//                 METHODES                   //
////////////////////////////////////////////////

void Solution::update(int *grille, QPixmap **images){
    for(int i=0; i<81; i++){
        m_boutons[i]->setPixmap(*images[grille[i]]);
    }
}
