// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

/*!
 * @file demo/main.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 *
 * @brief WSGI boostrap code, in C++.
 */

#include "python.hpp"
#include <iostream>

namespace wsgi {

    /*!
     * @brief WSGI gateway bootstrap mechanism.
     *
     * The WSGI specification is somewhat touchy to implement directly using
     * the Python C API.  This helper loads a piece of Python code that wraps
     * the WSGI logic into a synchronous interface.  This simplified interface
     * allows to write a WSGI gateway quickly at the cost of requiring the
     * gateway to buffer the complete response in memory before formatting it
     * as an HTTP response and sending it to the client.
     *
     * The buffering required by the simplified interface may seem very
     * limiting, but it has other very valuable side-effects.  First, in the
     * event that the gateway starts sending the HTTP response before the
     * response body is finished generating, the gateway cannot map an error
     * (exception) in the application handler to an HTTP error response
     * because the HTTP status line and headers have already been sent.
     * Second, if the application handler does not know the length of the body
     * because it is being generated dynamically, the gateway can add the
     * HTTP @c Content-Length header to the HTTP response before returning it
     * to the client.
     */
    class Runner
    {
        /* data. */
    private:
        py::Module   myModule;
        py::Callable myWrapper;

        /* construction. */
    public:
        /*!
         * @brief Load WSGI bootstrap in the Python source file at @a path.
         */
        Runner ( const std::string& path )
            : myModule(py::Module::load("wsgi", path)),
              myWrapper(myModule.symbol("call_application"))
        {
        }

        /* operators. */
    public:
        /*!
         * @brief Invokes the WSGI application callable.
         * @param bootstrap Python function that wraps WSGI logic
         * @param application WSGI application callable
         * @param environment WSGI environment dictionary
         */
        const py::Tuple operator()
            ( py::Callable application, py::Map environment ) const
        {
            py::Tuple arguments(2);
            arguments[0] = application;
            arguments[1] = environment;
            return (py::Tuple(myWrapper(arguments)));
        }
    };

    /*!
     * @brief WSGI application handler.
     *
     * A WSGI application handler provides a two-argument callable that takes
     * an @c environ dictionary and a @c start_response callable.  This
     * callable is invoked by the WSGI implementation to have the application
     * process an HTTP request.
     *
     * This class performs the task of loading a Python source file as a
     * module and resolving the WSGI callable by name.  Use a @c Runner
     * instance to execute the resolved callable.
     *
     * @see http://www.python.org/dev/peps/pep-0333/
     */
    class Application
    {
        /* data. */
    private:
        py::Module   myModule;
        py::Callable myCallable;

        /* construction. */
    public:
        /*!
         * @brief Load an application handler and resolve the callable.
         * @param name Name the loaded module will be given.
         * @param path Path to the source code for the application handler.
         */
        Application ( const std::string& name, const std::string& path )
            : myModule(py::Module::load(name, path)),
              myCallable(myModule.symbol("app"))
        {
        }

        /* operators. */
    public:
        /*!
         * @brief Use the @c Application instance as its callable.
         */
        operator const py::Callable& () const
        {
            return (myCallable);
        }
    };

    /*!
     * @brief Split WSGI application response parts and invoke HTTP handler.
     * @param response 3-Tuple received from @c wsgi::call().
     * @param handler 3-parameter function object that receives response parts.
     *
     * The handler function object requires 3 parameters:
     *
     * @li @c status the HTTP status line (minus the HTTP version);
     * @li @c headers a list of pairs of strings with HTTP headers;
     * @li @c body the response body.
     */
    template<typename Handler>
    void http_response ( const py::Tuple response, Handler handler )
    {
          // Collect WSGI application response parts.
        const py::Bytes status (response[0]);
        const py::List  headers(response[1]);
        const py::Bytes body   (response[2]);
          // Process response parts using handler.
        handler(status, headers, body);
    }

    /*!
     * @brief Sample HTTP response handler that prints to an @c std::ostream.
     */
    class ostream_handler
    {
        /* data. */
    private:
        std::ostream& myStream;

        /* construction. */
    public:
        /*!
         * @brief Build a handler that writes to @a stream.
         * @param stream Standard output stream, defaults to @c std::cout.
         */
        ostream_handler ( std::ostream& stream=std::cout )
            : myStream(stream)
        {}

