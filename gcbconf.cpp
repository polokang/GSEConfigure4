#include "gcbconf.h"
#include "ui_gcbconf.h"

GCBConf::GCBConf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GCBConf)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Widget);

    delegate = new Gcbdelegate(this);
    multiPortcf = new PortCf(this);
    setMultiAction = new QAction(tr("Set Multi Ports"),this);

    selectMultiAction = new QAction(tr("Select all"),this);
    cancelMultiAction = new QAction(tr("Cancel all"),this);
    curTable = 0;
    PUBMACSUM = 1;

    connect(ui->impIU_btn,SIGNAL(clicked()),this,SLOT(importIUGSE()));
    connect(ui->impMU_btn,SIGNAL(clicked()),this,SLOT(importMUGSE()));
    connect(ui->btn_genIUGS,SIGNAL(clicked()),this,SLOT(genIUGS()));
    connect(ui->btn_genMUGS,SIGNAL(clicked()),this,SLOT(genMUGS()));
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SLOT(close()));

    connect(setMultiAction,SIGNAL(triggered()),this,SLOT(setMultiSelect()));
    connect(selectMultiAction,SIGNAL(triggered()),this,SLOT(selectMultiSelect()));
    connect(cancelMultiAction,SIGNAL(triggered()),this,SLOT(cancelMultiSelect()));
}

void GCBConf::selectMultiSelect()
{
    QList<QTableWidgetItem*> items;
    if(curTable == 0)   //IU_Table
    {
        items = ui->table_IU->selectedItems();
    }
    else
    {
        items = ui->table_MU->selectedItems();
    }

    foreach (QTableWidgetItem* item, items)
    {
        item->setCheckState(Qt::Checked);
    }
}

void GCBConf::cancelMultiSelect()
{
    QList<QTableWidgetItem*> items;
    if(curTable == 0)   //IU_Table
    {
        items = ui->table_IU->selectedItems();
    }
    else
    {
        items = ui->table_MU->selectedItems();
    }

    foreach (QTableWidgetItem* item, items)
    {
        item->setCheckState(Qt::Unchecked);
    }
}

void GCBConf::setMultiSelect()
{
    multiPortcf->resetPort("");
    if(multiPortcf->exec() == QDialog::Accepted)
    {
        QString portsStr = multiPortcf->getPortsID();
        QList<QTableWidgetItem*> items;
        if(curTable == 0)   //IU_Table
        {
            items = ui->table_IU->selectedItems();
        }
        else
        {
            items = ui->table_MU->selectedItems();
        }

        foreach (QTableWidgetItem* item, items)
        {
            item->setText(portsStr);
        }
    }
}

void GCBConf::contextMenuEvent (QContextMenuEvent *event )
{
    QTableWidget *table = ui->table_IU;

    QWidget *w_MU = ui->table_MU->viewport();
    QPoint p_MU = w_MU->mapFromGlobal(QCursor::pos());
    if(ui->table_MU->itemAt(p_MU) != NULL)
    {
        table = ui->table_MU;
        curTable = 1;
    }
    else
    {
        curTable = 0;
    }

    QTableWidgetItem *curItem = table->currentItem();
    int colNum = curItem->column();
    QMenu* popMenu = new QMenu(this);
    if(colNum == 3 || colNum == 4)
    {
        popMenu->addAction(setMultiAction);
        popMenu->exec(QCursor::pos());
    }
    else if(colNum == 0)
    {
        popMenu->addAction(selectMultiAction);
        popMenu->addAction(cancelMultiAction);
        popMenu->exec(QCursor::pos());
    }
    else
    {
        popMenu->removeAction(setMultiAction);
        popMenu->removeAction(selectMultiAction);
        popMenu->removeAction(cancelMultiAction);
    }
}

