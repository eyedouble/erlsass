# erlsass
Compile Sass/Scss implemented as Erlang NIF using libsass.

## Known to work on:
- Ubuntu 17.10
- Ubuntu 16.04
- Fedora 27
- Windows 10 x64 (Compile via MinGW gcc) *See usage on Windows section below*

## Prerequisites
- gcc
- g++

*Please note on fedora and possibly other linux distro's that use yum as package manger the g++ compiler is called gcc-c++*

## Install
Simply add `erlsass` to the `rebar.config` file of your application and add to your `application.src` file.

## API
### compile/2
#### Compile a file and return result as string
Default compilation style is compressed see compile/4 for options.
```erlang
  erlsass:compile ( file, "foo/bar/style.scss" ).
  >> {ok, "body{color:#000;}"}
```
### compile/3
#### Compile a file and return result as string and specify comilation style
Style options:

- Compact
- Compressed
- Expanded
- Nested

```erlang
  erlsass:compile ( file, "foo/bar/style.scss", "compressed" ).
  >> {ok, "body{color:#000;}"}
````
### compile_write/3 & compile_write/4
#### Compile a file and write result to a file
```erlang
  erlsass:compile_write ( file, "foo/bar/style.scss", "foo/bar/style.css", "compressed" ).
  >> ok  
  erlsass:compile_write ( file, "foo/bar/style.scss", "foo/bar/style.css").
  >> ok  
```

## Usage on Windows 
To build erlsass on Windows 64bit you need to provide GNU gcc and g++ compilers.
Follow the steps below:

1. Download  [MinGW64 for Windows 64bit](http://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/4.9.2/threads-win32/seh/x86_64-4.9.2-release-win32-seh-rt_v3-rev0.7z/download) , and unzip to `C:\mingw64`.

2. Add `C:\mingw64` to your Path environment variable. ( On Windows 10: Open the Start menu, type `environment` in the results click on `Edit environment variables for your account`. Select the `Path` entry and click on `Edit`. )

3. Open CMD or Powershell and execute `gcc --version`. It should show you the gcc version that is present. Do the same for g++. You are now done, please see the section **Install** to continue.


