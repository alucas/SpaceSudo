////////////////////////////////////////////////
//                                            //
// Auteur : Heero                             //
// Début du projet : 04/07/08                 //
// Dernière modification : 25/07/08           //
// Bibliothèque : Qt 4.4                      //
//                                            //
// Information : Classe Imprimer              //
// Description : Fenêtre de choix des options //
//   pour l'impression.                       //
//                                            //
////////////////////////////////////////////////


#include "Imprimer.h"


////////////////////////////////////////////////
//               CONSTRUCTEURS                //
////////////////////////////////////////////////

Imprimer::Imprimer(QWidget *parent):QDialog(parent){

    m_fenetre = new QWidget(this);
    m_layout = new QGridLayout();

    m_layoutGrille = new QVBoxLayout();
    m_layoutAide = new QHBoxLayout();

    m_groupboxGrille = new QGroupBox("Que voulez vous imprimer ?");
    m_groupboxAide = new QGroupBox("Imprimer les case d'aides ?");

    m_grille1 = new QRadioButton("Imprimer la grille actuele.");
    m_grille6 = new QRadioButton("Imprimer six nouvelles grilles.");

    m_aideOui = new QRadioButton("Oui.");
    m_aideNon = new QRadioButton("Non.");

    m_annuler = new QPushButton("Annuler");
    m_valider = new QPushButton("Valider");

    connect(m_annuler, SIGNAL(clicked()), this, SLOT(reject()));
    connect(m_valider, SIGNAL(clicked()), this, SLOT(accept()));

    m_grille1->setChecked(true);
    m_aideNon->setChecked(true);

    m_layoutGrille->addWidget(m_grille1);
    m_layoutGrille->addWidget(m_grille6);

    m_layoutAide->addWidget(m_aideOui);
    m_layoutAide->addWidget(m_aideNon);

    m_groupboxGrille->setLayout(m_layoutGrille);
    m_groupboxAide->setLayout(m_layoutAide);

    m_layout->addWidget(m_groupboxGrille, 0, 0, 1, 2);
    m_layout->addWidget(m_groupboxAide, 1, 0, 1, 2);
    m_layout->addWidget(m_annuler, 2, 0);
    m_layout->addWidget(m_valider, 2, 1);

    m_fenetre->setLayout(m_layout);
}

////////////////////////////////////////////////
//                 ACCESSEURS                 //
////////////////////////////////////////////////

bool Imprimer::getAfficherAide() const{
    return m_aideOui->isChecked();
}
bool Imprimer::getModeNormal() const{
    return m_grille1->isChecked();
}
