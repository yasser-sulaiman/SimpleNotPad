#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // remove the spaces from the right and left sides of the text box
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    filePath = "";
    ui->textEdit->clear();
    //ui->textEdit->setText("");
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "select a file");
    QFile file(fileName);
    filePath = fileName;
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "File Not Opende", "The File Did Not Open Properly");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    if (filePath==""){
       on_actionSave_as_triggered();
   }
   else{
       QFile file(filePath);
       if(!file.open(QFile::WriteOnly | QFile::Text)){
           QMessageBox::warning(this, "File Not Opende", "The File Did Not Open Properly");
           return;
       }
       QTextStream out(&file);
       QString text = ui->textEdit->toPlainText();
       out << text;
       file.flush();
       file.close();
   }
}


void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save As");
    QFile file(fileName);
    filePath = fileName;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "File Not Opende", "The File Did Not Open Properly");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionAbout_triggered()
{
    QString aboutMessage= "This GUI is only for learning purposes\
                          \n it was written using Qt creator and C++ language";
    QMessageBox::about(this, "About", aboutMessage);
}


void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok){
        ui->textEdit->setFont(font);
    }else return;
}


void MainWindow::on_actionColor_triggered()
{

    QColor color = QColorDialog::getColor(Qt::black, this, "Choose a Color");
    if(color.isValid()){
        ui->textEdit->setTextColor(color);
    }
}


void MainWindow::on_actionBackground_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Choose a Color");
    if(color.isValid()){
        ui->textEdit->setPalette(QPalette(color));
    }
}




void MainWindow::on_actionHighlighte_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Choose a Color");
    if(color.isValid()){
        ui->textEdit->setTextBackgroundColor(color);
    }
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("My Printer");
    QPrintDialog dialog(&printer, this);
    if(dialog.exec() == QDialog::Rejected) return;
    ui->textEdit->print(&printer);


}

