#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "findghost.h"
#include <QAbstractItemView>


//Stores previous currentIndex of cB1 & cB2 for equalIndex handling
int prevcB1 = -1;
int prevcB2 = -1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
        Contains GHOST TYPE, EVIDENCE
            Evidence in format 0 - 6
            0 - Fingerprints
            1 - Ghost Orbs
            2 - Freezing Temperatures
            3 - Spirit Box
            4 - EMF Level 5
            5 - D.O.T.S Projector
            6 - Ghost Writing
    */
    QStringList evidDB = {"Fingerprints", "Ghost Orbs", "Freezing Temperatures",
                          "Spirit Box", "EMF Level 5", "D.O.T.S Projector", "Ghost Writing"};

    //Add list to both comboBoxes
    ui->cB1->addItems(evidDB);
    ui->cB2->addItems(evidDB);

    //Set up the PlaceHolderText
    ui->cB1->setPlaceholderText("EVIDENCE 1");
    ui->cB2->setPlaceholderText("EVIDENCE 2");

    //Current Index after adding list is 0
    //To display PlaceHolderText change current index to -1
    ui->cB1->setCurrentIndex(-1);
    ui->cB2->setCurrentIndex(-1);

    //Proof that setText(QString) works
    //ui->label->setText("test");

    //Output label text
    ui->label->setText("");

    //Intro label text
    ui->introLabel->setText("Please enter two pieces of evidence.");

    //Sets both signals for equal index
    //cB2 is changing Indexes
    connect(ui->cB2, SIGNAL( currentIndexChanged(int) ), this, SLOT ( cB2equalIndex() ));
    //cB1 is changing Indexes
    connect(ui->cB1, SIGNAL( currentIndexChanged(int) ), this, SLOT ( cB1equalIndex() ));

    //Sets both to same function that displays last evidence output as label
    connect(ui->cB1, SIGNAL( currentIndexChanged(int) ), this, SLOT ( cBsDisplayEvid() ));
    connect(ui->cB2, SIGNAL( currentIndexChanged(int) ), this, SLOT ( cBsDisplayEvid() ));

    //Had to #import<AbstractItemView>
    //The function stops Windows OS from adding shadows to the ComboBox
    ui->cB1->view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    ui->cB2->view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

    //ui->cB1->view()->parentWidget()->setWindowOpacity(.75);




}

//Handles for equalIndexes for changing Index of cB1
void MainWindow::cB1equalIndex()
{
    //Firstly checks if they are equal
    //Afterwards confirms that they are not equal to -1
    if( (ui->cB1->currentIndex() == ui->cB2->currentIndex()) && ( ui->cB1->currentIndex() != -1))
    //Stores value of previous index until needed
    {
        //Once they are equal though, changes it back to the previous index
        ui->cB1->setCurrentIndex(prevcB1);
    }
    else
    {
        prevcB1 = ui->cB1->currentIndex();
    }
}
void MainWindow::cB2equalIndex()
{
    //Clone of function above 'cB1equalIndex()'
    if( (ui->cB1->currentIndex() == ui->cB2->currentIndex()) && ( ui->cB1->currentIndex() != -1))
    {
        ui->cB2->setCurrentIndex(prevcB2);
    }
    else
    {
        prevcB2 = ui->cB2->currentIndex();
    }
}

//Changes the displayed last evidence associated with ghosts for different ComboBox 1 & 2 inputs
void MainWindow::cBsDisplayEvid()
{
    //Need to know neither currentIndex of both comboBoxes are -1
    if( (ui->cB1->currentIndex() != -1) && (ui->cB2->currentIndex() != -1) )
    {
        //Creates the findGhost object and wraps it around a smart pointer to automatically deconstruct it
        unique_ptr<findGhost> ghostFindy(new findGhost( ui->cB1->currentIndex(), ui->cB2->currentIndex() ));
        ui->label->setText(ghostFindy->printLastGhostEvid());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

