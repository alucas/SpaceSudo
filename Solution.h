#ifndef DEF_SOLUTION
#define DEF_SOLUTION

#include <QtGui>

class Solution : public QWidget{
    public:
        // Constructeurs
        Solution(QWidget *parent);
        // Méthodes
        void update(int *grille, QPixmap **images);

    private:
        QWidget *m_fenetre;
        QGridLayout *m_layout;
        QLabel *m_boutons[81];
        QPushButton *m_bouton;
};

#endif
