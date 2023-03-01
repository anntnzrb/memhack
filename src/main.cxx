#include <iostream>

#include "memory.hxx"
#include "util.hxx"

namespace me {
constexpr std::size_t TARGET_ARCH {64};
const std::string     PROCESS_NAME {"dwm.exe"};
const std::string     MODULE_NAME {"kernel32.dll"};
} // namespace me

auto
main() -> int {
    // ensure app is running at desired architecture
    util::ensureArch(me::TARGET_ARCH);

    const auto mem {Memory {me::PROCESS_NAME}};

    std::cout << "Process '" << me::PROCESS_NAME << "' found, "
              << "PID: " << mem.getPID() << '\n';

    // pause
    std::cin.get();

    return 0;
}
