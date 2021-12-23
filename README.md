# sintl - SchilliX Internationalization

This project repackages the catgets() functions and gettext() functions and utilities originally implemented in the [OpenSolaris fork SchilliX](https://sourceforge.net/projects/schillix-on/) into a portable library, sintl.  
Furthermore, it aims at implementing the functionality proposed in [the standardization draft of gettext in the Single UNIX Specification](https://posix.rhansen.org/p/gettext_draft) that was originally missing on SchilliX.  
The project is still work in progress and should not be used in production. 

## Contained functions
  - catopen() - include/nl_types.h
  - catgets() - include/nl_types.h
  - catclose() - include/nl_types.h

  - bindtextdomain() - include/libintl.h
  - bind_textdomain_codeset() - include/libintl.h

  - dcgettext() - include/libintl.h
  - dcgettext_l() - include/libintl.h
  - dcngettext() - include/libintl.h
  - dcngettext_l() - include/libintl.h
  - dgettext() - include/libintl.h
  - dgettext_l() - include/libintl.h
  - dngettext() - include/libintl.h
  - dngettext_l() - include/libintl.h
  - gettext() - include/libintl.h
  - gettext_l() - include/libintl.h
  - ngettext() - include/libintl.h
  - ngettext_l() - include/libintl.h

Note that while the *_l() functions are always declared in the header, they are only linkable on platforms that either support the querylocale() (e.g. FreeBSD, OpenBSD, MacOSX) or [getlocalename_l()  interfaces. Without these (or equivalent) functions, the additional locale_t parameters cannot be mapped to a locale name, and no messages object can be located.

## Contained utilities
  - gettext
  - ngettext
  - msgfmt (msgfmt utility as specified in the SuS draft)
  - msgfmt_rev (the same as msgfmt, but outputs binary message catalogs with swapped endinanness)
  - smsgfmt ("Solaris Message Format")
  - xgettext

## Building and Installing
sintl uses a CMake build system.  
For building sintl, you need to install the following utilities:
  - a c compiler
  - flex
  - bison
  - cmake
  - make, or a different [generator supported by cmake](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html)

After that, the project can be built as follows:
```bash
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --install . # --prefix $PREFIX
```
In the last step, you can use --prefix to install the sintl library, headers and binaries to a prefix other than / (e.g. /opt/sintl).  
If you install sintl to a non-default prefix, make sure to include $PREFIX/bin in your PATH and use the compiler / linker flags -I$PREFIX/include and -L$PREFIX/lib when using the utilities or linking against the library.

## Testing

Configure and build first.

```bash
cd build
ctest -V
```