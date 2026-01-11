# Configuration

Reference for CMake configuration arguments and variables

Please note: variable names and argument names (the `-X` part) and 

## CMake Argument

| Argument                | Description                                                         |
| ----------------------- | ------------------------------------------------------------------- |
| `-B <path>`             | The path to the directory where the configuration files will be put |
| `-G <generator>`        | The generator used by CMake, more [here](#cmake-generators)         |
| `-D <variable>=<value>` | A variable to set, and it's value                                   |

## CMake variables

Please note: when setting one of these, they must be prefixed by `-D`

| Variable                         | Description                                            | Default |
| -------------------------------- | ------------------------------------------------------ | ------- |
| `CMAKE_COMPILE_WARNING_AS_ERROR` | Tell the compiler to treat any warnings as errors      | `ON`    |
| `CMAKE_C_COMPILER`               | The compiler to use, more [here](#cmake-compilers)     |         |
| `CMAKE_BUILD_TYPE`               | The type of build, usually either `Release` or `Debug` |         |

## IMC variables

Please note: when setting one of these, they must be prefixed by `-D`

| Variable           | Description                                | Default |
| ------------------ | ------------------------------------------ | ------- |
| `BUILD_TESTING`    | Enable building tests                      | `ON`    |
| `DISABLE_BUILD_ID` | Disable giving the build a unique build id | `OFF`   |

## Notes

### CMake Generators

For more a list of supported generators, go
[here](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#cmake-generators)

Generally, on Linux, it usually is `Unix Makefiles` (put in quotes while typing the command) or `Ninja`

### CMake Compilers

For a list of supported compilers, go
[here](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#supported-compilers)

Generally, on Linux, it usually is `gcc` or `clang`
