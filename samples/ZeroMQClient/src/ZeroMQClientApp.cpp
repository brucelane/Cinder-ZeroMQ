
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <zmq.h>

using namespace ci;
using namespace ci::app;

class ZeroMQClientApp : public App {

public:

    void setup();
    void draw();
    void update();
    void mouseDown(MouseEvent event);

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
	int request_nbr;
	for (request_nbr = 0; request_nbr != 10; request_nbr++) {
		char buffer[10];
		printf("Sending Hello %d…\n", request_nbr);
		zmq_send(requester, "Hello", 5, 0);
		zmq_recv(requester, buffer, 10, 0);
		printf("Received World %d\n", request_nbr);
	}
	zmq_close(requester);
	zmq_ctx_destroy(context);
}

void ZeroMQClientApp::draw()
{

}


CINDER_APP(ZeroMQClientApp, RendererGl)
