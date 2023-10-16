#include <iostream>
#include "requestdispatcher.h"

using namespace std;

RequestDispatcher::RequestDispatcher()
{

}

string RequestDispatcher::handleIt(std::shared_ptr<Request> req)
{
    string reply = "HTTP/1.1 404 Not Found\r\n";

    bool itemExist = false;
    switch(req.get()->getMethod())
    {
    case HttpMethod::GET:
        for(auto &it: requestsStorage)
        {
            if (it.get()->getUri().path == req.get()->getUri().path)
            {
                itemExist = true;
                cout << "GET:"<< req.get()->getUri().path << " item" << endl;
                reply = "HTTP/1.1 200 OK\r\n Content-Type: application/json \r\n" + it.get()->getData() + "\r\n";
                break;
            }
        }
        if (!itemExist)
        {
            cout << "GET:"<< req.get()->getUri().path <<"Not Found" << endl;
            reply = "HTTP/1.1 404 Not Found\r\n";
        }
        break;
    case HttpMethod::POST:
        if (requestsStorage.empty())
        {
            requestsStorage.emplace_back(req);
            cout << "POST:"<< req.get()->getUri().path <<" New item is added(first)" << endl;
        }
        else
        {
            for(auto &it: requestsStorage)
            {
                if (it.get()->getUri().path == req.get()->getUri().path)
                {
                    cout << "POST:" << req.get()->getUri().path <<" Item updated" << endl;
                    it->updateData(req->getData());
                    itemExist = true;
                    break;
                }
            }
            if(!itemExist)
            {
                cout << "POST:" << req.get()->getUri().path << " New item is added" << endl;
                requestsStorage.push_back(req);
            }
        }
        reply = "HTTP/1.1 200 OK\r\n";
        break;
    case HttpMethod::DELETE:
        for(auto it = requestsStorage.begin(); it != requestsStorage.end(); it++)
        {
            if (it->get()->getUri().path == req.get()->getUri().path)
            {
                cout << "DELETE:" << req.get()->getUri().path <<" Item deleted" << endl;;
                requestsStorage.erase(it);
                itemExist = true;
                reply = "HTTP/1.1 200 OK\r\n";
                break;
            }
        }
        if (!itemExist)
        {
            cout << "DELETE:"<< req.get()->getUri().path << " Not Found" << endl;
            reply = "HTTP/1.1 404 Not Found\r\n";
        }
        break;
    case HttpMethod::UNDEFINED:
        break;
    }
    std::cout.flush();
    return reply;
}
