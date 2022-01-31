#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(770, 450);
    w.setWindowIcon(QIcon("SQLITE_logo.png"));
    w.show();

    return a.exec();
}


// Test
// Make in C++ Qt:

// 1. Databases
// A. Generate a csv file of 1024 records in 6 columns filled with strings random characters (numbers and Latin letters) 8 characters long.
// B. Read file content, replace odd digits with #, delete records where any of the six lines begin with a vowel, keep edited file with a different name.
// C. Read the contents of the file from point A, create a sqlite database programmatically, store all data in a table. Using sql, delete records in which the first character in the second column is a digit.

// 2. Compile the application from the previous task for Raspberry Pi.

// *All moments that you do not understand and ambiguous wording in the TEST - you can do at your discretion.
