test: build
    ctest --test-dir build --output-on-failure

build:
    cmake -B build
    cmake --build build -j8
