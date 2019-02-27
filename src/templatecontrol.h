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
    void readTemplateFileLoop(QDomElement &templateElemnet,QStandardItem &parentItem);
    void exportTemplate(QString path,QString templateName);
    void setIconSetting(QIcon folderIconSet,QIcon fileIconSet);

    QComboBox *templateList;

signals:

public slots:
    void loadTemplate(QString templateName);
    void deleteTemplate(QString templateName);

private:
    void initTemplateFile();

    QDomDocument *domDocument;
    TemplateView *templateViewIns;
    QString localSaveFileName = QApplication::applicationDirPath()+"/template.xml";
    QIcon folderIcon;
    QIcon fileIcon;
};

#endif // TEMPLATECONTROL_H
