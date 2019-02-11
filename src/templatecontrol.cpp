#include "templatecontrol.h"
#include <QFIle>
#include <QTextStream>

TemplateControl::TemplateControl(TemplateView *templateView,QObject *parent) : QObject(parent)
{
    templateViewIns = templateView;
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
