# pass-zero

## A secure password manager writen in qt5

#### Security Features
- Key derivation algorithm: Argon2
- Encryption: aes-256-cbc

#### Build
- generate makefile using qmake:
  - ```qmake -o Makefile pass-zero.pro
- Compile the project:
  - ```make -j8 #option -j8 enables multiple jobs```

#### Requirements
- qt5
- make

