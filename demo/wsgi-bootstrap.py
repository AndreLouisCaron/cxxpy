# foo.py
#

def call_application(application, environ):
    """Invoke WSGI application handler, collect results and return them."""
    body = []
    status_headers = [None, None]
    def start_response(status, headers):
        status_headers[:] = [status, headers]
        return body.append
    items = application(environ, start_response)
    try:
        for item in items:
            body.append(item)
    finally:
        if hasattr(items, 'close'):
            items.close()
    return (status_headers[0], status_headers[1], ''.join(body))
