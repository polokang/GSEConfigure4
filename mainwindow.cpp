#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 6);
    ui->splitter->setStretchFactor(1, 1);
    ui->splitter->setStretchFactor(2, 3);

//    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    ui->mainToolBar->addAction(ui->action_scd);
    ui->mainToolBar->addAction(ui->action_ehc);
    ui->mainToolBar->addAction(ui->action_version);

    connect(ui->action_scd,SIGNAL(triggered()),this,SLOT(importSCD()));
    connect(ui->action_ehc,SIGNAL(triggered()),this,SLOT(importEHC()));
    connect(ui->btn_startMUCFG,SIGNAL(clicked()),this,SLOT(openMUCFG()));
    connect(ui->btn_generateGSE,SIGNAL(clicked()),this,SLOT(generGSE()));
    connect(ui->btn_startGCBCF,SIGNAL(clicked()),this,SLOT(openGCBCF()));

    connect(ui->tab_scd,SIGNAL(currentChanged(int)),this,SLOT(dymicEHCTab(int)));
    connect(ui->tab_ehc,SIGNAL(currentChanged(int)),this,SLOT(dymicSCDTab(int)));

    connect(ui->tb_RtoL,SIGNAL(clicked()),this,SLOT(rightToleft()));
    connect(ui->action_version,SIGNAL(triggered()),this,SLOT(about()));

    curIndex_IN = 0;
    curIndex_OUT = 0;
    left_doublePos = 0;
    right_doublePos = 0;

    pro = new QProcess;
}

void MainWindow::about()
{
    aboutdialog=new About;
    aboutdialog->setModal(true);
    //设置标题栏具有关闭按钮
    Qt::WindowFlags flags=Qt::Dialog;
    flags =  Qt::WindowCloseButtonHint;
    aboutdialog->setWindowFlags(flags);
    aboutdialog->show();
}

void MainWindow::rightToleft()
{
    QListWidget *listWidget = ui->list_ehc_in;
    if(ui->tab_ehc->currentIndex() == 1)
    {
        listWidget = ui->list_ehc_out;
    }
    else if(ui->tab_ehc->currentIndex() == 2)
    {
        listWidget = ui->list_ehc_hdo;
    }

    QList<QListWidgetItem*> items = listWidget->selectedItems();
    foreach (QListWidgetItem* item, items)
    {
        dymicPoint(item);
    }
}


void MainWindow::openGCBCF()
{
    gcbCf.exec();
}

void MainWindow::generGSE()
{
    loadInput();
    loadOutput();

    QDomDocument doc;
    QDomElement root = doc.createElement("Config");
    doc.appendChild(root);
    root.setAttribute("VERSION","4.0");
    root.setAttribute("PROJECTNAME","操作箱-三相");

    QDomElement tag_DATAINFO = doc.createElement("DATAINFO");
    root.appendChild(tag_DATAINFO);
    QDomElement tag_SUB_GOOSE = doc.createElement("SUB_GOOSE");
    tag_DATAINFO.appendChild(tag_SUB_GOOSE);
    //1.SUB_GOOSE*********
    foreach (GCB* gcb, inputGCBList)
    {
        QDomElement tag_GCB = doc.createElement("GCB");
        tag_GCB.setAttribute("GoID",gcb->GoID);
        tag_GCB.setAttribute("GcRef",gcb->GcRef);
        tag_GCB.setAttribute("ConfRev",gcb->ConfRev);
        tag_GCB.setAttribute("DatasetRef",gcb->DatasetRef);
        tag_GCB.setAttribute("AppID",gcb->AppID);
        tag_GCB.setAttribute("IEDName",gcb->IEDName);

        QDomElement tag_NET = doc.createElement("NET");
        QDomElement tag_Address = doc.createElement("Address");
        QDomElement tag_PORT = doc.createElement("PORT");
        QDomText txt_PORT = doc.createTextNode("0");
        tag_PORT.appendChild(txt_PORT);
        QDomElement tag_DST_MAC = doc.createElement("DST_MAC");
        QDomText txt_DST_MAC = doc.createTextNode(gcb->addrList->DST_MAC);
        tag_DST_MAC.appendChild(txt_DST_MAC);
        tag_Address.appendChild(tag_PORT);
        tag_Address.appendChild(tag_DST_MAC);
        tag_NET.appendChild(tag_Address);
        tag_GCB.appendChild(tag_NET);
        QDomElement tag_DATASET = doc.createElement("DATASET");
        tag_GCB.appendChild(tag_DATASET);
        for(int i=0;i<gcb->pointList.size();i++)
        {
            Pointdef *p = gcb->pointList.at(i);
            QDomElement tag_FCDA = doc.createElement("FCDA");
            tag_FCDA.setAttribute("INDEX",QString::number(i+1));
            tag_FCDA.setAttribute("ORDINAL",p->ORDINAL);
            tag_FCDA.setAttribute("TYPE",p->TYPE);
            tag_FCDA.setAttribute("LEAF",p->leaf);
            tag_FCDA.setAttribute("DESC",p->DESC);

            tag_DATASET.appendChild(tag_FCDA);
        }

        tag_SUB_GOOSE.appendChild(tag_GCB);
    }

    //2.PUB_GOOSE**
    QDomElement tag_PUB_GOOSE = doc.createElement("PUB_GOOSE");
    tag_DATAINFO.appendChild(tag_PUB_GOOSE);

    QMapIterator<QString,GCB*> outMap(PUB_GOOSE_GCB);
    while (outMap.hasNext())
    {
        outMap.next();
        QString dsName = outMap.key();
        GCB* gcb = outMap.value();
        QDomElement tag_GCB = doc.createElement("GCB");
        tag_GCB.setAttribute("GoID",gcb->GoID);
        tag_GCB.setAttribute("Priority",gcb->Priority_G);
        tag_GCB.setAttribute("GcRef",gcb->GcRef);
        tag_GCB.setAttribute("ConfRev",gcb->ConfRev);
        tag_GCB.setAttribute("DatasetRef",gcb->DatasetRef);
        tag_GCB.setAttribute("AppID",gcb->AppID);
        tag_GCB.setAttribute("IEDName",gcb->IEDName);
        tag_GCB.setAttribute("T0",gcb->addrList->t0);
        tag_GCB.setAttribute("T1",gcb->addrList->t1);

        QDomElement tag_NET = doc.createElement("NET");
        QDomElement tag_Address = doc.createElement("Address");
        QDomElement tag_PORT = doc.createElement("PORT");
        QDomText txt_PORT = doc.createTextNode("0");
        tag_PORT.appendChild(txt_PORT);
        QDomElement tag_VID = doc.createElement("VID");
        QDomText txt_VID = doc.createTextNode(gcb->addrList->VID);
        tag_VID.appendChild(txt_VID);
        QDomElement tag_DST_MAC = doc.createElement("DST_MAC");
        QDomText txt_DST_MAC = doc.createTextNode(gcb->addrList->DST_MAC);
        tag_DST_MAC.appendChild(txt_DST_MAC);
        tag_Address.appendChild(tag_PORT);
        tag_Address.appendChild(tag_VID);
        tag_Address.appendChild(tag_DST_MAC);
        tag_NET.appendChild(tag_Address);
        tag_GCB.appendChild(tag_NET);
        QDomElement tag_DATASET = doc.createElement("DATASET");
        tag_GCB.appendChild(tag_DATASET);
        for(int i=0;i<gcb->pointList.size();i++)
        {
            Pointdef *p = gcb->pointList.at(i);
            QDomElement tag_FCDA = doc.createElement("FCDA");
            tag_FCDA.setAttribute("INDEX",QString::number(i+1));
            tag_FCDA.setAttribute("ORDINAL",p->ORDINAL);
            tag_FCDA.setAttribute("TYPE",p->TYPE);
            tag_FCDA.setAttribute("LEAF",p->leaf);
            tag_FCDA.setAttribute("DESC",p->DESC);

            tag_DATASET.appendChild(tag_FCDA);
        }

        tag_PUB_GOOSE.appendChild(tag_GCB);
    }

    //3.SUB_DATASET*********
    QDomElement tag_DATAMAP = doc.createElement("DATAMAP");
    root.appendChild(tag_DATAMAP);
    QDomElement tag_SUB_DATASET = doc.createElement("SUB_DATASET");
    tag_DATAMAP.appendChild(tag_SUB_DATASET);
    QMapIterator<int, Pointdef*> inDataSetMap(SUB_DATASET);
    int inputCount = 0;
    int outputCount = 0;
    while (inDataSetMap.hasNext())
    {
        inDataSetMap.next();
        Pointdef *inP = inDataSetMap.value();
        QDomElement tag_FCDA = doc.createElement("FCDA");        
        tag_FCDA.setAttribute("ORDINAL",inP->ORDINAL);
        tag_FCDA.setAttribute("TYPE",inP->TYPE);
        tag_FCDA.setAttribute("DAINDEX",inP->DAINDEX);
        tag_FCDA.setAttribute("LEAF",inP->leaf);
        tag_FCDA.setAttribute("DESC",inP->DESC);
        tag_SUB_DATASET.appendChild(tag_FCDA);
        inputCount = inP->ORDINAL;
    }

    QMapIterator<QString, QString> inputMap(ehcInputMap);
    while (inputMap.hasNext())
    {
        inputMap.next();
        QString sn = inputMap.key();
        QString desc = inputMap.value();
        QDomElement tag_FCDA = doc.createElement("FCDA");
        tag_FCDA.setAttribute("ORDINAL",++inputCount);
        tag_FCDA.setAttribute("TYPE","BOOL");
        tag_FCDA.setAttribute("DAINDEX",sn);
        tag_FCDA.setAttribute("LEAF","");
        tag_FCDA.setAttribute("DESC",desc);
        tag_SUB_DATASET.appendChild(tag_FCDA);
    }

    //4.PUB_DATASET*********
    QDomElement tag_PUB_DATASET = doc.createElement("PUB_DATASET");
    tag_DATAMAP.appendChild(tag_PUB_DATASET);
    QDomElement tag_PUB_FCD = doc.createElement("FCD");
    tag_PUB_FCD.setAttribute("DESC",tr("开关量输出"));
    QDomElement tag_PUB_FCDMX = doc.createElement("FCD");
    tag_PUB_FCDMX.setAttribute("DESC",tr("模拟量输出"));
    tag_PUB_DATASET.appendChild(tag_PUB_FCD);
    tag_PUB_DATASET.appendChild(tag_PUB_FCDMX);
    QMapIterator<int, Pointdef*> outDataSetMap(PUB_DATASET);
    while (outDataSetMap.hasNext())
    {
        outDataSetMap.next();
        Pointdef *outP = outDataSetMap.value();
        int ordinal = outP->ORDINAL;
        QDomElement tag_FCDA = doc.createElement("FCDA");
        tag_FCDA.setAttribute("ORDINAL",ordinal);
        tag_FCDA.setAttribute("TYPE",outP->TYPE);
        tag_FCDA.setAttribute("DAINDEX",outP->DAINDEX);
        tag_FCDA.setAttribute("LEAF",outP->leaf);
        tag_FCDA.setAttribute("DESC",outP->DESC);

        if(outP->src_fc == "MX")
        {
            tag_PUB_FCDMX.appendChild(tag_FCDA);
        }
        else
        {
            tag_PUB_FCD.appendChild(tag_FCDA);
        }

        if(outP->haveQ)
        {
            QDomElement tag_FCDAQ = doc.createElement("FCDA");
            tag_FCDAQ.setAttribute("DEVTYPE","2");
            tag_FCDAQ.setAttribute("ORDINAL",++ordinal);
            tag_FCDAQ.setAttribute("TYPE","QUALITY");
            tag_FCDAQ.setAttribute("DAINDEX",outP->DAINDEX.replace(7,1,"2"));
            tag_FCDAQ.setAttribute("CPUID","1");
            tag_PUB_FCD.appendChild(tag_FCDAQ);
        }

        if(outP->haveT)
        {
            QString TSRCDI = "";
            if(outP->TSRCDI1 != 0)
            {
                TSRCDI = QString::number(outP->TSRCDI1);
                if(outP->TSRCDI2 != 0)
                {
                    TSRCDI = TSRCDI+","+QString::number(outP->TSRCDI2);
                }
            }

            QDomElement tag_FCDAT = doc.createElement("FCDA");
            tag_FCDAT.setAttribute("TSRCDI",TSRCDI);
            tag_FCDAT.setAttribute("ORDINAL",++ordinal);
            tag_FCDAT.setAttribute("TYPE","UTC");
            tag_FCDAT.setAttribute("DAINDEX",outP->DAINDEX.replace(7,1,"3"));
            tag_FCDAT.setAttribute("CPUID","1");
            tag_PUB_FCD.appendChild(tag_FCDAT);
        }

        outputCount = ordinal;
    }

    QMapIterator<QString, QString> outputMap(ehcOutputMap);
    while (outputMap.hasNext())
    {
        outputMap.next();
        QString sn = outputMap.key();
        QString desc = outputMap.value();
        QDomElement tag_FCDA = doc.createElement("FCDA");
        tag_FCDA.setAttribute("ORDINAL",++outputCount);
        tag_FCDA.setAttribute("TYPE","BOOL");
        tag_FCDA.setAttribute("DAINDEX",sn);
        tag_FCDA.setAttribute("LEAF","");
        tag_FCDA.setAttribute("DESC",desc);
        if(sn.startsWith("01"))
        {
            tag_PUB_FCDMX.appendChild(tag_FCDA);
        }
        else
        {
            tag_PUB_FCD.appendChild(tag_FCDA);
        }
    }


    //*********生成XML
    QString savePath = "../conf/IU/cid";
    QString gseSavePath = QString("%1/%2gse.xml").arg(savePath).arg(this->ldName);
    QFile file(gseSavePath);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    QTextStream out(&file);
    out.setCodec("GB2312");
    doc.save(out,4,QDomNode::EncodingFromTextStream);
    file.close();            

    QMessageBox::information(NULL, tr("Information"), tr("Success."),tr("Ok"));
}

//根据已配置好的table_scd_in 表格装载开入量
void MainWindow::loadInput()
{
    //1.装载开入的27个数据集*****DATAMAP
    SUB_DATASETHash.clear();
    for(int i=0;i<ui->table_scd_in->rowCount();i++)
    {
        QTableWidgetItem *hdItem = ui->table_scd_in->item(i,2);
        if(hdItem != NULL)
        {
            int ordinal = ui->table_scd_in->item(i,0)->data(Qt::UserRole).toInt();
            QString desc_ehc = hdItem->text().trimmed();            
            QString strDAI = hdItem->data(Qt::UserRole).toString();
            ehcInputMap.take(strDAI);

            Pointdef* p = SUB_DATASET.value(ordinal);            

            p->DESC = desc_ehc;
            p->DAINDEX = strDAI;

            //key:iedName%ldInst%prefix%lnClass%lnInst%doName%daName
            QString key = p->src_iedName+"%"+p->src_ldInst+"%"+p->src_prefix+"%"+p->src_lnClass+"%"+p->src_lnInst+"%"+p->src_doName+"%"+p->src_daName;
            SUB_DATASETHash.insert(key,p);  //将27个开入点放入 hash表
        }
    }


    //2.*****DATASET   //key:PM0001%G1%PI0%LLN0%dsGOOSE1
    inputGCBList.clear();
    QMapIterator<QString, Point_LDNode*> in(SUB_GOOSE_LDNode);
    while (in.hasNext())
    {
        in.next();
        QString pointkey = in.key();
        Point_LDNode *p_ldNode = in.value();
        QDomNode ldNode = p_ldNode->ldNode;
        Pointdef *datasetP = p_ldNode->p;

        QStringList keyList = pointkey.split("%");
        QString iedName = keyList.at(0);
        QString accName = keyList.at(1);
        QString ldName = keyList.at(2);
        QString dsName = keyList.at(4);

        GCB* gcb = new GCB;
        QString goid = "";
        QString cbName = "";
        QString gcref = iedName+ldName+"/LLN0$GO$";
        QString confrev = "";
        QString datasetRef = iedName+ldName+"/LLN0$";
        QString appid = "";

        QDomNode gseCtrlNode = xmlhelplib.getChildNode(ldNode,QString("LN0/GSEControl[@datSet=%1]").arg(dsName));

        QDomElement gseCtrlELE = gseCtrlNode.toElement();
        goid = gseCtrlELE.attribute("appID");   //PM0001PI0/LLN0.GO_Gcb1
        cbName = gseCtrlELE.attribute("name");      //GO_Gcb1
        datasetRef = datasetRef + gseCtrlELE.attribute("datSet");       //PM0001PI0/LLN0$dsGOOSE1
        confrev = gseCtrlELE.attribute("confRev");      //1
        gcref = gcref + cbName;     //PM0001PI0/LLN0$GO$GO_Gcb1

        QDomNode apGSENode = xmlhelplib.getChildNode(subNetwork,QString("ConnectedAP[@iedName=%1][@apName=%2]/GSE[@cbName=%3][@ldInst=%4]").arg(iedName).arg(accName).arg(cbName).arg(ldName));

        QDomElement mac_addrNode = xmlhelplib.getChildNode(apGSENode,"Address/P[@type=MAC-Address]").toElement();
        QDomElement appidNode = xmlhelplib.getChildNode(apGSENode,"Address/P[@type=APPID]").toElement();
        QDomElement vidNode = xmlhelplib.getChildNode(apGSENode,"Address/P[@type=VLAN-ID]").toElement();

        QDomElement minNode = xmlhelplib.getChildNode(apGSENode,"MinTime").toElement();
        QDomElement maxNode = xmlhelplib.getChildNode(apGSENode,"MaxTime").toElement();

        QString mac = mac_addrNode.text();
        QString vid = vidNode.text();
        QString t0 = maxNode.text();
        QString t1 = minNode.text();
        Address* addr = new Address;
        addr->DST_MAC = mac;
        addr->VID = vid;
        addr->t0 = t0.toInt();
        addr->t1 = t1.toInt();
        gcb->addrList = addr;

        appid = appidNode.text();

        QList<QDomNode> fcdaNodeList = xmlhelplib.getChildNodes(ldNode,QString("LN0/DataSet[@name=%1]/FCDA").arg(dsName));
        QString comkey = QString(datasetP->src_iedName+"%"+datasetP->src_ldInst);
        for(int i=0;i<fcdaNodeList.size();i++)
        {
            QDomElement fcdaNodeELE = fcdaNodeList.at(i).toElement();
            QString daName = fcdaNodeELE.attribute("daName");
            QString doName = fcdaNodeELE.attribute("doName");
            QString prefix = fcdaNodeELE.attribute("prefix","");
            QString lnClass = fcdaNodeELE.attribute("lnClass");
            QString lnInst = fcdaNodeELE.attribute("lnInst");

            int ordinal = 600;
            QString hashKey = comkey+"%"+prefix+"%"+lnClass+"%"+lnInst+"%"+doName+"%"+daName;
            Pointdef *ordPoint = SUB_DATASETHash.value(hashKey,NULL);
            if(ordPoint != NULL)
            {
                ordinal = ordPoint->ORDINAL;
            }
            QDomNode lnDomNode = xmlhelplib.getChildNode(ldNode,QString("LN[@prefix=%1][@lnClass=%2][@inst=%3]")
                                                        .arg(prefix).arg(lnClass).arg(lnInst));

            Pointdef* fcdaPoint = new Pointdef;
            fcdaPoint->ORDINAL = ordinal;
            fcdaPoint->TYPE = getbType(lnDomNode.toElement().attribute("lnType"),lnClass,doName,daName);
            fcdaPoint->DESC = getFCDADesc(fcdaNodeELE,lnDomNode.toElement());

            gcb->pointList.append(fcdaPoint);
        }
        gcb->GoID = goid;
        gcb->GcRef = gcref;
        gcb->ConfRev = confrev;
        gcb->DatasetRef = datasetRef;
        gcb->AppID = appid;
        gcb->IEDName = datasetP->src_iedName;

        inputGCBList.append(gcb);
    }

}

QString MainWindow::transInt(int i)
{
    QString str = "00";
    QString strInt = QString::number(i,16).toUpper();
    if(strInt.size() == 2)
    {
        return str+strInt;
    }
    else
    {
        return str+"0"+strInt;
    }

    return str;
}

void MainWindow::loadOutput()
{
    //1.装载开出数据集*****PUB_DATASET
    for(int i=0;i<ui->table_scd_out->rowCount();i++)
    {
        QTableWidgetItem *hdItem = ui->table_scd_out->item(i,2);
        if(hdItem != NULL)
        {
            int ordinal = ui->table_scd_out->item(i,0)->data(Qt::UserRole).toInt();
            QString desc_ehc = hdItem->text().trimmed();
            QString strDAI = hdItem->data(Qt::UserRole).toString();
            ehcOutputMap.take(strDAI);

            Pointdef* p = PUB_DATASET.value(ordinal);            

            p->DESC = desc_ehc;
            p->DAINDEX = strDAI;

            //判断该点是否为双点
            if(p->haveT)
            {
                QTableWidgetItem *tsrItem1 = ui->table_scd_out->item(i,3);
                QTableWidgetItem *tsrItem2 = ui->table_scd_out->item(i,4);
                if(tsrItem1 != NULL)
                {
                    p->TSRCDI1 = tsrItem1->data(Qt::UserRole).toInt();
                }

                if(tsrItem2 != NULL)
                {
                    p->TSRCDI2 = tsrItem2->data(Qt::UserRole).toInt();
                }
            }
        }
    }

    //2.*****PUB_GOOSE GCB   //key:dsGOOSE1
    QDomNode ldNode = ldMap.value(this->iedName+"@"+this->accessPoint+"@"+this->ldName);
    if(!ldNode.isNull())
    {
        QMapIterator<QString,GCB*> outMap(PUB_GOOSE_GCB);
        while (outMap.hasNext())
        {
            outMap.next();
            QString dsName = outMap.key();
            GCB* gcb = outMap.value();

            QString goid = "";
            QString cbName = "";
            QString gcref = iedName+ldName+"/LLN0$GO$";
            QString confrev = "";
            QString datasetRef = iedName+ldName+"/LLN0$";
            QString appid = "";

            QDomNode gseCtrlNode = xmlhelplib.getChildNode(ldNode,QString("LN0/GSEControl[@datSet=%1]").arg(dsName));

            QDomElement gseCtrlELE = gseCtrlNode.toElement();
            goid = gseCtrlELE.attribute("appID");   //PM0001PI0/LLN0.GO_Gcb1
            cbName = gseCtrlELE.attribute("name");      //GO_Gcb1
            datasetRef = datasetRef + gseCtrlELE.attribute("datSet");       //PM0001PI0/LLN0$dsGOOSE1
            confrev = gseCtrlELE.attribute("confRev");      //1
            gcref = gcref + cbName;     //PM0001PI0/LLN0$GO$GO_Gcb1

            QDomNode apGSENode = xmlhelplib.getChildNode(subNetwork,QString("ConnectedAP[@iedName=%1][@apName=%2]/GSE[@cbName=%3][@ldInst=%4]").arg(iedName).arg(accessPoint).arg(cbName).arg(ldName));
    //        QDomElement apGSELE = apGSENode.toElement();
            QDomElement mac_addrNode = xmlhelplib.getChildNode(apGSENode,"Address/P[@type=MAC-Address]").toElement();
            QDomElement appidNode = xmlhelplib.getChildNode(apGSENode,"Address/P[@type=APPID]").toElement();
            QDomElement vidNode = xmlhelplib.getChildNode(apGSENode,"Address/P[@type=VLAN-ID]").toElement();
            QDomElement priorityNode = xmlhelplib.getChildNode(apGSENode,"Address/P[@type=VLAN-PRIORITY]").toElement();

            QDomElement minNode = xmlhelplib.getChildNode(apGSENode,"MinTime").toElement();
            QDomElement maxNode = xmlhelplib.getChildNode(apGSENode,"MaxTime").toElement();


            QString mac = mac_addrNode.text();
            QString vid = vidNode.text();
            QString t0 = maxNode.text();
            QString t1 = minNode.text();
            Address* addr = new Address;
            addr->DST_MAC = mac;
            addr->VID = vid;
            addr->t0 = t0.toInt();
            addr->t1 = t1.toInt();
            gcb->addrList = addr;

            appid = appidNode.text();

            gcb->GoID = goid;
            gcb->GcRef = gcref;
            gcb->ConfRev = confrev;
            gcb->DatasetRef = datasetRef;
            gcb->AppID = appid;
            gcb->IEDName = iedName;
            gcb->Priority_G = priorityNode.text();
        }

    }
}

void MainWindow::openMUCFG()
{
    pro->start("./MUCFG.exe");
}

//读取硬件配置文件中的描述和内部id
void MainWindow::importEHC()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open HardFile"), "." , tr("XLS files (*.ehc)"));
    if(path.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."),tr("Ok"));
    }
    else
    {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) {
            return;
        }

        ui->list_ehc_in->clear();
        ui->list_ehc_out->clear();
        ui->list_ehc_hdo->clear();

        ehcInputMap.clear();
        ehcOutputMap.clear();

        QString ehcStrFile = path;
        char*  ch;
        QByteArray ba = ehcStrFile.toLatin1();
        ch = ba.data();
        int re = RD_Initialize(ch);
        HIO_INFO *hi = &hioinfo;

//        QString temp = path+"-"+re+"-";
//        QMessageBox::information(NULL, tr("Path"), temp ,tr("Ok"));

        while(hi->gdi)
        {
            if(hi->gdi != NULL)
            {
                QString sn = QString::number(hi->gdi->sn);
                QString strDAI = "02"+transInt(hi->gdi->sn)+"01";

                QString desc = QString::fromLocal8Bit(hi->gdi->desc);
                QListWidgetItem* item = new QListWidgetItem(sn + " . " + desc);
                item->setData(Qt::UserRole,strDAI);
                item->setData(Qt::UserRole+1,desc);
                ui->list_ehc_in->addItem(item);
                ehcInputMap.insert(strDAI,desc.trimmed());
            }
            hi->gdi = hi->gdi->next;
        }

        while(hi->gdo)
        {
            if(hi->gdo != NULL)
            {
                QString sn = QString::number(hi->gdo->sn);
                QString strDAI = "02"+transInt(hi->gdo->sn)+"01";
                QString desc = QString::fromLocal8Bit(hi->gdo->desc);
                QListWidgetItem* item = new QListWidgetItem(sn + " . " + desc);
                item->setData(Qt::UserRole,strDAI);
                item->setData(Qt::UserRole+1,desc);
                ui->list_ehc_out->addItem(item);
                ehcOutputMap.insert(strDAI,desc.trimmed());
            }
            hi->gdo = hi->gdo->next;
        }

        while(hi->gao)
        {
            if(hi->gao != NULL)
            {
                QString sn = QString::number(hi->gao->sn);
                QString strDAI = "01"+transInt(hi->gao->sn)+"01";
                QString desc = QString::fromLocal8Bit(hi->gao->desc);
                QListWidgetItem* item = new QListWidgetItem(sn + " . " + desc);
                item->setData(Qt::UserRole,strDAI);
                item->setData(Qt::UserRole+1,desc);
                item->setBackground(QBrush(QColor(Qt::green)));
                ui->list_ehc_out->addItem(item);
                ehcOutputMap.insert(strDAI,desc.trimmed());
            }
            hi->gao = hi->gao->next;
        }

        while(hi->hdi)
        {
            if(hi->hdi != NULL)
            {
                QString sn = QString::number(hi->hdi->sn);
                QString desc = QString::fromLocal8Bit(hi->hdi->desc);
                QListWidgetItem* item = new QListWidgetItem(sn + " . " + desc);
                item->setData(Qt::UserRole,sn);
                item->setData(Qt::UserRole+1,desc);
                ui->list_ehc_hdo->addItem(item);
            }
            hi->hdi = hi->hdi->next;
        }

        connect(ui->list_ehc_in,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(dymicPoint(QListWidgetItem*)),Qt::UniqueConnection);
        connect(ui->list_ehc_out,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(dymicPoint(QListWidgetItem*)),Qt::UniqueConnection);
        connect(ui->list_ehc_hdo,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(dymicPoint(QListWidgetItem*)),Qt::UniqueConnection);
    }
}

void MainWindow::dymicPoint(QListWidgetItem* item)
{
    item->setBackgroundColor(Qt::red);

    int curTab = ui->tab_scd->currentIndex();
    QTableWidgetItem* dyItem = new QTableWidgetItem(item->data(Qt::UserRole+1).toString());
    dyItem->setData(Qt::UserRole,item->data(Qt::UserRole).toString());
    if(curTab == 0) //同步开入
    {
        ui->table_scd_in->setItem(curIndex_IN,2,dyItem);

        ui->table_scd_in->resizeColumnsToContents();

        ui->table_scd_in->setCurrentCell(++curIndex_IN,2);

    }
    else    //同步开出
    {
        if(ui->tab_ehc->currentIndex() == 1) //同步开出点
        {
            ui->table_scd_out->setItem(curIndex_OUT,2,dyItem);
            ui->table_scd_out->setCurrentCell(++curIndex_OUT,2);

        }
        else    //同步双点
        {
            if(left_doublePos == right_doublePos)   //说明是左边
            {
                QTableWidgetItem* item = ui->table_scd_out->item(left_doublePos,3);
                if(item != NULL)
                {
                    if(item->flags() == Qt::NoItemFlags)
                    {
                        return;
                    }
                }
                ui->table_scd_out->setItem(left_doublePos,3,dyItem);
                ui->table_scd_out->setCurrentCell(left_doublePos++,4);
            }
            else
            {
                ui->table_scd_out->setItem(right_doublePos,4,dyItem);
                ui->table_scd_out->setCurrentCell(left_doublePos,3);
                right_doublePos++;
            }
        }
        ui->table_scd_out->resizeColumnsToContents();
    }
}


void MainWindow::setcurrTableRow(int curRow,int curCol)
{
    int currTab = ui->tab_scd->currentIndex();
    if(curCol == 2)
    {
        if(currTab == 0)    //开入
        {
            curIndex_IN = curRow;
        }
        else if(currTab == 1) //开出
        {
            curIndex_OUT = curRow;
            ui->tab_ehc->setCurrentIndex(1);
        }
    }
    else if (curCol == 3 || curCol == 4)    //设置双点当前光标位置
    {
        QTableWidgetItem* dyItem = ui->table_scd_out->item(curRow,curCol);
        if(dyItem != NULL)
        {
            if(dyItem->flags() == Qt::NoItemFlags)
            {
                return;
            }
        }
        ui->tab_ehc->setCurrentIndex(2);
        //***左右点一定要同时设置
        left_doublePos = curRow;
        right_doublePos = curRow;
    }
}


void MainWindow::importSCD()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open scd"), "." , tr("XLS files (*.scd)"));
    if(path.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."),tr("Ok"));
    }
    else
    {
        iedMap.clear();
        xmlhelplib.document.clear();
        xmlhelplib.loadXML(path);

        ui->comboBox_IED->clear();
        this->scdPath = path;

        QList<QDomNode> iedList = xmlhelplib.selectNodesList("SCL/IED");
        dataTypeTemplates = xmlhelplib.selectNodesList("SCL/DataTypeTemplates").at(0);
        subNetwork = xmlhelplib.selectNodesList("SCL/Communication/SubNetwork").at(0);

        if(iedList.count()>0)
        {
            ui->comboBox_IED->addItem(tr("[Select IED]"),"");
            for(int i=0;i<iedList.count();i++)
            {
                QDomNode iedNode = iedList.at(i);
                QDomElement iedELE = iedNode.toElement();
                QString iedName= iedELE.attribute("name");
                QString iedDesc = iedELE.attribute("desc");
                ui->comboBox_IED->addItem(iedName+"->"+iedDesc,iedName);
                iedMap.insert(iedName,iedNode);
            }
            connect(ui->comboBox_IED,SIGNAL(currentIndexChanged(int)),this,SLOT(selectLD(int)),Qt::UniqueConnection);
        }
    }
}

void MainWindow::selectLD(int iedIndex)
{
    ui->comboBox_LD->clear();
    ldMap.clear();
    this->iedName = ui->comboBox_IED->itemData(iedIndex).toString();
    QDomNode iedNode = iedMap.value(this->iedName);
    QList<QDomNode> accList = xmlhelplib.getChildNodes(iedNode,"AccessPoint");

    QList<QString> ldItemList;
    for(int i=0;i<accList.count();i++)
    {
        QDomNode accNode = accList.at(i);
        QDomElement accELE = accNode.toElement();
        QString acc = accELE.attribute("name");
        QString xpath = QString("AccessPoint[@name=%2]/Server/LDevice").arg(acc);
        QList<QDomNode> ldList = xmlhelplib.getChildNodes(iedNode,xpath);
        if(ldList.size()>0)
        {
            for(int j=0;j<ldList.count();j++)
            {
                QDomNode ldNode = ldList.at(j);
                QDomElement ldELE = ldNode.toElement();
                QString ldName = ldELE.attribute("inst");
                QString ldDesc = ldELE.attribute("desc");
                QString ldKey = this->iedName+"@"+acc+"@"+ldName;
                ldItemList.append(ldName+"->"+ldDesc+":"+ldKey);
                ldMap.insert(ldKey,ldNode);
            }
        }
    }

    if(ldItemList.size() > 0)
    {
        ui->comboBox_LD->addItem(tr("[Select LDevice]"), "");
        foreach (QString ldinfo, ldItemList)
        {
            QStringList ldinfoList = ldinfo.split(":");
            ui->comboBox_LD->addItem(ldinfoList.at(0),ldinfoList.at(1));
        }
    }

    connect(ui->comboBox_LD,SIGNAL(currentIndexChanged(int)),this,SLOT(listAllPoints(int)),Qt::UniqueConnection);
}


void MainWindow::listAllPoints(int ldIndex)
{
    //清除所有scd数据
    curIndex_IN = 0;
    curIndex_OUT = 0;
    left_doublePos = 0;
    right_doublePos = 0;
    ui->table_scd_in->clearContents();
    ui->table_scd_out->clearContents();
    SUB_DATASET.clear();
    PUB_DATASET.clear();
    PUB_GOOSE_GCB.clear();
    SUB_GOOSE_LDNode.clear();
    //**********
    QStringList userDataList = ui->comboBox_LD->itemData(ldIndex).toString().split("@");
    if(userDataList.size() > 1)
    {
        this->accessPoint = userDataList.at(1);
        this->ldName = userDataList.at(2);
        ui->lab_currLD->setText(this->iedName+"->"+this->ldName);

        //设置开入表格
        QMap<int,Pointdef*> inMap = getPointList_IN(ui->comboBox_LD->itemData(ldIndex).toString());
        if(inMap.size())
        {
            ui->table_scd_in->setRowCount(inMap.size());
            QMapIterator<int, Pointdef*> in(inMap);
            int row = 0;
            while (in.hasNext())
            {
                in.next();
                Pointdef* p = in.value();
                p->leaf = p->src_iedName+p->src_ldInst+"$"+p->src_prefix+p->src_lnClass+p->src_lnInst+"$"+p->src_doName+"$"+p->src_daName;
                QTableWidgetItem* nameItem = new QTableWidgetItem(p->leaf);
                nameItem->setData(Qt::UserRole,p->ORDINAL);
                ui->table_scd_in->setItem(row,0,nameItem);
                QTableWidgetItem* descItem = new QTableWidgetItem(p->src_desc);
                ui->table_scd_in->setItem(row,1,descItem);
                row++;
            }
            ui->table_scd_in->resizeColumnsToContents();
            connect(ui->table_scd_in,SIGNAL(cellClicked(int,int)),this,SLOT(setcurrTableRow(int,int)));
        }

        //设置开出表格
        QMap<int,Pointdef*> outMap = getPointList_OUT(ui->comboBox_LD->itemData(ldIndex).toString());
        if(outMap.size())
        {
            ui->table_scd_out->setRowCount(outMap.size());
            QMapIterator<int, Pointdef*> out(outMap);
            int row = 0;
            while (out.hasNext())
            {
                out.next();
                Pointdef* p = out.value();

                QString name = p->leaf;

                QTableWidgetItem* nameItem = new QTableWidgetItem(name);
                nameItem->setData(Qt::UserRole,p->ORDINAL);
                ui->table_scd_out->setItem(row,0,nameItem);
                QTableWidgetItem* descItem = new QTableWidgetItem(p->src_desc);
                ui->table_scd_out->setItem(row,1,descItem);

                if(p->src_fc == "MX")
                {
                    nameItem->setBackgroundColor(Qt::green);
                    descItem->setBackground(Qt::green);
                }

                if(!p->haveT)
                {
                    QTableWidgetItem* oneItem = new QTableWidgetItem("");
                    oneItem->setBackgroundColor(Qt::gray);
                    oneItem->setFlags(Qt::NoItemFlags);
                    ui->table_scd_out->setItem(row,3,oneItem);
                    QTableWidgetItem* twoItem = new QTableWidgetItem("");
                    twoItem->setFlags(Qt::NoItemFlags);
                    twoItem->setBackgroundColor(Qt::gray);
                    ui->table_scd_out->setItem(row,4,twoItem);
                }
                row++;
            }

            ui->table_scd_out->resizeColumnsToContents();
            connect(ui->table_scd_out,SIGNAL(cellClicked(int,int)),this,SLOT(setcurrTableRow(int,int)));
        }
    }
}


//获取开入点 本设备逻辑设备下的 LN0/Inputs/ExtRef
QMap<int,Pointdef*> MainWindow::getPointList_IN(QString xpath)
{   
    QDomNode ldNode = ldMap.value(xpath);
    QList<QDomNode> pointList = xmlhelplib.getChildNodes(ldNode,"LN0/Inputs/ExtRef");
    iedNum = 0;
    int pointNum = 0;
    QString curTempIed = "";    
    for(int i=0;i<pointList.count();i++)
    {
        QDomNode pointNode = pointList.at(i);
        QDomElement pELE = pointNode.toElement();

        Pointdef* p = new Pointdef();
        p->src_iedName = pELE.attribute("iedName");
        p->src_ldInst = pELE.attribute("ldInst");
        p->src_prefix = pELE.attribute("prefix");
        p->src_lnClass = pELE.attribute("lnClass");
        p->src_lnInst = pELE.attribute("lnInst");
        p->src_doName = pELE.attribute("doName");
        p->src_daName = pELE.attribute("daName");

        if(curTempIed == p->src_iedName)
        {
            pointNum++;
        }
        else
        {
            curTempIed = p->src_iedName;
            iedNum = iedNum + 100;
            pointNum = 1;
        }

        p->ORDINAL = iedNum + pointNum;
        p->src_desc = getSrcPointDesc(p);
        //key:iedName%ldInst%prefix%lnClass%lnInst%doName%daName
//        SUB_DATASET.insert(p->src_iedName+"$"+p->src_ldInst+"$"+p->src_prefix+"$"+p->src_lnClass+"$"+p->src_lnInst+"$"+p->src_doName+"$"+p->src_daName,p);
        SUB_DATASET.insert(p->ORDINAL,p);
    }
    return SUB_DATASET;
}


//获取开出量 1.获取选取的LD 下所有的数据集点； 2.合并 q,t,f 点为一个点
QMap<int,Pointdef*> MainWindow::getPointList_OUT(QString xpath)
{    
    int pointNum = 100;

    QHash<QString,Pointdef*> pHash;

    QDomNode ldNode = ldMap.value(xpath);
    QList<QDomNode> dsList = xmlhelplib.getChildNodes(ldNode,"LN0/DataSet");

    for(int ds=0;ds<dsList.count();ds++)
    {
        QDomNode dsNode = dsList.at(ds);
        //key:PM0001%G1%PI0%LLN0%dsGOOSE1
        QString dsName = dsNode.toElement().attribute("name");
        GCB* gcb = new GCB;
        QList<QDomNode> pointList = xmlhelplib.getChildNodes(dsNode,QString("FCDA"));

        for(int i=0;i<pointList.count();i++)
        {
            QDomNode pointNode = pointList.at(i);
            QDomElement pELE = pointNode.toElement();

            Pointdef* p = new Pointdef();            
            p->src_iedName = this->iedName;
            p->src_ldInst = pELE.attribute("ldInst");
            p->src_prefix = pELE.attribute("prefix");
            p->src_lnClass = pELE.attribute("lnClass");
            p->src_lnInst = pELE.attribute("lnInst");
            p->src_doName = pELE.attribute("doName");
            p->src_daName = pELE.attribute("daName");
            p->src_fc = pELE.attribute("fc");

            QString key = p->src_iedName+p->src_ldInst+"$"+p->src_prefix+p->src_lnClass+p->src_lnInst+"$"+p->src_doName;
            p->leaf = key + "$" + p->src_daName;

            p->ORDINAL = ++pointNum;

            QDomNode lnDomNode = xmlhelplib.getChildNode(ldNode,QString("LN[@prefix=%1][@lnClass=%2][@inst=%3]")
                                                        .arg(p->src_prefix).arg(p->src_lnClass).arg(p->src_lnInst));
            QString pType = getbType(lnDomNode.toElement().attribute("lnType"),p->src_lnClass,p->src_doName,p->src_daName);
            p->TYPE = pType;

            if(pType == "UTC" || pType == "QUALITY")
            {
                Pointdef *parentP = pHash.value(key);
                if(pType == "UTC")
                {
                    parentP->haveT = true;
                }
                else if(pType == "QUALITY")
                {
                    parentP->haveQ = true;
                }
            }
            else
            {                
                PUB_DATASET.insert(p->ORDINAL,p);
                pHash.insert(key,p);
            }

            QString desc = getFCDADesc(pELE,lnDomNode.toElement());
            p->src_desc = desc;
            p->DESC = desc;

            gcb->pointList.append(p);
        }
        PUB_GOOSE_GCB.insert(dsName,gcb);
    }

    return PUB_DATASET;
}



