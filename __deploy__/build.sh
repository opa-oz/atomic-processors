#!/usr/bin/env bash

docker build \
    -f Dockerfile \
    -t "atomic_processors" \
    .
