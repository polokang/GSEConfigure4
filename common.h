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



//数据点结构类型
struct Pointdef
{
    QString DESC;   //scd文件中的描述
    int ORDINAL;
    QString TYPE;   //DBPOS,BOOL,UTC,QUALITY,FLOAT
    QString DAINDEX;  //自分配的序数

    QString name;   //数据点名称 varchar(1024)
    QString leaf;  //模型文件中的名称
    QString datasetXPath;   //该点所在数据集的 XPath
    QString src_iedName;
    QString src_acc;    //访问点
    QString src_ldInst; //逻辑设备名称
    QString src_dsName; //数据集名称
    QString src_lnClass;
    QString src_lnInst;
    QString src_prefix;
    QString src_doName;
    QString src_daName;
    QString src_desc;
    QString src_fc;

    QString desc_ehc;   //硬件配置文件中的描述

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
        t0 = 5000;  //单位毫秒
        t1 = 2;     //单位毫秒
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

    int gcbType;    //0:SUB 开入；    1:PUB 开出
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
