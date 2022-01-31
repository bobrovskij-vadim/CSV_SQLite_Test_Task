#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //-------text labels-------
    Ex_1_label = new QLabel("Exercise 1: ");
    Ex_1_A_task_label = new QLabel("A. Creating and filling CSV file");
    Ex_1_B_task_label = new QLabel("B. Reading and changing file ");
    Ex_1_C_task_label = new QLabel("C_1. Reading from csv, writing to db");
    Ex_1_changed_db_text = new QLabel("C.2. Changed data from sqlite");

    //-------Buttons-------
    Ex_1_A_button = new QPushButton("Create CSV file", this);
    Ex_1_B_button = new QPushButton("Read and change CSV", this);
    Ex_1_C_button = new QPushButton("Read CSV fill db", this);
    Ex_1_C_2_button = new QPushButton("Change sqlite file", this);

    //-------TableView-------
    Ex_1_fill_t_view = new QTableView;
    Ex_1_change_t_view = new QTableView;

    //-------Signals and slots-------
    connect(Ex_1_A_button, SIGNAL(clicked()), this,SLOT(on_Ex_1_A_button_clicked()));       //creating and filling csv file
    connect(Ex_1_B_button, SIGNAL(clicked()), this,SLOT(on_Ex_1_B_button_clicked()));       //reading and changing csv file
    connect(Ex_1_C_button, SIGNAL(clicked()), this,SLOT(on_Ex_1_C_button_clicked()));       //reading from csv file and writing to sqlite db then makes changes
    connect(Ex_1_C_2_button, SIGNAL(clicked()), this,SLOT(on_Ex_1_C_2_button_clicked()));   //deleting records at sqlite table, which starts with numbers

    //-------Layers-------
    Ex_1_layout = new QVBoxLayout;
    Ex_1_A_layout = new QHBoxLayout;
    Ex_1_B_layout = new QHBoxLayout;
    Ex_1_C_layout = new QHBoxLayout;
    Ex_1_C_2_layout = new QHBoxLayout;

    main_layout = new QVBoxLayout;

    //-------overlay to layers-------
    Ex_1_layout->addWidget(Ex_1_label);
    Ex_1_A_layout->addWidget(Ex_1_A_task_label);
    Ex_1_A_layout->addWidget(Ex_1_A_button);

    Ex_1_B_layout->addWidget(Ex_1_B_task_label);
    Ex_1_B_layout->addWidget(Ex_1_B_button);

    Ex_1_C_layout->addWidget(Ex_1_C_task_label);
    Ex_1_C_layout->addWidget(Ex_1_C_button);

    Ex_1_C_2_layout->addWidget(Ex_1_changed_db_text);
    Ex_1_C_2_layout->addWidget(Ex_1_C_2_button);

    main_layout->addLayout(Ex_1_layout);
    main_layout->addLayout(Ex_1_A_layout);
    main_layout->addLayout(Ex_1_B_layout);
    main_layout->addLayout(Ex_1_C_layout);
    main_layout->addWidget(Ex_1_fill_t_view);
    main_layout->addLayout(Ex_1_C_2_layout);
    main_layout->addWidget(Ex_1_change_t_view);

    QWidget *wgt = new QWidget(this);
    wgt->setLayout(main_layout);
    setCentralWidget(wgt);

    setLayout(main_layout);

}

MainWindow::~MainWindow()
{   }

void MainWindow::on_Ex_1_A_button_clicked()              //creating and filling csv file
{

    QFile data_file("data.csv");

    if (!data_file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::information(this, "Error", "file not open");
    }

    srand(time(NULL));
    int size_of_string = 8;
    QTextStream stream(&data_file);


    for(int i = 0; i < 1024; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            stream << random_string_generating(size_of_string) << ",";
        }
        stream << "\n";

    }
    data_file.close();
}

