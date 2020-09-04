#!/bin/bash

if [ -z "$1" ]
  then
    echo "Usage: ./build.sh <tag name>"
    exit 1
fi

docker build -t akagaeng/tetris:$1 .