
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <memory>

namespace database {
    using row_t = std::vector<std::string>;
    using db_t = std::unordered_map<std::string, std::vector<std::string>>;

    class db {
     public:
        auto insert_row(std::string const& key, row_t const& row) -> bool {
            return false;
        }

        auto update_row(std::string const& key, row_t const& data) -> bool {
            return false;
        }

     private:
        std::string filename_;
        std::ifstream in_stream_;
        std::ofstream out_stream_;
        std::unique_ptr<db_t> handler_;
        
        static auto split(std::string const& delimiter, std::string const& s, row_t& out) -> void {
            size_t pos = 0;
            auto token = std::string{};
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                out.push_back(token);
            }
        }


     public:
        explicit db(std::string f)
        : filename_{std::move(f)}, handler_{std::make_unique<db_t>()}  {
            if (not in_stream_) {
                throw std::runtime_error("Unable to open file.");
            }

            std::vector<std::string> in_row;
            std::copy(std::istream_iterator<std::string>(in_stream_), {}, std::inserter(in_row, in_row.end()));
            if (in_stream_.bad()) {
                std::runtime_error("I/O error while reading");
            }
            if (!in_stream_.eof()) {
                std::runtime_error("Didn't reach end of file");
            }


            for(auto const& r : in_row) {
                auto out = row_t{};
                split(",", r, out);
                handler_->at(out[0]) = out;
            }

        };
        ~db() = default;
    };

} // namespace database