void GCBConf::replaceGCBPorts(QString fileName,QString destFolder,QList<GCB*> selectedGCBs)
{
    if(xmlhelplib_rep.loadXML(fileName) == -1)
    {
        return;
    }

    QList<QDomNode> subNodeList = xmlhelplib_rep.selectNodesList("DATAINFO/SUB_GOOSE");
    QList<QDomNode> pubNodeList = xmlhelplib_rep.selectNodesList("DATAINFO/PUB_GOOSE");
    QDomNode subNode;
    QDomNode pubNode;
    if(subNodeList.size()>0)
    {
        subNode = subNodeList.at(0);
    }
    if(pubNodeList.size()>0)
    {
        pubNode = pubNodeList.at(0);
    }

    foreach (GCB* gcb, selectedGCBs)
    {
        QDomNode srcGCBNode;
        if(gcb->gcbType == 0)
        {
            srcGCBNode = xmlhelplib_rep.getChildNode(subNode,QString("GCB[@AppID=%1]").arg(gcb->AppID));
        }
        else
        {
            srcGCBNode = xmlhelplib_rep.getChildNode(pubNode,QString("GCB[@AppID=%1]").arg(gcb->AppID));
        }

        if(!srcGCBNode.isNull())
        {
            QDomDocument doc = xmlhelplib_rep.document;
            QDomElement newNetNode = doc.createElement("NET");
            QStringList ports = gcb->addrList->ports;
//            QStringList transPorts = gcb->addrList->transports;
            foreach (QString port, ports) {
                QDomElement tag_Address = doc.createElement("Address");
                QDomElement tag_PORT = doc.createElement("PORT");
                QDomText txt_PORT = doc.createTextNode(port);
                tag_PORT.appendChild(txt_PORT);
                tag_Address.appendChild(tag_PORT);
                if(gcb->gcbType == 1)   //开出
                {
                    QDomElement tag_VID = doc.createElement("VID");
                    QDomText txt_VID = doc.createTextNode(gcb->addrList->VID);
                    tag_VID.appendChild(txt_VID);
                    tag_Address.appendChild(tag_VID);
                }
                QDomElement tag_DST_MAC = doc.createElement("DST_MAC");
                QDomText txt_DST_MAC = doc.createTextNode(gcb->addrList->DST_MAC);                
                tag_DST_MAC.appendChild(txt_DST_MAC);

                tag_Address.appendChild(tag_DST_MAC);

                if(gcb->gcbType == 1)   //开出
                {
                    QDomElement tag_SRC_MAC = doc.createElement("SRC_MAC");
                    QDomText txt_SRC_MAC = doc.createTextNode(gcb->addrList->SRC_MAC);
                    tag_SRC_MAC.appendChild(txt_SRC_MAC);
                    tag_Address.appendChild(tag_SRC_MAC);
                }
                newNetNode.appendChild(tag_Address);
            }

//            foreach (QString port, transPorts)
//            {
//                if(port != "")
//                {
//                    QDomElement tag_Address = doc.createElement("DST_Address");
//                    QDomElement tag_PORT = doc.createElement("PORT");
//                    QDomText txt_PORT = doc.createTextNode(port);
//                    tag_PORT.appendChild(txt_PORT);
//                    tag_Address.appendChild(tag_PORT);
//                    newNetNode.appendChild(tag_Address);
//                }
//            }

            QDomNode oldNode = srcGCBNode.firstChild();
            srcGCBNode.replaceChild(newNetNode,oldNode);
        }
    }

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    QTextStream out(&file);
    out.setCodec("GB2312");
    xmlhelplib_rep.document.save(out,4,QDomNode::EncodingFromTextStream);

    QFile destfile(destFolder);
    destfile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    QTextStream destout(&destfile);
    destout.setCodec("GB2312");
    xmlhelplib_rep.document.save(destout,4,QDomNode::EncodingFromTextStream);
}


QString GCBConf::transInt(int i)
{
    QString str = "00";
    QString strInt = QString::number(i,16).toUpper();
    if(strInt.size() == 2)
    {
        return strInt;
    }
    else
    {
        return "0"+strInt;
    }

    return str;
}

//获取已选择的 GCB ，并设置所有 GCB List(allGCBs_IU 或 allGCBs_MU)
QList<GCB*> GCBConf::getAllGCBList()
{
    QList<GCB*> allList;
    QList<GCB*> selectedGCBs_IU = getGCBListByTable("IU");
    QList<GCB*> selectedGCBs_MU = getGCBListByTable("MU");

    allList.append(selectedGCBs_IU);
    allList.append(selectedGCBs_MU);
    return allList;
}



