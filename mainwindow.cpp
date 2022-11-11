#include "mainwindow.h"
#include "ui_mainwindow.h"

double displayvalue = 0;
bool multtrigger = false;
bool divtrigger = false;
bool addtrigger = false;
bool subtrigger = false;
bool equalstrigger = false;
double mem = 0.0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Initialise Display to 0.0
    ui->Display->setText(QString::number(displayvalue));

    //Connect the 0-9 Buttons to NumPressed
    for(int i = 0; i<10; i++)
    {
    QString ButtonName = "Button" + QString::number(i);
    QPushButton* ptr = MainWindow::findChild<QPushButton*>(ButtonName);
    connect(ptr, &QPushButton::clicked, this, &MainWindow::NumPressed);
    }

    //The Clear Button
    connect(ui->AllClear, &QPushButton::clicked, this, &MainWindow::clearALL);

    //Math Number Connections
    connect(ui->Add, &QPushButton::clicked, this, &MainWindow::MathNumPressed);
    connect(ui->Subtract, &QPushButton::clicked, this, &MainWindow::MathNumPressed);
    connect(ui->Multiply, &QPushButton::clicked, this, &MainWindow::MathNumPressed);
    connect(ui->Divide, &QPushButton::clicked, this, &MainWindow::MathNumPressed);

    //Connect Equals Button
    connect(ui->Equals, &QPushButton::clicked, this, &MainWindow::EqualsPressed);

    //Connect Change Sign Button
    connect(ui->ChangeSign, &QPushButton::clicked, this, &MainWindow::changesign);

    //Connect the Memory Buttons
    connect(ui->MemAdd, &QPushButton::clicked, this, &MainWindow::addmem);
    connect(ui->MemSub, &QPushButton::clicked, this, &MainWindow::submem);
    connect(ui->MemRecall, &QPushButton::clicked, this, &MainWindow::recallmem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed()
{
    if (equalstrigger != 0)
    {
        displayvalue = 0;
        ui->Display->setText(QString::number(displayvalue));
        ui->label->clear();
        equalstrigger = 0;
    }

    QPushButton* WhichButton = (QPushButton*)sender();
    QString ButtonTxt = WhichButton->text();
   // int ButtonVal = ButtonTxt.toInt();
    QString CurrentDisplayTxt = ui->Display->text();

    if ((CurrentDisplayTxt.toDouble() == 0) || (CurrentDisplayTxt.toDouble()) == 0.0)
    ui->Display->setText(ButtonTxt);
    else
    {
        QString NewVal = CurrentDisplayTxt + ButtonTxt;
        double dblNewVal = NewVal.toDouble();

        // g means whether precision is fixed or not, g means not fixed so counts from left mostdigit.
        // the number says how many digits to display in precision before scientific kicks in.
        // No Trailing zeros by default, so 0.0 will be displayed as 0.
        ui->Display->setText(QString::number(dblNewVal, 'g', 10));
    }

    ui->label->clear();

}

void MainWindow::clearALL()
{
    displayvalue = 0;
    ui->Display->setText(QString::number(displayvalue));
    ui->label->clear();

    //Clear All Math Number Triggers
    multtrigger = false;
    divtrigger = false;
    addtrigger = false;
    subtrigger = false;
    equalstrigger = false;

}

void MainWindow::MathNumPressed()
{
    QPushButton* WhichButton = (QPushButton*)sender();
    QString ButtonTxt = WhichButton->text();

    //Clear All Math Number Triggers
    multtrigger = false;
    divtrigger = false;
    addtrigger = false;
    subtrigger = false;
    equalstrigger = 0;

    //Set the Label and store which math button pressed
    if (ButtonTxt == "*")
    { ui->label->setText("Multiply"); multtrigger = true; }
    else if (ButtonTxt == "/")
    { ui->label->setText("Divide"); divtrigger = true; }
    else if (ButtonTxt == "+")
    { ui->label->setText("Add"); addtrigger = true; }
    else if (ButtonTxt == "-")
    { ui->label->setText("Subtract"); subtrigger = true; }

    //Store Current Value on Display and clear it
    QString CurrentValueTxt = ui->Display->text();
    displayvalue = CurrentValueTxt.toDouble();
    ui->Display->clear();
}

void MainWindow::EqualsPressed()
{
    if (!equalstrigger)
    {
    equalstrigger = true;

    if (addtrigger)
    {
    QString CurrentDisplayTxt = ui->Display->text();
    double val = CurrentDisplayTxt.toDouble() + displayvalue;
    ui->Display->setText(QString::number(val));
    }

    if (subtrigger)
    {
        QString CurrentDisplayTxt = ui->Display->text();
        double val = displayvalue - CurrentDisplayTxt.toDouble();
        ui->Display->setText(QString::number(val));
    }

    if (multtrigger)
    {
        QString CurrentDisplayTxt = ui->Display->text();
        double val = CurrentDisplayTxt.toDouble() * displayvalue;
        ui->Display->setText(QString::number(val));
    }

    if (divtrigger)
    {
        QString CurrentDisplayTxt = ui->Display->text();
        double val = displayvalue / CurrentDisplayTxt.toDouble();
        ui->Display->setText(QString::number(val));
    }
    }
}

void MainWindow::changesign()
{
    QString CurrentDisplayTxt = ui->Display->text();
    double val = CurrentDisplayTxt.toDouble() * -1;
    ui->Display->setText(QString::number(val));
}

void MainWindow::addmem()
{
    ui->label->clear();
    QString CurrentDisplayTxt = ui->Display->text();
    mem = CurrentDisplayTxt.toDouble() + mem;
    ui->memlabel->setText(QString::number(mem));
}


void MainWindow::submem()
{
    ui->label->clear();
    QString CurrentDisplayTxt = ui->Display->text();
    if (mem > 0)
    {
    mem = mem - CurrentDisplayTxt.toDouble();
    ui->memlabel->setText(QString::number(mem));
    }
}


void MainWindow::recallmem()
{
    ui->label->clear();
    ui->Display->setText(QString::number(mem));
    ui->memlabel->clear();
    mem = 0.0;
}
