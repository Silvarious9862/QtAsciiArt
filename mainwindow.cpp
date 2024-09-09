#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QDialog>
#include <QString>
#include <QScrollBar>
#include <QClipboard>
#include "AsciiArt.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Path->setReadOnly(true);
    ui->ButtonGenerate->setEnabled(false);
    ui->SymbolsArray->setEnabled(false);
    ui->Quality->setEnabled(false);
    ui->ButtonExplore->setFocus();
    ui->plainTextEdit->setPlaceholderText("Здесь будет ваш ASCII-Art");
    ui->plainTextEdit->setReadOnly(true);
    ui->zoomIn->setEnabled(false);
    ui->zoomOut->setEnabled(false);
    ui->zoomValue->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ButtonExplore_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open image"), "/", tr("Image file (*.bmp)"));
    qDebug() << "filename is: " << filename;
    ui->Path->setText(filename);
}


void MainWindow::on_ButtonExit_clicked()
{
    QApplication::quit();
}


void MainWindow::on_Path_textChanged(const QString &arg1)
{
    if(!ui->Path->text().isEmpty()) {
        ui->Quality->setEnabled(true);
        ui->SymbolsArray->setEnabled(true);
    }
    else {
         ui->SymbolsArray->setEnabled(false);
         ui->Quality->setEnabled(false);
    }
    if( !ui->Path->text().isEmpty() && !ui->SymbolsArray->text().isEmpty())
        ui->ButtonGenerate->setEnabled(true);
    else ui->ButtonGenerate->setEnabled(false);
}


void MainWindow::on_SymbolsArray_textChanged(const QString &arg1)
{
    if( !ui->Path->text().isEmpty() && !ui->SymbolsArray->text().isEmpty())
        ui->ButtonGenerate->setEnabled(true);
    else ui->ButtonGenerate->setEnabled(false);
}


void MainWindow::on_ButtonGenerate_clicked()
{

    std::string result (MakeAsciiArt((ui->Path->text()).toStdString(), ui->Quality->value(), (ui->SymbolsArray->text()).toStdString()));
    if(result == "") {
        QMessageBox::critical(this, "Ошибка", "Преобразование данного изображения недоступно.\nВозможные причины:"
                                              "\n- Файл изображения поврежден или недоступен\n- Разрядность картинки не равна 24 бит");
        return;
    }
    time_t sec;
    sec = time(NULL);
    qDebug() << "Art Done! " << std::asctime(std::localtime(&sec));

    QString qstr = QString::fromStdString(result);
    QFont newfont("Consolas", 2);
    ui->plainTextEdit->setFont(newfont);
    ui->plainTextEdit->setPlainText(qstr);
    ui->plainTextEdit->setFocus();


    ui->zoomValue->setText("10%");
    ui->zoomValue->setEnabled(true);
    ui->zoomIn->setEnabled(true);
    ui->zoomOut->setEnabled(true);
}


void MainWindow::on_ButtonCopy_clicked()
{
    ui->plainTextEdit->selectAll();
    ui->plainTextEdit->copy();
}


void MainWindow::on_zoomOut_clicked()
{
    QFontInfo fontinfo = ui->plainTextEdit->fontInfo();
    if(fontinfo.pointSize()>1){
        ui->plainTextEdit->zoomOut();
        QString zoomValueStr = ui->zoomValue->text();
        zoomValueStr.resize(zoomValueStr.size()-1);
        int zoomValue = zoomValueStr.toInt();
        zoomValue-=10;
        zoomValueStr = zoomValueStr.fromStdString(std::to_string(zoomValue)+"%");
        ui->zoomValue->setText(zoomValueStr);
        if(zoomValue == 0)
            ui->zoomOut->setEnabled(false);
        if(zoomValue < 200) ui->zoomIn->setEnabled(true);
    }

}


void MainWindow::on_zoomIn_clicked()
{

    QFontInfo fontinfo = ui->plainTextEdit->fontInfo();
    if(fontinfo.pointSize()<21){
        ui->plainTextEdit->zoomIn();
        QString zoomValueStr = ui->zoomValue->text();
        zoomValueStr.resize(zoomValueStr.size()-1);
        int zoomValue = zoomValueStr.toInt();
        zoomValue+=10;
        zoomValueStr = zoomValueStr.fromStdString(std::to_string(zoomValue)+"%");
        ui->zoomValue->setText(zoomValueStr);
        if(zoomValue > 0 ) ui->zoomOut->setEnabled(true);
        if(zoomValue == 200) ui->zoomIn->setEnabled(false);
    }
}


void MainWindow::on_plainTextEdit_textChanged()
{

}

