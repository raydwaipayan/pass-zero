TEMPLATE = subdirs

SUBDIRS = \
	argon2 \
	crypto \
	storage \
 	io \
	app \
        docs \
        tests

CONFIG += ordered

app.subdir     = src/app
io.subdir      = src/io
storage.subdir = src/storage
crypto.subdir  = src/crypto
argon2.subdir  = src/argon2
docs.subdir = docs
