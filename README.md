# rune

A collection of C++23 header files for handling various cross platform related tasks

## Features

- OS detection & OS version detection
- Compiler detection & compiler version detection
- Cross platform path library (home dir, config dir, etc.)

## Installation

Just copy the required files into your project :)

## Usage

### OS detection & OS version detection

This is split into two parts, one which is basically only defines:

```cpp
#include <iostream>

#include <rune/rune_defs.hpp>

int main() {
    #if RUNE_OS_LINUX
    std::cout << "Hello from Linux!" << std::endl;
    #elif RUNE_OS_WINDOWS
    std::cout << "Bonjeur Windows" << std::endl;
    #else
    std::cout << "Hallo von " << RUNE_OS_NAME << std::endl;
    #endif

    #if RUNE_OS_PLATFORM_DESKTOP
    std::cout << "This is a desktop platform" << std::endl;
    #endif

    return 0;
}
```

and there is also rune_os.hpp which goes way more in-depth:

```cpp
#include <iostream>

#include <rune/rune_os.hpp>

int main() {
    auto current_os = rune::os::current();

    if (current_os == rune::os::OperatingSystem::Linux) {
        std::cout << "Hello from Linux!" << std::endl;
    }

    // output is from my system as of time of this commit:
    std::cout << rune::os::name() << std::endl;    // NixOS 25.05 (Warbler)
    std::cout << rune::os::version() << std::endl; // 6.12.12

    return 0;
}

```

### Compiler detection & compiler version detection

Like OS this is also split into two parts, one which is only defines:

```cpp
#include <iostream>

#include <rune/rune_defs.hpp>

int main() {
    #if RUNE_COMPILER_GCC
    std::cout << "Hello from GCC!" << std::endl;
    #elif RUNE_COMPILER_MSVC
    std::cout << "MSVC" << std::endl;
    #endif

    std::cout << RUNE_COMPILER_NAME << ": " << RUNE_COMPILER_VERSION << std::endl; // gcc: 14.2.0

    return 0;
}
```

and there is also rune_compiler.hpp:

```cpp
#include <iostream>

#include <rune/rune_compiler.hpp>

int main() {
    auto current_compiler = rune::compiler::current();

    if (current_compiler == rune::compiler::Compiler::GCC) {
        std::cout << "Hello from GCC!" << std::endl;
    }

    // output is from my system as of time of this commit:
    std::cout << rune::compiler::name() << std::endl;          // gcc
    std::cout << rune::compiler::version() << std::endl;       // 14.2.0
    std::cout << rune::compiler::major_version() << std::endl; // 14

    return 0;
}
```

### Cross platform path library (home dir, config dir, etc.)

```cpp
#include <iostream>
#include <fstream>

#include <rune/rune_paths.hpp>

int main() {
    auto home = rune::paths::home_dir();

    std::cout << "User Home Dir: " << home << std::endl;

    auto config_dir = rune::paths::config_dir("my-app"); // creates a "my-app" dir in the base config dir if doesnt exist
    auto config_file_path = config_dir / "config.json"; // assuming: { "name": "Test" }
    auto config_file = std::ifstream {config_file_path};

    assert(config_file.is_open());

    auto config_data = std::string {};

    config_file >> config_data;

    auto root = Json::Value {};
    auto reader = Json::Reader {};
    reader.parse(config_data, root);

    std::cout << root["name"] << std::endl; // should return "Test"

    return 0;
}
```

## License

MIT
