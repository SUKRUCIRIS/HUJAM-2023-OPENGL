# Code: ŞÜKRÜ ÇİRİŞ, Art: SELİM EMRE

# HOW TO BUILD?

## Build project files:

```
mkdir build
cd build
cmake .. -DCMAKE_VERBOSE_MAKEFILE=1
```

## Compile with msvc on windows:

You can't compile on other platforms.

Make sure that you use native tools command prompt for vs.

```
msbuild HUJAM.sln /p:Configuration=Release /p:Platform=x64
```
