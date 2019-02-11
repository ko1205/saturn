#ifndef TEMPLATECONTROL_H
#define TEMPLATECONTROL_H

#include <QObject>
#include <QApplication>
#include <QDomDocument>
#include "templateview.h"

class TemplateControl : public QObject
{
    Q_OBJECT
public:
    explicit TemplateControl(TemplateView *templateView,QObject *parent = 0);
    QStringList readTemplateList();
signals:

public slots:

private:
    void initTemplateFile();
    QDomDocument *domDocument;
    TemplateView *templateViewIns;
    QString localSaveFileName = QApplication::applicationDirPath()+"/template.xml";
};

#endif // TEMPLATECONTROL_H
