/**************************************
  ��    ��:  novice   
  ��    ��:  QTray.h   
  ��    ��:  Qt ����   
  ��    ��:  1.0   
  ĩ���޸�:  2019/08/02   
  ��������:  OnActivated ���������   


***************************************/

#ifndef QTRAY_H
#define QTRAY_H

#include <QMenu>
#include <QSystemTrayIcon>

namespace novice
{
	class QTray : public QSystemTrayIcon
	{
		Q_OBJECT

	public:
		QTray(QWidget *parent, const QIcon& icon);
		~QTray();

		void SetShowIcon(const QIcon& icon);
		void SetHideIcon(const QIcon& icon);
		void SetExitIcon(const QIcon& icon);

	signals:
		void ShowWindow();
		void HideWindow();
		void ExitWindow();

	private slots:
		void OnActivated(QSystemTrayIcon::ActivationReason reason);
	private:
		void InitAction();
	private:
		QMenu*     m_pMenu;

		QAction*   m_pActionShow;
		QAction*   m_pActionHide;
		QAction*   m_pActionExit;
	};
};



#endif // QTRAY_H
