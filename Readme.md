# Ying Yang Ping Pong

Build using Raylib on Linux.
Should work on any platform that supports Raylib.

## Building

Build the [build system](https://github.com/nailuj05/noob) yourself by compiling noob.c, after that use `./noob` to build and `./noob run` to build and run.

If you want to build for WASM I support that aswell, you'll need to provide raylib with compiled sources for `PLATFORM_WEB` inside of raylib/src, 
aswell as emscripten (installed and activated `source /path/to/emsdk/emsdk_env.sh`).

Running `./noob web` will the compile for WASM. Using `./noob web serve` will also serve the html page using emscriptens webserver.
