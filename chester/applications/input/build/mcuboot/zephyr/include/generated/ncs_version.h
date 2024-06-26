#ifndef _NCS_VERSION_H_
#define _NCS_VERSION_H_

/*  values come from cmake/version.cmake
 * BUILD_VERSION related  values will be 'git describe',
 * alternatively user defined BUILD_VERSION.
 */

/* #undef ZEPHYR_VERSION_CODE */
/* #undef ZEPHYR_VERSION */

#define NCSVERSION          
#define NCS_VERSION_NUMBER  0x20500
#define NCS_VERSION_MAJOR   2
#define NCS_VERSION_MINOR   5
#define NCS_PATCHLEVEL      0
#define NCS_VERSION_STRING  "2.5.0"

#define NCS_BUILD_VERSION v2.0.0-rc1-6545-g52c40e51c79f
#define BANNER_VERSION STRINGIFY(NCS_BUILD_VERSION)

#endif /* _NCS_VERSION_H_ */
