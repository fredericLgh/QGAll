/********************************************************************************
** Form generated from reading UI file 'QImageProcWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QIMAGEPROCWIDGET_H
#define UI_QIMAGEPROCWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QImageProcWidgetClass
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *m_pLableModel;
    QLabel *m_pLabelFrame;
    QLabel *m_pLableTransmit;
    QLabel *m_pLabelMsg;
    QPushButton *m_pRtnState;
    QLabel *label_3;
    QLabel *m_pLabelServer;

    void setupUi(QWidget *QImageProcWidgetClass)
    {
        if (QImageProcWidgetClass->objectName().isEmpty())
            QImageProcWidgetClass->setObjectName(QString::fromUtf8("QImageProcWidgetClass"));
        QImageProcWidgetClass->resize(393, 578);
        label = new QLabel(QImageProcWidgetClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 90, 54, 12));
        label_2 = new QLabel(QImageProcWidgetClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 130, 54, 12));
        m_pLableModel = new QLabel(QImageProcWidgetClass);
        m_pLableModel->setObjectName(QString::fromUtf8("m_pLableModel"));
        m_pLableModel->setGeometry(QRect(30, 545, 181, 21));
        m_pLabelFrame = new QLabel(QImageProcWidgetClass);
        m_pLabelFrame->setObjectName(QString::fromUtf8("m_pLabelFrame"));
        m_pLabelFrame->setGeometry(QRect(100, 90, 251, 16));
        m_pLabelFrame->setFrameShape(QFrame::Box);
        m_pLableTransmit = new QLabel(QImageProcWidgetClass);
        m_pLableTransmit->setObjectName(QString::fromUtf8("m_pLableTransmit"));
        m_pLableTransmit->setGeometry(QRect(100, 130, 251, 16));
        m_pLableTransmit->setFrameShape(QFrame::Box);
        m_pLabelMsg = new QLabel(QImageProcWidgetClass);
        m_pLabelMsg->setObjectName(QString::fromUtf8("m_pLabelMsg"));
        m_pLabelMsg->setGeometry(QRect(30, 170, 311, 331));
        m_pLabelMsg->setFrameShape(QFrame::Box);
        m_pRtnState = new QPushButton(QImageProcWidgetClass);
        m_pRtnState->setObjectName(QString::fromUtf8("m_pRtnState"));
        m_pRtnState->setGeometry(QRect(30, 20, 75, 23));
        label_3 = new QLabel(QImageProcWidgetClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(160, 25, 111, 21));
        m_pLabelServer = new QLabel(QImageProcWidgetClass);
        m_pLabelServer->setObjectName(QString::fromUtf8("m_pLabelServer"));
        m_pLabelServer->setGeometry(QRect(283, 30, 61, 21));

        retranslateUi(QImageProcWidgetClass);

        QMetaObject::connectSlotsByName(QImageProcWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *QImageProcWidgetClass)
    {
        QImageProcWidgetClass->setWindowTitle(QApplication::translate("QImageProcWidgetClass", "QImageProc", nullptr));
        label->setText(QApplication::translate("QImageProcWidgetClass", "\345\233\276\345\203\217\347\272\277\347\250\213", nullptr));
        label_2->setText(QApplication::translate("QImageProcWidgetClass", "\344\274\240\350\276\223\347\272\277\347\250\213", nullptr));
        m_pLableModel->setText(QApplication::translate("QImageProcWidgetClass", "\345\244\204\347\220\206\346\250\241\345\235\227", nullptr));
        m_pLabelFrame->setText(QString());
        m_pLableTransmit->setText(QString());
        m_pLabelMsg->setText(QString());
        m_pRtnState->setText(QString());
        label_3->setText(QApplication::translate("QImageProcWidgetClass", "View     Camera", nullptr));
        m_pLabelServer->setText(QApplication::translate("QImageProcWidgetClass", "\346\234\215\345\212\241\345\231\250\350\277\236\346\216\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QImageProcWidgetClass: public Ui_QImageProcWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QIMAGEPROCWIDGET_H
