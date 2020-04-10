/********************************************************************************
** Form generated from reading UI file 'QCamGrab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCAMGRAB_H
#define UI_QCAMGRAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QCamGrabClass
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *PB_Img;
    QLabel *label_7;
    QLabel *label_6;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *ImageItem;
    QPushButton *pushButton_3;
    QPushButton *PB_Record;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QLabel *label_5;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *exposure;
    QLabel *label_2;
    QPushButton *m_SetTime;

    void setupUi(QWidget *QCamGrabClass)
    {
        if (QCamGrabClass->objectName().isEmpty())
            QCamGrabClass->setObjectName(QString::fromUtf8("QCamGrabClass"));
        QCamGrabClass->resize(512, 321);
        layoutWidget = new QWidget(QCamGrabClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(220, 180, 179, 25));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        PB_Img = new QPushButton(layoutWidget);
        PB_Img->setObjectName(QString::fromUtf8("PB_Img"));

        horizontalLayout_5->addWidget(PB_Img);

        label_7 = new QLabel(QCamGrabClass);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(60, 80, 91, 16));
        label_6 = new QLabel(QCamGrabClass);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(50, 40, 111, 16));
        layoutWidget_2 = new QWidget(QCamGrabClass);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(30, 270, 435, 27));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        ImageItem = new QLineEdit(layoutWidget_2);
        ImageItem->setObjectName(QString::fromUtf8("ImageItem"));

        horizontalLayout_2->addWidget(ImageItem);

        pushButton_3 = new QPushButton(layoutWidget_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        PB_Record = new QPushButton(layoutWidget_2);
        PB_Record->setObjectName(QString::fromUtf8("PB_Record"));

        horizontalLayout_2->addWidget(PB_Record);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        horizontalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_6->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_8 = new QLabel(layoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_3->addWidget(label_8);

        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);


        horizontalLayout_6->addLayout(horizontalLayout_3);

        layoutWidget_3 = new QWidget(QCamGrabClass);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(60, 130, 336, 25));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget_3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        exposure = new QLineEdit(layoutWidget_3);
        exposure->setObjectName(QString::fromUtf8("exposure"));

        horizontalLayout_4->addWidget(exposure);

        label_2 = new QLabel(layoutWidget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        m_SetTime = new QPushButton(layoutWidget_3);
        m_SetTime->setObjectName(QString::fromUtf8("m_SetTime"));

        horizontalLayout_4->addWidget(m_SetTime);


        retranslateUi(QCamGrabClass);
        QObject::connect(pushButton_3, SIGNAL(clicked()), ImageItem, SLOT(selectAll()));

        QMetaObject::connectSlotsByName(QCamGrabClass);
    } // setupUi

    void retranslateUi(QWidget *QCamGrabClass)
    {
        QCamGrabClass->setWindowTitle(QApplication::translate("QCamGrabClass", "QCamGrab", nullptr));
        label_3->setText(QApplication::translate("QCamGrabClass", "\345\270\247\344\277\241\346\201\257", nullptr));
        label_4->setText(QApplication::translate("QCamGrabClass", "TextLabel", nullptr));
        PB_Img->setText(QApplication::translate("QCamGrabClass", "\345\233\276\345\203\217", nullptr));
        label_7->setText(QApplication::translate("QCamGrabClass", "\347\233\270\346\234\272\351\207\207\351\233\206\350\277\233\347\250\213", nullptr));
        label_6->setText(QApplication::translate("QCamGrabClass", "\350\241\250\351\235\242\347\274\272\351\231\267\346\243\200\346\265\213\347\263\273\347\273\237", nullptr));
        pushButton_3->setText(QApplication::translate("QCamGrabClass", "\351\200\211\346\213\251", nullptr));
        PB_Record->setText(QApplication::translate("QCamGrabClass", "\345\275\225\345\210\266", nullptr));
        label_8->setText(QApplication::translate("QCamGrabClass", "\345\216\213\347\274\251\350\200\227\346\227\266\357\274\232", nullptr));
        label_5->setText(QApplication::translate("QCamGrabClass", "TextLabel", nullptr));
        label->setText(QApplication::translate("QCamGrabClass", "\350\256\276\345\256\232\346\233\235\345\205\211\346\227\266\351\227\264\357\274\232", nullptr));
        label_2->setText(QApplication::translate("QCamGrabClass", "\345\276\256\347\247\222", nullptr));
        m_SetTime->setText(QApplication::translate("QCamGrabClass", "\350\256\276\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QCamGrabClass: public Ui_QCamGrabClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCAMGRAB_H
