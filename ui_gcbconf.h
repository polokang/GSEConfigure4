/********************************************************************************
** Form generated from reading UI file 'gcbconf.ui'
**
** Created: Wed Jan 8 16:57:41 2014
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GCBCONF_H
#define UI_GCBCONF_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GCBConf
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *impIU_btn;
    QSpacerItem *horizontalSpacer;
    QTableWidget *table_IU;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *impMU_btn;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *table_MU;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btn_genIUGS;
    QPushButton *btn_genMUGS;
    QPushButton *btn_cancel;

    void setupUi(QDialog *GCBConf)
    {
        if (GCBConf->objectName().isEmpty())
            GCBConf->setObjectName(QString::fromUtf8("GCBConf"));
        GCBConf->resize(671, 494);
        gridLayout = new QGridLayout(GCBConf);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(GCBConf);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        impIU_btn = new QPushButton(layoutWidget);
        impIU_btn->setObjectName(QString::fromUtf8("impIU_btn"));

        horizontalLayout->addWidget(impIU_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        table_IU = new QTableWidget(layoutWidget);
        if (table_IU->columnCount() < 6)
            table_IU->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table_IU->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table_IU->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table_IU->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        table_IU->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        table_IU->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        table_IU->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        table_IU->setObjectName(QString::fromUtf8("table_IU"));
        table_IU->setSelectionBehavior(QAbstractItemView::SelectItems);

        verticalLayout->addWidget(table_IU);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        impMU_btn = new QPushButton(layoutWidget1);
        impMU_btn->setObjectName(QString::fromUtf8("impMU_btn"));

        horizontalLayout_2->addWidget(impMU_btn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        table_MU = new QTableWidget(layoutWidget1);
        if (table_MU->columnCount() < 6)
            table_MU->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        table_MU->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        table_MU->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        table_MU->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        table_MU->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        table_MU->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        table_MU->setHorizontalHeaderItem(5, __qtablewidgetitem11);
        table_MU->setObjectName(QString::fromUtf8("table_MU"));

        verticalLayout_2->addWidget(table_MU);

        splitter->addWidget(layoutWidget1);

        gridLayout->addWidget(splitter, 0, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btn_genIUGS = new QPushButton(GCBConf);
        btn_genIUGS->setObjectName(QString::fromUtf8("btn_genIUGS"));

        horizontalLayout_3->addWidget(btn_genIUGS);

        btn_genMUGS = new QPushButton(GCBConf);
        btn_genMUGS->setObjectName(QString::fromUtf8("btn_genMUGS"));

        horizontalLayout_3->addWidget(btn_genMUGS);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        btn_cancel = new QPushButton(GCBConf);
        btn_cancel->setObjectName(QString::fromUtf8("btn_cancel"));

        gridLayout->addWidget(btn_cancel, 1, 1, 1, 1);


        retranslateUi(GCBConf);

        QMetaObject::connectSlotsByName(GCBConf);
    } // setupUi

    void retranslateUi(QDialog *GCBConf)
    {
        GCBConf->setWindowTitle(QApplication::translate("GCBConf", "\351\205\215\347\275\256\347\253\257\345\217\243\346\230\240\345\260\204\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        impIU_btn->setText(QApplication::translate("GCBConf", "\345\257\274\345\205\245\346\231\272\350\203\275\350\256\276\345\244\207\351\205\215\347\275\256\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = table_IU->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("GCBConf", "\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = table_IU->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("GCBConf", "\346\225\260\346\215\256\351\233\206\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = table_IU->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("GCBConf", "\347\233\256\346\240\207\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = table_IU->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("GCBConf", "    \347\253\257\345\217\243    ", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = table_IU->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("GCBConf", "\350\275\254\345\217\221\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = table_IU->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("GCBConf", "\346\272\220\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        impMU_btn->setText(QApplication::translate("GCBConf", "\345\257\274\345\205\245\345\220\210\345\271\266\345\215\225\345\205\203\351\205\215\347\275\256\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = table_MU->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("GCBConf", "\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = table_MU->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("GCBConf", "\346\225\260\346\215\256\351\233\206\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = table_MU->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("GCBConf", "\347\233\256\346\240\207\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = table_MU->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QApplication::translate("GCBConf", "    \347\253\257\345\217\243    ", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = table_MU->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QApplication::translate("GCBConf", "\350\275\254\345\217\221\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = table_MU->horizontalHeaderItem(5);
        ___qtablewidgetitem11->setText(QApplication::translate("GCBConf", "\346\272\220\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        btn_genIUGS->setText(QApplication::translate("GCBConf", "\347\224\237\346\210\220\346\231\272\350\203\275\347\273\210\347\253\257gs.xml", 0, QApplication::UnicodeUTF8));
        btn_genMUGS->setText(QApplication::translate("GCBConf", "\347\224\237\346\210\220\345\220\210\345\271\266\345\215\225\345\205\203gs.xml", 0, QApplication::UnicodeUTF8));
        btn_cancel->setText(QApplication::translate("GCBConf", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GCBConf: public Ui_GCBConf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GCBCONF_H