//1.获取所有的 GCB，并放入 allGCBs_IU 或 allGCBs_MU
//2.返回已选择的 GCB
QList<GCB*> GCBConf::getGCBListByTable(QString tableName)
{
    QList<GCB*> gcbList;
    QTableWidget *table = NULL;
    if(tableName == "IU")
    {
        allGCBs_IU.clear();
        table = ui->table_IU;
    }
    else
    {
        allGCBs_MU.clear();
        table = ui->table_MU;
    }

    for(int i=0;i<table->rowCount();i++)
    {
        QString name = table->item(i,1)->text();
        QString mac = table->item(i,2)->text();
        QStringList ports = getPortsList(table->item(i,3));
        QStringList transPorts = getPortsList(table->item(i,4));
        QString src_mac = table->item(i,5)->text();
        GCB* gcb = NULL;
        if(tableName == "IU")
        {
            gcb = IUGCBList.value(name);
        }
        else
        {
            gcb = MUGCBList.value(name);
        }
        gcb->addrList->DST_MAC = mac;
        gcb->addrList->ports = ports;
        gcb->addrList->transports = transPorts;
        gcb->addrList->SRC_MAC = src_mac;
        if(tableName == "IU")
        {
            allGCBs_IU.append(gcb);
        }
        else
        {
            allGCBs_MU.append(gcb);
        }

        if(table->item(i,0)->checkState() == Qt::Checked)
        {
            gcbList.append(gcb);
        }
    }
    return gcbList;
}



void GCBConf::genIUGS()
{
    QList<GCB*> allSelectedGCBs = getAllGCBList();
    genGS("../conf/IU/tffs",allSelectedGCBs);
    replaceGCBPorts(gsePath_IU,"../conf/IU/cid/gse.xml",allGCBs_IU);
    QMessageBox::information(NULL, tr("Information"), tr("gs.xml of IU generate success."),tr("Ok"));
}



void GCBConf::genMUGS()
{
    QList<GCB*> allSelectedGCBs = getAllGCBList();
    genGS("../conf/MU/tffs",allSelectedGCBs);
    replaceGCBPorts(gsePath_MU,"../conf/MU/cid/gse.xml",allGCBs_MU);
    QMessageBox::information(NULL, tr("Information"), tr("gs.xml of MU generate success."),tr("Ok"));
}


void GCBConf::genGS(QString xmlPath,QList<GCB*> allSelectedGCBs)
{
    QDomDocument doc;
    QDomElement root = doc.createElement("Config");
    doc.appendChild(root);
    root.setAttribute("VERSION","4.0");
    root.setAttribute("PROJECTNAME","测试用例");
    QDomElement tag_DATAINFO = doc.createElement("DATAINFO");
    root.appendChild(tag_DATAINFO);
    QDomElement tag_SUB_GOOSE = doc.createElement("SUB_GOOSE");
    tag_DATAINFO.appendChild(tag_SUB_GOOSE);

    foreach (GCB* gcb, allSelectedGCBs)
    {
        Address* addr = gcb->addrList;
        QString mac = addr->DST_MAC;
        QStringList ports = addr->ports;
        QStringList transPorts = addr->transports;

        QDomElement tag_GCB = doc.createElement("GCB");
        tag_GCB.setAttribute("GoID",gcb->GoID);
        tag_GCB.setAttribute("GcRef",gcb->GcRef);
        tag_GCB.setAttribute("ConfRev",gcb->ConfRev);
        tag_GCB.setAttribute("DatasetRef",gcb->DatasetRef);
        tag_GCB.setAttribute("AppID",gcb->AppID);
        tag_GCB.setAttribute("IEDName",gcb->IEDName);

        QDomElement tag_NET = doc.createElement("NET");
        tag_GCB.appendChild(tag_NET);
        foreach (QString port, ports) {
            QDomElement tag_Address = doc.createElement("Address");
            QDomElement tag_PORT = doc.createElement("PORT");
            QDomText txt_PORT = doc.createTextNode(port);
            tag_PORT.appendChild(txt_PORT);
            QDomElement tag_DST_MAC = doc.createElement("DST_MAC");
            QDomText txt_DST_MAC = doc.createTextNode(mac);
            tag_DST_MAC.appendChild(txt_DST_MAC);
            tag_Address.appendChild(tag_PORT);
            tag_Address.appendChild(tag_DST_MAC);
            tag_NET.appendChild(tag_Address);
        }

        foreach (QString port, transPorts)
        {
            if(port != "")
            {
                QDomElement tag_Address = doc.createElement("DST_Address");
                QDomElement tag_PORT = doc.createElement("PORT");
                QDomText txt_PORT = doc.createTextNode(port);
                tag_PORT.appendChild(txt_PORT);
                tag_Address.appendChild(tag_PORT);
                tag_NET.appendChild(tag_Address);
            }
        }

        tag_SUB_GOOSE.appendChild(tag_GCB);
    }

    //*********生成XML
    QString gseSavePath = QString("%1/gs.xml").arg(xmlPath);
    QFile file(gseSavePath);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    QTextStream out(&file);
    out.setCodec("GB2312");
    doc.save(out,4,QDomNode::EncodingFromTextStream);
    file.close();
}


