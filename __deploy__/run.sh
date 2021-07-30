#!/usr/bin/env bash

docker run --mount type=bind,src="$(pwd)/artefacts",dst="/var/build_artefacts" "atomic_processors"
