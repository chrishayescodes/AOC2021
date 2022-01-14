#!/bin/sh

docker run \
  --rm \
  -v $(pwd):/src \
  -u $(id -u):$(id -g) \
  emscripten/emsdk \
  emcc part02.cpp -o part02.js --preload-file ./files@/home

node part02.js

