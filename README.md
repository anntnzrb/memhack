# memhack

`memhack` is a C++ program template that allows interacting with the memory of
a **Windows** process using the **Windows API**. With this program template,
one can read and write values to specific memory addresses and get the base
address of a module in the process's memory. This template is useful for
creating tools such as game trainers, cheats, and other similar applications.

The core of `memhack` is the `Memory` class, which provides a simple interface
for interacting with the process memory.This class provides methods for reading
and writing to memory and getting the base address of a module in the process's
memory.

Additionally, there is an auxiliary `util` namespace with a variety of
utilities. `ensureArch()` serves the purpose of ensuring that the program is
running on an architecture that is supported by the program, based on the
specified number of bits. This can be useful in preventing issues related to
running a program on an unsupported architecture, such as attempting to run a
64-bit program on a 32-bit operating system or vice versa.

## Requirements

- `C++20` compatible compiler
- Windows OS

### Other Notes

The project was first initialized using **CLion**, with the intention of
using **CMake** as the build system. The program is designed to work out of the
box with **Visual Studio** as well as other IDEs.
However, the author did not want to use **Visual Studio's** solution files and
prefers **CLion** as their preferred IDE. Therefore, the author has only tested
the project using latter mentioned environment, but it should be compatible
with other IDEs as well.

## Usage

Classical example of hacking **CSGO**'s memory:

```c++
...
#include <memory.hxx>

auto main() -> int
{
    // ensure app is running at desired architecture
    util::ensureArch(32);
    
    // open cs:go process
    const auto process {Memory {"csgo.exe"}};

    // get base address of the client module
    const auto clientBase = process.getModuleBase("client.dll");

    // find player's health
    const auto health = process.read<std::int32_t>(clientBase + 0xF8);
    std::cout << "Player's health: " << health << '\n';

    // write new value to the player's health
    const auto newHealth = 1337;
    process.write<std::int32_t>(healthAddress, newHealth);
    std::cout << "Player's health set to " << newHealth << '\n';

    return 0;
}

```

## Disclaimer

This resource is intended for learning and educational purposes only.
The author of this project is not responsible for any misuse or incorrect usage
of the code provided. The use of this program is at the user's own risk and may
be subject to the terms and conditions set forth by the game's publisher.

This project was created with the aim of providing a helpful and convenient
tool for learning purposes. The code uses **C++20** and the **Windows API** to
interact with the memory of a **Windows** process. While efforts have been made
to ensure the accuracy and safety of the code, there may be areas for
improvement.

## Copying

Refer to the [COPYING](./COPYING) file for licensing information.

Unless otherwise noted, all code herein is distributed under the terms of the
[GNU General Public License Version 3 or later](https://www.gnu.org/licenses/gpl-3.0.en.html).