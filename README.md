# sakura (桜)

> "I am not a monster!"
>
> [Cardcaptor Sakura, by Nanase Ohkawa](https://en.wikipedia.org/wiki/Cardcaptor_Sakura)

sakura (桜) is an instruction accurate PC Engine/TurboGrafx-16 emulator written in modern C++.

## Project status

I've come to the realization that I probably won't finish this project any time soon. Started in late 2021 with the goal of making a simple yet modern PC Engine/TurboGrafx-16 emulator because all other projects out there are either closed source or arguably old and complicated codebases. But each day that passes makes it painfully obvious that I don't have as much time anymore to put into this hobby. In terms of progress, HUC6280 is complete and HUC6260 and HUC6270 are far enough to partially display simple screens:

![15_in_1.png](/images/15_in_1.png)

## Building

This project can be build in Linux with CMake, Clang, Ninja and [`vcpkg`](https://github.com/Microsoft/vcpkg). Other operating systems, compilers, generators and package managers combinations might build this project but they're not actively used or supported.

`vcpkg` packages needed:

- `fmt`
- `catch2`
- `spdlog`
- `nlohmann-json`
- `sdl2`
- `glad[gl-api-46]`
- `imgui[opengl3-glad-binding,sdl2-binding]`

```Shell Session
$ cmake -Bbuild -GNinja -DCMAKE_CXX_COMPILER=/usr/local/bin/clang++ -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake src/
-- The CXX compiler identification is Clang 12.0.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/local/bin/clang++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /build
$ ninja -C build
ninja: Entering directory `build'
[4/4] Linking CXX executable app/sakura
```
