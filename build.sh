#!/bin/bash

echo "Usage: ./build.sh <tag name ex: v1.0.0 >"

if [ -z "$1" ]
  then
    docker build -t akagaeng/tetris .
  else
    docker build -t akagaeng/tetris:$1 .
fi