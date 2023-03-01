#include "memory.hxx"

Memory::Memory(const std::string_view pName): pid(0), pHandle(nullptr) {
    // get a snapshot of the system processes
    auto* const procSnapshot {CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)};
    // check if snapshot creation failed
    if (procSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create processes snapshot: " << GetLastError()
                  << '\n';
        std::exit(1); // NOLINT
    }

    // iterate through processes in snapshot and find desired process
    PROCESSENTRY32 entry {};
    entry.dwSize = sizeof(PROCESSENTRY32);

    while (Process32Next(procSnapshot, &entry) != 0) {
        if (pName == entry.szExeFile) { // NOLINT
            this->pid = entry.th32ProcessID;
            this->pHandle = OpenProcess(PROCESS_ALL_ACCESS,
                                        FALSE,
                                        static_cast<std::uint32_t>(this->pid));
            break;
        }
    }

    // close snapshot handle
    CloseHandle(procSnapshot);
}

Memory::~Memory() {
    if (this->pHandle != nullptr) {
        CloseHandle(this->pHandle);
    }
}

auto
Memory::getModuleAddress(std::string_view moduleName) const -> std::uintptr_t {
    // create snapshot of  module list in the target process
    auto* const modSnapshot {CreateToolhelp32Snapshot(
        TH32CS_SNAPMODULE, static_cast<std::uint32_t>(this->pid))};

    // check if snapshot creation failed
    if (modSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create modules snapshot: " << GetLastError()
                  << '\n';
        std::exit(1); // NOLINT(concurrency-mt-unsafe)
    }

    // iterate over module list and convert module base address to uintptr_t
    MODULEENTRY32 entry {};
    entry.dwSize = sizeof(MODULEENTRY32);
    std::uintptr_t result {};

    while (Module32Next(modSnapshot, &entry) != 0) {
        if (moduleName == entry.szModule) { // NOLINT
            // NOLINTNEXTLINE
            result = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
            break;
        }
    }

    // close snapshot handle
    CloseHandle(modSnapshot);

    return result;
}

auto
Memory::getPID() const -> uintptr_t {
    return pid;
}

auto
Memory::getPHandle() const -> void* {
    return pHandle;
}