/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Mar 21 21:54:47 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qtcolorbutton.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    Utils::QtColorButton *toolButton_6;
    QRadioButton *radioButton_6;
    QHBoxLayout *horizontalLayout_2;
    Utils::QtColorButton *toolButton_2;
    QRadioButton *radioButton_2;
    QHBoxLayout *horizontalLayout_4;
    Utils::QtColorButton *toolButton_3;
    QRadioButton *radioButton_3;
    QHBoxLayout *horizontalLayout_5;
    Utils::QtColorButton *toolButton_4;
    QRadioButton *radioButton_4;
    QHBoxLayout *horizontalLayout_6;
    Utils::QtColorButton *toolButton_5;
    QRadioButton *radioButton_5;
    QHBoxLayout *horizontalLayout_8;
    Utils::QtColorButton *toolButton_7;
    QRadioButton *radioButton_7;
    QHBoxLayout *horizontalLayout_3;
    Utils::QtColorButton *toolButton_10;
    QRadioButton *radioButton_10;
    QHBoxLayout *horizontalLayout_10;
    Utils::QtColorButton *toolButton_9;
    QRadioButton *radioButton_9;
    QHBoxLayout *horizontalLayout_11;
    Utils::QtColorButton *toolButton_11;
    QRadioButton *radioButton_11;
    QHBoxLayout *horizontalLayout_9;
    Utils::QtColorButton *toolButton_8;
    QRadioButton *radioButton_8;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(194, 394);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(194, 394));
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        toolButton_6 = new Utils::QtColorButton(centralWidget);
        toolButton_6->setObjectName(QString::fromUtf8("toolButton_6"));
        sizePolicy.setHeightForWidth(toolButton_6->sizePolicy().hasHeightForWidth());
        toolButton_6->setSizePolicy(sizePolicy);
        toolButton_6->setMinimumSize(QSize(50, 30));

        horizontalLayout_7->addWidget(toolButton_6);

        radioButton_6 = new QRadioButton(centralWidget);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));
        radioButton_6->setEnabled(true);

        horizontalLayout_7->addWidget(radioButton_6);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        toolButton_2 = new Utils::QtColorButton(centralWidget);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        sizePolicy.setHeightForWidth(toolButton_2->sizePolicy().hasHeightForWidth());
        toolButton_2->setSizePolicy(sizePolicy);
        toolButton_2->setMinimumSize(QSize(50, 30));

        horizontalLayout_2->addWidget(toolButton_2);

        radioButton_2 = new QRadioButton(centralWidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        horizontalLayout_2->addWidget(radioButton_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        toolButton_3 = new Utils::QtColorButton(centralWidget);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        sizePolicy.setHeightForWidth(toolButton_3->sizePolicy().hasHeightForWidth());
        toolButton_3->setSizePolicy(sizePolicy);
        toolButton_3->setMinimumSize(QSize(50, 30));

        horizontalLayout_4->addWidget(toolButton_3);

        radioButton_3 = new QRadioButton(centralWidget);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        horizontalLayout_4->addWidget(radioButton_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        toolButton_4 = new Utils::QtColorButton(centralWidget);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        sizePolicy.setHeightForWidth(toolButton_4->sizePolicy().hasHeightForWidth());
        toolButton_4->setSizePolicy(sizePolicy);
        toolButton_4->setMinimumSize(QSize(50, 30));

        horizontalLayout_5->addWidget(toolButton_4);

        radioButton_4 = new QRadioButton(centralWidget);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        horizontalLayout_5->addWidget(radioButton_4);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        toolButton_5 = new Utils::QtColorButton(centralWidget);
        toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));
        sizePolicy.setHeightForWidth(toolButton_5->sizePolicy().hasHeightForWidth());
        toolButton_5->setSizePolicy(sizePolicy);
        toolButton_5->setMinimumSize(QSize(50, 30));

        horizontalLayout_6->addWidget(toolButton_5);

        radioButton_5 = new QRadioButton(centralWidget);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));

        horizontalLayout_6->addWidget(radioButton_5);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        toolButton_7 = new Utils::QtColorButton(centralWidget);
        toolButton_7->setObjectName(QString::fromUtf8("toolButton_7"));
        sizePolicy.setHeightForWidth(toolButton_7->sizePolicy().hasHeightForWidth());
        toolButton_7->setSizePolicy(sizePolicy);
        toolButton_7->setMinimumSize(QSize(50, 30));

        horizontalLayout_8->addWidget(toolButton_7);

        radioButton_7 = new QRadioButton(centralWidget);
        radioButton_7->setObjectName(QString::fromUtf8("radioButton_7"));

        horizontalLayout_8->addWidget(radioButton_7);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        toolButton_10 = new Utils::QtColorButton(centralWidget);
        toolButton_10->setObjectName(QString::fromUtf8("toolButton_10"));
        sizePolicy.setHeightForWidth(toolButton_10->sizePolicy().hasHeightForWidth());
        toolButton_10->setSizePolicy(sizePolicy);
        toolButton_10->setMinimumSize(QSize(50, 30));

        horizontalLayout_3->addWidget(toolButton_10);

        radioButton_10 = new QRadioButton(centralWidget);
        radioButton_10->setObjectName(QString::fromUtf8("radioButton_10"));

        horizontalLayout_3->addWidget(radioButton_10);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        toolButton_9 = new Utils::QtColorButton(centralWidget);
        toolButton_9->setObjectName(QString::fromUtf8("toolButton_9"));
        sizePolicy.setHeightForWidth(toolButton_9->sizePolicy().hasHeightForWidth());
        toolButton_9->setSizePolicy(sizePolicy);
        toolButton_9->setMinimumSize(QSize(50, 30));

        horizontalLayout_10->addWidget(toolButton_9);

        radioButton_9 = new QRadioButton(centralWidget);
        radioButton_9->setObjectName(QString::fromUtf8("radioButton_9"));

        horizontalLayout_10->addWidget(radioButton_9);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        toolButton_11 = new Utils::QtColorButton(centralWidget);
        toolButton_11->setObjectName(QString::fromUtf8("toolButton_11"));
        sizePolicy.setHeightForWidth(toolButton_11->sizePolicy().hasHeightForWidth());
        toolButton_11->setSizePolicy(sizePolicy);
        toolButton_11->setMinimumSize(QSize(50, 30));

        horizontalLayout_11->addWidget(toolButton_11);

        radioButton_11 = new QRadioButton(centralWidget);
        radioButton_11->setObjectName(QString::fromUtf8("radioButton_11"));

        horizontalLayout_11->addWidget(radioButton_11);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        toolButton_8 = new Utils::QtColorButton(centralWidget);
        toolButton_8->setObjectName(QString::fromUtf8("toolButton_8"));
        sizePolicy.setHeightForWidth(toolButton_8->sizePolicy().hasHeightForWidth());
        toolButton_8->setSizePolicy(sizePolicy);
        toolButton_8->setMinimumSize(QSize(50, 30));

        horizontalLayout_9->addWidget(toolButton_8);

        radioButton_8 = new QRadioButton(centralWidget);
        radioButton_8->setObjectName(QString::fromUtf8("radioButton_8"));

        horizontalLayout_9->addWidget(radioButton_8);


        verticalLayout->addLayout(horizontalLayout_9);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        toolButton_2->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "VoxelEditor", 0, QApplication::UnicodeUTF8));
        toolButton_6->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        radioButton_6->setText(QApplication::translate("MainWindow", "Color1", 0, QApplication::UnicodeUTF8));
        toolButton_2->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("MainWindow", "Color2", 0, QApplication::UnicodeUTF8));
        toolButton_3->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        radioButton_3->setText(QApplication::translate("MainWindow", "Color3", 0, QApplication::UnicodeUTF8));
        toolButton_4->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        radioButton_4->setText(QApplication::translate("MainWindow", "Color4", 0, QApplication::UnicodeUTF8));
        toolButton_5->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        radioButton_5->setText(QApplication::translate("MainWindow", "Color5", 0, QApplication::UnicodeUTF8));
        toolButton_7->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        radioButton_7->setText(QApplication::translate("MainWindow", "Color6", 0, QApplication::UnicodeUTF8));
        toolButton_10->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        radioButton_10->setText(QApplication::translate("MainWindow", "Color7", 0, QApplication::UnicodeUTF8));
        toolButton_9->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        radioButton_9->setText(QApplication::translate("MainWindow", "Color8", 0, QApplication::UnicodeUTF8));
        toolButton_11->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        radioButton_11->setText(QApplication::translate("MainWindow", "Color10", 0, QApplication::UnicodeUTF8));
        toolButton_8->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        radioButton_8->setText(QApplication::translate("MainWindow", "RadioButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
