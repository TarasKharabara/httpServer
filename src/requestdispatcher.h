#ifndef REQUESTDISPATCHER_H
#define REQUESTDISPATCHER_H

#include <unistd.h>
#include <thread>
#include <queue>
#include <memory>
#include "request.h"

//!  A RequestDispatcher class.
/*!
  This class will manage all request and give the answer
*/
class RequestDispatcher
{
public:
    RequestDispatcher();
    string handleIt(std::shared_ptr<Request> req);

private:
    std::vector<std::shared_ptr<Request>> requestsStorage;
};

#endif // REQUESTDISPATCHER_H
