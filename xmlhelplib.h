#ifndef XMLHELPLIB_H
#define XMLHELPLIB_H

#include <QtXml>
#include "xmlhelplib_global.h"


class XMLHELPLIBSHARED_EXPORT XMLHelpLib
{
public:
    XMLHelpLib();
    int loadXML(QString fileName);

    QDomNode selectSingleNode(QString xpath);
    QList<QDomNode> selectNodesList(QString xpath);
    QList<QDomNode> getChildNodes(QDomNode parentNode,QString xpath);//***
    QDomNode getChildNode(QDomNode parentNode,QString xpath);//***
    QDomNode selectNodeByIndex(int index);

    QDomNode getChildNode(int index);
    QString getAttribute(const QString atrributeName);
    QString getNodeValue();
    QDomNode getCurrentNode();
    int getChildCount();

    QString getXMLType();
    void setXMLType(QString xmlType);

    ~XMLHelpLib();
    QDomDocument document;

private:
    QDomNode search(QDomElement parentElement,QString xpath);
    QList<QDomNode> searchNodesList(QDomElement parentElement, QString xpath);

    QDomNode searchNode(QDomElement parentElement,QString xpath);

private:
    QRegExp regAttr;
    QRegExp regIndex;

    QDomNode curNode;
    QString xmlType;
};

#endif // XMLHELPLIB_H
