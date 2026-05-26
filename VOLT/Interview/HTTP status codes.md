In system design and API development, HTTP status codes are the "shorthand" communication between a server and a client. They tell the client whether a request was successful, if it needs to do something else, or if the server crashed.

They are grouped into five classes based on the first digit.

---

## 1. 2xx: Success

These indicate that the action was received, understood, and accepted.

- **200 OK:** The standard response for successful HTTP requests.
    
- **201 Created:** The request has been fulfilled and resulted in a new resource being created (common for `POST` requests).
    
- **202 Accepted:** The request has been accepted for processing, but the processing has not been completed. This is crucial for **asynchronous systems** or long-running tasks.
    
- **204 No Content:** The server successfully processed the request but isn't returning any content (common for `DELETE` or `PUT` requests where the client doesn't need a body back).
    

## 2. 3xx: Redirection

The client must take additional action to complete the request.

- **301 Moved Permanently:** Used when a URL has been changed.
    
- **304 Not Modified:** Used for **caching**. It tells the client that the resource hasn't changed, so it can keep using the version it already has.
    

## 3. 4xx: Client Errors

These indicate that the client seems to have erred (e.g., bad syntax or unauthorized access).

- **400 Bad Request:** The server cannot process the request due to a client error (e.g., malformed request syntax).
    
- **401 Unauthorized:** The user lacks valid authentication credentials.
    
- **403 Forbidden:** The server understands the request but refuses to authorize it (even if authenticated, you don't have permission for this specific resource).
    
- **404 Not Found:** The requested resource could not be found.
    
- **429 Too Many Requests:** The user has sent too many requests in a given amount of time ("rate limiting"). This is vital in system design for **API Throttling**.
    

## 4. 5xx: Server Errors

The server failed to fulfill an apparently valid request.

- **500 Internal Server Error:** A generic error message when the server encounters an unexpected condition.
    
- **502 Bad Gateway:** The server was acting as a gateway or proxy and received an invalid response from the upstream server.
    
- **503 Service Unavailable:** The server cannot handle the request (usually due to overload or maintenance).
    
- **504 Gateway Timeout:** The server was acting as a gateway and did not receive a timely response from the upstream server.
    

---

### Comparison Table for System Design

|**Scenario**|**Recommended Status Code**|
|---|---|
|Successfully created a user|`201 Created`|
|Updating a record with no return data|`204 No Content`|
|User tries to access an admin page|`403 Forbidden`|
|API Rate Limit reached|`429 Too Many Requests`|
|Database connection timed out|`504 Gateway Timeout`|
|Microservice A can't reach Microservice B|`502 Bad Gateway`|

Are you looking to implement these within a specific framework like FastAPI or Express, or just preparing for a design interview?