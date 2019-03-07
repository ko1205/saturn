#include "platesequenceview.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

SequenceNameInputDialog::SequenceNameInputDialog(QWidget *parent)
    :QDialog (parent)
{
    QLabel *valueLabel = new QLabel("Value");
    QLabel *startNumLabel = new QLabel("Start Number");
    QLabel *stapNumLabel = new QLabel("Stap");

    valueEdit = new QLineEdit("C###");
    startNumSpin = new QSpinBox();
    stapNumSpin = new QSpinBox();

    startNumSpin->setValue(10);
    stapNumSpin->setValue(10);

    QPushButton *okButton = new QPushButton("Ok");
    QPushButton *cancelButton = new QPushButton("Cancel");

    QGridLayout *buttonLayout = new QGridLayout();
    buttonLayout->addWidget(okButton,0,1);
    buttonLayout->addWidget(cancelButton,0,2);
    buttonLayout->setColumnStretch(0,1);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(valueLabel,0,0);
    layout->addWidget(startNumLabel,1,0);
    layout->addWidget(stapNumLabel,2,0);

    layout->addWidget(valueEdit,0,1);
    layout->addWidget(startNumSpin,1,1);
    layout->addWidget(stapNumSpin,2,1);

    layout->addLayout(buttonLayout,4,1);
    layout->setRowStretch(3,1);

    setLayout(layout);

    connect(cancelButton,SIGNAL(clicked(bool)),this,SLOT(reject()));
    connect(okButton,SIGNAL(clicked(bool)),this,SLOT(acceptValue()));
}

SequenceNameInputDialog::~SequenceNameInputDialog()
{

}

void SequenceNameInputDialog::acceptValue()
{
    QString value = valueEdit->text();
    int start = startNumSpin->value();
    int stap = stapNumSpin->value();
    emit sendeValue(value,start,stap);
    accept();
}

PlateSequenceView::PlateSequenceView(QWidget *parent)
    :QTableView (parent)
{
    removeSelectedAct = new QAction("remove selected");
    itemUpAct = new QAction("Up");
    itemDownAct = new QAction("Down");
    singleDataInputAct = new QAction("Single Data Input");
    sequentialDataInputAct = new QAction("Sequential Data Input");

    connect(removeSelectedAct,SIGNAL(triggered(bool)),this,SLOT(removeSelected()));
    connect(itemUpAct,SIGNAL(triggered(bool)),this,SLOT(itemUp()));
    connect(itemDownAct,SIGNAL(triggered(bool)),this,SLOT(itemDown()));
    connect(singleDataInputAct,SIGNAL(triggered(bool)),this,SLOT(singleDataInput()));
    connect(sequentialDataInputAct,SIGNAL(triggered(bool)),this,SLOT(sequentialDataInput()));
}

void PlateSequenceView::contextMenuEvent(QContextMenuEvent *event)
{
    contextPos = event->y();
    QMenu *popupMenu = new QMenu(this);
    QMenu *inputMenu = popupMenu->addMenu("Multiple Data Input");
    popupMenu->addSeparator();
    popupMenu->addAction(itemUpAct);
    popupMenu->addAction(itemDownAct);
    popupMenu->addSeparator();
    popupMenu->addAction(removeSelectedAct);
    inputMenu->addAction(singleDataInputAct);
    inputMenu->addAction(sequentialDataInputAct);
    popupMenu->exec(event->globalPos());

}

void PlateSequenceView::testFunc()
{
    int index = rowAt(contextPos);
    QModelIndexList lists =  selectedIndexes();
    qDebug() << index;
    foreach (QModelIndex index, lists) {
        qDebug() << index.row() << " " << index.column();
    }
    model()->removeRow(index);
}

void PlateSequenceView::removeSelected()
{
    QModelIndexList list = selectedIndexes();
    while (!list.isEmpty()) {
        model()->removeRow(list[0].row());
        list = selectedIndexes();
    }
}

void PlateSequenceView::itemUp()
{
    int preItemIndex = 0;
    QModelIndexList list = selectedIndexes();
    qSort(list.begin(),list.end(),qLess<QModelIndex>());
    if(list[0].row() != 0){
        foreach (QModelIndex index, list) {
            if(index.row() != preItemIndex){
                model()->moveRow(QModelIndex(),index.row(),QModelIndex(),index.row()-1);
            }
            preItemIndex = index.row();
        }
    }
}

void PlateSequenceView::itemDown()
{
    int preItemIndex = -1;
    QModelIndexList list = selectedIndexes();
    qSort(list.begin(),list.end(),qGreater<QModelIndex>());
    if(list.first().row() != model()->rowCount()-1){
        foreach (QModelIndex index, list) {
            if(index.row() != preItemIndex){
                model()->moveRow(QModelIndex(),index.row(),QModelIndex(),index.row()+2);
            }
            preItemIndex = index.row();
        }
    }
}

bool PlateSequenceView::isValidSelected(QModelIndexList &list)
{
    int count = list.count();
    int col = list.first().column();
    if(col < 4 || col > 6 ){
        return false;
    }
    for (int i = 0; i < count; i++) {
        if(list.at(i).column() != col)
        {
            return false;
        }
    }
    return true;
}

void PlateSequenceView::singleDataInput()
{
    bool ok;
    bool isSelectedOK;
    QModelIndexList list = selectedIndexes();
    if (list.isEmpty()) {
        QMessageBox::information(this,"Waring","No Selected",QMessageBox::Yes);
    }else{
        isSelectedOK = isValidSelected(list);
        if(!isSelectedOK)
        {
            QMessageBox::information(this,"Waring","Selected is not valid",QMessageBox::Yes);
        }else {
            QString value = QInputDialog::getText(this,"Single Data Input", "Value",QLineEdit::Normal,"",&ok);
            if(ok && !value.isEmpty()){
                for (int i = 0;i<list.count();i++) {
                    model()->setData(list.at(i),value,Qt::DisplayRole);
                }
            }
        }
    }
}

void PlateSequenceView::sequentialDataInput()
{
    bool isSelectedOK;
    QModelIndexList list = selectedIndexes();
    if (list.isEmpty()) {
        QMessageBox::information(this,"Waring","No Selected",QMessageBox::Yes);
    }else{
        isSelectedOK = isValidSelected(list);
        if(!isSelectedOK)
        {
            QMessageBox::information(this,"Waring","Selected is not valid",QMessageBox::Yes);
        }else {
            SequenceNameInputDialog *inputDialog = new SequenceNameInputDialog(this);
            connect(inputDialog,SIGNAL(sendeValue(QString,int,int)),this,SLOT(writeSequenceValue(QString,int,int)));
            inputDialog->exec();
        }
    }
}

void PlateSequenceView::writeSequenceValue(QString valueText, int startNum, int stapNum)
{
    QModelIndexList list = selectedIndexes();
    QRegExp *regex = new QRegExp("(\\w*)(#+)");
    if(regex->indexIn(valueText) != -1)
    {
        QString text = regex->cap(1);
        QString Number = regex->cap(2);

        QString pattern = text + QString("%1");

        int DigiCount = Number.count();

        for (int i = 0; i < list.count(); ++i) {
            QString value = pattern.arg(startNum+(i*stapNum),DigiCount,10,QLatin1Char('0'));
            model()->setData(list.at(i),value,Qt::DisplayRole);
        }

    }else{
        QMessageBox::information(this,"","Invalid Sequence Name",QMessageBox::Yes);
    }

}

