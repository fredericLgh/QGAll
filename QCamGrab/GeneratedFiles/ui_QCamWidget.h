/********************************************************************************
** Form generated from reading UI file 'QCamWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCAMWIDGET_H
#define UI_QCAMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QCamWidgetClass
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QLabel *m_lbCamName;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLabel *m_lbWarning;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *m_leExp;
    QLabel *label_2;
    QPushButton *m_pbExpSetTime;
    QHBoxLayout *horizontalLayout;
    QLabel *label3;
    QLineEdit *m_leGain;
    QLabel *label_4;
    QPushButton *m_pbGainSet;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label4;
    QLabel *m_lbCoilID;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLabel *m_lbFrameID;
    QPushButton *m_pbImg;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *m_lePath;
    QPushButton *m_pbSelectPath;
    QPushButton *m_pbRecord;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QLabel *m_lbCompressionTime;

    void setupUi(QWidget *QCamWidgetClass)
    {
        if (QCamWidgetClass->objectName().isEmpty())
            QCamWidgetClass->setObjectName(QString::fromUtf8("QCamWidgetClass"));
        QCamWidgetClass->resize(380, 336);
        widget = new QWidget(QCamWidgetClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 40, 301, 271));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_8->addWidget(label_6);

        m_lbCamName = new QLabel(widget);
        m_lbCamName->setObjectName(QString::fromUtf8("m_lbCamName"));
        m_lbCamName->setTextFormat(Qt::PlainText);

        horizontalLayout_8->addWidget(m_lbCamName);


        gridLayout->addLayout(horizontalLayout_8, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_7->addWidget(label_7);

        m_lbWarning = new QLabel(widget);
        m_lbWarning->setObjectName(QString::fromUtf8("m_lbWarning"));

        horizontalLayout_7->addWidget(m_lbWarning);


        gridLayout->addLayout(horizontalLayout_7, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        m_leExp = new QLineEdit(widget);
        m_leExp->setObjectName(QString::fromUtf8("m_leExp"));

        horizontalLayout_4->addWidget(m_leExp);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        m_pbExpSetTime = new QPushButton(widget);
        m_pbExpSetTime->setObjectName(QString::fromUtf8("m_pbExpSetTime"));

        horizontalLayout_4->addWidget(m_pbExpSetTime);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label3 = new QLabel(widget);
        label3->setObjectName(QString::fromUtf8("label3"));
        QFont font;
        font.setPointSize(12);
        label3->setFont(font);

        horizontalLayout->addWidget(label3);

        m_leGain = new QLineEdit(widget);
        m_leGain->setObjectName(QString::fromUtf8("m_leGain"));
        m_leGain->setFont(font);

        horizontalLayout->addWidget(m_leGain);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setTextFormat(Qt::AutoText);

        horizontalLayout->addWidget(label_4);

        m_pbGainSet = new QPushButton(widget);
        m_pbGainSet->setObjectName(QString::fromUtf8("m_pbGainSet"));

        horizontalLayout->addWidget(m_pbGainSet);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label4 = new QLabel(widget);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setFont(font);

        horizontalLayout_2->addWidget(label4);

        m_lbCoilID = new QLabel(widget);
        m_lbCoilID->setObjectName(QString::fromUtf8("m_lbCoilID"));
        m_lbCoilID->setFont(font);
        m_lbCoilID->setFrameShape(QFrame::NoFrame);

        horizontalLayout_2->addWidget(m_lbCoilID);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        m_lbFrameID = new QLabel(widget);
        m_lbFrameID->setObjectName(QString::fromUtf8("m_lbFrameID"));

        horizontalLayout_5->addWidget(m_lbFrameID);

        m_pbImg = new QPushButton(widget);
        m_pbImg->setObjectName(QString::fromUtf8("m_pbImg"));

        horizontalLayout_5->addWidget(m_pbImg);


        horizontalLayout_3->addLayout(horizontalLayout_5);


        gridLayout->addLayout(horizontalLayout_3, 4, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_lePath = new QLineEdit(widget);
        m_lePath->setObjectName(QString::fromUtf8("m_lePath"));

        horizontalLayout_6->addWidget(m_lePath);

        m_pbSelectPath = new QPushButton(widget);
        m_pbSelectPath->setObjectName(QString::fromUtf8("m_pbSelectPath"));

        horizontalLayout_6->addWidget(m_pbSelectPath);

        m_pbRecord = new QPushButton(widget);
        m_pbRecord->setObjectName(QString::fromUtf8("m_pbRecord"));

        horizontalLayout_6->addWidget(m_pbRecord);


        gridLayout->addLayout(horizontalLayout_6, 5, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_9->addWidget(label_8);

        m_lbCompressionTime = new QLabel(widget);
        m_lbCompressionTime->setObjectName(QString::fromUtf8("m_lbCompressionTime"));

        horizontalLayout_9->addWidget(m_lbCompressionTime);


        gridLayout->addLayout(horizontalLayout_9, 6, 0, 1, 1);


        retranslateUi(QCamWidgetClass);
        QObject::connect(m_pbSelectPath, SIGNAL(clicked()), m_lePath, SLOT(selectAll()));

        QMetaObject::connectSlotsByName(QCamWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *QCamWidgetClass)
    {
        QCamWidgetClass->setWindowTitle(QApplication::translate("QCamWidgetClass", "QCamGrab", nullptr));
        label_6->setText(QApplication::translate("QCamWidgetClass", "\350\241\250\351\235\242\347\274\272\351\231\267\346\243\200\346\265\213\347\263\273\347\273\237", nullptr));
        m_lbCamName->setText(QApplication::translate("QCamWidgetClass", "Camera", nullptr));
        label_7->setText(QApplication::translate("QCamWidgetClass", "\347\233\270\346\234\272\351\207\207\351\233\206\350\277\233\347\250\213", nullptr));
        m_lbWarning->setText(QApplication::translate("QCamWidgetClass", "TextLabel", nullptr));
        label->setText(QApplication::translate("QCamWidgetClass", "\350\256\276\345\256\232\346\233\235\345\205\211\346\227\266\351\227\264\357\274\232", nullptr));
        label_2->setText(QApplication::translate("QCamWidgetClass", "\345\276\256\347\247\222", nullptr));
        m_pbExpSetTime->setText(QApplication::translate("QCamWidgetClass", "\350\256\276\345\256\232", nullptr));
        label3->setText(QApplication::translate("QCamWidgetClass", "\345\242\236\347\233\212\357\274\232", nullptr));
        label_4->setText(QApplication::translate("QCamWidgetClass", "   1-9", nullptr));
        m_pbGainSet->setText(QApplication::translate("QCamWidgetClass", "\350\256\276\345\256\232", nullptr));
        label4->setText(QApplication::translate("QCamWidgetClass", "CoilID\357\274\232", nullptr));
        m_lbCoilID->setText(QString());
        label_3->setText(QApplication::translate("QCamWidgetClass", "\345\270\247\344\277\241\346\201\257", nullptr));
        m_lbFrameID->setText(QString());
        m_pbImg->setText(QApplication::translate("QCamWidgetClass", "\345\233\276\345\203\217", nullptr));
        m_pbSelectPath->setText(QApplication::translate("QCamWidgetClass", "\351\200\211\346\213\251", nullptr));
        m_pbRecord->setText(QApplication::translate("QCamWidgetClass", "\345\275\225\345\210\266", nullptr));
        label_8->setText(QApplication::translate("QCamWidgetClass", "\345\216\213\347\274\251\350\200\227\346\227\266\357\274\232", nullptr));
        m_lbCompressionTime->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QCamWidgetClass: public Ui_QCamWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCAMWIDGET_H
