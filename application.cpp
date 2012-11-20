#include "application.h"

Application::Application(QObject *parent) :
    QObject(parent)
{
    // Start the JACK-thread
    QThread* thread = new QThread;
    worker = new JackThread();
    worker->moveToThread(thread);
    //connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), worker, SLOT(setup()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(worker, SIGNAL(midiEvent(char, char, char)), this, SLOT(midiEvent(char, char, char)));

    thread->start();
}

void Application::midiEvent(char c0, char c1, char c2) {
    if ((uchar)c0 != 0xb0) return;
    qDebug() << "MIDI event:" << QString("Channel 0x%1 Value: 0x%2")
                .arg((short)c1,2,16, QChar('0'))
                .arg((short)c2,2,16, QChar('0'));

    float opacity = 0.0f;

    opacity = (float)c2 / (float)127;

    switch (c1) {
      case 0x00:
        // Fader 1
        process = new QProcess();
        arguments.clear();
        arguments << "jukuz" << "setport" << "2" << "10" << "40" << "160" << "120" << "0" << "0" << "160" << "120" << QString("%1").arg(opacity) << "0";
        process->start("/usr/bin/krad_radio", arguments);
        process->waitForFinished();
        process->~QProcess();
        process = NULL;
        break;
      case 0x01:
        // Fader 2
        process = new QProcess();
        arguments.clear();
        arguments << "jukuz" << "setport" << "3" << "180" << "40" << "160" << "120" << "0" << "0" << "160" << "120" << QString("%1").arg(opacity) << "0";
        process->start("/usr/bin/krad_radio", arguments);
        process->waitForFinished();
        process->~QProcess();
        process = NULL;
        break;
      case 0x02:
        // Fader 3
        process = new QProcess();
        arguments.clear();
        arguments << "jukuz" << "setport" << "1" << "0" << "0" << "640" << "360" << "0" << "0" << "640" << "360" << QString("%1").arg(opacity) << "0";
        process->start("/usr/bin/krad_radio", arguments);
        process->waitForFinished();
        process->~QProcess();
        process = NULL;
        break;
    }
}
