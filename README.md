# FST - file searching tool

![build_linux](https://github.com/Slava2001/fst/actions/workflows/build_linux.yml/badge.svg)
![build_windows](https://github.com/Slava2001/fst/actions/workflows/build_windows.yml/badge.svg)


## 
### Linux

```
sudo apt update
sudo apt install build-essential cmake gcc g++ clang lcov clang-tidy
```

```
cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release
cmake --build ./build
```

```
./build/fst
```

#### test

```
cmake -S . -B ./coverage_build -DCODE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
cd ./coverage_build
cmake --build .
```

```
./coverage.html
```

```
firefox ./coverage_html/index.html
```
