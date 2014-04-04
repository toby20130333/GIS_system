/********************************************************************************
** Form generated from reading UI file 'firstwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRSTWIDGET_H
#define UI_FIRSTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FirstWidget
{
public:
    QPushButton *pushButton_search;
    QLabel *label_begin;
    QLineEdit *lineEdit_input_road;
    QPushButton *pushButton_find_road;
    QLabel *label_end;
    QComboBox *comboBox_begin;
    QComboBox *comboBox_end;
    QComboBox *comboBox_beg_end;
    QLabel *label_input;
    QLabel *label_option;
    QTextEdit *textEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *FirstWidget)
    {
        if (FirstWidget->objectName().isEmpty())
            FirstWidget->setObjectName(QString::fromUtf8("FirstWidget"));
        FirstWidget->resize(469, 380);
        pushButton_search = new QPushButton(FirstWidget);
        pushButton_search->setObjectName(QString::fromUtf8("pushButton_search"));
        pushButton_search->setGeometry(QRect(10, 320, 75, 23));
        pushButton_search->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 85, 0);\n"
"font: 9pt \"Adobe \344\273\277\345\256\213 Std R\";\n"
"color: rgb(0, 0, 0);"));
        label_begin = new QLabel(FirstWidget);
        label_begin->setObjectName(QString::fromUtf8("label_begin"));
        label_begin->setGeometry(QRect(20, 110, 31, 16));
        label_begin->setStyleSheet(QString::fromUtf8("color: rgb(20, 20, 255);"));
        lineEdit_input_road = new QLineEdit(FirstWidget);
        lineEdit_input_road->setObjectName(QString::fromUtf8("lineEdit_input_road"));
        lineEdit_input_road->setGeometry(QRect(80, 240, 181, 20));
        lineEdit_input_road->setStyleSheet(QString::fromUtf8("background-color: rgb(166, 214, 255);\n"
"font: 9pt \"Adobe \344\273\277\345\256\213 Std R\";"));
        pushButton_find_road = new QPushButton(FirstWidget);
        pushButton_find_road->setObjectName(QString::fromUtf8("pushButton_find_road"));
        pushButton_find_road->setGeometry(QRect(170, 320, 75, 23));
        pushButton_find_road->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 85, 0);\n"
"color: rgb(0, 0, 0);\n"
"font: 10pt \"Adobe \344\273\277\345\256\213 Std R\";"));
        label_end = new QLabel(FirstWidget);
        label_end->setObjectName(QString::fromUtf8("label_end"));
        label_end->setGeometry(QRect(20, 180, 31, 16));
        label_end->setStyleSheet(QString::fromUtf8("color: rgb(48, 21, 255);"));
        comboBox_begin = new QComboBox(FirstWidget);
        comboBox_begin->setObjectName(QString::fromUtf8("comboBox_begin"));
        comboBox_begin->setGeometry(QRect(60, 110, 201, 22));
        comboBox_begin->setStyleSheet(QString::fromUtf8("background-color: rgb(110, 166, 255);\n"
"font: 9pt \"Adobe \344\273\277\345\256\213 Std R\";"));
        comboBox_end = new QComboBox(FirstWidget);
        comboBox_end->setObjectName(QString::fromUtf8("comboBox_end"));
        comboBox_end->setGeometry(QRect(60, 180, 201, 22));
        comboBox_end->setStyleSheet(QString::fromUtf8("background-color: rgb(110, 188, 255);\n"
"font: 9pt \"Adobe \344\273\277\345\256\213 Std R\";"));
        comboBox_beg_end = new QComboBox(FirstWidget);
        comboBox_beg_end->setObjectName(QString::fromUtf8("comboBox_beg_end"));
        comboBox_beg_end->setGeometry(QRect(60, 50, 91, 22));
        comboBox_beg_end->setStyleSheet(QString::fromUtf8("background-color: rgb(79, 188, 255);\n"
"font: 9pt \"Adobe \344\273\277\345\256\213 Std R\";"));
        label_input = new QLabel(FirstWidget);
        label_input->setObjectName(QString::fromUtf8("label_input"));
        label_input->setGeometry(QRect(20, 240, 61, 16));
        label_input->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_option = new QLabel(FirstWidget);
        label_option->setObjectName(QString::fromUtf8("label_option"));
        label_option->setGeometry(QRect(20, 50, 31, 16));
        label_option->setStyleSheet(QString::fromUtf8("color: rgb(12, 28, 255);"));
        textEdit = new QTextEdit(FirstWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(280, 60, 181, 291));
        textEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(123, 191, 255);\n"
"font: 10pt \"Adobe \344\273\277\345\256\213 Std R\";\n"
"color: rgb(255, 47, 165);"));
        pushButton = new QPushButton(FirstWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(420, 10, 41, 21));
        pushButton->setStyleSheet(QString::fromUtf8("font: 9pt \"Adobe \344\273\277\345\256\213 Std R\";\n"
"color: rgb(0, 0, 0);\n"
"background-color: rgb(85, 0, 0);"));

        retranslateUi(FirstWidget);

        QMetaObject::connectSlotsByName(FirstWidget);
    } // setupUi

    void retranslateUi(QWidget *FirstWidget)
    {
        FirstWidget->setWindowTitle(QApplication::translate("FirstWidget", "Form", 0, QApplication::UnicodeUTF8));
        pushButton_search->setText(QApplication::translate("FirstWidget", "\346\237\245\346\211\276", 0, QApplication::UnicodeUTF8));
        label_begin->setText(QApplication::translate("FirstWidget", "\350\265\267\347\202\271", 0, QApplication::UnicodeUTF8));
        pushButton_find_road->setText(QApplication::translate("FirstWidget", "\345\257\273\350\267\257", 0, QApplication::UnicodeUTF8));
        label_end->setText(QApplication::translate("FirstWidget", "\347\273\210\347\202\271", 0, QApplication::UnicodeUTF8));
        comboBox_beg_end->clear();
        comboBox_beg_end->insertItems(0, QStringList()
         << QApplication::translate("FirstWidget", "\350\265\267\347\202\271", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FirstWidget", "\347\273\210\347\202\271", 0, QApplication::UnicodeUTF8)
        );
        label_input->setText(QApplication::translate("FirstWidget", "\350\276\223\345\205\245\350\265\267\347\202\271:", 0, QApplication::UnicodeUTF8));
        label_option->setText(QApplication::translate("FirstWidget", "\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("FirstWidget", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FirstWidget: public Ui_FirstWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRSTWIDGET_H
