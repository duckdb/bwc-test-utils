#pragma once

// TODO we cannot run these checks becuse they are not defined for DuckDB < 1.4.x
// #ifndef DUCKDB_MAJOR_VERSION
// #error "DUCKDB_MAJOR_VERSION is not defined"
// ...

// DuckDB main built with DUCKDB_VERSION=main (as extension-ci-tools does) defines the version macros as empty
// when compiling its own sources, which include this header. Treat that as the newest version.
// `0 - X - 1` is 1 only when X is empty.
#if defined(DUCKDB_MAJOR_VERSION) && (0 - DUCKDB_MAJOR_VERSION - 1) == 1

#define DUCKDB_VERSION_AT_MOST(major, minor, patch) 0
#define DUCKDB_VERSION_BEFORE(major, minor, patch)  0

#else

#define DUCKDB_VERSION_AT_MOST(major, minor, patch)                                                                    \
	(DUCKDB_MAJOR_VERSION < (major) || (DUCKDB_MAJOR_VERSION == (major) && DUCKDB_MINOR_VERSION < (minor)) ||          \
	 (DUCKDB_MAJOR_VERSION == (major) && DUCKDB_MINOR_VERSION == (minor) && DUCKDB_PATCH_VERSION <= (patch)))

#define DUCKDB_VERSION_BEFORE(major, minor, patch)                                                                     \
	(DUCKDB_MAJOR_VERSION < (major) || (DUCKDB_MAJOR_VERSION == (major) && DUCKDB_MINOR_VERSION < (minor)) ||          \
	 (DUCKDB_MAJOR_VERSION == (major) && DUCKDB_MINOR_VERSION == (minor) && DUCKDB_PATCH_VERSION < (patch)))

#endif