GCB* GCBConf::getGCB(QDomElement gcbELE)
{
    GCB* gcb = new GCB;

    gcb->GoID = gcbELE.attribute("GoID");
    gcb->GcRef = gcbELE.attribute("GcRef");
    gcb->ConfRev = gcbELE.attribute("ConfRev");
    gcb->DatasetRef = gcbELE.attribute("DatasetRef");
    gcb->AppID = gcbELE.attribute("AppID");
    gcb->IEDName = gcbELE.attribute("IEDName");

    return gcb;
}


QStringList GCBConf::getPortsList(QTableWidgetItem *item)
{
    if(item == NULL)
    {
        return QStringList("");
    }

    QString ports = item->text();
    QStringList portsList = ports.split("|");

    return portsList;
}


void GCBConf::importIUGSE()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open gse.xml"), "." , tr("XML files (*.xml)"));
    if(path.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."),tr("Ok"));
    }
    else
    {
        PUBMACSUM = 1;
        //**********
        xmlhelplib_gcb.document.clear();
        ui->table_IU->clearContents();
        IUGCBList.clear();

        xmlhelplib_gcb.loadXML(path);
        gsePath_IU = path;

        int row = 0;
        QList<QDomNode> gcbSubList = xmlhelplib_gcb.selectNodesList("DATAINFO/SUB_GOOSE/GCB");
        QList<QDomNode> gcbPubList = xmlhelplib_gcb.selectNodesList("DATAINFO/PUB_GOOSE/GCB");
        ui->table_IU->setRowCount(gcbSubList.size()+gcbPubList.size());
        for(int i=0;i<gcbSubList.size();i++)
        {
            QDomNode gcbNode = gcbSubList.at(i);
            QDomElement gcbELE = gcbNode.toElement();
            GCB* gcb = getGCB(gcbELE);

            QString name = gcb->GcRef;
            QTableWidgetItem* checkItem = new QTableWidgetItem("");
            checkItem->setCheckState(Qt::Unchecked);
            ui->table_IU->setItem(row,0,checkItem);
            QTableWidgetItem *nameItem = new QTableWidgetItem(name);
            ui->table_IU->setItem(row,1,nameItem);
            nameItem->setFlags(Qt::NoItemFlags);

            QDomElement netEle = xmlhelplib_gcb.getChildNode(gcbNode,"NET/Address/DST_MAC").toElement();
            QString netDST_MAC = netEle.text();
            QTableWidgetItem *netItem = new QTableWidgetItem(netDST_MAC);
            netItem->setFlags(Qt::NoItemFlags);
            ui->table_IU->setItem(row,2,netItem);

            Address* addr = new Address;
            addr->DST_MAC = netDST_MAC;
            QString port = "";
            QList<QDomNode> addrList = xmlhelplib_gcb.getChildNodes(gcbNode,"NET/Address");
            foreach (QDomNode addrNode, addrList) {
                QDomElement portEle = xmlhelplib_gcb.getChildNode(addrNode,"PORT").toElement();
                port = port + "|" + portEle.text();
                addr->ports.append(port);
            }
            if(port.startsWith("|"))
            {
                port = port.right(port.size()-1);
            }
            QTableWidgetItem *portItem = new QTableWidgetItem(port);
            ui->table_IU->setItem(row,3,portItem);
            QTableWidgetItem *transportItem = new QTableWidgetItem("");
            ui->table_IU->setItem(row,4,transportItem);
            QTableWidgetItem *srcMacItem = new QTableWidgetItem("");
            srcMacItem->setFlags(Qt::NoItemFlags);
            ui->table_IU->setItem(row,5,srcMacItem);

            gcb->addrList = addr;
            gcb->gcbType = 0;   //开入量
            IUGCBList.insert(name,gcb);
            row++;
        }

        for(int i=0;i<gcbPubList.size();i++)
        {
            QDomNode gcbNode = gcbPubList.at(i);
            QDomElement gcbELE = gcbNode.toElement();
            GCB* gcb = getGCB(gcbELE);

            QString name = gcb->GcRef;
            QTableWidgetItem* checkItem = new QTableWidgetItem("");
            checkItem->setCheckState(Qt::Unchecked);
            ui->table_IU->setItem(row,0,checkItem);
            QTableWidgetItem *nameItem = new QTableWidgetItem(name);
            ui->table_IU->setItem(row,1,nameItem);
            nameItem->setFlags(Qt::NoItemFlags);
            nameItem->setBackground(QBrush(QColor(Qt::green)));

            QDomElement netEle = xmlhelplib_gcb.getChildNode(gcbNode,"NET/Address/DST_MAC").toElement();
            QString netDST_MAC = netEle.text();
            QTableWidgetItem *netItem = new QTableWidgetItem(netDST_MAC);
            netItem->setBackground(QBrush(QColor(Qt::green)));
            netItem->setFlags(Qt::NoItemFlags);
            ui->table_IU->setItem(row,2,netItem);

            Address* addr = new Address;
            addr->DST_MAC = netDST_MAC;
            QString port = "";
            QList<QDomNode> addrList = xmlhelplib_gcb.getChildNodes(gcbNode,"NET/Address");
            foreach (QDomNode addrNode, addrList) {
                QDomElement portEle = xmlhelplib_gcb.getChildNode(addrNode,"PORT").toElement();                
                port = port + "|" + portEle.text();
                addr->ports.append(port);
                QDomElement vidEle = xmlhelplib_gcb.getChildNode(addrNode,"VID").toElement();
                addr->VID = vidEle.text();
            }
            if(port.startsWith("|"))
            {
                port = port.right(port.size()-1);
            }
            QTableWidgetItem *portItem = new QTableWidgetItem(port);
            ui->table_IU->setItem(row,3,portItem);

            QTableWidgetItem *transportItem = new QTableWidgetItem("");
            ui->table_IU->setItem(row,4,transportItem);

            QTableWidgetItem *srcMacItem = new QTableWidgetItem("00-1F-16-22-01-"+transInt(PUBMACSUM++));
            ui->table_IU->setItem(row,5,srcMacItem);

            gcb->addrList = addr;
            gcb->gcbType = 1;//开出量
            IUGCBList.insert(name,gcb);
            row++;
        }

        ui->table_IU->resizeColumnsToContents();

        ui->table_IU->setItemDelegate(delegate);
    }
}


