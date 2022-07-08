#include <stdint.h>
#include <Windows.h>

typedef uint32_t __u32;
typedef uint8_t __u8;
typedef uint64_t __u64;
typedef unsigned short __kernel_sa_family_t;

#ifdef __GNUC__
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif
