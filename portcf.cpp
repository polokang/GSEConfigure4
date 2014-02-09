#include "portcf.h"
#include "ui_portcf.h"

PortCf::PortCf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PortCf)
{
    ui->setupUi(this);
    port1 = qFindChild<QCheckBox*>(this, "checkBox");
    port2 = qFindChild<QCheckBox*>(this, "checkBox_2");
    port3 = qFindChild<QCheckBox*>(this, "checkBox_3");
    port4 = qFindChild<QCheckBox*>(this, "checkBox_4");
    port5 = qFindChild<QCheckBox*>(this, "checkBox_5");
    port6 = qFindChild<QCheckBox*>(this, "checkBox_6");
    port7 = qFindChild<QCheckBox*>(this, "checkBox_7");
    port8 = qFindChild<QCheckBox*>(this, "checkBox_8");
    port9 = qFindChild<QCheckBox*>(this, "checkBox_9");
    port10 = qFindChild<QCheckBox*>(this, "checkBox_10");

}


void PortCf::resetPort(QString portList)
{
    QStringList ports = portList.split("-");
    clearPort();
    int port = 0;
    for(int i=0;i<ports.size();i++)
    {
        QString portStr = ports[i];
        if(portStr != "")
        {
            port = portStr.toInt();
            setPortId(port);
        }
    }
}


void PortCf::setPortId(int portid)
{
    switch(portid)
    {
    case 1:
    {
        port1->setChecked(true);
        break;
    }
    case 2:
    {
        port2->setChecked(true);
        break;
    }
    case 3:
    {
        port3->setChecked(true);
        break;
    }
    case 4:
    {
        port4->setChecked(true);
        break;
    }
    case 5:
    {
        port5->setChecked(true);
        break;
    }
    case 6:
    {
        port6->setChecked(true);
        break;
    }
    case 7:
    {
        port7->setChecked(true);
        break;
    }
    case 8:
    {
        port8->setChecked(true);
        break;
    }
    case 9:
    {
        port9->setChecked(true);
        break;
    }
    case 10:
    {
        port10->setChecked(true);
        break;
    }
    default:
    {
        break;
    }
    }
}

QString PortCf::getPortsID()
{
    if(port1->checkState() == Qt::Checked)
    {
        curPortsID = "1";
    }
    if(port2->checkState() == Qt::Checked)
    {
        curPortsID = curPortsID+"|2";
    }
    if(port3->checkState() == Qt::Checked)
    {
        curPortsID = curPortsID+"|3";
    }
    if(port4->checkState() == Qt::Checked)
    {
        curPortsID = curPortsID+"|4";
    }
    if(port5->checkState() == Qt::Checked)
    {
        curPortsID = curPortsID+"|5";
    }
    if(port6->checkState() == Qt::Checked)
    {
        curPortsID = curPortsID+"|6";
    }
    if(port7->checkState() == Qt::Checked)
    {
        curPortsID = curPortsID+"|7";
    }
    if(port8->checkState() == Qt::Checked)
    {
        curPortsID = curPortsID+"|8";
    }
    if(port9->checkState() == Qt::Checked)
    {
        curPortsID = curPortsID+"|9";
    }
    if(port10->checkState() == Qt::Checked)
    {
        curPortsID = curPortsID+"|10";
    }

    if(curPortsID.startsWith("|"))
    {
        curPortsID = curPortsID.right(curPortsID.size()-1);
    }

    if(curPortsID.endsWith("|"))
    {
        curPortsID = curPortsID.left(curPortsID.size()-1);
    }
    return curPortsID;
}

void PortCf::clearPort()
{
    curPortsID = "";
    port1->setChecked(false);
    port2->setChecked(false);
    port3->setChecked(false);
    port4->setChecked(false);
    port5->setChecked(false);
    port6->setChecked(false);
    port7->setChecked(false);
    port8->setChecked(false);
    port9->setChecked(false);
    port10->setChecked(false);
}

PortCf::~PortCf()
{
    delete ui;
}
