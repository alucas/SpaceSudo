////////////////////////////////////////////////
//                                            //
// Auteur : Heero                             //
// Début du projet : 04/07/08                 //
// Dernière modification : 25/07/08           //
// Bibliothèque : Qt 4.4                      //
//                                            //
// Information : Classe Bouton                //
// Description : Boutons du jeu, Ils se       //
//   composent de 4 QLabel, un pour l'image   //
//   de font, un pour afficher la marque des  //
//   boutons fixes (qu'on ne peut pas         //
//   modifier), un pour afficher la marque    //
//   de sélection au clavier et un quatrième  //
//   pour afficher le chiffre correspondant.  //
//                                            //
////////////////////////////////////////////////

#include "Bouton.h"

////////////////////////////////////////////////
//               CONSTRUCTEURS                //
////////////////////////////////////////////////

Bouton::Bouton(QPixmap **images, int numero, int valeur){
    QWidget();

    // QLabel image.
    m_label[0] = new QLabel(this);
    m_label[0]->setFixedSize(40, 40);
    m_label[0]->setPixmap(*images[valeur]);

    // QLabel marque bouton fixe.
    m_label[1] = new QLabel(this);
    m_label[1]->setFixedSize(40, 40);
    m_label[1]->setPixmap(*images[12]);

    // QLabel marque de localisation.
    m_label[2] = new QLabel(this);
    m_label[2]->setFixedSize(40, 40);
    m_label[2]->setPixmap(*images[13]);

    // QLabel de texte.
    m_label[3] = new QLabel(this);
    m_label[3]->setFixedSize(40, 40);
    m_label[3]->setAlignment(Qt::AlignCenter);
    m_label[3]->setText(QString::number(valeur));

    setFixe(false);
    setAfficherValeur(false);
    showLabel(1, false);
    showLabel(2, false);
    showLabel(3, false);
    setNumero(numero);
    setValeur(valeur);
}

////////////////////////////////////////////////
//                 MUTATEURS                  //
////////////////////////////////////////////////

void Bouton::setValeur(int valeur){
    m_valeur = valeur;
    m_label[3]->setText(QString::number(valeur));
}
void Bouton::setNumero(int numero){
    m_numero = numero;
}
void Bouton::setAfficherValeur(bool afficher){
    m_afficherValeur = afficher;
}
void Bouton::setFixe(bool fixe){
    m_fixe = fixe;
    if(fixe){
        setCursor(Qt::ArrowCursor);
    }else{
        setCursor(Qt::PointingHandCursor);
    }
}
void Bouton::setImage(QPixmap *image){
    m_label[0]->setPixmap(*image);
}

////////////////////////////////////////////////
//                 ACCESSEURS                 //
////////////////////////////////////////////////

int Bouton::getValeur() const{
    return m_valeur;
}
int Bouton::getNumero() const{
    return m_numero;
}
bool Bouton::getAfficherValeur() const{
    return m_afficherValeur;
}
bool Bouton::getFixe() const{
    return m_fixe;
}

////////////////////////////////////////////////
//                  METHODES                  //
////////////////////////////////////////////////

void Bouton::mouseReleaseEvent(QMouseEvent* _event){
    if (!m_fixe and _event->button() == Qt::LeftButton){
        emit clicked(getNumero(), getValeur());
    }
}
void Bouton::showLabel(int numero, bool valeur){
    if(valeur){
        m_label[numero]->show();
    }else{
        m_label[numero]->hide();
    }
    if(numero = 3){
        setAfficherValeur(valeur);
    }
}
