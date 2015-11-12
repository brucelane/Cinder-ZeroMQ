
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include <zmq.h>

using namespace ci;
using namespace ci::app;

class ZeroMQServerApp : public App {

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

void ZeroMQServerApp::setup()
{
    context = zmq_ctx_new();
    responder = zmq_socket(context, ZMQ_REP);
    rc = zmq_bind(responder, "tcp://*:5555");
	if (rc != 0) {
		CI_LOG_E("Failed to create the ZeroMQ binding.");
		quit();
	}
}

void ZeroMQServerApp::update()
{
    char buffer [10];
    zmq_recv (responder, buffer, 10, 0);
    printf ("Received Hello\n");
    //sleep (1);          //  Do some 'work'
    zmq_send (responder, "World", 5, 0);
}

void ZeroMQServerApp::mouseDown(MouseEvent event)
{
    
}

void ZeroMQServerApp::draw()
{

}

void ZeroMQServerApp::cleanup()
{
	zmq_ctx_destroy(context);
}

CINDER_APP(ZeroMQServerApp, RendererGl)
