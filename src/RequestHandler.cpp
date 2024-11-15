#include "RequestHandler.h"

RequestHandler::RequestHandler() {
    m_pool.start();
}

RequestHandler::~RequestHandler() {
    m_pool.stop();
}
