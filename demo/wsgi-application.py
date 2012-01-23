# bar.py
#

def app(environ, start_response):
    start_response('200 OK', [('Content-Type', 'text/plain')])
    environ['wsgi.input'].read()
    yield 'Hello, World!\n'
