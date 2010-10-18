#ifndef QGSTHREAD_H
#define QGSTHREAD_H

#include <QThread>

class QGSThread : public QThread
{
    Q_OBJECT
public:
    explicit QGSThread(QObject *parent = 0);

signals:

public slots:

};

#endif // QGSTHREAD_H
