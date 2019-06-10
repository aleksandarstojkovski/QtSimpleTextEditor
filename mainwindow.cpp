#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    connect(this->ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(this->ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(this->ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    ui->textEdit->clear();
    m_filename="";
    this->setWindowTitle("");
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save file");
    m_filename=fileName;
    QFile file{fileName};
    if (!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot open file");
        return;
    }
    setWindowTitle(fileName);
    QString text = ui->textEdit->toPlainText();
    QTextStream out(&file);
    out << text;
    file.close();
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file");
    m_filename=fileName;
    QFile file{fileName};
    if (!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot open file");
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
}
