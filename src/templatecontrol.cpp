#include "templatecontrol.h"
#include <QFile>
#include <QTextStream>
#include <QComboBox>
#include <QMessageBox>

TemplateControl::TemplateControl(TemplateView *templateView,QComboBox *templateCombo,QObject *parent) : QObject(parent)
{
    templateViewIns = templateView;
    templateList = templateCombo;
    domDocument = new QDomDocument;
}

void TemplateControl::initTemplateFile()
{
    QFile file(localSaveFileName);
    if(file.open(QFile::WriteOnly|QFile::Text))
    {
        QTextStream out(&file);
        domDocument->clear();
        QDomElement root = domDocument->createElement("xml");
        domDocument->appendChild(root);
        domDocument->save(out,4);
        file.close();
    }
}

QStringList TemplateControl::readTemplateList()
{
    QStringList templateNames;
    QFile file(localSaveFileName);
    if(file.open(QFile::ReadOnly|QFile::Text))
    {
        if(!domDocument->setContent(&file))
        {
            file.close();
            initTemplateFile();
            return templateNames;
        }
        file.close();
        QDomElement root = domDocument->documentElement();
        if(root.tagName()=="xml")
        {
            QDomElement element = root.firstChildElement();
            while(!element.isNull())
            {
                if(element.tagName()=="template")
                {
                    templateNames.append(element.attribute("name"));
                }
                element = element.nextSiblingElement();
            }
        }
        return templateNames;
    }else{
        initTemplateFile();
        return templateNames;
    }
}

void TemplateControl::readTemplateViewLoop(QDomElement &templateElement, QModelIndex &index)
{
    bool hasChildren = templateViewIns->model()->hasChildren();
    if(hasChildren)
    {

        QAbstractItemModel *model = templateViewIns->model();
        int count = model->rowCount(index);
        for(int i = 0; i < count; i++)
        {
            QModelIndex childrenIndex = model->index(i,0,index);
            QString data = model->data(childrenIndex,Qt::DisplayRole).toString();
            int type = model->data(childrenIndex,Qt::UserRole).toInt();
            QDomElement element = domDocument->createElement("item");
            element.setAttribute("name",data);
            element.setAttribute("type",type);
            if(type){
                element.setAttribute("DigitNum",model->data(childrenIndex,Qt::UserRole+1).toInt());
                element.setAttribute("startNum",model->data(childrenIndex,Qt::UserRole+2).toInt());
                element.setAttribute("setRenumber",model->data(childrenIndex,Qt::UserRole+3).toUInt());
            }
            templateElement.appendChild(element);
            readTemplateViewLoop(element,childrenIndex);
        }
    }

}

bool TemplateControl::saveTemplateFile(QString templateName)
{
    QFile file(localSaveFileName);
    if(file.open(QFile::WriteOnly|QFile::Text))
    {
        QTextStream out(&file);
        QDomElement root = domDocument->documentElement();
        if(root.tagName()=="xml")
        {
            QDomElement domElement = domDocument->createElement("template");
            root.appendChild(domElement);
            domElement.setAttribute("name",templateName);
            QStandardItem *item = templateViewIns->root();
            QModelIndex rootIndex = item->index();
            readTemplateViewLoop(domElement,rootIndex);
            domDocument->replaceChild(root,domDocument->documentElement());
            domDocument->save(out,4);
            return true;
        }
    }else{
        return false;
    }

}

void TemplateControl::saveTemplateList(QString templateName)
{
    int templateIndex;
    if(templateList->findText(templateName)==-1)
    {
        if(saveTemplateFile(templateName))
        {
            templateList->addItem(templateName);
            templateIndex = templateList->findData(templateName,Qt::DisplayRole);
            templateList->setCurrentIndex(templateIndex);
        }else{
            QMessageBox::information(nullptr,"","save false",QMessageBox::Yes);
        }
    }else{
        QMessageBox::information(nullptr,"","already have the same template name",QMessageBox::Yes);
    }
}
