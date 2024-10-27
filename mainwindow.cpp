#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QList>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QtSql>
#include <QLineSeries>
#include <QChartView>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int weapon_Choice = ui->comboBox->currentIndex();
    on_comboBox_activated(weapon_Choice);

    // Connecting signals and slots
    connect(this, SIGNAL(showGraph(QStringList)), this, SLOT(makePlot(QStringList)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QStringList inputList;
    QString inputString;
    QFile file(ui->plainTextEdit->toPlainText());
    
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "title", "File not open");
        return;
    }

    QTextStream in(&file);
    while (!file.atEnd()) {
        inputString = QString(file.readLine());
        ui->plainTextEdit_2->appendPlainText(inputString);
        inputList << inputString.split("\t");
        inputList.removeAll("\n");

        QFuture<void> t2 = QtConcurrent::run(this, &MainWindow::showWarning, inputList);
        QFuture<void> t3 = QtConcurrent::run(this, &MainWindow::showGraph, inputList);
    }
    file.close();
}

void MainWindow::onShowWarning(QStringList inputList)
{
    if (inputList.size() > 7) {
        for (int count = 4; count <= inputList.size() - 8; count += 4) {
            if (inputList[count].toInt() <= 50) {
                QMessageBox::warning(this, "title", "Track_id: " + QString(inputList[count + 3]) +
                    " X: " + QString(inputList[count]) + " Y: " + QString(inputList[count + 1]) + 
                    " Z: " + QString(inputList[count + 2]) + "\n");
            }
        }
    }
}

void MainWindow::makePlot(QStringList inputList)
{
    QVector<double> x(101), y(101);
    int index = 0;

    if (inputList.size() > 7) {
        for (int count = 4; count <= inputList.size() - 4; count += 4) {
            x[index] = inputList[count].toDouble();
            y[index] = inputList[count + 1].toDouble();
            index++;
        }
    }

    ui->customPlot->addGraph();
    ui->customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(3)->setData(x, y);

    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    ui->customPlot->xAxis->setRange(-50, 150);
    ui->customPlot->replot();
}

void MainWindow::on_comboBox_activated(int weapon_Choice)
{
    int weapon_Chosen = weapon_Choice + 1;
    qDebug() << weapon_Chosen;

    QString server_Name = "LOCALHOST\\SQLEXPRESS";
    QString database_Name = "DRDO";
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    QString dsn = QString("DRIVER={SQL Native Client};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;")
                      .arg(server_Name)
                      .arg(database_Name);
    db.setDatabaseName(dsn);

    if (db.open()) {
        QSqlQuery query;
        query.prepare("SELECT [Weapon_ID],[Range],[Azimuth],[Elevation] FROM [dbo].[Weapons] WHERE Weapon_ID = :weapon_Chosen");
        query.bindValue(":weapon_Chosen", weapon_Chosen);
        
        if (query.exec()) {
            query.first();
            qreal range = query.value(1).toReal();
            qreal elevation = query.value(2).toReal();
            qDebug() << elevation;
            circleFunction(range, -elevation, elevation, 50, 75);
        } else {
            qDebug() << "error==" << db.lastError().text();
        }
        db.close();
    } else {
        qDebug() << "error=" << db.lastError().text();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    example = new Dialog(this);
    example->show();
}

void MainWindow::circleFunction(qreal range, qreal minimum_angle, qreal maximum_angle, int x_position, int y_position)
{
    QPen pen;
    pen.setColor(QColor(123, 112, 145));
    QVector<double> x, y, x_line, y_line, x_line2, y_line2;

    x_line.push_back(0);
    y_line.push_back(0);
    x_line2.push_back(0);
    y_line2.push_back(0);

    for (int i = minimum_angle; i <= maximum_angle; i++) {
        double theta = qDegreesToRadians(double(i));
        double temp_x = range * qCos(theta);
        double temp_y = range * qSin(theta);
        x.push_back(temp_x);
        y.push_back(temp_y);

        if (i == minimum_angle) {
            x_line.push_back(temp_x);
            y_line.push_back(temp_y);
        }

        if (i == maximum_angle) {
            x_line2.push_back(temp_x);
            y_line2.push_back(temp_y);
        }
    }

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    ui->customPlot->xAxis->setRange(-x_position, 150);
    ui->customPlot->yAxis->setRange(-y_position, 150);
    ui->customPlot->replot();

    ui->customPlot->graph(0)->setPen(pen);
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(123, 112, 145, 59)));
    ui->customPlot->replot();

    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setData(x_line, y_line);
    ui->customPlot->graph(1)->setPen(pen);
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->replot();

    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setData(x_line2, y_line2);
    ui->customPlot->graph(2)->setPen(pen);
    ui->customPlot->graph(2)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->replot();
}

void MainWindow::on_Change_Position(int x_position, int y_position)
{
    int weapon_choice = ui->comboBox->currentIndex() + 1;
    QString server_Name = "LOCALHOST\\SQLEXPRESS";
    QString database_Name = "DRDO";
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    QString dsn = QString("DRIVER={SQL Native Client};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;")
                      .arg(server_Name)
                      .arg(database_Name);
    db.setDatabaseName(dsn);

    if (db.open()) {
        QSqlQuery query;
        query.prepare("SELECT [Weapon_ID],[Range],[Azimuth],[Elevation] FROM [dbo].[Weapons] WHERE Weapon_ID = :weapon_Chosen");
        query.bindValue(":weapon_Chosen", weapon_choice);

        if (query.exec()) {
            query.first();
            qreal range = query.value(1).toReal();
            qreal elevation = query.value(2).toReal();

            ui->customPlot->addGraph();
            ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
            ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);

            circleFunction(range, -elevation, elevation, x_position, y_position);
        } else {
            qDebug() << "error==" << db.lastError().text();
        }
        db.close();
    } else {
        qDebug() << "error=" << db.lastError().text();
    }
}

void MainWindow::add_Weapon(double range, double elevation)
{
    QString server_Name = "LOCALHOST\\SQLEXPRESS";
    QString database_Name = "DRDO";
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    QString dsn = QString("DRIVER={SQL Native Client};SERVER=%1;DATABASE=%
