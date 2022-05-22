#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <utility>
#include <vector>
// #include <ranges>

#include <cmath>
#include <random>
#include <thread>

namespace life {

    using board_t = std::vector<std::vector<int>>;

    struct player {
        player() = default;
        ~player() = default;

        player(std::pair<int, int> cords, char ic)
        : x{static_cast<std::size_t>(cords.first)}
        , y{static_cast<std::size_t>(cords.second)}
        , icon{ic} {}

        std::size_t x;
        std::size_t y;
        char icon;
    };

    class game_of_life {
     public:
        game_of_life() = default;
        ~game_of_life() = default;

        explicit game_of_life(int const size) {
            board_ = board_t(size, std::vector<int>(size, 0));
            player_ = player({size / 2, size / 2}, '0');
        }

        explicit game_of_life(board_t b)
        : board_{std::move(b)} {};

        game_of_life(game_of_life& g) noexcept {
            this->board_ = board_t(g.board_);
            this->player_ = g.player_;
        }

        game_of_life(game_of_life&& g) noexcept {
            this->board_ = board_t(std::move(g.board_));
            mt_ = std::mt19937{rd_()};
        }

        auto operator=(game_of_life&& g) noexcept -> game_of_life& {
            this->board_ = board_t(std::move(g.board_));
            return *this;
        }

        [[nodiscard]] auto get_player() const -> player {
            return player_;
        }

        auto get_player() -> player& {
            return player_;
        }

        [[nodiscard]] auto get_board() const -> board_t {
            return board_;
        }

        auto get_board() -> board_t& {
            return board_;
        }

        auto update() -> void {
            for (std::size_t i = 0; i < board_.size(); ++i) {
                for (std::size_t j = 0; j < board_[i].size(); ++j) {
                    auto c = count_live_neighbors(board_, static_cast<int>(i), static_cast<int>(j));
                    if (c == 3 or (board_[i][j] != 0 and c == 2)) {
                        board_[i][j] |= 0b10;
                    }
                }
            }
            for (auto& row : board_) {
                for (auto& cell : row) {
                    cell >>= 1;
                }
            }
            player_.x = player_.x;
            player_.y = player_.y;
        }

        auto populate_cell(int l, int h) -> void {
            normal_dist_ = std::uniform_int_distribution<int>(l, h);
            for (std::size_t i = 0; i < get_board().size(); ++i) {
                for (std::size_t j = 0; j < board_[i].size(); ++j) {
                    auto const n = normal_dist_(mt_);
                    board_[i][j] = player_.x != i and player_.y != j and equation(i, j, n) ? 1 : 0;
                }
            }
        }

        auto print(std::function<int(const unsigned)> const& printer, char const delim) -> void {
            // board_[player_.x][player_.y] = 0b1;
            for (auto const& rows : get_board()) {
                for (auto const& cell : rows) {
                    printer(cell == 0b1 ? '*' : ' ');
                    printer(delim);
                }
                printer('\n');
            }
        }

        /*
        auto print(std::function<int(const char*)> const& printer, char const delim) -> void {
            for (std::size_t i = 0; i < board_.size(); ++i) {
                printer(mk_string(board_[i], static_cast<int>(i), delim).c_str());
            }
        }*/

        /*
        auto print(WINDOW* wind, std::function<int(WINDOW*, const char*)> const& printer, char const delim)
            -> void {
            for (std::size_t i = 0; i < board_.size(); ++i) {
                printer(wind, mk_string(board_[i], static_cast<int>(i), delim).c_str());
            }
        }*/

     private:
        board_t board_;
        player player_;
        std::random_device rd_;
        std::mt19937 mt_;
        std::uniform_int_distribution<int> normal_dist_;

        static auto count_live_neighbors(board_t const& board, int x, int y) -> int {
            auto m = static_cast<int>(board.size());
            auto n = static_cast<int>(board[0].size());
            auto count = 0;
            for (auto i = std::max(x - 1, 0); i < std::min(x + 2, m); ++i) {
                for (auto j = std::max(y - 1, 0); j < std::min(y + 2, n); ++j) {
                    count += board[i][j] & 0b01;
                }
            }
            return count -= board[x][y];
        }

