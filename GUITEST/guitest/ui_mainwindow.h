/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Mar 28 20:16:06 2013
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
#include <qtcolorbutton.h>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_22;
    GLWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    Utils::QtColorButton *c0;
    QRadioButton *r0;
    QHBoxLayout *horizontalLayout_11;
    Utils::QtColorButton *c1;
    QRadioButton *r1;
    QHBoxLayout *horizontalLayout_18;
    Utils::QtColorButton *c10;
    QRadioButton *r10;
    QHBoxLayout *horizontalLayout_16;
    Utils::QtColorButton *c8;
    QRadioButton *r8;
    QHBoxLayout *horizontalLayout_20;
    Utils::QtColorButton *c2;
    QRadioButton *r2;
    QHBoxLayout *horizontalLayout_15;
    Utils::QtColorButton *c7;
    QRadioButton *r7;
    QHBoxLayout *horizontalLayout_13;
    Utils::QtColorButton *c5;
    QRadioButton *r5;
    QHBoxLayout *horizontalLayout_21;
    Utils::QtColorButton *c3;
    QRadioButton *r3;
    QHBoxLayout *horizontalLayout_14;
    Utils::QtColorButton *c6;
    QRadioButton *r6;
    QHBoxLayout *horizontalLayout_12;
    Utils::QtColorButton *c4;
    QRadioButton *r4;
    QHBoxLayout *horizontalLayout_17;
    Utils::QtColorButton *c9;
    QRadioButton *r9;
    QHBoxLayout *horizontalLayout_19;
    Utils::QtColorButton *c11;
    QRadioButton *r11;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(615, 547);
        MainWindow->setFocusPolicy(Qt::NoFocus);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_22 = new QHBoxLayout(centralWidget);
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        widget = new GLWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setCursor(QCursor(Qt::CrossCursor));
        widget->setMouseTracking(true);
        widget->setFocusPolicy(Qt::ClickFocus);
        widget->setContextMenuPolicy(Qt::NoContextMenu);

        horizontalLayout_22->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        c0 = new Utils::QtColorButton(centralWidget);
        c0->setObjectName(QString::fromUtf8("c0"));
        c0->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(c0->sizePolicy().hasHeightForWidth());
        c0->setSizePolicy(sizePolicy1);
        c0->setMinimumSize(QSize(50, 0));
        c0->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(c0);

        r0 = new QRadioButton(centralWidget);
        r0->setObjectName(QString::fromUtf8("r0"));
        r0->setEnabled(true);
        sizePolicy1.setHeightForWidth(r0->sizePolicy().hasHeightForWidth());
        r0->setSizePolicy(sizePolicy1);
        r0->setFocusPolicy(Qt::NoFocus);
        r0->setChecked(true);

        horizontalLayout->addWidget(r0);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        c1 = new Utils::QtColorButton(centralWidget);
        c1->setObjectName(QString::fromUtf8("c1"));
        sizePolicy1.setHeightForWidth(c1->sizePolicy().hasHeightForWidth());
        c1->setSizePolicy(sizePolicy1);
        c1->setMinimumSize(QSize(50, 0));
        c1->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_11->addWidget(c1);

        r1 = new QRadioButton(centralWidget);
        r1->setObjectName(QString::fromUtf8("r1"));
        sizePolicy1.setHeightForWidth(r1->sizePolicy().hasHeightForWidth());
        r1->setSizePolicy(sizePolicy1);
        r1->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_11->addWidget(r1);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        c10 = new Utils::QtColorButton(centralWidget);
        c10->setObjectName(QString::fromUtf8("c10"));
        sizePolicy1.setHeightForWidth(c10->sizePolicy().hasHeightForWidth());
        c10->setSizePolicy(sizePolicy1);
        c10->setMinimumSize(QSize(50, 0));
        c10->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_18->addWidget(c10);

        r10 = new QRadioButton(centralWidget);
        r10->setObjectName(QString::fromUtf8("r10"));
        sizePolicy1.setHeightForWidth(r10->sizePolicy().hasHeightForWidth());
        r10->setSizePolicy(sizePolicy1);
        r10->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_18->addWidget(r10);


        verticalLayout->addLayout(horizontalLayout_18);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        c8 = new Utils::QtColorButton(centralWidget);
        c8->setObjectName(QString::fromUtf8("c8"));
        sizePolicy1.setHeightForWidth(c8->sizePolicy().hasHeightForWidth());
        c8->setSizePolicy(sizePolicy1);
        c8->setMinimumSize(QSize(50, 0));
        c8->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_16->addWidget(c8);

        r8 = new QRadioButton(centralWidget);
        r8->setObjectName(QString::fromUtf8("r8"));
        sizePolicy1.setHeightForWidth(r8->sizePolicy().hasHeightForWidth());
        r8->setSizePolicy(sizePolicy1);
        r8->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_16->addWidget(r8);


        verticalLayout->addLayout(horizontalLayout_16);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        c2 = new Utils::QtColorButton(centralWidget);
        c2->setObjectName(QString::fromUtf8("c2"));
        sizePolicy1.setHeightForWidth(c2->sizePolicy().hasHeightForWidth());
        c2->setSizePolicy(sizePolicy1);
        c2->setMinimumSize(QSize(50, 0));
        c2->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_20->addWidget(c2);

        r2 = new QRadioButton(centralWidget);
        r2->setObjectName(QString::fromUtf8("r2"));
        sizePolicy1.setHeightForWidth(r2->sizePolicy().hasHeightForWidth());
        r2->setSizePolicy(sizePolicy1);
        r2->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_20->addWidget(r2);


        verticalLayout->addLayout(horizontalLayout_20);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        c7 = new Utils::QtColorButton(centralWidget);
        c7->setObjectName(QString::fromUtf8("c7"));
        sizePolicy1.setHeightForWidth(c7->sizePolicy().hasHeightForWidth());
        c7->setSizePolicy(sizePolicy1);
        c7->setMinimumSize(QSize(50, 0));
        c7->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_15->addWidget(c7);

        r7 = new QRadioButton(centralWidget);
        r7->setObjectName(QString::fromUtf8("r7"));
        sizePolicy1.setHeightForWidth(r7->sizePolicy().hasHeightForWidth());
        r7->setSizePolicy(sizePolicy1);
        r7->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_15->addWidget(r7);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        c5 = new Utils::QtColorButton(centralWidget);
        c5->setObjectName(QString::fromUtf8("c5"));
        sizePolicy1.setHeightForWidth(c5->sizePolicy().hasHeightForWidth());
        c5->setSizePolicy(sizePolicy1);
        c5->setMinimumSize(QSize(50, 0));
        c5->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_13->addWidget(c5);

        r5 = new QRadioButton(centralWidget);
        r5->setObjectName(QString::fromUtf8("r5"));
        sizePolicy1.setHeightForWidth(r5->sizePolicy().hasHeightForWidth());
        r5->setSizePolicy(sizePolicy1);
        r5->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_13->addWidget(r5);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        c3 = new Utils::QtColorButton(centralWidget);
        c3->setObjectName(QString::fromUtf8("c3"));
        sizePolicy1.setHeightForWidth(c3->sizePolicy().hasHeightForWidth());
        c3->setSizePolicy(sizePolicy1);
        c3->setMinimumSize(QSize(50, 0));
        c3->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_21->addWidget(c3);

        r3 = new QRadioButton(centralWidget);
        r3->setObjectName(QString::fromUtf8("r3"));
        sizePolicy1.setHeightForWidth(r3->sizePolicy().hasHeightForWidth());
        r3->setSizePolicy(sizePolicy1);
        r3->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_21->addWidget(r3);


        verticalLayout->addLayout(horizontalLayout_21);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        c6 = new Utils::QtColorButton(centralWidget);
        c6->setObjectName(QString::fromUtf8("c6"));
        sizePolicy1.setHeightForWidth(c6->sizePolicy().hasHeightForWidth());
        c6->setSizePolicy(sizePolicy1);
        c6->setMinimumSize(QSize(50, 0));
        c6->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_14->addWidget(c6);

        r6 = new QRadioButton(centralWidget);
        r6->setObjectName(QString::fromUtf8("r6"));
        sizePolicy1.setHeightForWidth(r6->sizePolicy().hasHeightForWidth());
        r6->setSizePolicy(sizePolicy1);
        r6->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_14->addWidget(r6);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        c4 = new Utils::QtColorButton(centralWidget);
        c4->setObjectName(QString::fromUtf8("c4"));
        sizePolicy1.setHeightForWidth(c4->sizePolicy().hasHeightForWidth());
        c4->setSizePolicy(sizePolicy1);
        c4->setMinimumSize(QSize(50, 0));
        c4->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_12->addWidget(c4);

        r4 = new QRadioButton(centralWidget);
        r4->setObjectName(QString::fromUtf8("r4"));
        sizePolicy1.setHeightForWidth(r4->sizePolicy().hasHeightForWidth());
        r4->setSizePolicy(sizePolicy1);
        r4->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_12->addWidget(r4);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        c9 = new Utils::QtColorButton(centralWidget);
        c9->setObjectName(QString::fromUtf8("c9"));
        sizePolicy1.setHeightForWidth(c9->sizePolicy().hasHeightForWidth());
        c9->setSizePolicy(sizePolicy1);
        c9->setMinimumSize(QSize(50, 0));
        c9->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_17->addWidget(c9);

        r9 = new QRadioButton(centralWidget);
        r9->setObjectName(QString::fromUtf8("r9"));
        sizePolicy1.setHeightForWidth(r9->sizePolicy().hasHeightForWidth());
        r9->setSizePolicy(sizePolicy1);
        r9->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_17->addWidget(r9);


        verticalLayout->addLayout(horizontalLayout_17);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        c11 = new Utils::QtColorButton(centralWidget);
        c11->setObjectName(QString::fromUtf8("c11"));
        sizePolicy1.setHeightForWidth(c11->sizePolicy().hasHeightForWidth());
        c11->setSizePolicy(sizePolicy1);
        c11->setMinimumSize(QSize(50, 0));
        c11->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_19->addWidget(c11);

        r11 = new QRadioButton(centralWidget);
        r11->setObjectName(QString::fromUtf8("r11"));
        sizePolicy1.setHeightForWidth(r11->sizePolicy().hasHeightForWidth());
        r11->setSizePolicy(sizePolicy1);
        r11->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_19->addWidget(r11);


        verticalLayout->addLayout(horizontalLayout_19);


        horizontalLayout_22->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        c0->raise();
        widget->raise();

        retranslateUi(MainWindow);
        QObject::connect(r0, SIGNAL(pressed()), widget, SLOT(set0()));
        QObject::connect(r5, SIGNAL(pressed()), widget, SLOT(set5()));
        QObject::connect(r4, SIGNAL(pressed()), widget, SLOT(set4()));
        QObject::connect(r1, SIGNAL(pressed()), widget, SLOT(set1()));
        QObject::connect(r6, SIGNAL(pressed()), widget, SLOT(set6()));
        QObject::connect(r7, SIGNAL(pressed()), widget, SLOT(set7()));
        QObject::connect(r8, SIGNAL(pressed()), widget, SLOT(set8()));
        QObject::connect(r9, SIGNAL(pressed()), widget, SLOT(set9()));
        QObject::connect(r10, SIGNAL(pressed()), widget, SLOT(set10()));
        QObject::connect(r11, SIGNAL(pressed()), widget, SLOT(set11()));
        QObject::connect(r2, SIGNAL(pressed()), widget, SLOT(set2()));
        QObject::connect(r3, SIGNAL(pressed()), widget, SLOT(set3()));
        QObject::connect(c0, SIGNAL(colorChanged(QColor)), widget, SLOT(setColor0(QColor)));
        QObject::connect(c1, SIGNAL(colorChanged(QColor)), widget, SLOT(setColor1(QColor)));
        QObject::connect(c10, SIGNAL(colorChanged(QColor)), widget, SLOT(setColor10(QColor)));
        QObject::connect(c8, SIGNAL(colorChanged(QColor)), widget, SLOT(setColor8(QColor)));
        QObject::connect(c7, SIGNAL(colorChanged(QColor)), widget, SLOT(setColor7(QColor)));
        QObject::connect(c2, SIGNAL(colorChanged(QColor)), widget, SLOT(setColor2(QColor)));
        QObject::connect(c5, SIGNAL(colorChanged(QColor)), widget, SLOT(setColor5(QColor)));
        QObject::connect(c3, SIGNAL(colorChanged(QColor)), widget, SLOT(setColor3(QColor)));
        QObject::connect(c6, SIGNAL(colorChanged(QColor)), widget, SLOT(setColor6(QColor)));
        QObject::connect(c4, SIGNAL(colorChanged(QColor)), widget, SLOT(setColor4(QColor)));
        QObject::connect(c9, SIGNAL(colorChanged(QColor)), widget, SLOT(setColor9(QColor)));
        QObject::connect(c11, SIGNAL(colorChanged(QColor)), widget, SLOT(setColor11(QColor)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        c0->setText(QString());
        r0->setText(QString());
        c1->setText(QString());
        r1->setText(QString());
        c10->setText(QString());
        r10->setText(QString());
        c8->setText(QString());
        r8->setText(QString());
        c2->setText(QString());
        r2->setText(QString());
        c7->setText(QString());
        r7->setText(QString());
        c5->setText(QString());
        r5->setText(QString());
        c3->setText(QString());
        r3->setText(QString());
        c6->setText(QString());
        r6->setText(QString());
        c4->setText(QString());
        r4->setText(QString());
        c9->setText(QString());
        r9->setText(QString());
        c11->setText(QString());
        r11->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
