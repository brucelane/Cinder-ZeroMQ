
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
	zmq_pollitem_t items[] = {
		{ responder, 0, ZMQ_POLLIN, 0 }
	};

	int npoll = sizeof(items) / sizeof(items[0]);
	int timeout = 1000;

	rc = zmq_poll(items, npoll, timeout);
	if (rc == 0) {
		// timeout
		CI_LOG_W("timeout");
	}
	if (rc < 0) {
		CI_LOG_W("interrupt");
	}
	if (rc > 0) {
		CI_LOG_W("rc");
		if (items[0].revents == ZMQ_POLLIN) {
			// handle REQ-REP
			CI_LOG_W("REQ-REP");
		
			char buffer [10];
			zmq_recv (responder, buffer, 10, 0);
			CI_LOG_W(buffer);
			//zmq_send (responder, "Received", 8, 0);
		}	}


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
