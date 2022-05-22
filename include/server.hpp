#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/streams.h>

#include <string>
#include <unordered_map>

namespace server {
    using http_request = web::http::http_request;
    using http_methods = web::http::methods;
    using db_t = std::unordered_map<std::string, std::vector<std::string>>;

    static inline auto trace(auto const& msg) -> void {
        std::wcout << msg << '\n';
    }

    // NOLINTNEXTLINE
    auto handle_get(http_request req) -> void {
        // auto req_body = req.extract_json().get();
        auto ans = web::json::value::object();

        // req.reply(web::http

        (void)req;
    }
    // NOLINTNEXTLINE
    auto handle_post(http_request req) -> void {
        (void)req;
    }
    // NOLINTNEXTLINE
    auto handle_put(http_request req) -> void {
        (void)req;
    }
    // NOLINTNEXTLINE
    auto handle_del(http_request req) -> void {
        (void)req;
    }

    class server {
     private:
        std::string url_;
        db_t database_;

     public:
        server() = default;
        ~server() = default;
    };

} // namespace server
