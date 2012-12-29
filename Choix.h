#ifndef DEF_CHOIX
#define DEF_CHOIX

#include <QtGui>
#include "Bouton.h"

class Choix : public QWidget{
    Q_OBJECT

    public:
        // Constructeurs
        Choix(Bouton **boutons,QPixmap **images, QWidget *parent=0);
        // Méthodes
        void update(int numero, int valeur, Bouton **boutons, bool filtrer, bool afficherValeur, bool modeClavier);
        void afficherValeur(bool valeur);
        void keyPressEvent(QKeyEvent *event);
        // Accesseurs
        bool getModeClavier() const;
        int getModeClavierPos() const;
        // Mutateurs
        void setModeClavier(bool mode);
        void setModeClavierPos(int pos);

    public slots:
        void slotSendAtributs(int numero, int valeur);

    signals:
        void signalFermerFenetre(int numero, int valeur);

	private:
        bool m_modeClavier;
        int m_modeClavierPos;
        QWidget *m_fenetre;
        QGridLayout *m_layout;
        Bouton *m_boutons[10];
};

#endif
