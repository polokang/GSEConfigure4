#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gcbconf.h"
#include "common.h"
#include "about.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString scdPath;
private:
    Ui::MainWindow *ui;
    GCBConf gcbCf;
    QString iedName;
    QString ldName;
    QString accessPoint;
    XpathOp* xOP;
    XMLHelpLib xmlhelplib;
    int iedNum;
    QProcess *pro;
    int curIndex_IN;
    int curIndex_OUT;
    int left_doublePos;
    int right_doublePos;

    QMap<QString,Point_LDNode*> SUB_GOOSE_LDNode;   //重选需clear()
    QMap<int,Pointdef*> SUB_DATASET;    //ORDINAL //key:iedName%ldInst%prefix%lnClass%lnInst%doName%daName
    QHash<QString,Pointdef*> SUB_DATASETHash;   //key:iedName%ldInst%prefix%lnClass%lnInst%doName%daName    27 个开入点

    QMap<QString,GCB*> PUB_GOOSE_GCB;   //key:dsGOOSE1  , value:初始化的GCB指针，里面只有 GCB.pointList
    QMap<int,Pointdef*> PUB_DATASET;

    QMap<QString,QDomNode> iedMap;  //scd 文件中的ied列表
    QMap<QString,QDomNode> ldMap;   //scd 文件中的
    QDomNode dataTypeTemplates; //scd 文件的数据模板
    QDomNode subNetwork; //scd 文件的网络

    QList<GCB*> inputGCBList;   // 开入数据集

    //增加硬件配置数据集
    QMap<QString,QString> ehcInputMap;   //开入点
    QMap<QString,QString> ehcOutputMap;   //开出点
    About *aboutdialog;
private:
    QMap<int,Pointdef*> getPointList_IN(QString xpath);
    QMap<int,Pointdef*> getPointList_OUT(QString xpath);
    QString getSrcPointDesc(Pointdef* p);   //主要设置开入点
    QString transInt(int i);
    QString getFCDADesc(QDomElement fcda,QDomElement lnEle);
    QString getbType(QString lnType,QString lnClass,QString doName,QString daName);
    void loadInput();
    void loadOutput();
public slots:
    void openGCBCF();
    void importSCD();
    void importEHC();
    void selectLD(int iedIndex);
    void listAllPoints(int iedIndex);

    void dymicSCDTab(int);
    void dymicEHCTab(int);
    void dymicPoint(QListWidgetItem* item);

    void setcurrTableRow(int,int);

    void openMUCFG();   //打开MU 配置工具
    void generGSE();    //生成 gse.xml

    void rightToleft();
    void about();
};

#endif // MAINWINDOW_H
