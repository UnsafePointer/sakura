# sakura (桜)

> "I am not a monster!"
>
> [Cardcaptor Sakura, by Nanase Ohkawa](https://en.wikipedia.org/wiki/Cardcaptor_Sakura)

sakura (桜) is an instruction accurate PC Engine/TurboGrafx-16 emulator written in modern C++.

## Building

This project can be build in Linux with CMake, Clang and Ninja. Other operating systems, compilers and generators combinations might build this project but they're not actively used or supported.

```Shell Session
$ cmake -Bbuild -GNinja -DCMAKE_CXX_COMPILER=/usr/local/bin/clang++ src/
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
