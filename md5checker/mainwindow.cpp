#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcryptographichash.h"

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent),  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//zwraca sume kontrolna pliku w danym algorytmie
QByteArray fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile f(fileName);
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&f)) {
            return hash.result();
        }
    }
    return QByteArray();
}

//wyswietl sume kontrolna pliku
void MainWindow::checkChecksum(){
    if (filePath !=""){
        ui->openButton->setText(filePath);
        try {
            QString l = fileChecksum(filePath,QCryptographicHash::Md5).toHex();
            ui->lineEdit_md5file->setText(l);
        }catch(...) {}

        //jesli podano md5
        if (ui->lineEdit_md5compare->text() != ""){
            //sprawdzenie czy md5 sa takie same
            if (ui->lineEdit_md5file->text() == ui->lineEdit_md5compare->text()){
                ui->label_info->setText("OK! Its the same file.");
            }
            else {
                ui->label_info->setText("OPS! Its not the same file!");
            }
        }
    }

}

//klikniecie buttona otwierajacego plik
void MainWindow::on_openButton_clicked()
{   

    filePath = QFileDialog::getOpenFileName(this,tr("Open File"), filePath, tr("all types (*)"));
    checkChecksum();

}

//zmiana pola z md5 do porownania
void MainWindow::on_lineEdit_md5compare_textChanged(const QString &arg1)
{
    if (ui->lineEdit_md5file->text() != ""){
        //sprawdzenie czy md5 sa takie same
        if (ui->lineEdit_md5file->text() == ui->lineEdit_md5compare->text()){
            ui->label_info->setText("OK! Its the same file.");
        }
        else {
            ui->label_info->setText("OPS! Its not the same file!");
        }
    }
}
