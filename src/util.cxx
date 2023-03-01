#include "util.hxx"

namespace util {
auto
ensureArch(const std::size_t bits) -> void {
    constexpr uint8_t byte {8};
    assert(bits == sizeof(void*) * byte
           && "This program is not running in the expected architecture!");
}

auto
sleep(const std::size_t ms) -> void {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
} // namespace util