#ifndef GCBCONF_H
#define GCBCONF_H

#include "common.h"
#include "gcbdelegate.h"

namespace Ui {
    class GCBConf;
}

class GCBConf : public QDialog
{
    Q_OBJECT

public:
    explicit GCBConf(QWidget *parent = 0);
    ~GCBConf();

    void contextMenuEvent(QContextMenuEvent * event);
private:
    Ui::GCBConf *ui;
    XMLHelpLib xmlhelplib_gcb;
    XMLHelpLib xmlhelplib_rep;
    Gcbdelegate *delegate;
    PortCf *multiPortcf;
    int curTable;  //0:IUTable ; 1:MUTable

    QMap<QString,GCB*> IUGCBList;
    QMap<QString,GCB*> MUGCBList;

    QList<GCB*> allGCBs_IU;    //所有IU GCB
    QList<GCB*> allGCBs_MU;    //所有MU GCB

    QString gsePath_IU;
    QString gsePath_MU;

    QAction *selectMultiAction;
    QAction *cancelMultiAction;
    QAction *setMultiAction;

    GCB* getGCB(QDomElement gcbELE);
    QStringList getPortsList(QTableWidgetItem *item);
    void genGS(QString xmlPath,QList<GCB*> allSelectedGCBs);
    QList<GCB*> getAllGCBList();
    QList<GCB*> getGCBListByTable(QString tableName);

    void replaceGCBPorts(QString fileName,QString destFolder,QList<GCB*> selectedGCBs);
    QString transInt(int i);
    int PUBMACSUM;    //开出自增MAC地址，填写默认mac 00-1F-16-22-01- 的最后一位
public slots:
    void importIUGSE();
    void importMUGSE();
    void genIUGS();
    void genMUGS();
    void setMultiSelect();
    void selectMultiSelect();
    void cancelMultiSelect();
};

#endif // GCBCONF_H
