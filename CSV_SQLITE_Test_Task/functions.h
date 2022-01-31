#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include <QVector>


QString random_string_generating(int size);          //the function generates a ramdom string to fill csv file

bool str_vowel_start(QString str);                   //the function checks the record, if the string inside starts with a vowel, return false

void change_odd_num(QString &str);                   //the function reads the record and if the string inside the record has odd numbers change it to #

QVector <QString> divide_str_to_vec(QString &str);  //The function gets string from csv file and makes vector array

#endif // FUNCTIONS_H
