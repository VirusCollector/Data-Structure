/********************************************************************************
** Form generated from reading UI file 'polynomial.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLYNOMIAL_H
#define UI_POLYNOMIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_polynomial
{
public:
    QTextEdit *input;
    QPushButton *run;
    QTextEdit *output;

    void setupUi(QWidget *polynomial)
    {
        if (polynomial->objectName().isEmpty())
            polynomial->setObjectName(QString::fromUtf8("polynomial"));
        polynomial->resize(576, 300);
        input = new QTextEdit(polynomial);
        input->setObjectName(QString::fromUtf8("input"));
        input->setGeometry(QRect(10, 10, 471, 61));
        QFont font;
        font.setPointSize(12);
        input->setFont(font);
        input->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 127);"));
        run = new QPushButton(polynomial);
        run->setObjectName(QString::fromUtf8("run"));
        run->setGeometry(QRect(500, 10, 71, 61));
        run->setFont(font);
        output = new QTextEdit(polynomial);
        output->setObjectName(QString::fromUtf8("output"));
        output->setGeometry(QRect(10, 90, 471, 191));
        output->setFont(font);
        output->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);"));

        retranslateUi(polynomial);

        QMetaObject::connectSlotsByName(polynomial);
    } // setupUi

    void retranslateUi(QWidget *polynomial)
    {
        polynomial->setWindowTitle(QCoreApplication::translate("polynomial", "Form", nullptr));
        run->setText(QCoreApplication::translate("polynomial", "\350\277\220\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class polynomial: public Ui_polynomial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLYNOMIAL_H
