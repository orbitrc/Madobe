Madobe
======

Madobe(窓辺, まどべ) is a highly customizable KWin window decoration.

Build
-----

### Preparation

#### Arch Linux

TODO

#### Ubuntu

```sh
$ sudo apt install cmake extra-cmake-modules
```

### Compilation

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

#### Ubuntu

```sh
$ sudo cp madobedecoration.so /usr/lib/x86_64-linux-gnu/qt5/plugins/org.kde.kdecoration2/
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
