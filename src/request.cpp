#include "request.h"
#include <vector>
#include <iostream>
#include <sstream>


HttpMethod httpMethodfromString(const string data)
{
    HttpMethod method = HttpMethod::UNDEFINED;
    if (data == "GET")
    {
        method = HttpMethod::GET;
    }
    else if (data == "POST")
    {
        method = HttpMethod::POST;
    }
    else if (data == "DELETE")
    {
        method = HttpMethod::DELETE;
    }
    return method;
}

HttpVersion httpVersionfromString(const string data)
{
    //only HTTP/1.1 supported
    HttpVersion version = HttpVersion::UNDEFINED;

    if (data == "HTTP/1.1")
    {
        version = HttpVersion::HTTP_1_1;
    }
    return version;
}

Request::Request(std::string incomeDate)
{
    std::stringstream ss(incomeDate.data());
    std::string to;

    std::getline(ss,to,'\n');
    std::string methodStr, pathStr, versionStr;

    std::stringstream startLine(to.data());
    startLine >> methodStr >> pathStr >> versionStr;
    // end with reading start line (method, path and version)

    method = httpMethodfromString(methodStr);
    version = httpVersionfromString(versionStr);
    uri.path = pathStr;

    // handling the second line(host and port)
    std::getline(ss,to,'\n');
    std::string hostLabelStr, hostAndportStr;
    std::stringstream hostDataInfo(to.data());
    hostDataInfo >> hostLabelStr >> hostAndportStr;

    std::stringstream hostData(hostAndportStr.data());

    std::vector<string> host;
    while(hostData.good())
    {
        string substr;
        getline( hostData, substr, ':' );
        host.push_back(substr);
    }
    uri.host = host.at(0).data();
    uri.port = std::stoi(host.at(1).data());

    bool isData = false, isContextType = false;
    while(ss.good())
    {
        std::getline(ss,to,'\n');
        std::stringstream headerData(to.data());

        if (!isData)
        {
            headerItems.push_back(to);
        }
        else
        {
            data = to;
            isData = false;
        }

        while(headerData.good())
        {
            string substr;
            getline( headerData, substr, ':' );

            if (isContextType)
            {
                MIMEtype = substr;
                isContextType = false;
            }

            if (substr == "Content-Type")
            {
                isContextType = true;
            }
            else if (substr == "\r")
            {
                isData = true;
            }
        }
    }
}


Uri Request::getUri() const
{
    return uri;
}
string Request::getMIME() const
{
    return MIMEtype;
}

HttpMethod Request::getMethod() const
{
    return method;
}

string Request::getData() const
{
    return data;
}

void Request::updateData(const string data)
{
    this->data = data;
}
