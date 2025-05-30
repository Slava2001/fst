<img src="./logo.svg"></img>

![build_linux](https://github.com/Slava2001/fst/actions/workflows/build_linux.yml/badge.svg)
![build_windows](https://github.com/Slava2001/fst/actions/workflows/build_windows.yml/badge.svg)

<svg>
    <style>
        .letters { fill: #2E2E2E; }

        @media (prefers-color-scheme: dark) {
            .letters { fill: #ffffff; }
        }
    </style>
    <text class="letters" xml:space="preserve" text-anchor="start" font-family="'Noto Sans JP'" font-size="50" id="svg_10" y="65.89516" x="63.25734" stroke-width="0" stroke="#000" fill="currentColor">f</text>
</svg>

## Используемые библиотеки

## Сборка
### Linux

Убедитесь что установлены все необходимые инструменты:

```
sudo apt update
sudo apt install build-essential cmake gcc g++ clang lcov clang-tidy
```

Выполните следующие команды для сборки:

```
cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release
cmake --build ./build
```

Запустите FST следующей командой:

```
./build/fst
```

После успешного завершения работы, проверьте появившийся файл `./answers.json`:

```
cat ./answers.json
```


#### Тестирование и покрытие кода

Для запуска тестов выполните следующие команды:

```
cmake -S . -B ./coverage_build -DCODE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
cd ./coverage_build
cmake --build .
ctest
```

Оставаясь в билд директории, выполните скрипт (может не работать, если вы используете WSL):
```
../coverage.html
```

Отчет о покрытие появится в директории `./coverage_html`, используйте любой браузер для просмотра, например, `firefox`:

```
firefox ./coverage_html/index.html
```

### Windows

#### MinGW

```
cmake -G "MinGW Makefiles" -S . -B .\build
cmake --build .\build
.\build\fst
```

#### Developer Command Prompt for VS

Запустите Developer Command Prompt for VS, перейдите в корень репозитория и выполните:

```
cmake -S . -B .\win_build
cmake --build .\win_build
.\win_build\Debug\fst.exe
```
