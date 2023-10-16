#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <vector>
using namespace std;

/** An enum type.
*  A list of supported http methods!
*/
enum class HttpMethod {
    GET,
    POST,
    DELETE,
    UNDEFINED = -1
};

/** An enum type.
*  A list of http version, for now only http 1.1 supported
*/
enum class HttpVersion {
    HTTP_0_9,
    HTTP_1_0,
    HTTP_1_1,
    HTTP_2_0,
    UNDEFINED = -1
};

/** An enum type.
*  A list of status code
*/
enum class HttpStatusCode {

    Ok = 200,           /**< enum value 200 status(OK) */
    NotFount = 404,   /**< enum value 404 status(Not found) */
    UNDEFINED = -1
};

/** An enum type.
* URI structure to keep scheme, host, port and path
*/
struct Uri
{
    std::string scheme;
    std::string host;
    std::uint16_t port;
    std::string path;
};

//! Will convert http method into emun mothod code
/*!
    \param http method in string representation
    \return http method in enum representation
*/
HttpMethod httpMethodfromString(const std::string data);

//! Will convert http version into emun version code
/*!
    \param http version in string representation
    \return http version in enum representation
*/
HttpVersion httpVersionfromString(const std::string data);


//!  A Request class.
/*!
  This class include all components of client requests
*/
class Request
{
public:
    Request(std::string incomeDate);
    HttpMethod getMethod() const;
    Uri getUri() const;
    string getMIME() const;
    string getData() const;
    void updateData(const string data);
private:
    HttpMethod method;
    HttpVersion version;
    Uri uri;
    vector<string> headerItems;
    string MIMEtype;
    string data;
};

#endif // REQUEST_H
