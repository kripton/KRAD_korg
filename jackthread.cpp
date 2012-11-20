#include "jackthread.h"

// Implemented in main.cpp
int process_wrapper(jack_nframes_t nframes, void *arg);

JackThread::JackThread() :
    QObject()
{
}

JackThread::~JackThread() {

}

void JackThread::setup() {
    if((client = jack_client_open ("korgKRAD", JackNullOption, NULL)) == 0)
    {
        emit error("Jack server not running?");
    }
    jack_set_process_callback (client, process_wrapper, 0);
    input_port  = jack_port_register (client, "in",  JACK_DEFAULT_MIDI_TYPE, JackPortIsInput , 0);

    if (jack_activate(client))
    {
        emit error("Cannot activate jack client");
    }
}

int JackThread::process(jack_nframes_t nframes, void *arg) {
    Q_UNUSED(arg);
    uint32_t i = 0;
    void* in_port_buf  = jack_port_get_buffer(input_port , nframes);

    jack_midi_event_t in_event;
    jack_nframes_t event_count = jack_midi_get_event_count(in_port_buf);

    //printf ("We have %d events to handle\n", event_count);

    if (!event_count) return 0;

    for (i = 0; i < event_count; i++) {
        jack_midi_event_get(&in_event, in_port_buf, i);

        emit midiEvent((char)in_event.buffer[0], (char)in_event.buffer[1], (char)in_event.buffer[2]);
    }
    return 0;
}
