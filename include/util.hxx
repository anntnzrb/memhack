#pragma once

#include <cassert>
#include <iostream>
#include <thread>

namespace util {
/**
 * @brief Ensures that the program is running in the correct architecture
 *
 * This function checks whether the program is running in the
 * correct architecture based on the specified number of bits.
 * If the program is not running in the correct architecture, an error
 * message is printed to standard error stream and the program exits.
 *
 * @param bits The number of bits in the expected architecture.
 */
auto
ensureArch(std::size_t bits) -> void;

/**
 * Sleep for the specified number of milliseconds
 *
 * @param ms The number of milliseconds to sleep for.
 */
auto
sleep(std::size_t ms) -> void;
} // namespace util