void GCBConf::importMUGSE()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open gse.xml"), "." , tr("XML files (*.xml)"));
    if(path.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."),tr("Ok"));
    }
    else
    {
        xmlhelplib_gcb.document.clear();
        ui->table_MU->clearContents();
        MUGCBList.clear();

        xmlhelplib_gcb.loadXML(path);
        gsePath_MU = path;

        int row = 0;
        QList<QDomNode> gcbSubList = xmlhelplib_gcb.selectNodesList("DATAINFO/SUB_GOOSE/GCB");
        QList<QDomNode> gcbPubList = xmlhelplib_gcb.selectNodesList("DATAINFO/PUB_GOOSE/GCB");
        ui->table_MU->setRowCount(gcbSubList.size()+gcbPubList.size());
        for(int i=0;i<gcbSubList.size();i++)
        {            
            QDomNode gcbNode = gcbSubList.at(i);
            QDomElement gcbELE = gcbNode.toElement();
            GCB* gcb = getGCB(gcbELE);

            QString name = gcb->GcRef;
            QTableWidgetItem* checkItem = new QTableWidgetItem("");
            checkItem->setCheckState(Qt::Unchecked);
            ui->table_MU->setItem(row,0,checkItem);
            QTableWidgetItem *nameItem = new QTableWidgetItem(name);
            ui->table_MU->setItem(row,1,nameItem);
            nameItem->setFlags(Qt::NoItemFlags);

            QDomElement netEle = xmlhelplib_gcb.getChildNode(gcbNode,"NET/Address/DST_MAC").toElement();
            QString netDST_MAC = netEle.text();
            QTableWidgetItem *netItem = new QTableWidgetItem(netDST_MAC);
            netItem->setFlags(Qt::NoItemFlags);
            ui->table_MU->setItem(row,2,netItem);

            Address* addr = new Address;
            addr->DST_MAC = netDST_MAC;
            QString port = "";
            QList<QDomNode> addrList = xmlhelplib_gcb.getChildNodes(gcbNode,"NET/Address");
            foreach (QDomNode addrNode, addrList) {
                QDomElement portEle = xmlhelplib_gcb.getChildNode(addrNode,"PORT").toElement();
                port = port + "|" + portEle.text();
                addr->ports.append(port);
            }
            if(port.startsWith("|"))
            {
                port = port.right(port.size()-1);
            }
            QTableWidgetItem *portItem = new QTableWidgetItem(port);
            ui->table_MU->setItem(row,3,portItem);
            QTableWidgetItem *transportItem = new QTableWidgetItem("");
            ui->table_MU->setItem(row,4,transportItem);
            QTableWidgetItem *srcMacItem = new QTableWidgetItem("");
            srcMacItem->setFlags(Qt::NoItemFlags);
            ui->table_MU->setItem(row,5,srcMacItem);

            gcb->addrList = addr;
            gcb->gcbType = 0;//开入量
            MUGCBList.insert(name,gcb);
            row++;
        }

        for(int i=0;i<gcbPubList.size();i++)
        {
            QDomNode gcbNode = gcbPubList.at(i);
            QDomElement gcbELE = gcbNode.toElement();
            GCB* gcb = getGCB(gcbELE);

            QString name = gcb->GcRef;
            QTableWidgetItem* checkItem = new QTableWidgetItem("");
            checkItem->setCheckState(Qt::Unchecked);
            ui->table_MU->setItem(row,0,checkItem);
            QTableWidgetItem *nameItem = new QTableWidgetItem(name);
            ui->table_MU->setItem(row,1,nameItem);
            nameItem->setFlags(Qt::NoItemFlags);
            nameItem->setBackground(QBrush(QColor(Qt::green)));

            QDomElement netEle = xmlhelplib_gcb.getChildNode(gcbNode,"NET/Address/DST_MAC").toElement();
            QString netDST_MAC = netEle.text();
            QTableWidgetItem *netItem = new QTableWidgetItem(netDST_MAC);
            netItem->setBackground(QBrush(QColor(Qt::green)));
            netItem->setFlags(Qt::NoItemFlags);
            ui->table_MU->setItem(row,2,netItem);

            Address* addr = new Address;
            addr->DST_MAC = netDST_MAC;
            QString port = "";
            QList<QDomNode> addrList = xmlhelplib_gcb.getChildNodes(gcbNode,"NET/Address");
            foreach (QDomNode addrNode, addrList) {
                QDomElement portEle = xmlhelplib_gcb.getChildNode(addrNode,"PORT").toElement();
                port = port + "|" + portEle.text();
                addr->ports.append(port);
                QDomElement vidEle = xmlhelplib_gcb.getChildNode(addrNode,"VID").toElement();
                addr->VID = vidEle.text();
            }
            if(port.startsWith("|"))
            {
                port = port.right(port.size()-1);
            }
            QTableWidgetItem *portItem = new QTableWidgetItem(port);
            ui->table_MU->setItem(row,3,portItem);
            QTableWidgetItem *transportItem = new QTableWidgetItem("");
            ui->table_MU->setItem(row,4,transportItem);

            QTableWidgetItem *srcMacItem = new QTableWidgetItem("00-1F-16-22-01-"+transInt(PUBMACSUM++));
            ui->table_MU->setItem(row,5,srcMacItem);

            gcb->addrList = addr;
            gcb->gcbType = 1; //开出量
            MUGCBList.insert(name,gcb);
            row++;
        }

        ui->table_MU->resizeColumnsToContents();

        ui->table_MU->setItemDelegate(delegate);
    }
}



GCBConf::~GCBConf()
{
    delete ui;
}
