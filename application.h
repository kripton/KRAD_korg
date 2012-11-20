#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QThread>
#include <QProcess>

#include <QDebug>

#include "jackthread.h"

class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = 0);
    JackThread* worker;

signals:

public slots:
    void midiEvent(char c0, char c1, char c2);

private:
    QProcess *process;
    QStringList arguments;

};

#endif // APPLICATION_H
