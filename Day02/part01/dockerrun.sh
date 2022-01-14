#!/bin/sh

docker run \
  --rm \
  -v $(pwd):/src \
  -u $(id -u):$(id -g) \
  emscripten/emsdk \
  emcc part01.cpp -o part01.js --preload-file ./files@/home

node part01.js

