#ifndef DEF_BOUTON
#define DEF_BOUTON

#include <QtGui>

class Bouton : public QWidget{
    Q_OBJECT


    public:
        // Constructeurs
        Bouton(QPixmap **images, int numero, int valeur);
        // Mutateurs
        void setValeur(int valeur);
        void setNumero(int numero);
        void setAfficherValeur(bool afficher);
        void setFixe(bool fixe);
        void setImage(QPixmap *image);
        // Accesseurs
        int getValeur() const;
        int getNumero() const;
        bool getAfficherValeur() const;
        bool getFixe() const;
        // Méthodes
        void showLabel(int numero, bool valeur);
        void mouseReleaseEvent(QMouseEvent* _event);


    signals:
        void clicked(int numero, int valeur) const;


    private:
        int m_numero;
        int m_valeur;
        bool m_afficherValeur;
        bool m_fixe;
        //////////////////////
        QLabel *m_label[4];
};

#endif
