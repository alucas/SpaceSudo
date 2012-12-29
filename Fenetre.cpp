////////////////////////////////////////////////
//                                            //
// Auteur : Heero                             //
// Début du projet : 04/07/08                 //
// Dernière modification : 25/07/08           //
// Bibliothèque  : Qt 4.4                     //
//                                            //
// Information : Classe Fenetre               //
// Description : Fenêtre principale qui       //
//   contient les boutons du Sudoku.          //
//                                            //
////////////////////////////////////////////////

#include <time.h>
#include "Fenetre.h"

////////////////////////////////////////////////
//               CONSTRUCTEURS                //
////////////////////////////////////////////////

Fenetre::Fenetre(){
    ////////////////////////////////////////////////
    //               INITIALISATION               //
    ////////////////////////////////////////////////

    for(int i=0; i<81; i++){
        m_grille[i] = 0;
        m_grille_full[i] = 0;
    }
    m_resolut = -1;
    m_modeClavier = false;
    m_modeClavierPos = 0;
    m_temps = 0;
    srand(time(NULL));

    // Création du chronomètre de la barre de titre.
    QTimer *timer =  new QTimer();
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotChrono()));

    ////////////////////////////////////////////////
    //            IMAGES AND STYLESHEET           //
    ////////////////////////////////////////////////

    for(int i=0; i<14; i++){
        m_images[i] = new QPixmap("images/"+QString::number(i)+".png");
        if(i<10){
            m_imagesMini[i] = new QPixmap(m_images[i]->scaled(20,20));
        }
    }

    setStyleSheet(
        "QWidget#fenetre{"
            "background-image : url('images/10.png') ;"
            "background-position : bottom left ;"
        "}"
        "Choix > QWidget#choix{"
            "background-image : url('images/11.png') ;"
        "}"
    );

    ////////////////////////////////////////////////
    //                    MENU                    //
    ////////////////////////////////////////////////

    m_menuPartie = menuBar()->addMenu("&Partie");
        m_actionPartieNouveau = m_menuPartie->addAction("&Nouveau");
        m_actionPartieNouveau->setShortcut(QKeySequence(QKeySequence::New));
        m_actionPartieNouveau->setIcon(QIcon("icone/nouveau.png"));
        m_actionPartieOuvrir = m_menuPartie->addAction("&Ouvrir");
        m_actionPartieOuvrir->setShortcut(QKeySequence(QKeySequence::Open));
        m_actionPartieOuvrir->setIcon(QIcon("icone/ouvrir.png"));
            m_menuPartie->addSeparator();
        m_actionPartieEnregistrer = m_menuPartie->addAction("&Enregistrer");
        m_actionPartieEnregistrer->setShortcut(QKeySequence(QKeySequence::Save));
        m_actionPartieEnregistrer->setIcon(QIcon("icone/enregistrer.png"));
        m_actionPartieImprimer = m_menuPartie->addAction("&Imprimer");
        m_actionPartieImprimer->setShortcut(QKeySequence(QKeySequence::Print));
        m_actionPartieImprimer->setIcon(QIcon("icone/imprimer.png"));
            m_menuPartie->addSeparator();
        m_actionPartieQuitter = m_menuPartie->addAction("&Quitter");
        m_actionPartieQuitter->setShortcut(QKeySequence(QKeySequence::Close));
        m_actionPartieQuitter->setIcon(QIcon("icone/quitter.png"));
    m_menuAide = menuBar()->addMenu("&Aides");
        m_actionAideFiltrer = m_menuAide->addAction("&Filtrer les planètes");
        m_actionAideFiltrer->setIcon(QIcon("icone/nocheck.png"));
            m_menuAide->addSeparator();
        m_actionAideVerifierRegles = m_menuAide->addAction("&Vérifier la grille (règles)");
        m_actionAideVerifierRegles->setIcon(QIcon("icone/verifier.png"));
        m_actionAideVerifierSolution = m_menuAide->addAction("&Vérifier la grille (solution)");
        m_actionAideVerifierSolution->setIcon(QIcon("icone/verifier.png"));
        m_actionAideReveler = m_menuAide->addAction("&Révéler une planète");
        m_actionAideReveler->setIcon(QIcon("icone/solutionUn.png"));
        m_actionAideResoudre = m_menuAide->addAction("&Afficher la solution");
        m_actionAideResoudre->setIcon(QIcon("icone/solution.png"));
    m_menuOption = menuBar()->addMenu("&Options");
        m_actionOptionAfficher = m_menuOption->addAction("&Marquer les planètes fixes");
        m_actionOptionAfficher->setIcon(QIcon("icone/nocheck.png"));
        m_actionOptionValeur = m_menuOption->addAction("&Numéroter les planètes");
        m_actionOptionValeur->setIcon(QIcon("icone/nocheck.png"));
            m_menuOption->addSeparator();
        m_actionOptionVider = m_menuOption->addAction("&Vider la grille");
        m_actionOptionVider->setIcon(QIcon("icone/clear.png"));
        m_actionOptionRegles = m_menuOption->addAction("&Règles");
        m_actionOptionRegles->setIcon(QIcon("icone/info.png"));
    m_menuAbout = menuBar()->addMenu("&?");
        m_actionAbout = m_menuAbout->addAction("&A propos");
        m_actionAbout->setIcon(QIcon("icone/about.png"));
        m_actionAboutQt = m_menuAbout->addAction("&A propos de Qt");
        m_actionAboutQt->setIcon(QIcon("icone/qt.png"));

    connect(m_actionPartieNouveau, SIGNAL(triggered()), this, SLOT(slotPartieNouveau()));
    connect(m_actionPartieOuvrir, SIGNAL(triggered()), this, SLOT(slotPartieOuvrir()));
    connect(m_actionPartieEnregistrer, SIGNAL(triggered()), this, SLOT(slotPartieEnregistrer()));
    connect(m_actionPartieImprimer, SIGNAL(triggered()), this, SLOT(slotPartieImprimer()));
    connect(m_actionPartieQuitter, SIGNAL(triggered()), this, SLOT(slotPartieQuitter()));
    connect(m_actionAideVerifierRegles, SIGNAL(triggered()), this, SLOT(slotAideVerifierRegles()));
    connect(m_actionAideVerifierSolution, SIGNAL(triggered()), this, SLOT(slotAideVerifierSolution()));
    connect(m_actionAideFiltrer, SIGNAL(triggered()), this, SLOT(slotCheck()));
    connect(m_actionAideReveler, SIGNAL(triggered()), this, SLOT(slotAideReveler()));
    connect(m_actionAideResoudre, SIGNAL(triggered()), this, SLOT(slotAideResoudre()));
    connect(m_actionOptionAfficher, SIGNAL(triggered()), this, SLOT(slotCheck()));
    connect(m_actionOptionAfficher, SIGNAL(triggered()), this, SLOT(slotOptionAfficher()));
    connect(m_actionOptionValeur, SIGNAL(triggered()), this, SLOT(slotCheck()));
    connect(m_actionOptionValeur, SIGNAL(triggered()), this, SLOT(slotOptionValeur()));
    connect(m_actionOptionVider, SIGNAL(triggered()), this, SLOT(slotOptionVider()));
    connect(m_actionOptionRegles, SIGNAL(triggered()), this, SLOT(slotOptionRegles()));
    connect(m_actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));
    connect(m_actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    ////////////////////////////////////////////////
    //                  TOOL BAR                  //
    ////////////////////////////////////////////////

    // Création d'une toolbar qui servira à afficher le nombre de planètes présentes sur la grille.
    m_toolbar = addToolBar("Afficher le nombre de planètes");
    m_toolbar->setMovable(false);

    for(int i=0; i<10; i++){
        // Image de la planète.
        m_toolbarLabel[2*i] = new QLabel();
        m_toolbarLabel[2*i]->setPixmap(*m_imagesMini[i]);
        m_toolbarLabel[2*i]->setFixedSize(20, 20);

        // Nombre d'occurence de cette planète.
        m_toolbarLabel[2*i+1] = new QLabel();
        m_toolbarLabel[2*i+1]->setFixedSize(15, 20);
        m_toolbarLabel[2*i+1]->setAlignment(Qt::AlignCenter);
        if(i == 0){
            // Par defaut, grille vide, donc 81 planètes 0.
            m_toolbarLabel[2*i+1]->setText(QString::number(81));
            m_toolbarValeur[0] = 81;
        }else{
            m_toolbarLabel[2*i+1]->setText(QString::number(0));
            m_toolbarValeur[i] = 0;
        }

        // Un séparateur pour organiser le tout.
        m_toolbar->addWidget(m_toolbarLabel[2*i]);
        m_toolbar->addWidget(m_toolbarLabel[2*i+1]);
        m_toolbar->addSeparator();
    }

    ////////////////////////////////////////////////
    //              LAYOUT PRINCIPAl              //
    ////////////////////////////////////////////////

    // Layout contenant les boutons du Sudoku.
    m_layout = new QGridLayout();
    m_layout->setContentsMargins(10,10,10,70);
    m_layout->setSpacing(0);
    m_layout->setColumnMinimumWidth(3, 20); //
    m_layout->setColumnMinimumWidth(7, 20); //
    m_layout->setRowMinimumHeight(3, 20);   // Espace entre les zones.
    m_layout->setRowMinimumHeight(7, 20);   //

    int curseur = 0;
    for(int i=0; i<11; i++){
        for(int o=0; o<11; o++){
            if(o != 3 && o != 7 && i != 3 && i != 7){ // Cases qui servent d'espaceurs.
                m_boutons[curseur] = new Bouton(m_images, curseur, m_grille[curseur]);
                m_boutons[curseur]->setFixedSize(40, 40);

                connect(m_boutons[curseur], SIGNAL(clicked(int, int)), this, SLOT(slotAfficherChoix(int, int)));

                m_layout->addWidget(m_boutons[curseur], i, o);

                curseur++;
            }
        }
    }

    // Widget principal, conteneur du layout.
	m_fenetre = new QWidget();
	m_fenetre->setObjectName("fenetre");
    m_fenetre->setLayout(m_layout);

    ////////////////////////////////////////////////
    //               FENETRE CHOIX                //
    ////////////////////////////////////////////////

    m_choix = new Choix(m_boutons, m_images, m_fenetre);
    m_choix->setWindowFlags(Qt::Tool | Qt::WindowTitleHint);
    m_choix->setWindowModality(Qt::WindowModal);
    m_choix->setFixedSize(140,180);

    connect(m_choix, SIGNAL(signalFermerFenetre(int, int)), this, SLOT(slotModifierBouton(int, int)));

    ////////////////////////////////////////////////
    //              FENETRE SOLUTION              //
    ////////////////////////////////////////////////

    m_solution = new Solution(m_fenetre);
    m_solution->setWindowFlags(Qt::Tool | Qt::WindowTitleHint);
    m_solution->setWindowTitle("Solution");
    m_solution->setFixedSize(220,250);

    ////////////////////////////////////////////////
    //              FENETRE IMPRIMER              //
    ////////////////////////////////////////////////

    m_imprimer = new Imprimer(m_fenetre);
    m_imprimer->setWindowFlags(Qt::Tool | Qt::WindowTitleHint);
    m_imprimer->setWindowModality(Qt::WindowModal);
    m_imprimer->setWindowTitle("Imprimer");
    m_imprimer->setFixedSize(200,190);

    ////////////////////////////////////////////////
    //             FENETRE PRINCIPALE             //
    ////////////////////////////////////////////////

    setWindowIcon(QPixmap("icone/icone.png"));
    setWindowTitle("SpaceSudo (00:00)");
    setCentralWidget(m_fenetre);
}

