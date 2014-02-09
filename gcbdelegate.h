#ifndef GCBDELEGATE_H
#define GCBDELEGATE_H

#include <QtGui/QStyledItemDelegate>
#include "common.h"
#include "portcf.h"

class Gcbdelegate : public QStyledItemDelegate
{

public:
    Gcbdelegate(QObject *paren=0);

private:
    PortCf *portcf;

private:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;


private slots:
    void commitAndCloseEditor();
};

#endif // GCBDELEGATE_H
