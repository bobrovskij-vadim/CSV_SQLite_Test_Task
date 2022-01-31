#include "functions.h"

QString random_string_generating(int size)            //Exercise 1A generate string to fill csv file
{

    QString rand_string;
    for (int i = 0; i < size; ++i)
    {
       int range = rand() % 3;
       int symbol;
       if(range == 0)
       {
           symbol = (48 + rand() % (57 - 48 + 1));     //generate char from 0 - 9
       }
       else if (range == 1)
       {
           symbol = (65 + rand() % (90 - 65 + 1));     //generate char from A - Z
       }
       else
       {
           symbol = (97 + rand() % (122 - 97 + 1));    //generate char from a - z
       }
       rand_string.append(char(symbol));
    }
    return rand_string;
}

bool str_vowel_start(QString str)                      //Exercise 1B Delete strings which starts with a vowel
{
    QString vowels = "AEIOUYaeiouy";
    for(int i = 0; i < str.size(); i+=9)
    {
        for (int j = 0; j < vowels.size(); ++j)
        {
            if (str[i] == vowels[j])
            {
                return false;
            }
        }
    }
    return true;
}

void change_odd_num(QString &str)                      //Exercise 1B Changing odd number to #
{
     for(int i = 0; i < str.size(); ++i)
     {
         if(str[i].digitValue() % 2 == 1)
         {
             str[i] = '#';
         }
     }
}

QVector <QString> divide_str_to_vec(QString &str)      //The function gets string from csv file and makes vector array
{
    QVector <QString> arr;

    QString little_str;
    for (int i = 0; i < str.size(); ++i)
    {
        if(str[i] == ',')
        {
             arr.push_back(little_str);
             little_str = "";
             continue;
        }
        little_str += str[i];
    }

    return arr;
}
