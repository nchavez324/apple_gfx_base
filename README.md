# Setup

## Tools
1. Install Xcode
1. Install CMake

## VSCode Extensions
1. [clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd)
1. [Clang-Format](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format) 
1. [CodeLLDB](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb)
1. [cmake-format](https://marketplace.visualstudio.com/items?itemName=cheshirekow.cmake-format) for formatting CMake files.
1. [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake) for syntax highlighting, autocomplete, and suggestions for CMake code.
1. [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) for integration into VSCode task and launch workflows.

# Build and Run

## CLI + Xcode

Choose one of the following presets:

  - `macos`
  - `ios_simulator`
  - `ios_device`
  - `tvos_simulator`
  - `tvos_device`

```shell
cmake --preset=${PRESET}
cmake --build --preset=${PRESET}
open build/${PRESET}/AppleGfxBase.xcodeproj
```

These correspond to one of 3 app targets:

  - `examples_macos_app`
  - `examples_ios_app`
  - `examples_tvos_app`

which can be run from Xcode.

## VSCode

Alternatively, use VSCode to drive configuration, building, and launching.

1. \> CMake: Select Configure Preset (e.g. `macOS`)
1. \> CMake: Select Build Preset (e.g. `macOS`)
1. \> CMake: Set Build Target (e.g. `examples_macos_app`)
1. \> CMake: Set Debug Target (e.g. `examples_macos_app`)
1. \> Debug: Start Debugging (or F5)

And re-rinse as needed to select a different build/debug target.
