#!make

include .env
export $(shell sed 's/=.*//' .env)

current_dir = $(shell pwd)

build:
	/usr/local/bin/cmake --no-warn-unused-cli -DCMAKE_TOOLCHAIN_FILE:STRING=$(FILESYSTEM_PREFIX)/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/local/bin/x86_64-apple-darwin19-gcc-9.3.0 -H$(current_dir) -B$(current_dir)/build -G Ninja

tests: clean run_tests

clean:
	rm -rf ./tests/runtime/*.json
	rm -rf ./tests/runtime/*.csv
	rm -rf ./tests/runtime/*.bin
	rm -rf ./tests/runtime/*.txt

run_tests:
	bats ./tests/*

.PHONY: tests build clean run_tests