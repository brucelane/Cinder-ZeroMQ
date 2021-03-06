
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include <zmq.h>

using namespace ci;
using namespace ci::app;

class _TBOX_PREFIX_App : public App {

public:

    void setup() override;
    void cleanup() override;
    void draw() override;
    void update() override;
    void mouseDown(MouseEvent event) override;

    void *context;
    void *responder;
    int rc ;
};

void _TBOX_PREFIX_App::setup()
{
    context = zmq_ctx_new();
    responder = zmq_socket(context, ZMQ_REP);
    rc = zmq_bind(responder, "tcp://*:5555");
    if (rc != 0) {
        CI_LOG_E("Failed to create the ZeroMQ binding.");
        quit();
    }
}

void _TBOX_PREFIX_App::update()
{
    char buffer [10];
    zmq_recv (responder, buffer, 10, 0);
    printf ("Received Hello\n");
    //sleep (1);          //  Do some 'work'
    zmq_send (responder, "World", 5, 0);
}

void _TBOX_PREFIX_App::mouseDown(MouseEvent event)
{
    
}

void _TBOX_PREFIX_App::draw()
{

}

void _TBOX_PREFIX_App::cleanup()
{

}

CINDER_APP(_TBOX_PREFIX_App, RendererGl)
