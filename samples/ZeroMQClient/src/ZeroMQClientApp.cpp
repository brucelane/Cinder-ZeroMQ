
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <zmq.h>

using namespace ci;
using namespace ci::app;

class ZeroMQClientApp : public App {

public:

	void setup() override;
	void cleanup() override;
	void draw() override;
	void update() override;
	void mouseDown(MouseEvent event) override;

	void *context;
	void *requester;

};

void ZeroMQClientApp::setup()
{
	context = zmq_ctx_new();
	requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, "tcp://localhost:5555");
}

void ZeroMQClientApp::update()
{

}

void ZeroMQClientApp::mouseDown(MouseEvent event)
{
	char buffer[10];

	zmq_send(requester, "Hello", 5, 0);
	zmq_recv(requester, buffer, 10, 0);
}

void ZeroMQClientApp::draw()
{

}

void ZeroMQClientApp::cleanup()
{
	zmq_close(requester);
	zmq_ctx_destroy(context);
}


CINDER_APP(ZeroMQClientApp, RendererGl)