        auto mk_string(std::vector<int> const& row, int row_n, char const delim) -> std::string {
            int col_n = 0;
            return std::accumulate(row.begin(),
                                   row.end(),
                                   std::string{""},
                                   [delim, &row_n, &col_n, this](auto acc, auto const& x) -> std::string {
                                       auto segment = x == 0b1 ? '*'
                                                               : (row_n == player_.x and col_n == player_.y
                                                                      ? player_.icon
                                                                      : ' ');
                                       ++col_n;
                                       return acc + segment + delim;
                                   })
                   + '\n';
        }

        static auto equation(std::size_t i, std::size_t j, int n) -> bool {
            auto a = std::sqrt(((i - n) ^ 2) + ((j - n) ^ 2));
            // NOLINTNEXTLINE
            return (j == n * std::sin(n) and j < n * std::cos(n))
                   or (a <= n or (i >= n / 2 and i <= n and j >= n / 2 and j <= n));
        }
    };

    class interface {
     private:
        life::game_of_life gol_;

     public:
        explicit interface(int const size)
        : gol_{life::game_of_life(size)} {};

        ~interface() = default;

        auto get_gol() -> life::game_of_life& {
            return gol_;
        }

        /*
        auto run(int latency, WINDOW* wind, std::function<int(WINDOW*, const char*)> const& printer) -> void {
        */
        /*
        auto interact_thread = std::thread([latency, &wind, this]() -> void {
            for (int i = 0; i < latency; ++i) {
                interact(wind);
                // std::this_thread::sleep_for(std::chrono::microseconds(1));
            }
        });
        */

        /*
            auto timer_thread = std::thread([latency]() -> void {
                std::this_thread::sleep_for(std::chrono::microseconds(latency));
            });

            auto update_print_thread = std::thread([&wind, &printer, this]() -> void {

                // wclear(wind);
                gol_.update();
                gol_.print(wind, printer, ' ');
                interact(wind);
                gol_.get_player() = player({gol_.get_player().x, gol_.get_player().y}, '0');
                // mvwaddch(wind, gol_.get_player().y, gol_.get_player().x, gol_.get_player().icon);

            });

            timer_thread.join();
            update_print_thread.join();
            wrefresh(wind);
        }
        */
    };

} // namespace life

/*

auto run(int latency, std::function<int(const char*)> const& printer) -> void {
    auto t0 = std::thread(
        [latency]() -> void { std::this_thread::sleep_for(std::chrono::microseconds(latency)); });
    auto t1 = std::thread([printer, this]() -> void {
        clear();
        gol_.update();
        gol_.print(printer, ' ');
    });
    t0.join();
    t1.join();
    refresh();
}
*/
/*
class animation {
 public:
    animation() = default;

 private:
};
*/
/*
std::vector<state<animation>> animations_;
static auto loop(std::vector<state<animation> const*>& an) -> void {
    std::for_each(an.begin(), an.end(), [](auto const& x) -> void { x->run(); });
}

static auto init(WINDOW* curr_window, board_t& b, std::vector<state<animation>>& an) -> void {
    auto a = std::make_unique<life::animation>();
    auto start = std::make_unique<state<animation>>(curr_window, 0, std::move(a), std::move(b));
    an.emplace_back(std::move(start));
}*/

/*
    struct state {
        state(WINDOW* w, int l, std::unique_ptr<T>&& a, board_t&& b)
        : window{w}
        , latency{l} // , animation{std::move(a)}
        , board{b} {};

        WINDOW* window;
        int latency;
        // std::unique_ptr<T> animation;
        board_t const& board;

        auto run() const -> void {
            // TODO(oscar):
            auto t0 = std::thread([this]() -> void {
                sleep(this->latency);
            });
        }
    };

 */
