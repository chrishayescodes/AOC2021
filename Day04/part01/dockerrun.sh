#!/bin/sh

docker run \
  --rm \
  -v $(pwd):/src \
  -u $(id -u):$(id -g) \
  emscripten/emsdk \
  emcc prog.cpp -o prog.js --preload-file ./files

node prog.js

