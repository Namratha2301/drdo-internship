#ifndef MAINWINDOW_H 
#define MAINWINDOW_H

#include <QMainWindow> 
#include "dialog.h"

QT_BEGIN_NAMESPACE 
namespace Ui { 
    class MainWindow; 
} 
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    
    public:
        MainWindow(QWidget *parent = nullptr); 
        ~MainWindow();

        void on_Change_Position(int x_position, int y_position); 
        void add_Weapon(qreal range, qreal elevation);

    public slots:
        void on_pushButton_clicked();
        void makePlot(QStringList);
        void on_comboBox_activated(int weapon_Choice);
        void on_pushButton_2_clicked();
        void on_pushButton_3_clicked();

    private:
        Ui::MainWindow *ui; 
        Dialog *example;
};

#endif // MAINWINDOW_H
