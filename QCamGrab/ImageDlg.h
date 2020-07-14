#ifndef QIMAGEDLG_H
#define QIMAGEDLG_H

#include <QWidget>

class QNovieSimpleImageWidget;
class QTimer;

class QImageDlg : public QWidget
{
    Q_OBJECT
public:
    explicit QImageDlg(QWidget *parent = nullptr);
    ~QImageDlg();
signals:

public slots:

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void InitWnd();
    void ExitWnd();
    void TimeOut();

private:
    QNovieSimpleImageWidget *m_pImageWidget;
    QTimer                  *m_pTimer;
};

#endif // QIMAGEDLG_H
