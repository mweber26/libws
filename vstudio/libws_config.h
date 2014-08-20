
#ifndef __LIBWS_CONFIG_H__
#define __LIBWS_CONFIG_H__

#define ENOMEM 12
#define EINVAL 22

#define LIBWS_WITH_LOG 1

#define LIBWS_HAVE_STDINT_H
#define LIBWS_HAVE_INTTYPES_H
#define LIBWS_HAVE_SYS_TYPES_H

#if defined(LIBWS_HAVE_STDINT_H)
#  include <stdint.h>
#elif defined(LIBWS_HAVE_INTTYPES_H)
#  include <inttypes.h>
#elif defined(LIBWS_HAVE_SYS_TYPES_H)
#  include <sys/types.h>
#endif

#define LIBWS_HAVE_UINT32_T 1
#ifndef LIBWS_HAVE_UINT32_T
#  define uint32_t uint32_t
#endif

#define LIBWS_HAVE_UINT64_T 1
#ifndef LIBWS_HAVE_UINT64_T
#  define uint64_t uint64_t
#endif

#define LIBWS_HAVE_PRIU64 1
#ifndef LIBWS_HAVE_PRIU64
#  define PRIu64 1
#endif

// If your compiler supports the inline keyword in C, JSON_INLINE is
// defined to `inline', otherwise empty. In C++, the inline is always
// supported.
#ifdef __cplusplus
#define LIBWS_INLINE inline
#else
#define LIBWS_INLINE 
#endif

#endif // __LIBWS_CONFIG_H__
