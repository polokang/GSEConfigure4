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

    QMap<QString,Point_LDNode*> SUB_GOOSE_LDNode;   //��ѡ��clear()
    QMap<int,Pointdef*> SUB_DATASET;    //ORDINAL //key:iedName%ldInst%prefix%lnClass%lnInst%doName%daName
    QHash<QString,Pointdef*> SUB_DATASETHash;   //key:iedName%ldInst%prefix%lnClass%lnInst%doName%daName    27 �������

    QMap<QString,GCB*> PUB_GOOSE_GCB;   //key:dsGOOSE1  , value:��ʼ����GCBָ�룬����ֻ�� GCB.pointList
    QMap<int,Pointdef*> PUB_DATASET;

    QMap<QString,QDomNode> iedMap;  //scd �ļ��е�ied�б�
    QMap<QString,QDomNode> ldMap;   //scd �ļ��е�
    QDomNode dataTypeTemplates; //scd �ļ�������ģ��
    QDomNode subNetwork; //scd �ļ�������

    QList<GCB*> inputGCBList;   // �������ݼ�

    //����Ӳ���������ݼ�
    QMap<QString,QString> ehcInputMap;   //�����
    QMap<QString,QString> ehcOutputMap;   //������
    About *aboutdialog;
private:
    QMap<int,Pointdef*> getPointList_IN(QString xpath);
    QMap<int,Pointdef*> getPointList_OUT(QString xpath);
    QString getSrcPointDesc(Pointdef* p);   //��Ҫ���ÿ����
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

    void openMUCFG();   //��MU ���ù���
    void generGSE();    //���� gse.xml

    void rightToleft();
    void about();
};

#endif // MAINWINDOW_H
