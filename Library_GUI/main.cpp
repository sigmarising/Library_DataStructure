#include "dmain1.h"
#include "dmain2.h"
#include "dmainc.h"
#include "dcolor.h"
#include "dlogin.h"
#include "dadmin.h"
#include "dadmin_nbook1.h"
#include "dadmin_nbook2.h"
#include "dadmin_nperson.h"
#include "dadmin_fbook.h"
#include "dadmin_fbook2.h"
#include "dadmin_fperson1.h"
#include "dadmin_fperson2.h"
#include "duser.h"
#include "duser_borrow.h"
#include "duser_return.h"
#include "duser_convert.h"
#include "duser_key.h"
#include "function.h"
#include "books.h"
#include "logbook.h"
#include "people.h"
#include "dadmin_key.h"
#include <QApplication>
#include <string>
#include <QString>
#include <QFile>
#include <fstream>
#include <QTime>

long Day = 1;
long Num_book0 = 0;
long Num_book1 = 0;
long Num_book2 = 0;
bool Manual_Time = true;
bool SysRun = true;
int uiset = 1;
string BName,BAuthor,BPubli,UserNow;
QTime Time_Start;
DMain1 *w1_1 = NULL;

int main(int argc, char *argv[])
{  
    /*init the file*/
    string init = FileLine_Getline("logbook\\sys.txt", 1);
    if (init == "") {
        system("md logbook");
        system("md book");
        system("md people");

        fstream f("logbook\\sys.txt",fstream::out);

        f << 1 << endl;
        f << "Admin" << endl;
        f << 0 << endl;
        f << 0 << endl;
        f << 0 << endl;
        f << 1 << endl;
        f << 1<< endl;

        f.close();

        f.open("book\\booklist.txt", fstream::out);
        f << 0 << endl;
        f.close();

        f.open("people\\peoplelist.txt", fstream::out);
        f << 0 << endl;
        f.close();

        f.open("logbook\\temp.txt", fstream::out);
        f << 0 << endl;
        f.close();

        //log first day
        Logs L(Day, true);

    }
    else {
        // new day log
        Day =1 + Convert_strtolong(FileLine_Getline("logbook\\sys.txt", 6));
        Logs L(Day, true);
        FileLine_Change("logbook\\sys.txt", 6, Convert_longtostr(Day));

        FlashDay();
    }

    Q_INIT_RESOURCE(resource);

    QApplication a(argc, argv);

    int theme = int(Convert_strtolong(FileLine_Getline("logbook\\sys.txt", 7)));
    if (1 == theme){
    // load qss
        QString qss;
        QFile qssFile(":/qss/ThemeBlue.qss");
        qssFile.open(QIODevice::ReadOnly);
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
        // load qss - ok
    }
    else if (2 == theme){
        QString qss;
        QFile qssFile(":/qss/ThemeGreen.qss");
        qssFile.open(QIODevice::ReadOnly);
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }
    else{
        QString qss;
        QFile qssFile(":/qss/ThemePink.qss");
        qssFile.open(QIODevice::ReadOnly);
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }


    DMain2 *w1_2= NULL;
    DMainC *w2= NULL;
    DColor *w3= NULL;
    DLogin *w4= NULL;
    DAdmin *w5= NULL;
    DAdmin_NBook1 *w6= NULL;
    DAdmin_NBook2 *w7= NULL;
    DAdmin_NPerson *w8= NULL;
    DAdmin_FBook*w9= NULL;
    DAdmin_FPerson1 *w10= NULL;
    DAdmin_FPerson2 *w11= NULL;
    DUser *w12= NULL;
    DUser_Borrow *w13= NULL;
    DUser_Return *w14= NULL;
    DUser_Convert *w15= NULL;
    DUser_Key *w16= NULL;
    DAdmin_FBook2 *w17 = NULL;
    DAdmin_Key *w18 =NULL;

    while (SysRun){
        switch (uiset) {
        case 1:
            if (!Manual_Time){
                w1_1 = new DMain1;
                w1_1 ->exec();
                delete w1_1;
            }
            else{
                w1_2 = new DMain2;
                w1_2 ->exec();
                delete w1_2;
            }
            break;
        case 2:
            w2 = new DMainC;
            w2 ->exec();
            delete w2;

            break;
        case 3:
            w3 = new DColor;
            w3 ->exec();
            delete w3;

            break;
        case 4:
            w4 = new DLogin;
            w4 ->exec();
            delete w4;
            break;
        case 5:
            w5 = new DAdmin;
            w5 ->exec();
            delete w5;
            break;
        case 6:
            w6 = new DAdmin_NBook1;
            w6 ->exec();
            delete w6;
            break;
        case 7:
            w7 = new DAdmin_NBook2;
            w7 ->exec();
            delete w7;
            break;
        case 8:
            w8 = new DAdmin_NPerson;
            w8 ->exec();
            delete w8;
            break;
        case 9:
            w9 = new DAdmin_FBook;
            w9 ->exec();
            delete w9;
            break;
        case 10:
            w10 = new DAdmin_FPerson1;
            w10 ->exec();
            delete w10;
            break;
        case 11:
            w11 = new DAdmin_FPerson2;
            w11 ->exec();
            delete w11;
            break;
        case 12:
            w12 = new DUser;
            w12 ->exec();
            delete w12;
            break;
        case 13:
            w13 = new DUser_Borrow;
            w13 ->exec();
            delete w13;
            break;
        case 14:
            w14 = new DUser_Return;
            w14 ->exec();
            delete w14;
            break;
        case 15:
            w15 = new DUser_Convert;
            w15 ->exec();
            delete w15;
            break;
        case 16:
            w16 = new DUser_Key;
            w16 ->exec();
            delete w16;
            break;
        case 17:
            w17 = new DAdmin_FBook2;
            w17 ->exec();
            delete w17;
            break;
        case 18:
            w18 = new DAdmin_Key;
            w18->exec();
            delete w18;
            break;
        }
    }

    qApp->quit();
    return 0;
}
