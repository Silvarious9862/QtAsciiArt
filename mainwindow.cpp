#define _CRT_SECURE_NO_WARNINGS
#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QDialog>
#include <QString>
#include <QScrollBar>
#include <QClipboard>
#include <QSaveFile>
#include "AsciiArt.h"
#include "mystack.h"

struct Params{
    QString path;
    int quality;
    QString symbols;
};


my::Stack<Params> StackUndo;
my::Stack<Params> StackRedo;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Path->setReadOnly(true);
    ui->ButtonExplore->setFocus();
    ui->plainTextEdit->setPlaceholderText("Здесь будет ваш ASCII-Art");
    ui->plainTextEdit->setReadOnly(true);

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
        ui->ButtonClearSymbols->setEnabled(true);
        ui->ButtonResetSymbols->setEnabled(true);
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
    // --- before generating we save state of config in Undo stack
    Params state;
    state.path = ui->Path->text();
    state.quality = ui->Quality->value();
    state.symbols = ui->SymbolsArray->text();
    StackUndo.push(state);
    ui->ButtonUndo->setEnabled(true);
    StackRedo.clear();
    ui->ButtonRedo->setEnabled(false);


    // exec converter
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
}


void MainWindow::on_ButtonCopy_clicked()
{
    ui->plainTextEdit->selectAll();
    ui->plainTextEdit->copy();
    ui->plainTextEdit->textCursor().clearSelection();

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
    if(ui->plainTextEdit->toPlainText() != "") {

        ui->ButtonCopy->setEnabled(true);
        ui->ButtonSave->setEnabled(true);
        ui->zoomIn->setEnabled(true);
        ui->zoomOut->setEnabled(true);
        ui->zoomValue->setEnabled(true);
    }
    else {
        ui->ButtonCopy->setEnabled(false);
        ui->ButtonSave->setEnabled(false);
        ui->zoomIn->setEnabled(false);
        ui->zoomOut->setEnabled(false);
        ui->zoomValue->setEnabled(false);
    }
}


void MainWindow::on_ButtonClearSymbols_clicked()
{
    ui->SymbolsArray->setText("");
}


void MainWindow::on_ButtonResetSymbols_clicked()
{
    ui->SymbolsArray->setText(" `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@");
}


void MainWindow::on_ButtonUndo_clicked()
{
    StackRedo.push(StackUndo.top());
    StackUndo.pop();

    if(StackUndo.empty()) {
        ui->Path->setText("");
        ui->Quality->setValue(1);
        ui->SymbolsArray->setText("");
    }
    else {
        ui->Path->setText(StackUndo.top().path);
        ui->Quality->setValue(StackUndo.top().quality);
        ui->SymbolsArray->setText(StackUndo.top().symbols);
    }

    if(StackUndo.empty()) ui->ButtonUndo->setEnabled(false);
    ui->ButtonRedo->setEnabled(true);
}


void MainWindow::on_ButtonRedo_clicked()
{
    StackUndo.push(StackRedo.top());

    if(StackRedo.empty()) {
        ui->Path->setText("");
        ui->Quality->setValue(1);
        ui->SymbolsArray->setText("");
    }
    else {
        ui->Path->setText(StackRedo.top().path);
        ui->Quality->setValue(StackRedo.top().quality);
        ui->SymbolsArray->setText(StackRedo.top().symbols);
    }

    StackRedo.pop();
    if(StackRedo.empty()) ui->ButtonRedo->setEnabled(false);
    ui->ButtonUndo->setEnabled(true);
}


void MainWindow::on_ButtonSave_clicked()
{
    QSaveFile file(QFileDialog::getSaveFileName(this, tr("Save as .txt"), "/", tr("Text file (*.txt)")));
    file.setTextModeEnabled(true);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(ui->plainTextEdit->toPlainText().toStdString().c_str());
    file.commit();
}

