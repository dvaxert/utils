[![Build and Test Library](https://github.com/dvaxert/utils/actions/workflows/buildAndTest.yml/badge.svg?branch=master)](https://github.com/dvaxert/utils/actions/workflows/buildAndTest.yml)
[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fdvaxert%2Futils.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2Fdvaxert%2Futils?ref=badge_shield)

# Utils
A subproject with different utilities used in the modules of the [wormhole](https://github.com/dvaxert/wormhole) project.

# How to build

## Required
* C++17
* [CMake](https://cmake.org/)
* [Boost](https://www.boost.org/) (Preprocessor, Endian)
* [Spdlog](https://github.com/gabime/spdlog)
* [Fmt](https://github.com/fmtlib/fmt) (Included in spdlog)
* [Doxygen](https://doxygen.nl/) - optional

## CMake options

* **UTILS_BUILD_SHARED_LIBS** or **BUILD_SHARED_LIBS** - Build the project as a dynamic library
* **UTILS_BUILD_TESTING** or **BUILD_TESTING** - Build tests for the project
* **UTILS_INSTALL** - Generate a target for project installation
* **UTILS_BUILD_EXAMPLE** - Build examples for a project
* **UTILS_GENERATE_DOCUMENTATION** - Generate documentation when building a project
* **UTILS_PEDANTIC** - Enable the display of additional warnings
* **UTILS_WERROR** - Handle all compiler warnings with errors
* **UTILS_MSVC_STATIC_RUNTIME** - Link static runtime libraries

## Typical building

In the project directory, call the commands:
```
$ git clone https://github.com/dvaxert/utils
$ cmake -S . -B ./build
$ cmake --build ./build --config Release
```

## Run tests

In the project directory, call the commands:
```
$ cd ./build
$ ctest -C Release -VV
```

## Install

In the project directory, call the commands:
```
$ cmake --install ./build --prefix /my/install/prefix --config Release
```

## How to use in your project

The previously installed library can be found as follows:

```cmake
find_package(utils CONFIG REQUIRED)
```

set the path to the directory with cmake
```cmake
set(utils_DIR <install_prefix>/lib/cmake/utils)
```
or pass the parameter when generating the project
```
-Dutils_DIR=<install_prefix>/lib/cmake/utils
```

Link to your application purpose **wh::utils** as follows:
```cmake
target_link_libraries(<your_target>
    PRIVATE
        wh::utils
)
```


## License
[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fdvaxert%2Futils.svg?type=large)](https://app.fossa.com/projects/git%2Bgithub.com%2Fdvaxert%2Futils?ref=badge_large)