Copyright © 2016-2026 Kirk Rader

# cppExamples

C++ implementation of a thread-synchronization class modeled on Java's
"monitors."

This exists as an example both of wrapping a native API in a C++ class and as a
demonstration of basic multi-threaded application design.

## Dependencies

### Compile and Link

```bash
sudo apt install -y build-essential
```

### Documentation

[doxygen] 1.18.0 or later

_**Warning:** As of this writing, the version of `doxygen` installed by `apt` in
Ubuntu is years out of date, as for many commonly used packages._

## Build

### Library and Unit Tests

```bash
make cleanall unit_tests
```

### Documentation

```bash
make docs
```

[doxygen]: https://www.doxygen.nl