<p align="center">
    <img src="./logo.svg"/>
</p>

<p align="center">
    <a href="https://github.com/Slava2001/fst/actions/workflows/build_linux.yml">
        <img src="https://github.com/Slava2001/fst/actions/workflows/build_linux.yml/badge.svg" alt="Linux" />
    </a>
    <a href="https://github.com/Slava2001/fst/actions/workflows/build_windows.yml">
        <img src="https://github.com/Slava2001/fst/actions/workflows/build_windows.yml/badge.svg" alt="Windows" />
    </a>
</p>

---

## Стек используемых технологий:

 - Язык программирования: C++, bash
 - Компиляторы: GCC, Clang, MSVC++
 - Инструменты для тестирования: Google Test
 - Инструменты для сборки и автоматизации: CMake
 - Инструменты для профилирования и анализа: Clang-tidy, lcov
 - Операционные системы: Linux, Windows
 - Библиотеки:
   - [Google Test](https://github.com/google/googletest) – для написания юнит тестов
   - [thread-pool](https://github.com/bshoshany/thread-pool) – для реализации многопоточного индексирования файлов
   - [nlohmann/json](https://github.com/nlohmann/json/) – для работы c json-файлами
 - Документация: Doxygen

## Сборка
### Linux

Убедитесь что установлены все необходимые инструменты:

```sh
sudo apt update
sudo apt install build-essential cmake gcc g++ clang lcov clang-tidy
```

Выполните следующие команды для сборки:

```sh
cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release
cmake --build ./build
```

Запустите FST следующей командой:

```sh
./build/fst
```

После успешного завершения работы, проверьте появившийся файл `./answers.json`:

```sh
cat ./answers.json
```


#### Тестирование и покрытие кода

Для запуска тестов выполните следующие команды:

```sh
cmake -S . -B ./coverage_build -DCODE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
cd ./coverage_build
cmake --build .
ctest
```

Оставаясь в билд директории, выполните скрипт (может не работать, если вы используете WSL):
```sh
../coverage.sh
```

Отчет о покрытии появится в директории `./coverage_html`, используйте любой браузер для просмотра, например, `firefox`:

```sh
firefox ./coverage_html/index.html
```

### Windows

#### MinGW

```sh
cmake -G "MinGW Makefiles" -S . -B .\win_build
cmake --build .\win_build
.\win_build\fst
```

#### Developer Command Prompt for VS

Запустите Developer Command Prompt for VS, перейдите в корень репозитория и выполните:

```sh
cmake -S . -B .\win_build
cmake --build .\win_build
.\win_build\Debug\fst.exe
```

## Структура проекта

Подробное описание всех классов, структур и функций, а также графы их взаимодействия можно найти в [документации](https://slava2001.github.io/fst/index.html).

Также документация доступна офлайн, для этого откройте файл `./docs/index.html` любым браузером, например, `firefox`:

```sh
firefox ./docs/index.html
```
