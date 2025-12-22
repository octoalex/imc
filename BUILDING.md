# Building

A detailed guide to building 

## Prerequisites

To build this launcher, the following software will be necessary:

- CMake (version 3.23 minimum)
- Any C Compiler that supports C23
- Any C and CMake compatible Build System

Although not strictly necessary, it is recommended to install Git

Personally I use `clang` as the C Compiler, and `Ninja` as the Build System

Based on your system, run one of these commands to install the software I use:

- Debian/Ubuntu (and derived):
  ```bash
  sudo apt install clang ninja-build cmake git
  ```

Additionally, both during configuration and compilation, an internet connection will be necessary, and a Shell is also
necessary.

It is necessary to download the source, either by clicking on the `Code < >` button, then on the `Download ZIP` button
at [the GitHub page](https://github.com/octoalex/imc), or by running the following command in an appropriate directory

```bash
git clone https://github.com/octoalex/imc.git
```

Then navigate to the cloned directory with the following command

```bash
cd imc
```

## Configuring

During this step, CMake will be run, generating the buildsystem that will be used to build the launcher

The command will look something like this:

```bash
cmake -B cmake-build-release                \
      -G Ninja                              \
      -D CMAKE_C_COMPILER=clang             \
      -D BUILD_TESTING=OFF                  \
      -D CMAKE_COMPILE_WARNING_AS_ERROR=OFF \
      -D CMAKE_BUILD_TYPE=Release
```

New lines have been added for convenience

Here's a brief explanation of each element for the uninitiated:

- `-B cmake-build-release`: Where the build files will be generated, cmake-build-release can be any path to a free or
  non-existent directory. It is recommended to use a directory starting with `cmake-build-`, because it is excluded by
  .gitignore, and thus it reduces the risk of accidentally committing build files
- `-G Ninja`: Telling CMake to generate a build system for Ninja, Ninja can be any (installed and
  [supported](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#cmake-generators))
- `-D CMAKE_C_COMPILER=clang`: What compiler should be used to build the launcher, clang can be any C Compiler that
  supports C23 (and is installed and
  [supported](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#id10))
- `-D BUILD_TESTING=OFF`: Tells CMake whether to set up testing or not, can be either `ON` or `OFF`. Set to `OFF` for
  faster (probably) build times, and to `ON` to enable testing
- `-D CMAKE_COMPILE_WARNING_AS_ERROR=OFF`: Tells the compiler whether it should treat any warnings it finds as errors,
  can be either `ON` or `OFF`. Unless contributing to the project, this should be disabled, due to the fact that 
  different versions or different compilers may give different errors, and a warning not present in other compilers will
  fail your build
- `-D CMAKE_BUILD_TYPE=Release`: Tells CMake whether for what type fo build it should generate a build system, it may
  assume many values, but usually it's recommended to be either `Release` or `Debug`. Set to `Debug` only if it is used
  to contribute to the launcher. Otherwise, it's recommended to use `Release`

Feel free to change any of these values, as the launcher is designed to be (as) platform-independent (as possible)

## Building

In this step, the executable will be built

Just run:

```bash
cmake --build cmake-build-release/
```

Where `cmake-build-release` should be the path specified with `-B` in the previous command

If the build was successful, the final executable can be found at `cmake-build-release/app/imc/imc`, changing
`cmake-build-release` to match the previous two commands.

It's a single statically linked executable, you may copy, paste, or move it however you want, and it will still be
functional

However, if the build fails, before creating any bug report, please:

- check that the used software (e.g. the compiler) is actually supported
- check that the used software supports the necessary features (such as C23)
- check that the used software installations are not damaged

After all of these steps, it is strongly encouraged to create a bug report at
[the GitHub issues page](https://github.com/octoalex/imc/issues/new)

## Testing

To run tests (e.g. to make sure that the program will run *mostly* correctly on the host machine), only the next command
is necessary

```bash
ctest --test-dir cmake-build-rlease/ --output-on-failure
```

`cmake-build-release` should be substituted with the same directory where the project was build into

## Additional tools

A few python scripts are present in this repository, created to facilitate the analysis of the minecraft version files

To run them, `python3` must be installed, and the `request` python package too.

The scripts can be run with the following command

```bash
python3 scripts <command> <build_dir> [<...args>]
```

with the currently available commands:

- `destructure` (additionally requires a version as an argument) turns every field of a version into its type
- `redundancies` finds all fields that are identical in the manifest and in every version
- `substitutions` finds all arguments that should be substituted into some value
- `assets` finds all assets that don't correspond with asset index ids
