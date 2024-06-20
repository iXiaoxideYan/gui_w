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
#include <QtWidgets/QFormLayout>
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
    QFormLayout *formLayout;
    QTabWidget *Page;
    QWidget *home;
    QWidget *widget;
    QFormLayout *formLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_duration;
    QLabel *m_countdownLabel;
    QFormLayout *formLayout_3;
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
    QWidget *dynamic;
    QFormLayout *formLayout_4;
    QFormLayout *formLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QCustomPlot *backdrop;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_filepath;
    QLineEdit *filepath;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *show;
    QPushButton *exit;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *button_group;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(936, 606);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        Page = new QTabWidget(centralwidget);
        Page->setObjectName(QString::fromUtf8("Page"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Page->sizePolicy().hasHeightForWidth());
        Page->setSizePolicy(sizePolicy);
        Page->setLayoutDirection(Qt::LeftToRight);
        home = new QWidget();
        home->setObjectName(QString::fromUtf8("home"));
        widget = new QWidget(home);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(6, 6, 911, 521));
        formLayout_2 = new QFormLayout(widget);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_duration = new QLabel(widget);
        label_duration->setObjectName(QString::fromUtf8("label_duration"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_duration->sizePolicy().hasHeightForWidth());
        label_duration->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(label_duration);

        m_countdownLabel = new QLabel(widget);
        m_countdownLabel->setObjectName(QString::fromUtf8("m_countdownLabel"));
        m_countdownLabel->setSizeIncrement(QSize(20, 20));

        verticalLayout_2->addWidget(m_countdownLabel);


        formLayout_2->setLayout(1, QFormLayout::SpanningRole, verticalLayout_2);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_code = new QLabel(widget);
        label_code->setObjectName(QString::fromUtf8("label_code"));

        horizontalLayout->addWidget(label_code);

        line_code = new QLineEdit(widget);
        line_code->setObjectName(QString::fromUtf8("line_code"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line_code->sizePolicy().hasHeightForWidth());
        line_code->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(line_code);


        formLayout_3->setLayout(0, QFormLayout::SpanningRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_trial = new QLabel(widget);
        label_trial->setObjectName(QString::fromUtf8("label_trial"));

        horizontalLayout_2->addWidget(label_trial);

        line_trial = new QLineEdit(widget);
        line_trial->setObjectName(QString::fromUtf8("line_trial"));

        horizontalLayout_2->addWidget(line_trial);


        formLayout_3->setLayout(1, QFormLayout::SpanningRole, horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        auto_complete = new QRadioButton(widget);
        button_group = new QButtonGroup(MainWindow);
        button_group->setObjectName(QString::fromUtf8("button_group"));
        button_group->addButton(auto_complete);
        auto_complete->setObjectName(QString::fromUtf8("auto_complete"));

        verticalLayout->addWidget(auto_complete);

        overwritten = new QRadioButton(widget);
        button_group->addButton(overwritten);
        overwritten->setObjectName(QString::fromUtf8("overwritten"));

        verticalLayout->addWidget(overwritten);


        formLayout_3->setLayout(2, QFormLayout::SpanningRole, verticalLayout);

        start = new QPushButton(widget);
        start->setObjectName(QString::fromUtf8("start"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(start->sizePolicy().hasHeightForWidth());
        start->setSizePolicy(sizePolicy3);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, start);


        formLayout_2->setLayout(0, QFormLayout::SpanningRole, formLayout_3);

        Page->addTab(home, QString());
        dynamic = new QWidget();
        dynamic->setObjectName(QString::fromUtf8("dynamic"));
        formLayout_4 = new QFormLayout(dynamic);
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        formLayout_5 = new QFormLayout();
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        formLayout_5->setVerticalSpacing(4);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        backdrop = new QCustomPlot(dynamic);
        backdrop->setObjectName(QString::fromUtf8("backdrop"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(backdrop->sizePolicy().hasHeightForWidth());
        backdrop->setSizePolicy(sizePolicy4);

        horizontalLayout_4->addWidget(backdrop);


        formLayout_5->setLayout(0, QFormLayout::SpanningRole, horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_filepath = new QLabel(dynamic);
        label_filepath->setObjectName(QString::fromUtf8("label_filepath"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_filepath->sizePolicy().hasHeightForWidth());
        label_filepath->setSizePolicy(sizePolicy5);

        horizontalLayout_3->addWidget(label_filepath);

        filepath = new QLineEdit(dynamic);
        filepath->setObjectName(QString::fromUtf8("filepath"));

        horizontalLayout_3->addWidget(filepath);


        formLayout_5->setLayout(1, QFormLayout::SpanningRole, horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        show = new QPushButton(dynamic);
        show->setObjectName(QString::fromUtf8("show"));
        sizePolicy5.setHeightForWidth(show->sizePolicy().hasHeightForWidth());
        show->setSizePolicy(sizePolicy5);

        horizontalLayout_5->addWidget(show);

        exit = new QPushButton(dynamic);
        exit->setObjectName(QString::fromUtf8("exit"));
        sizePolicy5.setHeightForWidth(exit->sizePolicy().hasHeightForWidth());
        exit->setSizePolicy(sizePolicy5);

        horizontalLayout_5->addWidget(exit);


        formLayout_5->setLayout(2, QFormLayout::SpanningRole, horizontalLayout_5);


        formLayout_4->setLayout(0, QFormLayout::SpanningRole, formLayout_5);

        Page->addTab(dynamic, QString());

        formLayout->setWidget(0, QFormLayout::FieldRole, Page);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 936, 17));
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
        label_duration->setText(QString());
        m_countdownLabel->setText(QString());
        label_code->setText(QCoreApplication::translate("MainWindow", "Participant Code: ", nullptr));
        label_trial->setText(QCoreApplication::translate("MainWindow", "Trial:                   #", nullptr));
        auto_complete->setText(QCoreApplication::translate("MainWindow", "Auto", nullptr));
        overwritten->setText(QCoreApplication::translate("MainWindow", "Overwriten", nullptr));
        start->setText(QCoreApplication::translate("MainWindow", "start", nullptr));
        Page->setTabText(Page->indexOf(home), QCoreApplication::translate("MainWindow", "Home", nullptr));
        label_filepath->setText(QCoreApplication::translate("MainWindow", "File Path:", nullptr));
        show->setText(QCoreApplication::translate("MainWindow", "show", nullptr));
        exit->setText(QCoreApplication::translate("MainWindow", "exit", nullptr));
        Page->setTabText(Page->indexOf(dynamic), QCoreApplication::translate("MainWindow", "Dynamic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
