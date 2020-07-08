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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QCamWidgetClass
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLabel *m_lbFrameID;
    QPushButton *m_pbImg;
    QLabel *label_7;
    QLabel *label_6;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *m_leExp;
    QLabel *label_2;
    QPushButton *m_pbExpSetTime;
    QLabel *m_lbCamName;
    QLabel *label4;
    QLabel *m_lbCoilID;
    QLabel *label_8;
    QLabel *m_lbCompressionTime;
    QLineEdit *m_leGain;
    QLabel *label3;
    QLineEdit *m_lePath;
    QPushButton *m_pbSelectPath;
    QPushButton *m_pbRecord;
    QPushButton *m_pbGainSet;
    QLabel *label_4;
    QLabel *m_lbWarning;

    void setupUi(QWidget *QCamWidgetClass)
    {
        if (QCamWidgetClass->objectName().isEmpty())
            QCamWidgetClass->setObjectName(QString::fromUtf8("QCamWidgetClass"));
        QCamWidgetClass->resize(512, 321);
        layoutWidget = new QWidget(QCamWidgetClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(160, 200, 199, 25));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        m_lbFrameID = new QLabel(layoutWidget);
        m_lbFrameID->setObjectName(QString::fromUtf8("m_lbFrameID"));

        horizontalLayout_5->addWidget(m_lbFrameID);

        m_pbImg = new QPushButton(layoutWidget);
        m_pbImg->setObjectName(QString::fromUtf8("m_pbImg"));

        horizontalLayout_5->addWidget(m_pbImg);

        label_7 = new QLabel(QCamWidgetClass);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(70, 80, 91, 16));
        label_6 = new QLabel(QCamWidgetClass);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(50, 40, 111, 16));
        layoutWidget_3 = new QWidget(QCamWidgetClass);
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

        m_leExp = new QLineEdit(layoutWidget_3);
        m_leExp->setObjectName(QString::fromUtf8("m_leExp"));

        horizontalLayout_4->addWidget(m_leExp);

        label_2 = new QLabel(layoutWidget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        m_pbExpSetTime = new QPushButton(layoutWidget_3);
        m_pbExpSetTime->setObjectName(QString::fromUtf8("m_pbExpSetTime"));

        horizontalLayout_4->addWidget(m_pbExpSetTime);

        m_lbCamName = new QLabel(QCamWidgetClass);
        m_lbCamName->setObjectName(QString::fromUtf8("m_lbCamName"));
        m_lbCamName->setGeometry(QRect(300, 40, 45, 10));
        m_lbCamName->setTextFormat(Qt::PlainText);
        label4 = new QLabel(QCamWidgetClass);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setGeometry(QRect(50, 200, 61, 20));
        QFont font;
        font.setPointSize(12);
        label4->setFont(font);
        m_lbCoilID = new QLabel(QCamWidgetClass);
        m_lbCoilID->setObjectName(QString::fromUtf8("m_lbCoilID"));
        m_lbCoilID->setGeometry(QRect(90, 200, 81, 31));
        m_lbCoilID->setFont(font);
        m_lbCoilID->setFrameShape(QFrame::NoFrame);
        label_8 = new QLabel(QCamWidgetClass);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(180, 290, 50, 14));
        m_lbCompressionTime = new QLabel(QCamWidgetClass);
        m_lbCompressionTime->setObjectName(QString::fromUtf8("m_lbCompressionTime"));
        m_lbCompressionTime->setGeometry(QRect(250, 290, 100, 14));
        m_leGain = new QLineEdit(QCamWidgetClass);
        m_leGain->setObjectName(QString::fromUtf8("m_leGain"));
        m_leGain->setGeometry(QRect(140, 168, 101, 25));
        m_leGain->setFont(font);
        label3 = new QLabel(QCamWidgetClass);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setGeometry(QRect(80, 170, 41, 20));
        label3->setFont(font);
        m_lePath = new QLineEdit(QCamWidgetClass);
        m_lePath->setObjectName(QString::fromUtf8("m_lePath"));
        m_lePath->setGeometry(QRect(40, 250, 113, 19));
        m_pbSelectPath = new QPushButton(QCamWidgetClass);
        m_pbSelectPath->setObjectName(QString::fromUtf8("m_pbSelectPath"));
        m_pbSelectPath->setGeometry(QRect(170, 250, 62, 19));
        m_pbRecord = new QPushButton(QCamWidgetClass);
        m_pbRecord->setObjectName(QString::fromUtf8("m_pbRecord"));
        m_pbRecord->setGeometry(QRect(240, 250, 62, 19));
        m_pbGainSet = new QPushButton(QCamWidgetClass);
        m_pbGainSet->setObjectName(QString::fromUtf8("m_pbGainSet"));
        m_pbGainSet->setGeometry(QRect(320, 170, 75, 23));
        label_4 = new QLabel(QCamWidgetClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(250, 180, 54, 12));
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setTextFormat(Qt::AutoText);
        m_lbWarning = new QLabel(QCamWidgetClass);
        m_lbWarning->setObjectName(QString::fromUtf8("m_lbWarning"));
        m_lbWarning->setGeometry(QRect(310, 70, 81, 41));

        retranslateUi(QCamWidgetClass);
        QObject::connect(m_pbSelectPath, SIGNAL(clicked()), m_lePath, SLOT(selectAll()));

        QMetaObject::connectSlotsByName(QCamWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *QCamWidgetClass)
    {
        QCamWidgetClass->setWindowTitle(QApplication::translate("QCamWidgetClass", "QCamGrab", nullptr));
        label_3->setText(QApplication::translate("QCamWidgetClass", "\345\270\247\344\277\241\346\201\257", nullptr));
        m_lbFrameID->setText(QString());
        m_pbImg->setText(QApplication::translate("QCamWidgetClass", "\345\233\276\345\203\217", nullptr));
        label_7->setText(QApplication::translate("QCamWidgetClass", "\347\233\270\346\234\272\351\207\207\351\233\206\350\277\233\347\250\213", nullptr));
        label_6->setText(QApplication::translate("QCamWidgetClass", "\350\241\250\351\235\242\347\274\272\351\231\267\346\243\200\346\265\213\347\263\273\347\273\237", nullptr));
        label->setText(QApplication::translate("QCamWidgetClass", "\350\256\276\345\256\232\346\233\235\345\205\211\346\227\266\351\227\264\357\274\232", nullptr));
        label_2->setText(QApplication::translate("QCamWidgetClass", "\345\276\256\347\247\222", nullptr));
        m_pbExpSetTime->setText(QApplication::translate("QCamWidgetClass", "\350\256\276\345\256\232", nullptr));
        m_lbCamName->setText(QApplication::translate("QCamWidgetClass", "Camera", nullptr));
        label4->setText(QApplication::translate("QCamWidgetClass", "CoilID\357\274\232", nullptr));
        m_lbCoilID->setText(QString());
        label_8->setText(QApplication::translate("QCamWidgetClass", "\345\216\213\347\274\251\350\200\227\346\227\266\357\274\232", nullptr));
        m_lbCompressionTime->setText(QString());
        label3->setText(QApplication::translate("QCamWidgetClass", "\345\242\236\347\233\212\357\274\232", nullptr));
        m_pbSelectPath->setText(QApplication::translate("QCamWidgetClass", "\351\200\211\346\213\251", nullptr));
        m_pbRecord->setText(QApplication::translate("QCamWidgetClass", "\345\275\225\345\210\266", nullptr));
        m_pbGainSet->setText(QApplication::translate("QCamWidgetClass", "\350\256\276\345\256\232", nullptr));
        label_4->setText(QApplication::translate("QCamWidgetClass", "   1-9", nullptr));
        m_lbWarning->setText(QApplication::translate("QCamWidgetClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QCamWidgetClass: public Ui_QCamWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCAMWIDGET_H
