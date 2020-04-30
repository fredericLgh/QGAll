/********************************************************************************
** Form generated from reading UI file 'QImageProc.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QIMAGEPROC_H
#define UI_QIMAGEPROC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QImageProcClass
{
public:

    void setupUi(QWidget *QImageProcClass)
    {
        if (QImageProcClass->objectName().isEmpty())
            QImageProcClass->setObjectName(QString::fromUtf8("QImageProcClass"));
        QImageProcClass->resize(600, 400);

        retranslateUi(QImageProcClass);

        QMetaObject::connectSlotsByName(QImageProcClass);
    } // setupUi

    void retranslateUi(QWidget *QImageProcClass)
    {
        QImageProcClass->setWindowTitle(QApplication::translate("QImageProcClass", "QImageProc", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QImageProcClass: public Ui_QImageProcClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QIMAGEPROC_H
