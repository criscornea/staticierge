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
	ln -sf $(CURDIR)/build/staticierge ~/.local/bin


run:
	cd build && ./staticierge

tests: dev
	ctest --test-dir build --output-on-failure

tests_failed: dev
	ctest --test-dir build --rerun-failed --output-on-failure
