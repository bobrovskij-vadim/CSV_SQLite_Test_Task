#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <ctime>
#include <QTableView>
#include <QSqlTableModel>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QtDebug>
#include <QFileInfo>
#include <QVector>
#include "functions.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //-------Layers-------
    QVBoxLayout *Ex_1_layout;
    QHBoxLayout *Ex_1_A_layout;
    QHBoxLayout *Ex_1_B_layout;
    QHBoxLayout *Ex_1_C_layout;
    QHBoxLayout *Ex_1_C_2_layout;

    QVBoxLayout *main_layout;

    //-------Labels-------
    QLabel *Ex_1_label;
    QLabel *Ex_1_A_task_label;
    QLabel *Ex_1_B_task_label;
    QLabel *Ex_1_C_task_label;
    QLabel *Ex_1_changed_db_text;

    //-------Buttons-------
    QPushButton *Ex_1_A_button;
    QPushButton *Ex_1_B_button;
    QPushButton *Ex_1_C_button;
    QPushButton *Ex_1_C_2_button;

    //-------TableView-------
    QTableView *Ex_1_fill_t_view;
    QTableView *Ex_1_change_t_view;
    //-------SQLTableModel-------
    QSqlTableModel *model_1;
    QSqlTableModel *model_2;


private slots:
    void on_Ex_1_A_button_clicked();      //creating and filling csv file
    void on_Ex_1_B_button_clicked();      //reading and changing csv file
    void on_Ex_1_C_button_clicked();      //reading from csv file and writing to sqlite db then makes changes
    void on_Ex_1_C_2_button_clicked();    //deleting records at sqlite table, which starts with numbers
};


#endif // MAINWINDOW_H
