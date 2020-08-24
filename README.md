<h1 align="center"> Pass-Zero </h1>

<p align="center">
  Secure password manager, written with love in Qt.
</p>

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Build Process](#build-process)
- [Documentation](#documentaiton)
- [Testing](#testing)
- [To do](#to-do)


## Introduction

Store your passwords and notes securely. Built with Qt5, it uses strong cryptographic algorithms to keep your data safe.

## Features

* Open or create new storage databases
* 32 byte keys are created securely using Argon2 and Blake2
* All data is encrypted using AES-256-CBC during storage
* Two keys for every database
  - Master key unlocks secondary database key
  - Database key unlocks the user data


## Build Process

- Clone or download the repo
- `qmake pass-zero.pro` to generate the project makefile
- `make -j8` to build the project files
- `./pass-zero` to run the generated binary

## Documentation
Documentation is generated using [doxygen](https://www.doxygen.nl/index.html).

Execute the following command from inside the docs directory

```qmake docs.pro && makefile```

A html folder shall be generated. run `index.html` using the browser of your choice to view the docs.

## Testing
Test framework is written using QTestLib.

- Follow the [Build process](#build-process).
- Go to the tests directory and run the binary `./tests`.

## To Do

- Encrypt data while in memory
- Improve the GUI
- Allow other encryption methods like ChaCha and Salsa
- Option to use a key pair along with the master key for added security.