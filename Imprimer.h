#ifndef DEF_IMPRIMER
#define DEF_IMPRIMER

#include <QtGui>

class Imprimer : public QDialog{
    public:
        // Constructeurs
        Imprimer(QWidget *parent);
        // Accesseurs
        bool getAfficherAide() const;
        bool getModeNormal() const;

    private:
        QWidget *m_fenetre;
        QGridLayout *m_layout;
        QVBoxLayout *m_layoutGrille;
        QHBoxLayout *m_layoutAide;
        QGroupBox *m_groupboxGrille;
        QGroupBox *m_groupboxAide;
        QRadioButton *m_grille1;
        QRadioButton *m_grille6;
        QRadioButton *m_aideOui;
        QRadioButton *m_aideNon;
        QPushButton *m_valider;
        QPushButton *m_annuler;
};

#endif
