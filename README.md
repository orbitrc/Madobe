Madobe
======

Madobe(窓辺, まどべ) is a highly customizable KWin window decoration.

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

### Installation

#### Arch Linux

```sh
$ sudo cp madobedecoration.so /usr/lib/qt/plugins/org.kde.kdecoration2/
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
#### Images

TODO

License
-------

Madobe is developed under MIT License. For the detail, see the LICENSE file.
