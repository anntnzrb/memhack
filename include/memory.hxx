#pragma once

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <windows.h>
#include <tlhelp32.h>

class Memory {
  private:
    std::uintptr_t pid;
    void*          pHandle;

  public:
    /**
     * @brief Constructor that takes a process name and finds the corresponding
     * process ID and process handle
     *
     * @param pName The name of the process to find
     */
    explicit Memory(std::string_view pName);

    /**
     * @brief Destructor that releases the process handle
     */
    ~Memory();

    /**
     * Gets the base address of the specified module in the process's memory
     *
     * @param moduleName The name of the module to get the base address of.
     * @return The base address of the module in the process's memory.
     * @throws std::runtime_error If the module snapshot creation fails.
     */
    auto getModuleAddress(std::string_view moduleName) const -> std::uintptr_t;

    /**
     * @brief Reads a value of type T from the specified memory address
     *
     * @tparam T The type of the value to read.
     * @param address The memory address to read from.
     * @return The value read from the specified memory address.
     */
    template <typename T>
    constexpr auto read(const std::uintptr_t& address) const noexcept -> T {
        T val {};

        ReadProcessMemory(this->pHandle,
                          // NOLINTNEXTLINE
                          reinterpret_cast<LPCVOID>(address),
                          &val,
                          sizeof(T),
                          nullptr);
        return val;
    }

    /**
     * Writes a val of type T to the specified address in the process's memory
     *
     * @tparam T The type of val to write.
     * @param address The address to write the val to.
     * @param val The val to write.
     */
    constexpr auto write(const std::uintptr_t& address,
                         const auto&           val) const noexcept -> void {
        WriteProcessMemory(this->pHandle,
                           // NOLINTNEXTLINE
                           reinterpret_cast<LPVOID>(address),
                           &val,
                           sizeof(val),
                           nullptr);
    }

    /* getters & setters */
    auto getPID() const -> uintptr_t;

    auto getPHandle() const -> void*;
};