////////////////////////////////////////////////
//                   SLOTS                    //
////////////////////////////////////////////////

void Fenetre::slotPartieNouveau(){
    QString grille[9][9];
    bool masque[9][9];
    int var;

    //int temps = clock();

    if (generation(grille, masque)){
        for (int i=0; i<9; i++){
            for (int j=0; j<9; j++){
                var = i*9+j;
                if (masque[i][j]){ // Si on peut cacher cette case.
                    m_grille[var] = 0;
                    m_boutons[var]->setFixe(false);
                    m_boutons[var]->showLabel(1, false);
                }else{ // Sinon c'est une case fixe.
                    m_grille[var] = grille[i][j].toInt();
                    m_boutons[var]->setFixe(true);
                    m_boutons[var]->showLabel(1, m_actionOptionAfficher->isCheckable());
                }
                m_grille_full[var] = grille[i][j].toInt();
                slotModifierBouton(var, m_grille[var]);
            }
        }
        m_resolut = 1;
        m_modeClavier = false;
        m_boutons[m_modeClavierPos]->showLabel(2, false);
        m_solution->update(m_grille_full, m_imagesMini);
        m_solution->setWindowTitle("Solution");
        m_actionAideReveler->setEnabled(true);
        m_actionAideVerifierSolution->setEnabled(true);
        m_temps = 0;
    }else{
        QMessageBox::warning(this, "Génération", "La génération de la grille a <b>échouée</b>, veuillez réessayer.");
    }

    //int temps = clock()-temps;
    //QMessageBox::information(this, "Solution", "Solution calculée en : "+QString::number(temps)+"ms");
}
void Fenetre::slotPartieOuvrir(){
    QString fichierNom = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "./save", "Sudoku (*.sdk)");
    if(fichierNom != ""){
        QFile fichier(fichierNom);
        if(fichier.open(QIODevice::ReadOnly)){
            char grille[82];
            int pos;
            QString tab = "0abcdefghi";
            QString str;
            QRegExp regexp("^[0-9a-i]{81}");
            qint64 lineLength = fichier.readLine(grille, sizeof(grille));
            if(lineLength != 81 or QString::fromAscii(grille).contains(regexp)){
                for(int i=0; i<81; i++){
                    str = grille[i];
                    pos = tab.indexOf(str);
                    if(pos == -1){ // Si ce n'est pas un numero fixe.
                        m_grille[i] = str.toInt();
                        m_grille_full[i] = m_grille[i];
                        m_boutons[i]->setFixe(true);
                        m_boutons[i]->showLabel(1, m_actionOptionAfficher->isCheckable());
                        slotModifierBouton(i, m_grille[i]);
                    }else{
                        m_grille[i] = 0;
                        m_grille_full[i] = 0;
                        m_boutons[i]->setFixe(false);
                        m_boutons[i]->showLabel(1, false);
                        slotModifierBouton(i, pos);
                    }
                }
                m_resolut = -1;
                m_modeClavier = false;
                m_boutons[m_modeClavierPos]->showLabel(2, false);
                m_solution->setWindowTitle("Solution");
                m_actionAideReveler->setEnabled(true);
                m_actionAideVerifierSolution->setEnabled(true);
                m_temps = 0;
            }else{
                QMessageBox::warning(this, "Ouvrir", "Le fichier ouvert n'est <b>pas valide</b>.");
            }
        }else{
            QMessageBox::warning(this, "Ouvrir", "<b>Erreur</b> d'ouverture du fichier.");
        }
        fichier.close();
    }
}
void Fenetre::slotPartieEnregistrer(){
    QString fichierNom = QFileDialog::getSaveFileName(this, "Enregistrer sous :", "./save", "Sudoku (*.sdk)");
    QFile fichier(fichierNom);
    QString tab = "0abcdefghi";
    QString str;
    qint64 lineLength = 0;
    if(fichier.open(QIODevice::WriteOnly)){
        for(int i=0; i<81; i++){
            if(m_grille[i] != 0){
                str.setNum(m_grille[i]);
                lineLength += fichier.write( str.toUtf8());
            }else{
                str = tab.at(m_boutons[i]->getValeur());
                lineLength += fichier.write( str.toUtf8());
            }
        }
        if(lineLength != 81){
            QMessageBox::warning(this, "Enregistrer", "Une <b>erreur</b> c'est produite lors de l'enregistrement de votre partie.");
        }else{
            QMessageBox::warning(this, "Enregistrer", "Partie <b>enregistrée</b>.");
        }
        fichier.close();
    }
}
void Fenetre::slotPartieImprimer(){
    if(m_imprimer->exec() == QDialog::Accepted){
        QPrinter* print = new QPrinter;
        print->setOrientation(QPrinter::Portrait);
        print->setResolution(100);
        print->setPaperSize(QPrinter::A4);
        print->setPageMargins(15, 15, 15, 15, QPrinter::DevicePixel);
        QPrintDialog printDialog (print);
        if(printDialog.exec()){
            QPen pen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

            QPainter* paint = new QPainter (print);

            int espacex = 20;
            int espacey = 20;
            int casex = 35;
            int casey = 35;
            int minicasex = casex/3;
            int minicasey = casey/3;
            int pen1 = 4;
            int pen2 = 2;
            int pen3 = 1;
            int x = 2;
            int y = 2;

            QString grille[9][9];
            bool masque[9][9];
            int nbrGrilles;

            if(m_imprimer->getModeNormal()){
                nbrGrilles = 1;
            }else{
                nbrGrilles = 6;
            }

            for(int o=0; o<nbrGrilles; o++){
                if (!generation(grille, masque)){
                    o--;
                    continue;
                }

                pen.setWidth(pen1);
                paint->setPen(pen);

                paint->drawRect(x, y, 9*casex, 9*casey);

                paint->drawLine(x+3*casex, y, x+3*casex, y+9*casey);
                paint->drawLine(x+6*casex, y, x+6*casex, y+9*casey);

                paint->drawLine(x, y+3*casey, x+9*casex, y+3*casey);
                paint->drawLine(x, y+6*casey, x+9*casex, y+6*casey);

                pen.setWidth(pen2);
                paint->setPen(pen);

                paint->drawLine(x+1*casex, y, x+1*casex, y+9*casey);
                paint->drawLine(x+2*casex, y, x+2*casex, y+9*casey);
                paint->drawLine(x+4*casex, y, x+4*casex, y+9*casey);
                paint->drawLine(x+5*casex, y, x+5*casex, y+9*casey);
                paint->drawLine(x+7*casex, y, x+7*casex, y+9*casey);
                paint->drawLine(x+8*casex, y, x+8*casex, y+9*casey);

                paint->drawLine(x, y+1*casey, x+9*casex, y+1*casey);
                paint->drawLine(x, y+2*casey, x+9*casex, y+2*casey);
                paint->drawLine(x, y+4*casey, x+9*casex, y+4*casey);
                paint->drawLine(x, y+5*casey, x+9*casex, y+5*casey);
                paint->drawLine(x, y+7*casey, x+9*casex, y+7*casey);
                paint->drawLine(x, y+8*casey, x+9*casex, y+8*casey);

                for(int i=0; i<9; i++){
                    for(int j=0; j<9; j++){
                        if(!m_imprimer->getModeNormal() and !masque[i][j]){
                            pen.setWidth(pen2);
                            pen.setColor(Qt::black);
                            paint->setPen(pen);

                            paint->drawText(x+i*casex, y+j*casey, casex, casey, Qt::AlignCenter, grille[i][j]);
                        }else if(m_imprimer->getModeNormal() and m_grille[i*9+j] != 0){
                            pen.setWidth(pen2);
                            pen.setColor(Qt::black);
                            paint->setPen(pen);

                            paint->drawText(x+i*casex, y+j*casey, casex, casey, Qt::AlignCenter, QString::number(m_grille[i*9+j]));
                        }else if(m_imprimer->getAfficherAide()){
                            pen.setWidth(pen3);
                            pen.setColor(Qt::lightGray);
                            paint->setPen(pen);

                            paint->drawLine(x+i*casex+1*minicasex, y+j*casey, x+i*casex+1*minicasex, y+j*casey+casey);
                            paint->drawLine(x+i*casex+2*minicasex, y+j*casey, x+i*casex+2*minicasex, y+j*casey+casey);
                            paint->drawLine(x+i*casex, y+j*casey+1*minicasey, x+i*casex+casex, y+j*casey+1*minicasey);
                            paint->drawLine(x+i*casex, y+j*casey+2*minicasey, x+i*casex+casex, y+j*casey+2*minicasey);

                            for(int k=0; k<9; k++){
                                paint->drawText(x+i*casex+(k%3)*minicasex, y+j*casey+((k-k%3)/3)*minicasey, minicasex, minicasey, Qt::AlignCenter, QString::number(k+1));
                            }
                        }
                    }
                }

                if(x >= 9*casex+espacex){
                    x -= 9*casex+espacex;
                    y += 9*casey+espacey;
                }else{
                    x += 9*casex+espacex;
                }
            }

            paint->end();
        }
    }
}
void Fenetre::slotPartieQuitter(){
    if(QMessageBox::question(this, "Quitter", "Etes-vous sur de vouloir <b>quitter</b> ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
        if(QMessageBox::question(this, "Enregistrer", "Voulez-vous <b>enregistrer</b> la partie ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
            slotPartieEnregistrer();
        }
        qApp->quit();
    }
}
void Fenetre::slotAideVerifierRegles(){
    m_modeClavier = false;
    m_boutons[m_modeClavierPos]->showLabel(2, false);

    bool tab_erreur[81] = {false};
    int grille[81];
    for(int i=0; i<81; i++){
        grille[i] = m_boutons[i]->getValeur();
    }

    bool erreur = verifier(grille, tab_erreur);

    for(int i=0; i<81; i++){
        if(tab_erreur[i]){
            if(!m_boutons[i]->getFixe()){
                m_boutons[i]->showLabel(2, true);
            }else{
                tab_erreur[i] = false;
            }
        }
    }

    if(erreur){
        if(QMessageBox::warning(this, "Vérification", "Des <b>erreurs</b> on été trouvées dans votre grille, voulez-vous les supprimer ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
            for(int i=0; i<81; i++){
                if(tab_erreur[i]){
                    slotModifierBouton(i, 0);
                    m_boutons[i]->showLabel(2, false);
                }
            }
            QMessageBox::warning(this, "Vérification", "Les erreurs on été <b>reparées</b>.");
        }else{
            for(int i=0; i<81; i++){
                if(tab_erreur[i]){
                    m_boutons[i]->showLabel(2, false);
                }
            }
        }
    }else{
        QMessageBox::warning(this, "Vérification", "Votre grille est <b>valide</b>.\n(par rapport aux règles du sudoku)");
    }
}
void Fenetre::slotAideVerifierSolution(){
    if(m_resolut == -1){
        resoudre();
    }
    if(m_resolut == 0){
        QMessageBox::warning(this, "Vérification", "Votre grille n'a <b>pas de solution</b>.");
    }else if(m_resolut > 1){
        QMessageBox::warning(this, "Vérification", "Cette <b>option</b> est <b>désactivée</b> car la grille possède plusieurs solutions.");
    }else{
        m_modeClavier = false;
        m_boutons[m_modeClavierPos]->showLabel(2, false);

        bool erreur = false;
        bool tab_erreur[81] = {false};
        int valeur = 0;

        for(int i=0; i<81; i++){
            valeur = m_boutons[i]->getValeur();
            if(valeur != 0 and valeur != m_grille_full[i]){
                m_boutons[i]->showLabel(2, true);
                tab_erreur[i] = true;
                erreur = true;
            }
        }

        if(erreur){
            if(QMessageBox::warning(this, "Vérification", "Des <b>erreurs</b> on été trouvées dans votre grille, voulez-vous les supprimer ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
                for(int i=0; i<81; i++){
                    if(tab_erreur[i]){
                        slotModifierBouton(i, 0);
                        m_boutons[i]->showLabel(2, false);
                    }
                }
                QMessageBox::warning(this, "Vérification", "Les erreurs on été <b>reparées</b>.");
            }else{
                for(int i=0; i<81; i++){
                    if(tab_erreur[i]){
                        m_boutons[i]->showLabel(2, false);
                    }
                }
            }
        }else{
            QMessageBox::warning(this, "Vérification", "Votre grille est <b>valide</b>.\n(par rapport à la solution)");
        }
    }
}
void Fenetre::slotAideResoudre(){
    if(m_resolut == -1){
        resoudre();
        if(m_resolut > 1){
            QMessageBox::warning(this, "Solution", "Cette grille possède <b>plusieurs solutions</b>.");
        }
    }
    if(m_resolut == 0){
        QMessageBox::warning(this, "Solution", "Cette grille n'a <b>pas de solution</b>.");
    }else{
        m_solution->show();
    }
}
void Fenetre::slotAideReveler(){
    if(m_resolut == -1){
        resoudre();
    }
    if(m_resolut == 0){
        QMessageBox::warning(this, "Solution", "Cette grille n'a <b>pas de solution</b>.");
    }else if(m_resolut > 1){
        QMessageBox::warning(this, "Solution", "Cette <b>option</b> est <b>désactivée</b> car la grille possède plusieurs solutions.");
    }else{
        int t = rand()%81;
        while(true){
            t = (t+1)%81;
            if(m_boutons[t]->getValeur() == 0){
                slotModifierBouton(t, m_grille_full[t]);
                m_boutons[t]->setFixe(true);
                m_boutons[t]->showLabel(1, m_actionOptionAfficher->isCheckable());
                m_grille[t] = m_grille_full[t];
                break;
            }
        }
    }
}
void Fenetre::slotOptionAfficher(){
    for(int i=0; i<81; i++){
        if(m_boutons[i]->getFixe()){
            m_boutons[i]->showLabel(1, m_actionOptionAfficher->isCheckable());
        }
    }
}
void Fenetre::slotOptionValeur(){
    bool valeur = m_actionOptionValeur->isCheckable();
    for(int i=0; i<81; i++){
        m_boutons[i]->showLabel(3, valeur and m_boutons[i]->getValeur() != 0);
    }
    m_choix->afficherValeur(valeur);
}
void Fenetre::slotOptionVider(){
    if (QMessageBox::question(this, "Vider la grille", "Etes-vous sur de vouloir <b>vider</b> la grille ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
        for(int i=0; i<81; i++){
            if(!m_boutons[i]->getFixe()){
                slotModifierBouton(i, 0);
            }
        }
        m_modeClavier = false;
        m_boutons[m_modeClavierPos]->showLabel(2, false);
    }
}
void Fenetre::slotOptionRegles(){
    QMessageBox::information(this, "Règles du sudoku", "<b>But du jeu :</b><br />Vous devez compléter le tableau, c'est à dire remplacer touts les nuages par des planètes.<br/><br /><b>Contraintes :</b><br />-Une même planète ne peut pas se retrouver plusieurs fois sur une même ligne.<br />-Une même planète ne peut pas se retrouver plusieurs fois sur une même colonne.<br />-Une même planète ne peut pas se retrouver plusieurs fois dans une même zone. (les carrés 3x3)<br /><br /><b>Commandes :</b><br />Vous pouvez utiliser la souris (en cliquant sur les boutons) et/ou les touches directionnelles ainsi que la touche Entrer.");
}
void Fenetre::slotAbout(){
    QMessageBox::information(this, "A propos", "<b>Nom :</b> SpaceSudo<br /><b>Date de sortie :</b> 31/07/08.<br /><b>Auteur :</b> Heero.<br /><b>Autres :</b> Produit dans le cadre d'un concours diffusé sur le <a href='http://www.siteduzero.com/concours-654-2-le-sudoku-des-nombres-en-folie.html'>Site du Zér0</a>.");
}


void Fenetre::slotAfficherChoix(int numero, int valeur){
    m_choix->setWindowTitle("Planète n°"+QString::number(numero+1));
    m_choix->move(pos().x()+(width()-140)/2, pos().y()+(height()-180)/2);
    m_choix->update(numero, valeur, m_boutons, m_actionAideFiltrer->isCheckable(), m_actionOptionValeur->isCheckable(), m_modeClavier);
    m_choix->show();
    m_choix->activateWindow();
}
void Fenetre::slotModifierBouton(int numero, int valeur){
    int val = m_boutons[numero]->getValeur();
    m_toolbarValeur[val]--;
    m_toolbarValeur[valeur]++;
    m_toolbarLabel[val*2+1]->setText(QString::number(m_toolbarValeur[val]));
    m_toolbarLabel[valeur*2+1]->setText(QString::number(m_toolbarValeur[valeur]));

    m_boutons[numero]->showLabel(3, m_actionOptionValeur->isCheckable() and valeur != 0);
    m_boutons[numero]->setImage(m_images[valeur]);
    m_boutons[numero]->setValeur(valeur);

    if(m_toolbarValeur[0] == 0){
        bool tab_erreur[81] = {false};
        int grille[81];
        for(int i=0; i<81; i++){
            grille[i] = m_boutons[i]->getValeur();
        }
        bool erreur = verifier(grille, tab_erreur);
        if(!erreur){
            QMessageBox::information(this, "Résultat", "Bravo vous avez <b>terminé</b> cette partie.");
        }else{
            QMessageBox::information(this, "Résultat", "Votre grille comporte des <b>erreurs</b>.");
        }
    }
}
void Fenetre::slotCheck(){
    QAction *action = qobject_cast<QAction *>(sender());
    if(action->isCheckable()){
        action->setCheckable(false);
        action->setIcon(QIcon("icone/nocheck.png"));
    }else{
        action->setCheckable(true);
        action->setIcon(QIcon("icone/check.png"));
    }
}
void Fenetre::slotChrono(){
    m_temps += 1;
    int secondes = m_temps%60;
    int minutes = ((m_temps-secondes)/60)%60;
    QString sec = QString::number(secondes);
    QString min = QString::number(minutes);

    if(secondes < 10){
        sec = "0"+sec;
    }
    if(minutes < 10){
        min = "0"+min;
    }

    this->setWindowTitle("SpaceSudo ("+min+":"+sec+")");
}


////////////////////////////////////////////////
//                 METHODES                   //
////////////////////////////////////////////////

void Fenetre::closeEvent(QCloseEvent* event){
    slotPartieQuitter();
    event->ignore();
}
void Fenetre::keyPressEvent(QKeyEvent *event){
    int pos = m_modeClavierPos;
    if(event->key() == Qt::Key_Return){
        if(m_modeClavier){
            slotAfficherChoix(pos, m_boutons[pos]->getValeur());
        }
    }
    if(event->key() == Qt::Key_Right or event->key() == Qt::Key_Left or event->key() == Qt::Key_Up or event->key() == Qt::Key_Down){
        if(!m_modeClavier){
            m_modeClavier = true;
            pos = 0;
            while(pos<81 and m_boutons[pos]->getFixe() == true){
                pos ++;
            }
            if(pos < 81){
                m_modeClavierPos = pos;
                m_boutons[pos]->showLabel(2, true);
            }else{
                m_modeClavier = false;
                QMessageBox::warning(this, "Erreur", "C'est étonnant, <b>toutes</b> les planètes de votre grille sont <b>fixes</b>.");
            }
        }else{
            m_boutons[pos]->showLabel(2, false);

            if(event->key() == Qt::Key_Right){
                do{
                    pos++;
                    if(pos>80){
                        pos -= 81;
                    }
                }while(m_boutons[pos]->getFixe() == true);
            }
            if(event->key() == Qt::Key_Left){
                do{
                    pos--;
                    if(pos<0){
                        pos += 81;
                    }
                }while(m_boutons[pos]->getFixe() == true);
            }
            if(event->key() == Qt::Key_Up){
                do{
                    pos -= 9;
                    if(pos == -9){
                        pos = 80;
                    }else if(pos<0){
                        pos += 80;
                    }
                }while(m_boutons[pos]->getFixe() == true);
            }
            if(event->key() == Qt::Key_Down){
                do{
                    pos += 9;
                    if(pos == 89){
                        pos = 0;
                    }else if(pos > 80){
                        pos -= 80;
                    }
                }while(m_boutons[pos]->getFixe() == true);
            }

            m_boutons[pos]->showLabel(2, true);
            m_modeClavierPos = pos;
        }
    }
}
void Fenetre::resoudre(){

    bool grille_bool[81][9];
    int grille_nbr[81];
    int grille_nbr2 = 0;
    int grille[81];
    int niveau = 0;

    for(int i=0; i<81; i++){
        grille[i] = m_grille[i];
        if(m_grille[i] == 0){
            grille_nbr[i] = 0;
        }else{
            grille_nbr[i] = 8;
            grille_nbr2++;
        }
        for(int o=0; o<9; o++){
            grille_bool[i][o] = true;
        }
    }

    //int temps = clock();

    int nbrSol = solver(grille, grille_bool, grille_nbr, &grille_nbr2, m_grille_full, &niveau);

    //temps = clock()-temps;
    //QMessageBox::information(this, "Solution", "Solution calculée en : "+QString::number(fin)+"ms, "+QString::number(nbrSol));

    if(nbrSol > 1){
        m_solution->setWindowTitle("Solution (Il y en a d'autres)");
        m_actionAideReveler->setDisabled(true);
        m_actionAideVerifierSolution->setDisabled(true);
    }

    m_solution->update(m_grille_full, m_imagesMini);

    m_resolut = nbrSol;
}
int Fenetre::solver(int *grille, bool grille_bool[][9], int *grille_nbr, int *grille_nbr2, int *grilleSource, int *niveau){
    while (solver1(grille, grille_bool, grille_nbr, grille_nbr2)){
        for(int i=0; i<81; i++){
            if(grille_nbr[i] == 9){
                return 0;
            }
        }
    }

    if(*grille_nbr2 == 81){
        if(grilleSource != NULL){
            for(int i=0; i<81; i++){
                grilleSource[i] = grille[i];
            }
        }
        return 1;
    }else{
        bool grille_boolTemp[81][9];
        int grille_nbrTemp[81];
        int grille_nbr2Temp;
        int grilleTemp[81];
        int nbrSolution = 0;

        int tailleMax = 0;
        int tailleMaxPos = 0;
        for(int i=0; i<81; i++){
            if(grille_nbr[i] != -1 and grille_nbr[i]>tailleMax){
                tailleMax = grille_nbr[i];
                tailleMaxPos = i;
            }
        }

        for(int i=0; i<9; i++){
            if(grille_bool[tailleMaxPos][i]){
                for(int o=0; o<81; o++){
                    grilleTemp[o] = grille[o];
                    grille_nbrTemp[o] = grille_nbr[o];
                    for(int u=0; u<9; u++){
                        grille_boolTemp[o][u] = grille_bool[o][u];
                    }
                }

                grilleTemp[tailleMaxPos] = i+1;
                grille_nbrTemp[tailleMaxPos] = 8;
                grille_nbr2Temp = *grille_nbr2+1;

                if(grilleSource != NULL){
                    *niveau += 1;
                }
                int retour = solver(grilleTemp, grille_boolTemp, grille_nbrTemp, &grille_nbr2Temp, grilleSource, niveau);

                if(grilleSource != NULL){
                    *niveau -= 1;
                }

                if(retour > 1){
                    return 2; // il y a plusieurs solution
                }

                nbrSolution += retour;
            }
        }
        return nbrSolution;
    }
}
bool Fenetre::solver1(int *grille, bool grille_bool[][9], int *grille_nbr, int *grille_nbr2){
    bool retour = false;
    int pos = 0;
    int pos_i = 0;


    for(int i=0; i<81; i++){
        if(grille_nbr[i] == 8){

            if(grille[i] == 0){
                for(int o=0; o<9; o++){
                    if(grille_bool[i][o]){
                        grille[i] = o+1;
                        break;
                    }
                }
                *grille_nbr2 += 1;
            }

            pos_i = grille[i]-1;
            grille_nbr[i] = -1;
            retour = true;

            // ligne
            pos = i-i%9;
            for(int o=0; o<9; o++){
                if(grille[pos] == 0 and grille_bool[pos][pos_i]){
                    grille_bool[pos][pos_i] = false;
                    grille_nbr[pos]++;
                }
                pos++;
            }

            // colone
            pos = i%9;
            for(int o=0; o<9; o++){
                if(grille[pos] == 0 and grille_bool[pos][pos_i]){
                    grille_bool[pos][pos_i] = false;
                    grille_nbr[pos]++;
                }
                pos += 9;
            }

            // zone
            pos = (i-(i%3))-(((i-(i%9))/9)%3)*9;
            for(int o=0; o<9; o++){
                if(grille[pos] == 0 and grille_bool[pos][pos_i]){
                    grille_bool[pos][pos_i] = false;
                    grille_nbr[pos]++;
                }
                if(pos%3 == 2){
                    pos += 7;
                }else{
                    pos++;
                }
            }
        }
    }
    return retour;
}
bool Fenetre::verifier(int *grille, bool *tab_erreur){
    bool erreur = false;
    int tab_chiffres[10];
    int pos;

    // lignes
    for(int i=0; i<9; i++){
        for(int o=0; o<10; o++){
            tab_chiffres[o] = -1;
        }
        pos = i*9;
        for(int o=0; o<9; o++){
            if(grille[pos] != 0){
                if(tab_chiffres[grille[pos]] == -1){
                    tab_chiffres[grille[pos]] = pos;
                }else{
                    erreur = true;
                    tab_erreur[tab_chiffres[grille[pos]]] = true;
                    tab_erreur[pos] = true;
                }
            }
            pos++;
        }
    }

    // colones
    for(int i=0; i<9; i++){
        for(int o=0; o<10; o++){
            tab_chiffres[o] = -1;
        }
        pos = i;
        for(int o=0; o<9; o++){
            if(grille[pos] != 0){
                if(tab_chiffres[grille[pos]] == -1){
                    tab_chiffres[grille[pos]] = pos;
                }else{
                    erreur = true;
                    tab_erreur[tab_chiffres[grille[pos]]] = true;
                    tab_erreur[pos] = true;
                }
            }
            pos += 9;
        }
    }

    // zones
    pos = 0;
    for(int i=0; i<9; i++){
        for(int o=0; o<10; o++){
            tab_chiffres[o] = -1;
        }
        for(int o=0; o<9; o++){
            if(grille[pos] != 0){
                if(tab_chiffres[grille[pos]] == -1){
                    tab_chiffres[grille[pos]] = pos;
                }else{
                    erreur = true;
                    tab_erreur[tab_chiffres[grille[pos]]] = true;
                    tab_erreur[pos] = true;
                }
            }
            if(o%3 == 2){
                pos += 7;
            }else{
                pos++;
            }
        }
        if(i%3 == 2){
            pos -= 6;
        }else{
            pos -= 24;
        }
    }

    return erreur;
}
bool Fenetre::generation(QString grille[][9], bool masque[][9]){
    QString zone[9][9];
    QString ligne[9][9];
    QString colone[9][9];
    QString loterie = "depart";
    QString tab48 = "0123456789";
    QString tab97 = "abcdefghi";

    QString posi;
    QString liste;

    int tentative = 0;
    int tentative_max = 100;
    int iter;
    int itermax;

    int bingo;
    int p;
    int i;
    int j;
    int libre;

    while(loterie.size()>0 and tentative<tentative_max){
        tentative++;
        iter = 0;
        itermax = 82;
        loterie = "";
        // iniatisation, grille et masque, d'abord initialisée à '0'
        for (int n=0; n<9; n++){
            for (int m=0; m<9; m++){
                grille[n][m] = "0";
                masque[n][m] = false;
                loterie += tab97.at(n);
                loterie += tab48.at(m);
            }
        }
        // Au début toutes les positions sont possibles
        for (int n=0; n<9; n++){
            for (int m=0; m<9; m++){
                zone[n][m] = "012345678";
                ligne[n][m] = "012345678";
                colone[n][m] = "012345678";
            }
        }

        while (loterie != "" and iter<itermax){
            iter++;
            // placement déterministe d'un chiffre dans une case
            bingo = 0;
            for (int n=0; n<9; n++){
                for (int m=0; m<9; m++){
                    // en premier les régions
                    if (zone[n][m].size() == 1){
                        p = tab48.indexOf(zone[n][m]);
                        i = (n-n%3)+(p-p%3)/3;
                        j = (n%3)*3+(p%3);
                        affectation(zone, ligne, colone, grille, masque, &loterie, i, j, m, true);
                        bingo = 1;
                        break;
                    }
                    // en second les lignes
                    if (ligne[n][m].size() == 1){
                        p = tab48.indexOf(ligne[n][m]);
                        i = n;
                        j = p;
                        affectation(zone, ligne, colone, grille, masque, &loterie, i, j, m, true);
                        bingo = 1;
                        break;
                    }
                    // en troisième les colonnes
                    if (colone[n][m].size() == 1){
                        p = tab48.indexOf(colone[n][m]);
                        i = p;
                        j = n;
                        affectation(zone, ligne, colone, grille, masque, &loterie, i, j, m, true);
                        bingo = 1;
                        break;
                    }
                }
                if (bingo == 1){
                    break;
                }
            }
            // placement par tirage au sort, si le placement déterministe n'a pas abouti
            if (bingo == 0){
                // tirage d'une case $i,$j parmis les cases libres

                posi = loterie.mid((rand()%((loterie.size()-loterie.size()%2)/2))*2, 2);
                // détermination des coordonnées de la case: $i,$j
                i = tab97.indexOf(posi.mid(0, 1));
                j = tab48.indexOf(posi.mid(1, 1));
                // tirage d'un chiffre parmis les chiffres libres
                liste = "";
                for (int m=0; m<9; m++){
                    libre = 1;
                    // régions
                    p = (i-i%3)+((j-j%3)/3);
                    if (zone[p][m] == ""){
                        libre = 0;
                    }
                    // lignes
                    p = i;
                    if (ligne[p][m] == ""){
                        libre = 0;
                    }
                    // colonnes
                    p = j;
                    if (colone[p][m] == ""){
                        libre = 0;
                    }
                    // concaténation
                    if (libre == 1){
                        liste += tab48.at(m);
                    }
                }
                if (liste.size() > 0){
                    p = rand()%liste.size();
                    p = tab48.indexOf(liste.mid(p, 1));
                    affectation(zone, ligne, colone, grille, masque, &loterie, i, j, p, false);
                }
            }
        }
    }

    if (loterie.size() != 0){
        return false;
    }else{
        return true;
    }
}
void Fenetre::affectation(QString zone[][9], QString ligne[][9], QString colone[][9], QString grille[][9], bool masque[][9], QString *loterie, int i, int j, int m, bool masqueVal){
	if (grille[i][j] == "0"){
		QString tab48 = "0123456789";
        QString tab97 = "abcdefghi";
        QString posi;

		grille[i][j] = tab48.at(m+1);

		posi = tab97.at(i);
		posi += tab48.at(j);
		(*loterie).replace(posi, QString(""));
		elimination(zone, ligne, colone, i, j, m);
        masque[i][j] = masqueVal;
	}
}
void Fenetre::elimination(QString zone[][9], QString ligne[][9], QString colone[][9], int i, int j, int m){
	QString tab48 = "0123456789";
    QString tab97 = "abcdefghi";
    QString posi;
	int var;
	int var2;
	int ic;
	int jc;

	// case $i,$j , chiffre= $m+1
	// élimination du chiffre en mettant les positions possibles à rien (= "")
	var = (i-i%3)+((j-j%3)/3); // région concernée numéro $n
	zone[var][m] = "";
	var = i; // ligne concernée numéro $n
	ligne[var][m] = "";
	var = j; // Colonne concernée numéro $n
	colone[var][m] = "";
	// élimination sélective des positions possibles	dans les régions voisines
	for(int n=0; n<9; n++){
		for (int p=0; p<9; p++){
			// $p est la position d'une case dans une région
			// position de la case en coordonnées 'grille', $ic,$jc
			ic = (n-n%3)+((p-p%3)/3);
			jc = (n%3)*3+(p%3);
			if (ic == i or jc == j){
				posi = tab48.at(p);
				zone[n][m].replace(posi, QString(""));
			}
		}
	}
	// élimination sélective des positions possibles	dans les lignes voisines
	posi = tab48.at(j);
	for(int n=0; n<9; n++){
		ligne[n][m].replace(posi, QString(""));
	}
	// élimination sélective des positions possibles	dans les colonnes voisines
	posi = tab48.at(i);
	for(int n=0; n<9; n++){
		colone[n][m].replace(posi, QString(""));
	}
	// élimination sélective des positions possibles, lignes-colonnes/région
	var = (i-i%3)+((j-j%3)/3); // région concernée numéro $n
	for(int p=0; p<9; p++){
		// position de la case en coordonnées 'grille', $ic,$jc
		ic = (var-var%3)+((p-p%3)/3);
		jc = (var%3)*3+(p%3);
		posi = tab48.at(jc);
		ligne[ic][m].replace(posi, QString(""));
		posi = tab48.at(ic);
		colone[jc][m].replace(posi, QString(""));
	}
	// élimination de la position occupée quelque soit le chiffre
	for(int mc=0; mc<9; mc++){
		// régions (la région concernée, numéro $n)
		var = (i-i%3)+((j-j%3)/3);
		var2 = (i%3)*3+(j%3);
		posi = tab48.at(var2);
		zone[var][mc].replace(posi, QString(""));
		// lignes
		posi = tab48.at(j);
		ligne[i][mc].replace(posi, QString(""));
		// colonnes
		posi = tab48.at(i);
		colone[j][mc].replace(posi, QString(""));
	}
}
