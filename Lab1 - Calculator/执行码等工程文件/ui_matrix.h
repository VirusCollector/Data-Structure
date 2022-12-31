/********************************************************************************
** Form generated from reading UI file 'matrix.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIX_H
#define UI_MATRIX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_matrix
{
public:
    QTextEdit *input;
    QPushButton *run;
    QTextEdit *cmdlog;

    void setupUi(QWidget *matrix)
    {
        if (matrix->objectName().isEmpty())
            matrix->setObjectName(QString::fromUtf8("matrix"));
        matrix->resize(624, 461);
        input = new QTextEdit(matrix);
        input->setObjectName(QString::fromUtf8("input"));
        input->setGeometry(QRect(10, 10, 501, 211));
        input->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 127);"));
        run = new QPushButton(matrix);
        run->setObjectName(QString::fromUtf8("run"));
        run->setGeometry(QRect(530, 10, 81, 81));
        QFont font;
        font.setPointSize(12);
        run->setFont(font);
        cmdlog = new QTextEdit(matrix);
        cmdlog->setObjectName(QString::fromUtf8("cmdlog"));
        cmdlog->setGeometry(QRect(10, 240, 601, 211));
        cmdlog->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);"));

        retranslateUi(matrix);

        QMetaObject::connectSlotsByName(matrix);
    } // setupUi

    void retranslateUi(QWidget *matrix)
    {
        matrix->setWindowTitle(QCoreApplication::translate("matrix", "Form", nullptr));
        run->setText(QCoreApplication::translate("matrix", "\350\277\220\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class matrix: public Ui_matrix {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIX_H
