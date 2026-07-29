.PHONY: init dev build run tests

init:
	rm -rf build
	cmake -S . -B build
	ln -sf build/compile_commands.json .

dev:
	cmake -S . -B build -DENABLE_SANITIZERS=ON
	cmake --build build

build:
	cmake --build build

run:
	cd build && ./staticierge

tests: dev
	ctest --test-dir build