//1.返回开该入点所在其他设备中的描述信息
//2.设置该开入点所在其他设备中的数据集并将这些数据集添加到 SUB_GOOSE
QString MainWindow::getSrcPointDesc(Pointdef* p)
{
    QDomNode iedNode = iedMap.value(p->src_iedName);

    QString desc = "";
    QString acc = "G1";

    QList<QDomNode> accList = xmlhelplib.getChildNodes(iedNode,"AccessPoint");
    for(int i=0;i<accList.count();i++)
    {
        QDomNode accNode = accList.at(i);
        QDomElement accELE = accNode.toElement();
        QString accPoint = accELE.attribute("name");
        if(accPoint.startsWith("g",Qt::CaseInsensitive))
        {
            acc = accPoint;
            p->src_acc = acc;
            break;
        }
    }

    QString ldPath = QString("AccessPoint[@name=%1]/Server/LDevice[@inst=%2]").arg(acc).arg(p->src_ldInst);
    QDomNode ldDomNode = xmlhelplib.getChildNode(iedNode,ldPath);
    QList<QDomNode> dsList = xmlhelplib.getChildNodes(ldDomNode,QString("LN0/DataSet"));
    for(int j=0;j<dsList.count();j++)
    {
        QDomNode dsNode = dsList.at(j);
        QDomElement dsELE = dsNode.toElement();
        QString dsName = dsELE.attribute("name");
        p->src_dsName = dsName;
        QString fcdaPath = QString("FCDA[@ldInst=%1][@lnClass=%2][@lnInst=%3][@doName=%4][@daName=%5]")
                .arg(p->src_ldInst).arg(p->src_lnClass).arg(p->src_lnInst).arg(p->src_doName).arg(p->src_daName);

        QList<QDomNode> fcdaList = xmlhelplib.getChildNodes(dsNode,fcdaPath);
        if(fcdaList.size()>0)   //找到了该点所在的源数据集
        {
            //1.获取描述
            QDomElement fcda = fcdaList.at(0).toElement();
            QDomNode lnDomNode = xmlhelplib.getChildNode(ldDomNode,QString("LN[@prefix=%1][@lnClass=%2][@inst=%3]")
                                                        .arg(p->src_prefix).arg(p->src_lnClass).arg(p->src_lnInst));
            QString pType = getbType(lnDomNode.toElement().attribute("lnType"),p->src_lnClass,p->src_doName,p->src_daName);
            p->TYPE = pType;
            p->src_fc = fcda.attribute("fc");

            desc = getFCDADesc(fcda,lnDomNode.toElement());

            //2.将原始的逻辑设备Node放入SUB_GOOSE_LDNode key:PM0001%G1%PI0%LLN0%dsGOOSE1 ,同时根据 key 来过滤重复的 ldnode;
            QString key = p->src_iedName+"%"+acc+"%"+p->src_ldInst+"%LLN0%"+dsELE.attribute("name");

            Point_LDNode *p_ldNode = new Point_LDNode;
            p_ldNode->p = p;
            p_ldNode->ldNode = ldDomNode;

            SUB_GOOSE_LDNode.insert(key,p_ldNode);

            return desc;
        }
    }

    return desc;
}


QString MainWindow::getbType(QString lnType,QString lnClass,QString doName,QString daName)
{
    QString type = "";
    QDomNode lnDONode = xmlhelplib.getChildNode(dataTypeTemplates,QString("LNodeType[@id=%1][@lnClass=%2]/DO[@name=%3]").arg(lnType).arg(lnClass).arg(doName));
    QString doType = lnDONode.toElement().attribute("type");

    QStringList daList = daName.split(".");
    if(daList.size()>1) //mag.f
    {
        QDomNode lnDANode = xmlhelplib.getChildNode(dataTypeTemplates,QString("DOType[@id=%1]/DA[@name=%2]").arg(doType).arg(daList.at(0)));
        QString daType = lnDANode.toElement().attribute("type");

        QDomNode datypeNode = xmlhelplib.getChildNode(dataTypeTemplates,QString("DAType[@id=%1]/BDA[@name=%2]").arg(daType).arg(daList.at(1)));
        type = datypeNode.toElement().attribute("bType");
    }
    else
    {
        QDomNode lnDANode = xmlhelplib.getChildNode(dataTypeTemplates,QString("DOType[@id=%1]/DA[@name=%2]").arg(doType).arg(daName));
        type = lnDANode.toElement().attribute("bType");
    }

    if(type == "BOOLEAN")
    {
        return "BOOL";
    }
    else if (type == "Quality") {
        return "QUALITY";
    }
    else if (type == "Timestamp") {
        return "UTC";
    }
    else if (type == "FLOAT32") {
        return "FLOAT";
    }
    else if(type == "Dbpos")
    {
        return "DBPOS";
    }
    return type.toUpper();
}

QString MainWindow::getFCDADesc(QDomElement fcda,QDomElement lnEle)
{
    if(lnEle.isNull())
    {
        return "";
    }
    QString pointDesc;
    QDomNodeList doiNodes;
    QString doiName = fcda.attribute("doName");
    QString daiName = fcda.attribute("daName");

    if("" != daiName)
    {
        doiName.append(".").append(daiName);
    }

    QDomElement doiEle;
    QList<QString> doiNameList = doiName.split(".");

    doiNodes = lnEle.childNodes();
    pointDesc = lnEle.attribute("desc");

    while(doiNameList.size()>0)
    {
         doiName = doiNameList.at(0);
         for(int i=0;i<doiNodes.size();i++)
         {
             doiEle = doiNodes.at(i).toElement();
             if(doiName == doiEle.attribute("name"))
             {
                 pointDesc = ("" == doiEle.attribute("desc")) ? pointDesc : doiEle.attribute("desc");
                 doiNodes = doiEle.childNodes();
             }
         }
         doiNameList.takeAt(0);
    }

    return pointDesc;
}


void MainWindow::dymicSCDTab(int ind)
{
    if(ind == 0)
    {
        ui->tab_scd->setCurrentIndex(0);
    }
    else
    {
        ui->tab_scd->setCurrentIndex(1);
    }
}

void MainWindow::dymicEHCTab(int ind)
{
    ui->tab_ehc->setCurrentIndex(ind);
}



MainWindow::~MainWindow()
{
    delete ui;
}
