#ifndef TEMPLATECONTROL_H
#define TEMPLATECONTROL_H

#include <QObject>
#include <QApplication>
#include <QDomDocument>
#include "templateview.h"
#include <QComboBox>

class TemplateControl : public QObject
{
    Q_OBJECT
public:
    explicit TemplateControl(TemplateView *templateView,QComboBox *templateCombo,QObject *parent = 0);
    QStringList readTemplateList();
    bool saveTemplateFile(QString templateName);
    void saveTemplateList(QString templateName);
    void readTemplateViewLoop(QDomElement &templateElement,QModelIndex &index);
signals:

public slots:

private:
    void initTemplateFile();

    QComboBox *templateList;
    QDomDocument *domDocument;
    TemplateView *templateViewIns;
    QString localSaveFileName = QApplication::applicationDirPath()+"/template.xml";
};

#endif // TEMPLATECONTROL_H
