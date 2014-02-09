/********************************************************************************
** Form generated from reading UI file 'portcf.ui'
**
** Created: Wed Jan 8 16:57:41 2014
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PORTCF_H
#define UI_PORTCF_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_PortCf
{
public:
    QGridLayout *gridLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_10;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PortCf)
    {
        if (PortCf->objectName().isEmpty())
            PortCf->setObjectName(QString::fromUtf8("PortCf"));
        PortCf->resize(400, 300);
        gridLayout = new QGridLayout(PortCf);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkBox = new QCheckBox(PortCf);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        checkBox_6 = new QCheckBox(PortCf);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));

        gridLayout->addWidget(checkBox_6, 0, 1, 1, 1);

        checkBox_2 = new QCheckBox(PortCf);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        gridLayout->addWidget(checkBox_2, 1, 0, 1, 1);

        checkBox_7 = new QCheckBox(PortCf);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));

        gridLayout->addWidget(checkBox_7, 1, 1, 1, 1);

        checkBox_3 = new QCheckBox(PortCf);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        gridLayout->addWidget(checkBox_3, 2, 0, 1, 1);

        checkBox_8 = new QCheckBox(PortCf);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));

        gridLayout->addWidget(checkBox_8, 2, 1, 1, 1);

        checkBox_4 = new QCheckBox(PortCf);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        gridLayout->addWidget(checkBox_4, 3, 0, 1, 1);

        checkBox_9 = new QCheckBox(PortCf);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));

        gridLayout->addWidget(checkBox_9, 3, 1, 1, 1);

        checkBox_5 = new QCheckBox(PortCf);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));

        gridLayout->addWidget(checkBox_5, 4, 0, 1, 1);

        checkBox_10 = new QCheckBox(PortCf);
        checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));

        gridLayout->addWidget(checkBox_10, 4, 1, 1, 1);

        buttonBox = new QDialogButtonBox(PortCf);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 5, 0, 1, 2);


        retranslateUi(PortCf);
        QObject::connect(buttonBox, SIGNAL(accepted()), PortCf, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PortCf, SLOT(reject()));

        QMetaObject::connectSlotsByName(PortCf);
    } // setupUi

    void retranslateUi(QDialog *PortCf)
    {
        PortCf->setWindowTitle(QApplication::translate("PortCf", "Dialog", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("PortCf", "Port 1", 0, QApplication::UnicodeUTF8));
        checkBox_6->setText(QApplication::translate("PortCf", "Port 6", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("PortCf", "Port 2", 0, QApplication::UnicodeUTF8));
        checkBox_7->setText(QApplication::translate("PortCf", "Port 7", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("PortCf", "Port 3", 0, QApplication::UnicodeUTF8));
        checkBox_8->setText(QApplication::translate("PortCf", "Port 8", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("PortCf", "Port 4", 0, QApplication::UnicodeUTF8));
        checkBox_9->setText(QApplication::translate("PortCf", "Port 9", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("PortCf", "Port 5", 0, QApplication::UnicodeUTF8));
        checkBox_10->setText(QApplication::translate("PortCf", "Port 10", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PortCf: public Ui_PortCf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PORTCF_H
