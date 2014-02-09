/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Jan 24 10:35:01 2014
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_scd;
    QAction *action_ehc;
    QAction *action_version;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QSplitter *splitter_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_IED;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QComboBox *comboBox_LD;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QLabel *lab_currLD;
    QSplitter *splitter;
    QTabWidget *tab_scd;
    QWidget *tab;
    QGridLayout *gridLayout;
    QTableWidget *table_scd_in;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QTableWidget *table_scd_out;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QToolButton *tb_RtoL;
    QSpacerItem *verticalSpacer_2;
    QTabWidget *tab_ehc;
    QWidget *tab_3;
    QGridLayout *gridLayout_5;
    QListWidget *list_ehc_in;
    QWidget *tab_4;
    QGridLayout *gridLayout_4;
    QListWidget *list_ehc_out;
    QWidget *tab_5;
    QGridLayout *gridLayout_6;
    QListWidget *list_ehc_hdo;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_generateGSE;
    QPushButton *btn_startMUCFG;
    QPushButton *btn_startGCBCF;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 480);
        action_scd = new QAction(MainWindow);
        action_scd->setObjectName(QString::fromUtf8("action_scd"));
        action_ehc = new QAction(MainWindow);
        action_ehc->setObjectName(QString::fromUtf8("action_ehc"));
        action_version = new QAction(MainWindow);
        action_version->setObjectName(QString::fromUtf8("action_version"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        splitter_2 = new QSplitter(centralWidget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox_IED = new QComboBox(layoutWidget);
        comboBox_IED->setObjectName(QString::fromUtf8("comboBox_IED"));
        comboBox_IED->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout->addWidget(comboBox_IED);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox_LD = new QComboBox(layoutWidget);
        comboBox_LD->setObjectName(QString::fromUtf8("comboBox_LD"));
        comboBox_LD->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout->addWidget(comboBox_LD);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        lab_currLD = new QLabel(layoutWidget);
        lab_currLD->setObjectName(QString::fromUtf8("lab_currLD"));

        horizontalLayout->addWidget(lab_currLD);

        splitter_2->addWidget(layoutWidget);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tab_scd = new QTabWidget(splitter);
        tab_scd->setObjectName(QString::fromUtf8("tab_scd"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        table_scd_in = new QTableWidget(tab);
        if (table_scd_in->columnCount() < 3)
            table_scd_in->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table_scd_in->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table_scd_in->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table_scd_in->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        table_scd_in->setObjectName(QString::fromUtf8("table_scd_in"));

        gridLayout->addWidget(table_scd_in, 0, 0, 1, 1);

        tab_scd->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        table_scd_out = new QTableWidget(tab_2);
        if (table_scd_out->columnCount() < 5)
            table_scd_out->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        table_scd_out->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        table_scd_out->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        table_scd_out->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        table_scd_out->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        table_scd_out->setHorizontalHeaderItem(4, __qtablewidgetitem7);
        table_scd_out->setObjectName(QString::fromUtf8("table_scd_out"));

        gridLayout_2->addWidget(table_scd_out, 0, 0, 1, 1);

        tab_scd->addTab(tab_2, QString());
        splitter->addWidget(tab_scd);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tb_RtoL = new QToolButton(layoutWidget1);
        tb_RtoL->setObjectName(QString::fromUtf8("tb_RtoL"));
        tb_RtoL->setMinimumSize(QSize(35, 80));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/leftarrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        tb_RtoL->setIcon(icon);

        verticalLayout->addWidget(tb_RtoL);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        splitter->addWidget(layoutWidget1);
        tab_ehc = new QTabWidget(splitter);
        tab_ehc->setObjectName(QString::fromUtf8("tab_ehc"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_5 = new QGridLayout(tab_3);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        list_ehc_in = new QListWidget(tab_3);
        list_ehc_in->setObjectName(QString::fromUtf8("list_ehc_in"));
        list_ehc_in->setSelectionMode(QAbstractItemView::ExtendedSelection);

        gridLayout_5->addWidget(list_ehc_in, 0, 0, 1, 1);

        tab_ehc->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout_4 = new QGridLayout(tab_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        list_ehc_out = new QListWidget(tab_4);
        list_ehc_out->setObjectName(QString::fromUtf8("list_ehc_out"));
        list_ehc_out->setSelectionMode(QAbstractItemView::ExtendedSelection);

        gridLayout_4->addWidget(list_ehc_out, 0, 0, 1, 1);

        tab_ehc->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_6 = new QGridLayout(tab_5);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        list_ehc_hdo = new QListWidget(tab_5);
        list_ehc_hdo->setObjectName(QString::fromUtf8("list_ehc_hdo"));
        list_ehc_hdo->setSelectionMode(QAbstractItemView::ExtendedSelection);

        gridLayout_6->addWidget(list_ehc_hdo, 0, 0, 1, 1);

        tab_ehc->addTab(tab_5, QString());
        splitter->addWidget(tab_ehc);
        splitter_2->addWidget(splitter);

        gridLayout_3->addWidget(splitter_2, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btn_generateGSE = new QPushButton(centralWidget);
        btn_generateGSE->setObjectName(QString::fromUtf8("btn_generateGSE"));

        horizontalLayout_2->addWidget(btn_generateGSE);

        btn_startMUCFG = new QPushButton(centralWidget);
        btn_startMUCFG->setObjectName(QString::fromUtf8("btn_startMUCFG"));

        horizontalLayout_2->addWidget(btn_startMUCFG);

        btn_startGCBCF = new QPushButton(centralWidget);
        btn_startGCBCF->setObjectName(QString::fromUtf8("btn_startGCBCF"));

        horizontalLayout_2->addWidget(btn_startGCBCF);


        gridLayout_3->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tab_scd->setCurrentIndex(0);
        tab_ehc->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_scd->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245scd\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        action_ehc->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245\347\241\254\344\273\266\351\205\215\347\275\256\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_ehc->setToolTip(QApplication::translate("MainWindow", "\345\257\274\345\205\245\347\241\254\344\273\266\351\205\215\347\275\256\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_version->setText(QApplication::translate("MainWindow", "\350\275\257\344\273\266\350\257\264\346\230\216", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_version->setToolTip(QApplication::translate("MainWindow", "\347\211\210\346\234\254\350\257\264\346\230\216", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251IED\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\351\200\273\350\276\221\350\256\276\345\244\207\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\351\200\273\350\276\221\350\256\276\345\244\207\357\274\232", 0, QApplication::UnicodeUTF8));
        lab_currLD->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = table_scd_in->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = table_scd_in->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\346\217\217\350\277\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = table_scd_in->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\345\205\263\350\201\224\347\202\271", 0, QApplication::UnicodeUTF8));
        tab_scd->setTabText(tab_scd->indexOf(tab), QApplication::translate("MainWindow", "\345\274\200\345\205\245", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = table_scd_out->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = table_scd_out->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "\346\217\217\350\277\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = table_scd_out->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "\345\205\263\350\201\224\347\202\271", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = table_scd_out->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "\345\217\214\347\202\271\344\270\200", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = table_scd_out->horizontalHeaderItem(4);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "\345\217\214\347\202\271\344\272\214", 0, QApplication::UnicodeUTF8));
        tab_scd->setTabText(tab_scd->indexOf(tab_2), QApplication::translate("MainWindow", "\345\274\200\345\207\272", 0, QApplication::UnicodeUTF8));
        tb_RtoL->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        tab_ehc->setTabText(tab_ehc->indexOf(tab_3), QApplication::translate("MainWindow", "GOOSE\345\274\200\345\205\245", 0, QApplication::UnicodeUTF8));
        tab_ehc->setTabText(tab_ehc->indexOf(tab_4), QApplication::translate("MainWindow", "GOOSE\345\274\200\345\207\272", 0, QApplication::UnicodeUTF8));
        tab_ehc->setTabText(tab_ehc->indexOf(tab_5), QApplication::translate("MainWindow", "\345\274\200\345\205\245", 0, QApplication::UnicodeUTF8));
        btn_generateGSE->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\346\231\272\350\203\275\347\273\210\347\253\257\351\205\215\347\275\256\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        btn_startMUCFG->setText(QApplication::translate("MainWindow", "\351\205\215\347\275\256\345\220\210\345\271\266\345\215\225\345\205\203\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        btn_startGCBCF->setText(QApplication::translate("MainWindow", "\351\205\215\347\275\256\347\253\257\345\217\243\346\230\240\345\260\204\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
