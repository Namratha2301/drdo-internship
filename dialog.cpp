#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
}

Dialog::~Dialog() {
    delete ui;
}

void Dialog::on_pushButton_clicked() {
    QString x_coordinate = ui->plainTextEdit->toPlainText();
    QString y_coordinate = ui->plainTextEdit_2->toPlainText();
    MainWindow window;
    window.on_Change_Position(x_coordinate.toInt(), y_coordinate.toInt());
}

void Dialog::on_pushButton_2_clicked() {
    QString range = ui->plainTextEdit_3->toPlainText();
    QString elevation = ui->plainTextEdit_4->toPlainText();
    MainWindow window;
    window.add_Weapon(range.toDouble(), elevation.toDouble());
}
