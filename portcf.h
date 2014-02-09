#ifndef PORTCF_H
#define PORTCF_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class PortCf;
}

class PortCf : public QDialog
{
    Q_OBJECT

public:
    explicit PortCf(QWidget *parent = 0);
    ~PortCf();

    QCheckBox *port1;
    QCheckBox *port2;
    QCheckBox *port3;
    QCheckBox *port4;
    QCheckBox *port5;
    QCheckBox *port6;
    QCheckBox *port7;
    QCheckBox *port8;
    QCheckBox *port9;
    QCheckBox *port10;

    void resetPort(QString portList);
    void clearPort();
    void setPortId(int portid);
    QString getPortsID();
private:
    Ui::PortCf *ui;
    QString curPortsID;
};

#endif // PORTCF_H
