# erlsass
Compile Sass/Scss implemented as Erlang NIF using libsass.

## Known to work on:
- Ubuntu 17.10
- Windows 10 x64 (Compile via MinGW gcc)

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
