#ifndef COMMON_H
#define COMMON_H

#include <QtCore>
#include <QDomNode>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QMenu>
#include <QDropEvent>
#include <QDragEnterEvent>
#include "xpathop.h"
#include "xmlhelplib.h"
#include "hio.h"



//���ݵ�ṹ����
struct Pointdef
{
    QString DESC;   //scd�ļ��е�����
    int ORDINAL;
    QString TYPE;   //DBPOS,BOOL,UTC,QUALITY,FLOAT
    QString DAINDEX;  //�Է��������

    QString name;   //���ݵ����� varchar(1024)
    QString leaf;  //ģ���ļ��е�����
    QString datasetXPath;   //�õ��������ݼ��� XPath
    QString src_iedName;
    QString src_acc;    //���ʵ�
    QString src_ldInst; //�߼��豸����
    QString src_dsName; //���ݼ�����
    QString src_lnClass;
    QString src_lnInst;
    QString src_prefix;
    QString src_doName;
    QString src_daName;
    QString src_desc;
    QString src_fc;

    QString desc_ehc;   //Ӳ�������ļ��е�����

    bool haveQ;
    bool haveT;
    int TSRCDI1;
    int TSRCDI2;
    Pointdef()
    {
        haveQ = false;
        haveT = false;
        TSRCDI1 = 0;
        TSRCDI2 = 0;
    }

};

struct Address
{
    QStringList ports;
    QStringList transports;
    QString VID;
    QString DST_MAC;
    QString SRC_MAC;
    int t0;
    int t1;
    Address()
    {
        t0 = 5000;  //��λ����
        t1 = 2;     //��λ����
    }
};

struct GCB
{
    QString GoID;
    QString Priority_G;
    QString GcRef;
    QString ConfRev;
    QString DatasetRef;
    QString AppID;
    QString IEDName;
    int T0;
    int T1;
    Address* addrList;
    QList<Pointdef*> pointList;

    int gcbType;    //0:SUB ���룻    1:PUB ����
};

struct Point_LDNode
{
    Pointdef* p;
    QDomNode ldNode;
};

class Common
{
public:
    Common();
};

#endif // COMMON_H
