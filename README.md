Madobe
======

Highly customizable KWin window decoration.

Prepare
-------

### Ubuntu

```sh
$ sudo apt install cmake extra-cmake-modules
```

Build
-----

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Themes
------

Madobe as is a kind of theme engine. The config file is `/etc/madobe.conf` and
themes are stored under `/usr/share/madobe/themes/`.

A theme is structured as

```
theme-name/
 |- images/
 |- metadata.desktop
 +- theme.json
```
