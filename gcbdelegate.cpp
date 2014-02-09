#include "gcbdelegate.h"

Gcbdelegate::Gcbdelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    portcf = new PortCf;
}


void Gcbdelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter,option,index);
}

QWidget *Gcbdelegate:: createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int col = index.column();
    QLineEdit *lineEdit = new QLineEdit(parent);
    QString txt = index.data(Qt::DisplayRole).toString().trimmed();

    if(col == 3 || col == 4)
    {
        portcf->resetPort(txt);
        if(portcf->exec() == QDialog::Accepted)
        {
            txt = portcf->getPortsID();
        }
    }
    lineEdit->setText(txt);

//    connect(lineEdit,SIGNAL(editingFinished()),this,SLOT(commitAndCloseEditor()));
    return lineEdit;
}

void Gcbdelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    lineEdit->setText(lineEdit->displayText());
}

void Gcbdelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    model->setData(index, lineEdit->displayText());
}

void Gcbdelegate::commitAndCloseEditor()
{
    QLineEdit *edit = qobject_cast<QLineEdit *>(sender());
    emit commitData(edit);
    emit closeEditor(edit);
}
