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
#include <sstream>

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
                << "HTTP/1.1 " << status << "\r\n";
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

    int init ( py::Object self, py::Tuple args, py::Map kwds )
    {
        return (0);
    }

    py::Object read ( py::Object self, py::Tuple args )
    try
    {
        std::istream& stream = *static_cast<std::istream*>
            (py::TypeBuilder::get_baton(self));
        std::ostringstream payload;
        if ( args.size() == 1 )
        {
            char data[1024];
            long size = py::Int(args[0]);
            for (; (size > 0); size -= stream.gcount()) {
                stream.read(data, std::min(size, long(sizeof(data))));
                payload.write(data, stream.gcount());
            }
        }
        else {
            payload << stream.rdbuf();
        }
        return (py::Bytes(payload.str()));
    }
    catch ( const std::bad_cast& )
    {
        std::cerr << "Bad cast!" << std::endl;
        return (py::None());
    }

    py::Object readline ( py::Object self )
    {
        std::istream& stream = *static_cast<std::istream*>
            (py::TypeBuilder::get_baton(self));
        std::string line;
        if (!std::getline(stream,line)) {
            return (py::None());
        }
        return (py::Bytes(line));
    }

    py::Object readlines ( py::Object self, py::Tuple args )
    {
        std::istream& stream = *static_cast<std::istream*>
            (py::TypeBuilder::get_baton(self));
        py::List lines;
        for (std::string line; (std::getline(stream,line));) {
            lines.append(py::Bytes(line));
        }
        return (lines);
    }

    py::Object iter ( py::Object self )
    {
        return (self);
    }

    py::Object next ( py::Object self )
    {
        const py::Object line = readline(self);
        if (line.handle() == py::none.handle()) {
            return (py::Object());
        }
        return (line);
    }

    py::Object flush ( py::Object self )
    {
        std::ostream& stream = *static_cast<std::ostream*>
            (py::TypeBuilder::get_baton(self));
        stream << std::flush;
        return (py::None());
    }

    py::Object write ( py::Object self, py::Tuple args )
    {
        std::ostream& stream = *static_cast<std::ostream*>
            (py::TypeBuilder::get_baton(self));
        if (args.size() == 1)
        {
            stream << (std::string)py::Bytes(args[0]);
        }
        return (py::None());
    }

    py::Object writelines ( py::Object self, py::Tuple args )
    {
        std::ostream& stream = *static_cast<std::ostream*>
            (py::TypeBuilder::get_baton(self));
        if (args.size() == 1)
        {
            py::Iterator iterator(args[0]);
            while (iterator.next()) {
                stream << (std::string)py::Bytes(iterator.item());
            }
        }
        return (py::None());
    }

}

int main ( int, char ** )
try
{
    // Prepare the interpreter.a
    const py::Library library;

    // Build input stream class for 'wsgi.input' object.
    py::TypeBuilder itype("istream");
    itype.init(py::ctor<&exports::init>());
    itype.add(py::Method("read", py::vararg<&exports::read>()));
    itype.add(py::Method("readline", py::noargs<&exports::readline>()));
    itype.add(py::Method("readlines", py::vararg<&exports::readlines>()));
    itype.iterable(py::noargs<&exports::iter>(),
                  py::noargs<&exports::next>());
    itype.finish();

    // Have 'wsgi.input' object read from standard input stream.
    py::Object istream = itype();
    py::TypeBuilder::set_baton
        (istream, static_cast<std::istream*>(&std::cin));

    // Build output stream class for 'wsgi.errors' object.
    py::TypeBuilder otype("ostream");
    otype.init(py::ctor<&exports::init>());
    otype.add(py::Method("flush", py::noargs<&exports::flush>()));
    otype.add(py::Method("write", py::vararg<&exports::write>()));
    otype.add(py::Method("writelines", py::vararg<&exports::writelines>()));
    otype.finish();

    // Have 'wsgi.errors' object write to standard output stream.
    py::Object ostream = otype();
    py::TypeBuilder::set_baton
        (ostream, static_cast<std::ostream*>(&std::cout));

    // WSGI bootstrap code.
    wsgi::Runner execute("wsgi-bootstrap.py");
    // WSGI application handler.
    wsgi::Application application("sample", "wsgi-application.py");

    // Prepare application execution context.
    py::Map environment;
    // Required CGI-style variables.
    environment.put("REQUEST_METHOD", "GET");  // "GET", "POST", ...
#if 0
    environment.put("SCRIPT_NAME", "");     // Path to application script.
    environment.put("PATH_INFO", "");       // URL delegated to application.
    environment.put("QUERY_STRING", "");    // URL query string.
    environment.put("SERVER_NAME", "");     //
    environment.put("SERVER_PORT", "");     //
    environment.put("SERVER_PROTOCOL", ""); // "HTTP/1.x"
    // Optional CGI-style variables.
    environment.put("CONTENT_TYPE", "");
    environment.put("CONTENT_LENGTH", "");
#endif
#if 0
    // HTTP headers.
    environment.put("HTTP_HOST", "");
    //environment.put(...);
#endif
    // WSGI variables.
    py::Tuple version(2);
    version[0] = py::Int(1);
    version[1] = py::Int(0);
    environment.put("wsgi.version", version);
    environment.put("wsgi.url_scheme", "http");
    environment.put("wsgi.input", istream);
    environment.put("wsgi.errors", ostream);
    environment.put("wsgi.multithread", py::False());
    environment.put("wsgi.multiprocess", py::False());
    environment.put("wsgi.run_once", py::True());

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