void MainWindow::on_Ex_1_B_button_clicked()
{
    //-------Opening the existing csv file-------
    QFile data_file("data.csv");
    if (!data_file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(this, "Error", "File not open!");
    }
    QTextStream stream(&data_file);


    //-------Creating a new csv file with changed data-------
    QFile changed_file("data_2.csv");
    if (!changed_file.open(QFile::WriteOnly))
    {
        QMessageBox::information(this, "Error", "file not open");
    }
    QTextStream stream_2(&changed_file);


    //-------Reading, changing and rewriting data-------
    while(!stream.atEnd())
    {
        QString str = stream.readLine();
        if(str_vowel_start(str))
        {
            change_odd_num(str);
            stream_2 << str << "\n";
        }
    }
    data_file.close();
    changed_file.close();
}

void MainWindow::on_Ex_1_C_button_clicked()                     //Ex_1.C Read the contents of the file from point A, create a sqlite database                                                                        // store all data in a table
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if (!db.open())
    {
        QMessageBox::information(this, "Error", "SQL file not open!");
    }
    QSqlQuery query;
    QString   str  = "CREATE TABLE sql_database ( "
                            "ID INTEGER PRIMARY KEY NOT NULL, "
                            "A  VARCHAR(10), "
                            "B  VARCHAR(10), "
                            "C  VARCHAR(10), "
                            "D  VARCHAR(10), "
                            "E  VARCHAR(10), "
                            "F  VARCHAR(10) "
                      ");";

     if (!query.exec(str)) {
           QMessageBox::information(this, "Error", "The table already exists!");
           qDebug() << "Unable to create a table";
     }

     //-------Opening and reading csv file-------
     QFile csv_file("data.csv");
     if (!csv_file.open(QIODevice::ReadOnly))
     {
         QMessageBox::information(this, "Error", "File not open!");
     }

     QTextStream stream(&csv_file);

     int count = 1;
     while(!stream.atEnd())
     {
          QString str_csv = stream.readLine();
          QVector <QString> arr = divide_str_to_vec(str_csv);

          QString strF =
                        "INSERT INTO  sql_database (ID, A, B, C, D, E, F) "
                        "VALUES(%1, '%2', '%3', '%4', '%5', '%6', '%7');";

                        str = strF.arg(count)
                                  .arg(arr[0])
                                  .arg(arr[1])
                                  .arg(arr[2])
                                  .arg(arr[3])
                                  .arg(arr[4])
                                  .arg(arr[5]);
                         if (!query.exec(str))
                         {
                             QMessageBox::information(this, "Error", "This data has already inserted!");
                             qDebug() << "Unable to do insert opeation";
                             break;
                         }
           count++;
      }

      model_1 = new QSqlTableModel(this, db);
      model_1->setTable("sql_database");
      model_1->select();

      Ex_1_fill_t_view->setModel(model_1);

      csv_file.close();
      db.close();
}


void MainWindow::on_Ex_1_C_2_button_clicked()
{
//    //-------Ex_1.C Part 2. Delete records from second colom, which starts with number-------
     QFile::copy("database.db", "changed_db.db");

     QSqlDatabase db_2 = QSqlDatabase::addDatabase("QSQLITE");
     db_2.setDatabaseName("changed_db.db");
     if (!db_2.open())
     {
         QMessageBox::information(this, "Error", "SQL file not open!");
     }

     QSqlQuery q;
     QString str_d = ("DELETE FROM sql_database WHERE B LIKE '0%'"
                                                  "OR B LIKE '1%'"
                                                  "OR B LIKE '2%'"
                                                  "OR B LIKE '3%'"
                                                  "OR B LIKE '4%'"
                                                  "OR B LIKE '5%'"
                                                  "OR B LIKE '6%'"
                                                  "OR B LIKE '7%'"
                                                  "OR B LIKE '8%'"
                                                  "OR B LIKE '9%'");
     q.exec(str_d);

     model_2 = new QSqlTableModel(this, db_2);
     model_2->setTable("sql_database");
     model_2->select();

     Ex_1_change_t_view->setModel(model_2);

     db_2.close();
}
