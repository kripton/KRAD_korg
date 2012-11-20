#include <QCoreApplication>
#include <QThread>

#include "application.h"

Application* app;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    app = new Application();

    return a.exec();
}

int process_wrapper(jack_nframes_t nframes, void *arg) {
    return app->worker->process(nframes, arg);
}
