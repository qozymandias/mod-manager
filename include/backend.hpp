#include "../include/server.hpp"

#include <cpprest/http_listener.h>

#include <string>
#include <thread>
#include <utility>

namespace backend {
    using http_listener = web::http::experimental::listener::http_listener;
    using http_uri = web::http::uri;
    using http_methods = web::http::methods;

    class handler {
     private:
        std::string uri_;
        backend::http_listener listener_;
        server::server server_;

     public:
        handler(std::string const& url, std::string const& port, std::string const& path)
        : uri_{build_url(url, port, path)}
        , listener_{backend::http_listener(uri_.c_str())} {};

        ~handler() {
            listener_.close();
        }

        auto run() -> void {
            handler::setup_handlers();

            try {
                listener_.open().then([]() { handler::trace("Listening ... "); }).wait();

                while (true) {
                }

            } catch (std::exception const& e) {
                handler::trace(e.what());
            }
        }

     private:
        static inline auto build_url(std::string const& url, std::string const& port, std::string const& path)
            -> std::string {
            return url + std::string{":"} + port + std::string{"/"} + path;
        }

        auto setup_handlers() -> void {
            listener_.support(server::http_methods::GET, server::handle_get);
            listener_.support(server::http_methods::POST, server::handle_post);
            listener_.support(server::http_methods::PUT, server::handle_put);
            listener_.support(server::http_methods::DEL, server::handle_del);
        }

        static inline auto trace(auto const& msg) -> void {
            std::wcout << msg << '\n';
        }
    };

} // namespace backend
