TEMPLATE = aux
docs.commands = (cat doxyfile) | doxygen -
QMAKE_EXTRA_TARGETS += docs
