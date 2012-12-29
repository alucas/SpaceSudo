#ifndef DEF_FENETRE
#define DEF_BENETRE

#include <QtGui>
#include "Bouton.h"
#include "Choix.h"
#include "Solution.h"
#include "Imprimer.h"

class Fenetre : public QMainWindow{
    Q_OBJECT

    public:
        // Constructeurs
        Fenetre();
        // Méthodes
        void resoudre();
        bool generation(QString grille[][9], bool masque[][9]);
        void elimination(QString zone[][9], QString ligne[][9], QString colone[][9], int i, int j, int m);
        void affectation(QString zone[][9], QString ligne[][9], QString colone[][9], QString grille[][9], bool masque[][9], QString *loterie, int i, int j, int m, bool masqueVal);
        int solver(int *grille, bool grille_bool[][9], int *grille_nbr, int *grille_nbr2, int *grilleSource=NULL, int *niveau=NULL);
        bool solver1(int *grille, bool grille_bool[][9], int *grille_nbr, int *grille_nbr2);
        bool verifier(int *grille, bool *tab_erreur);
        void keyPressEvent(QKeyEvent *event);
        void closeEvent( QCloseEvent* event );

    public slots:
        void slotAfficherChoix(int numero, int valeur);
        void slotModifierBouton(int numero, int valeur);
        void slotCheck();
        void slotChrono();
        //////////////////////////////////////////////
        void slotPartieNouveau();
        void slotPartieOuvrir();
        void slotPartieEnregistrer();
        void slotPartieImprimer();
        void slotPartieQuitter();
        //////////////////////////////////////////////
        void slotAideVerifierRegles();
        void slotAideVerifierSolution();
        void slotAideReveler();
        void slotAideResoudre();
        ///////////////////////////////////////////////
        void slotOptionAfficher();
        void slotOptionValeur();
        void slotOptionVider();
        void slotOptionRegles();
        /////////////////////////////////////////////
        void slotAbout();

    private:
        int m_grille[81];
        int m_grille_full[81];
        int m_resolut;
        int m_temps;
        bool m_modeClavier;
        int m_modeClavierPos;
        QWidget *m_fenetre;
        QGridLayout *m_layout;
        Bouton *m_boutons[81];
        QLabel *m_marqueFixe[81];
        Choix *m_choix;
        Solution *m_solution;
        Imprimer *m_imprimer;
        QPixmap *m_images[14];
        QPixmap *m_imagesMini[10];
        // Pointeurs du menu.
        QMenu *m_menuPartie;
            QAction *m_actionPartieNouveau;
            QAction *m_actionPartieOuvrir;
            QAction *m_actionPartieEnregistrer;
            QAction *m_actionPartieImprimer;
            QAction *m_actionPartieQuitter;
        QMenu *m_menuAide;
            QAction *m_actionAideVerifierRegles;
            QAction *m_actionAideVerifierSolution;
            QAction *m_actionAideFiltrer;
            QAction *m_actionAideReveler;
            QAction *m_actionAideResoudre;
        QMenu *m_menuOption;
            QAction *m_actionOptionAfficher;
            QAction *m_actionOptionValeur;
            QAction *m_actionOptionVider;
            QAction *m_actionOptionRegles;
        QMenu *m_menuAbout;
            QAction *m_actionAbout;
            QAction *m_actionAboutQt;
        // Pointeurs toolbar.
        QToolBar *m_toolbar;
            QLabel *m_toolbarLabel[20];
            int m_toolbarValeur[10];

};

#endif
