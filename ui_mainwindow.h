/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *Page;
    QWidget *home;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_code;
    QLineEdit *line_code;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_trial;
    QLineEdit *line_trial;
    QVBoxLayout *verticalLayout;
    QRadioButton *auto_complete;
    QRadioButton *overwritten;
    QPushButton *start;
    QLabel *m_countdownLabel;
    QLabel *label_duration;
    QWidget *tab_2;
    QCustomPlot *backdrop;
    QPushButton *show;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_filepath;
    QLineEdit *filepath;
    QPushButton *exit;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *button_group;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(988, 689);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Page = new QTabWidget(centralwidget);
        Page->setObjectName(QString::fromUtf8("Page"));
        Page->setGeometry(QRect(40, 30, 911, 571));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Page->sizePolicy().hasHeightForWidth());
        Page->setSizePolicy(sizePolicy);
        Page->setLayoutDirection(Qt::LeftToRight);
        home = new QWidget();
        home->setObjectName(QString::fromUtf8("home"));
        layoutWidget = new QWidget(home);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 30, 731, 341));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_code = new QLabel(layoutWidget);
        label_code->setObjectName(QString::fromUtf8("label_code"));

        horizontalLayout->addWidget(label_code);

        line_code = new QLineEdit(layoutWidget);
        line_code->setObjectName(QString::fromUtf8("line_code"));

        horizontalLayout->addWidget(line_code);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_trial = new QLabel(layoutWidget);
        label_trial->setObjectName(QString::fromUtf8("label_trial"));

        horizontalLayout_2->addWidget(label_trial);

        line_trial = new QLineEdit(layoutWidget);
        line_trial->setObjectName(QString::fromUtf8("line_trial"));

        horizontalLayout_2->addWidget(line_trial);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        auto_complete = new QRadioButton(layoutWidget);
        button_group = new QButtonGroup(MainWindow);
        button_group->setObjectName(QString::fromUtf8("button_group"));
        button_group->addButton(auto_complete);
        auto_complete->setObjectName(QString::fromUtf8("auto_complete"));

        verticalLayout->addWidget(auto_complete);

        overwritten = new QRadioButton(layoutWidget);
        button_group->addButton(overwritten);
        overwritten->setObjectName(QString::fromUtf8("overwritten"));

        verticalLayout->addWidget(overwritten);


        verticalLayout_2->addLayout(verticalLayout);

        start = new QPushButton(layoutWidget);
        start->setObjectName(QString::fromUtf8("start"));

        verticalLayout_2->addWidget(start);

        m_countdownLabel = new QLabel(home);
        m_countdownLabel->setObjectName(QString::fromUtf8("m_countdownLabel"));
        m_countdownLabel->setGeometry(QRect(160, 450, 531, 41));
        m_countdownLabel->setSizeIncrement(QSize(20, 20));
        label_duration = new QLabel(home);
        label_duration->setObjectName(QString::fromUtf8("label_duration"));
        label_duration->setGeometry(QRect(70, 390, 729, 31));
        Page->addTab(home, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        backdrop = new QCustomPlot(tab_2);
        backdrop->setObjectName(QString::fromUtf8("backdrop"));
        backdrop->setGeometry(QRect(60, 100, 461, 261));
        show = new QPushButton(tab_2);
        show->setObjectName(QString::fromUtf8("show"));
        show->setGeometry(QRect(630, 230, 111, 32));
        layoutWidget_3 = new QWidget(tab_2);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(600, 170, 190, 25));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_filepath = new QLabel(layoutWidget_3);
        label_filepath->setObjectName(QString::fromUtf8("label_filepath"));

        horizontalLayout_3->addWidget(label_filepath);

        filepath = new QLineEdit(layoutWidget_3);
        filepath->setObjectName(QString::fromUtf8("filepath"));

        horizontalLayout_3->addWidget(filepath);

        exit = new QPushButton(tab_2);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setGeometry(QRect(630, 280, 111, 32));
        Page->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 988, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        Page->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_code->setText(QCoreApplication::translate("MainWindow", "Participant Code: ", nullptr));
        label_trial->setText(QCoreApplication::translate("MainWindow", "Trial:                     #", nullptr));
        auto_complete->setText(QCoreApplication::translate("MainWindow", "Auto", nullptr));
        overwritten->setText(QCoreApplication::translate("MainWindow", "Overwriten", nullptr));
        start->setText(QCoreApplication::translate("MainWindow", "start", nullptr));
        m_countdownLabel->setText(QString());
        label_duration->setText(QString());
        Page->setTabText(Page->indexOf(home), QCoreApplication::translate("MainWindow", "Home", nullptr));
        show->setText(QCoreApplication::translate("MainWindow", "show", nullptr));
        label_filepath->setText(QCoreApplication::translate("MainWindow", "File Path:", nullptr));
        exit->setText(QCoreApplication::translate("MainWindow", "exit", nullptr));
        Page->setTabText(Page->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Dynamic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