        /* operators. */
    public:
        /*!
         * @brief Format a WSGI application response as an HTTP response.
         * @param status HTTP status line (without the HTTP version)
         * @param headers a list of pairs of strings with HTTP headers
         * @param body the response body
         */
        void operator() ( const py::Bytes& status,
            const py::List& headers, const py::Bytes& body )
        {
              // Send status line.
            myStream
                << "HTTP/1.1" << status << "\r\n";
            bool contentlength = false;
              // Send headers.
            for ( py::ssize_t i = 0; (i < headers.size()); ++i )
            {
                const py::Tuple header(headers[i]);
                const py::Bytes field(header[0]);
                const py::Bytes value(header[1]);
                if ( field == "Content-Length" ) {
                    contentlength = true;
                }
                myStream
                    << field << ": " << value << "\r\n";
            }
              // More headers (if desired).
            if ( !contentlength ) {
                myStream
                    << "Content-Length" << ": " << body.size() << "\r\n";
            }
              // Send body.
            myStream
                << "\r\n" << body;
        }
    };

}

namespace exports {

    int __init__ ( py::Object self, py::Tuple args, py::Map kwds )
    {
        return (0);
    }

    py::Object read ( py::Object self, py::Tuple args )
    {
        if ( args.size() == 1 )
        {
            // integer with number of bytes...
        }
        return (py::None());
    }

    py::Object readline ( py::Object self )
    {
        return (py::None());
    }

    py::Object readlines ( py::Object self, py::Tuple args )
    {
        if ( args.size() == 1 )
        {
            // integer with number of bytes...
        }
        return (py::None());
    }

}

int main ( int, char ** )
try
{
    // Prepare the interpreter.a
    const py::Library library;

    // Export class to Python.
    py::TypeBuilder type("Export");
    type.init(py::ctor<&exports::__init__>());
    type.add(py::Method("read", py::vararg<&exports::read>()));
    type.finish();
    py::Object instance = type();

    // WSGI bootstrap code.
    wsgi::Runner execute("wsgi-bootstrap.py");
    // WSGI application handler.
    wsgi::Application application("sample", "wsgi-application.py");

    // Prepare application execution context.
    py::Map environment;
#if 0
    // Required CGI-style variables.
    environment.put("REQUEST_METHOD", "");  // "GET", "POST", ...
    environment.put("SCRIPT_NAME", "");     // Path to application script.
    environment.put("PATH_INFO", "");       // URL delegated to application.
    environment.put("QUERY_STRING", "");    // URL query string.
    environment.put("SERVER_NAME", "");     //
    environment.put("SERVER_PORT", "");     //
    environment.put("SERVER_PROTOCOL", ""); // "HTTP/1.x"
    // Optional CGI-style variables.
    environment.put("CONTENT_TYPE", "");
    environment.put("CONTENT_LENGTH", "");
    // HTTP headers.
    environment.put("HTTP_HOST", "");
    //environment.put("", "");
    // WSGI variables.
    environment.put("wsgi.version", "");      // tuple(1, 0)
    environment.put("wsgi.url_scheme", "");   // "http" or "https"
#endif
    environment.put("wsgi.input", instance);  // file-like object.
#if 0
    environment.put("wsgi.errors", "");       // file-like object.
    environment.put("wsgi.multithread", "");  // boolean
    environment.put("wsgi.multiprocess", ""); // boolean
    environment.put("wsgi.run_once", "");     // boolean
#endif

    // Execute application and print HTTP response to "cout".
    wsgi::http_response(execute(application, environment),
                        wsgi::ostream_handler(std::cout));
}
catch ( const py::SystemError& error )
{
    std::cerr
        << "Error: '" << error.message() << "'."
        << std::endl;
    return (EXIT_FAILURE);
}
catch ( const py::Error& )
{
    std::cerr
        << "Error: 'some python error'."
        << std::endl;
    return (EXIT_FAILURE);
}
catch ( const std::exception& error )
{
    std::cerr
        << "Error: '" << error.what() << "'."
        << std::endl;
    return (EXIT_FAILURE);
}
