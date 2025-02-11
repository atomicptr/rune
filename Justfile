test: build
    ctest --test-dir build

build:
    cmake -B build
    cmake --build build -j8
