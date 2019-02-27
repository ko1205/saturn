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
        disconnect(templateList,SIGNAL(currentIndexChanged(QString)),this,SLOT(loadTemplate(QString)));
        if(saveTemplateFile(templateName))
        {
            templateList->addItem(templateName);
            templateIndex = templateList->findData(templateName,Qt::DisplayRole);
            templateList->setCurrentIndex(templateIndex);
        }else{
            QMessageBox::information(nullptr,"","save false",QMessageBox::Yes);
        }
        connect(templateList,SIGNAL(currentIndexChanged(QString)),this,SLOT(loadTemplate(QString)));
    }else{
        QMessageBox::information(nullptr,"","already have the same template name",QMessageBox::Yes);
    }
}

void TemplateControl::readTemplateFileLoop(QDomElement &templateElemnet, QStandardItem &parentItem)
{
    QStandardItem *typeItem;
    QDomElement element = templateElemnet.firstChildElement("item");
    while (!element.isNull()) {
        QString itemName = element.attribute("name");
        int type = element.attribute("type").toInt();
        QStandardItem *item = new QStandardItem(itemName);
        item->setData(type,Qt::UserRole);
        switch (type) {
        case 0:
            item->setIcon(folderIcon);
            typeItem = new QStandardItem("folder");
            break;
        case 1:
            item->setData(element.attribute("DigitNum").toInt(),Qt::UserRole+1);
            item->setData(element.attribute("startNum").toInt(),Qt::UserRole+2);
            item->setData(element.attribute("setRenumber").toInt(),Qt::UserRole+3);
            item->setIcon(fileIcon);
            typeItem = new QStandardItem("file copy");
            templateViewIns->addFileCount();
            break;
        case 2:
            item->setData(element.attribute("DigitNum").toInt(),Qt::UserRole+1);
            item->setData(element.attribute("startNum").toInt(),Qt::UserRole+2);
            item->setData(element.attribute("setRenumber").toInt(),Qt::UserRole+3);
            item->setIcon(fileIcon);
            typeItem = new QStandardItem("thumbnail");
            templateViewIns->addFileCount();
            break;

        case 3:
            item->setData(element.attribute("DigitNum").toInt(),Qt::UserRole+1);
            item->setData(element.attribute("startNum").toInt(),Qt::UserRole+2);
            item->setData(element.attribute("setRenumber").toInt(),Qt::UserRole+3);
            item->setIcon(fileIcon);
            typeItem = new QStandardItem("jpeg proxy");
            templateViewIns->addFileCount();
            break;

        case 4:
            item->setData(element.attribute("DigitNum").toInt(),Qt::UserRole+1);
            item->setData(element.attribute("startNum").toInt(),Qt::UserRole+2);
            item->setData(element.attribute("setRenumber").toInt(),Qt::UserRole+3);
            item->setIcon(fileIcon);
            typeItem = new QStandardItem("mov preview");
            templateViewIns->addFileCount();
            break;

        default:
            break;
        }

        readTemplateFileLoop(element,*item);
        parentItem.appendRow(QList<QStandardItem *>() << item << typeItem);

        templateViewIns->expandAll();

        element = element.nextSiblingElement();
    }
}

void TemplateControl::loadTemplate(QString templateName)
{
    QDomElement root = domDocument->documentElement();
    if(root.tagName() == "xml")
    {
        QDomElement element = root.firstChildElement("template");
        while (!element.isNull())
        {
//            if(element.tagName() == "template")
//            {
                if(element.attribute("name") == templateName)
                {
                    break;
                }
//            }
            element = element.nextSiblingElement("template");
        }
        templateViewIns->resetTemplate();
        QStandardItem *item = templateViewIns->root();
        readTemplateFileLoop(element,*item);
        templateViewIns->refreshPreView();

    }
//    QMessageBox::information(nullptr,"",templateName,QMessageBox::Yes);
}

void TemplateControl::deleteTemplate(QString templateName)
{
    QFile file(localSaveFileName);
    if(file.open(QFile::WriteOnly|QFile::Text))
    {
        QTextStream out(&file);
        QDomElement root = domDocument->documentElement();
        if(root.tagName() == "xml")
        {
            QDomElement element = root.firstChildElement("template");
            while (!element.isNull())
            {
                if(element.attribute("name") == templateName)
                {
                    break;
                }
                element = element.nextSiblingElement("template");
            }
            root.removeChild(element);
            domDocument->replaceChild(root,domDocument->documentElement());
            domDocument->save(out,4);
        }
    }

}

void TemplateControl::setIconSetting(QIcon folderIconSet, QIcon fileIconSet)
{
    folderIcon = folderIconSet;
    fileIcon = fileIconSet;
}

void TemplateControl::exportTemplate(QString path, QString templateName)
{
    QDomDocument *exportDoc = new QDomDocument();
    QFile file(path);
    if(file.open(QFile::WriteOnly)|QFile::Text)
    {
        QTextStream out(&file);
        QDomElement root = exportDoc->createElement("xml");
        QDomElement domElement = exportDoc->createElement("template");
        root.appendChild(domElement);
        domElement.setAttribute("name",templateName);
        QStandardItem *item = templateViewIns->root();
        QModelIndex rootIndex = item->index();
        readTemplateViewLoop(domElement,rootIndex);
        exportDoc->appendChild(root);
        exportDoc->save(out,4);
        QMessageBox::information(nullptr,"","export completed",QMessageBox::Yes);
    }else{
       QMessageBox::information(nullptr,"","Save fales",QMessageBox::Yes);
    }

}

bool TemplateControl::importTemplate(QString path)
{
    QFile file(path);
    if(file.open(QFile::ReadOnly|QFile::Text))
    {
        QDomDocument *importDoc = new QDomDocument();
        if(!importDoc->setContent(&file))
        {
            file.close();
            QMessageBox::information(nullptr,"","Invalid save file",QMessageBox::Yes);
            return false;
        }
        file.close();
        QDomElement root = importDoc->documentElement();
        if(root.tagName() == "xml")
        {
            QDomElement element = root.firstChildElement("template");
            templateList->setCurrentIndex(0);
            QStandardItem *item = templateViewIns->root();
            readTemplateFileLoop(element,*item);
            templateViewIns->refreshPreView();
            return true;
        }else{
             QMessageBox::information(nullptr,"","Invalid save file",QMessageBox::Yes);
            return false;
        }
    }else{
        return false;
    }
}
