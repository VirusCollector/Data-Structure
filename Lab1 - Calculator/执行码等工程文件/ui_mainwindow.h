/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *output;
    QTextEdit *input;
    QLabel *label;
    QPushButton *Zero;
    QPushButton *Point;
    QPushButton *Equal;
    QPushButton *Plus;
    QPushButton *One;
    QPushButton *Two;
    QPushButton *Three;
    QPushButton *Sub;
    QPushButton *Four;
    QPushButton *Five;
    QPushButton *Six;
    QPushButton *Mul;
    QPushButton *Seven;
    QPushButton *Eight;
    QPushButton *Nine;
    QPushButton *Div;
    QPushButton *LeftBra;
    QPushButton *RightBra;
    QPushButton *Percent;
    QPushButton *Back;
    QPushButton *Clear;
    QPushButton *Sin;
    QPushButton *Cos;
    QPushButton *Tan;
    QPushButton *const_E;
    QPushButton *Ln;
    QPushButton *Log;
    QPushButton *const_Pai;
    QPushButton *Root;
    QPushButton *Index;
    QPushButton *Semicolon;
    QPushButton *Factorial;
    QPushButton *Square;
    QTextEdit *Cmd;
    QPushButton *CmdRun;
    QPushButton *runpol;
    QPushButton *runmat;
    QTextEdit *cmdlog;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(810, 793);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        output = new QTextEdit(centralwidget);
        output->setObjectName(QString::fromUtf8("output"));
        output->setGeometry(QRect(90, 60, 581, 31));
        QFont font;
        font.setPointSize(12);
        output->setFont(font);
        output->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);"));
        input = new QTextEdit(centralwidget);
        input->setObjectName(QString::fromUtf8("input"));
        input->setGeometry(QRect(20, 10, 651, 41));
        input->setFont(font);
        input->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 127);"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 60, 61, 31));
        QFont font1;
        font1.setPointSize(16);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        Zero = new QPushButton(centralwidget);
        Zero->setObjectName(QString::fromUtf8("Zero"));
        Zero->setGeometry(QRect(20, 470, 51, 41));
        Zero->setFont(font);
        Point = new QPushButton(centralwidget);
        Point->setObjectName(QString::fromUtf8("Point"));
        Point->setGeometry(QRect(90, 470, 51, 41));
        Point->setFont(font);
        Equal = new QPushButton(centralwidget);
        Equal->setObjectName(QString::fromUtf8("Equal"));
        Equal->setGeometry(QRect(160, 470, 51, 41));
        Equal->setFont(font);
        Plus = new QPushButton(centralwidget);
        Plus->setObjectName(QString::fromUtf8("Plus"));
        Plus->setGeometry(QRect(230, 470, 51, 41));
        Plus->setFont(font);
        One = new QPushButton(centralwidget);
        One->setObjectName(QString::fromUtf8("One"));
        One->setGeometry(QRect(20, 400, 51, 41));
        One->setFont(font);
        Two = new QPushButton(centralwidget);
        Two->setObjectName(QString::fromUtf8("Two"));
        Two->setGeometry(QRect(90, 400, 51, 41));
        Two->setFont(font);
        Three = new QPushButton(centralwidget);
        Three->setObjectName(QString::fromUtf8("Three"));
        Three->setGeometry(QRect(160, 400, 51, 41));
        Three->setFont(font);
        Sub = new QPushButton(centralwidget);
        Sub->setObjectName(QString::fromUtf8("Sub"));
        Sub->setGeometry(QRect(230, 400, 51, 41));
        Sub->setFont(font);
        Four = new QPushButton(centralwidget);
        Four->setObjectName(QString::fromUtf8("Four"));
        Four->setGeometry(QRect(20, 330, 51, 41));
        Four->setFont(font);
        Five = new QPushButton(centralwidget);
        Five->setObjectName(QString::fromUtf8("Five"));
        Five->setGeometry(QRect(90, 330, 51, 41));
        Five->setFont(font);
        Six = new QPushButton(centralwidget);
        Six->setObjectName(QString::fromUtf8("Six"));
        Six->setGeometry(QRect(160, 330, 51, 41));
        Six->setFont(font);
        Mul = new QPushButton(centralwidget);
        Mul->setObjectName(QString::fromUtf8("Mul"));
        Mul->setGeometry(QRect(230, 330, 51, 41));
        Mul->setFont(font);
        Seven = new QPushButton(centralwidget);
        Seven->setObjectName(QString::fromUtf8("Seven"));
        Seven->setGeometry(QRect(20, 260, 51, 41));
        Seven->setFont(font);
        Eight = new QPushButton(centralwidget);
        Eight->setObjectName(QString::fromUtf8("Eight"));
        Eight->setGeometry(QRect(90, 260, 51, 41));
        Eight->setFont(font);
        Nine = new QPushButton(centralwidget);
        Nine->setObjectName(QString::fromUtf8("Nine"));
        Nine->setGeometry(QRect(160, 260, 51, 41));
        Nine->setFont(font);
        Div = new QPushButton(centralwidget);
        Div->setObjectName(QString::fromUtf8("Div"));
        Div->setGeometry(QRect(230, 260, 51, 41));
        Div->setFont(font);
        LeftBra = new QPushButton(centralwidget);
        LeftBra->setObjectName(QString::fromUtf8("LeftBra"));
        LeftBra->setGeometry(QRect(20, 190, 51, 41));
        LeftBra->setFont(font);
        RightBra = new QPushButton(centralwidget);
        RightBra->setObjectName(QString::fromUtf8("RightBra"));
        RightBra->setGeometry(QRect(90, 190, 51, 41));
        RightBra->setFont(font);
        Percent = new QPushButton(centralwidget);
        Percent->setObjectName(QString::fromUtf8("Percent"));
        Percent->setGeometry(QRect(160, 190, 51, 41));
        Percent->setFont(font);
        Back = new QPushButton(centralwidget);
        Back->setObjectName(QString::fromUtf8("Back"));
        Back->setGeometry(QRect(230, 190, 51, 41));
        Back->setFont(font);
        Clear = new QPushButton(centralwidget);
        Clear->setObjectName(QString::fromUtf8("Clear"));
        Clear->setGeometry(QRect(20, 120, 261, 61));
        Clear->setFont(font1);
        Sin = new QPushButton(centralwidget);
        Sin->setObjectName(QString::fromUtf8("Sin"));
        Sin->setGeometry(QRect(400, 470, 51, 41));
        Sin->setFont(font);
        Cos = new QPushButton(centralwidget);
        Cos->setObjectName(QString::fromUtf8("Cos"));
        Cos->setGeometry(QRect(490, 470, 51, 41));
        Cos->setFont(font);
        Tan = new QPushButton(centralwidget);
        Tan->setObjectName(QString::fromUtf8("Tan"));
        Tan->setGeometry(QRect(580, 470, 51, 41));
        Tan->setFont(font);
        const_E = new QPushButton(centralwidget);
        const_E->setObjectName(QString::fromUtf8("const_E"));
        const_E->setGeometry(QRect(400, 400, 51, 41));
        const_E->setFont(font);
        Ln = new QPushButton(centralwidget);
        Ln->setObjectName(QString::fromUtf8("Ln"));
        Ln->setGeometry(QRect(490, 400, 51, 41));
        Ln->setFont(font);
        Log = new QPushButton(centralwidget);
        Log->setObjectName(QString::fromUtf8("Log"));
        Log->setGeometry(QRect(580, 400, 51, 41));
        Log->setFont(font);
        const_Pai = new QPushButton(centralwidget);
        const_Pai->setObjectName(QString::fromUtf8("const_Pai"));
        const_Pai->setGeometry(QRect(400, 330, 51, 41));
        const_Pai->setFont(font);
        Root = new QPushButton(centralwidget);
        Root->setObjectName(QString::fromUtf8("Root"));
        Root->setGeometry(QRect(490, 330, 51, 41));
        Root->setFont(font);
        Index = new QPushButton(centralwidget);
        Index->setObjectName(QString::fromUtf8("Index"));
        Index->setGeometry(QRect(580, 330, 51, 41));
        Index->setFont(font);
        Semicolon = new QPushButton(centralwidget);
        Semicolon->setObjectName(QString::fromUtf8("Semicolon"));
        Semicolon->setGeometry(QRect(400, 260, 51, 41));
        Semicolon->setFont(font);
        Factorial = new QPushButton(centralwidget);
        Factorial->setObjectName(QString::fromUtf8("Factorial"));
        Factorial->setGeometry(QRect(490, 260, 51, 41));
        Factorial->setFont(font);
        Square = new QPushButton(centralwidget);
        Square->setObjectName(QString::fromUtf8("Square"));
        Square->setGeometry(QRect(580, 260, 51, 41));
        Square->setFont(font);
        Cmd = new QTextEdit(centralwidget);
        Cmd->setObjectName(QString::fromUtf8("Cmd"));
        Cmd->setGeometry(QRect(20, 533, 641, 41));
        Cmd->setFont(font);
        CmdRun = new QPushButton(centralwidget);
        CmdRun->setObjectName(QString::fromUtf8("CmdRun"));
        CmdRun->setGeometry(QRect(690, 533, 91, 41));
        CmdRun->setFont(font);
        runpol = new QPushButton(centralwidget);
        runpol->setObjectName(QString::fromUtf8("runpol"));
        runpol->setGeometry(QRect(400, 120, 91, 61));
        runpol->setFont(font);
        runmat = new QPushButton(centralwidget);
        runmat->setObjectName(QString::fromUtf8("runmat"));
        runmat->setGeometry(QRect(520, 120, 91, 61));
        runmat->setFont(font);
        cmdlog = new QTextEdit(centralwidget);
        cmdlog->setObjectName(QString::fromUtf8("cmdlog"));
        cmdlog->setGeometry(QRect(20, 580, 781, 191));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 810, 19));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\273\223\346\236\234:", nullptr));
        Zero->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        Point->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        Equal->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        Plus->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        One->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        Two->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        Three->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        Sub->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        Four->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        Five->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        Six->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        Mul->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        Seven->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        Eight->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        Nine->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        Div->setText(QCoreApplication::translate("MainWindow", "\303\267", nullptr));
        LeftBra->setText(QCoreApplication::translate("MainWindow", "(", nullptr));
        RightBra->setText(QCoreApplication::translate("MainWindow", ")", nullptr));
        Percent->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        Back->setText(QCoreApplication::translate("MainWindow", "back", nullptr));
        Clear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        Sin->setText(QCoreApplication::translate("MainWindow", "sin", nullptr));
        Cos->setText(QCoreApplication::translate("MainWindow", "cos", nullptr));
        Tan->setText(QCoreApplication::translate("MainWindow", "tan", nullptr));
        const_E->setText(QCoreApplication::translate("MainWindow", "e", nullptr));
        Ln->setText(QCoreApplication::translate("MainWindow", "ln", nullptr));
        Log->setText(QCoreApplication::translate("MainWindow", "log", nullptr));
        const_Pai->setText(QCoreApplication::translate("MainWindow", "\317\200", nullptr));
        Root->setText(QCoreApplication::translate("MainWindow", "\342\210\232", nullptr));
        Index->setText(QCoreApplication::translate("MainWindow", "x^y", nullptr));
        Semicolon->setText(QCoreApplication::translate("MainWindow", "1/x", nullptr));
        Factorial->setText(QCoreApplication::translate("MainWindow", "x!", nullptr));
        Square->setText(QCoreApplication::translate("MainWindow", "x^2", nullptr));
        CmdRun->setText(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
        runpol->setText(QCoreApplication::translate("MainWindow", "\345\244\232\351\241\271\345\274\217\350\256\241\347\256\227", nullptr));
        runmat->setText(QCoreApplication::translate("MainWindow", "\347\237\251\351\230\265\350\256\241\347\256\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
