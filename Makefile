
init:
	rm -rf build
	cmake -S . -B build
	ln -s build/compile_commands.json .

build:
	cmake -S . -B build

