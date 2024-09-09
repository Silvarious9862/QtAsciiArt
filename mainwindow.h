#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ButtonExplore_clicked();

    void on_ButtonExit_clicked();



    void on_Path_textChanged(const QString &arg1);

    void on_SymbolsArray_textChanged(const QString &arg1);

    void on_ButtonGenerate_clicked();


    void on_ButtonCopy_clicked();

    void on_zoomOut_clicked();

    void on_zoomIn_clicked();

    void on_plainTextEdit_textChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
