#include <stdio.h>
#define _ALKR_SIMD_CONTEXTCLIB

#ifdef __SSE2__

#include <xmmintrin.h>
#define _ALKR_SIMDMODE 1

#ifdef __AVX__
	#include <immintrin.h>

        #define _ALKRS_REGTYPEF __m256
	#define _ALKRS_REGTYPEI __m256i
	#define _ALKRS_SETZERO _mm256_setzero_si256
	#define _ALKRS_LOADVALUE _mm256_loadu_si256
	#define _ALKRS_STOREVALUE _mm256_storeu_si256
	#define _ALKRS_DO_OR _mm256_or_si256
        #define _ALKRS_REGSZ 32
		
	#define _ALKRS_DO_ADD8I _mm256_add_epi8
	#define _ALKRS_DO_SUB8I _mm256_sub_epi8
	#define _ALKRS_DO_SLLI8I _mm256_slli_epi8
	#define _ALKRS_DO_SRLI8I _mm256_srli_epi8
	#define _ALKRS_DO_SRAI8I _mm256_srai_epi8

	#define _ALKRS_DO_ADD16I _mm256_add_epi16
	#define _ALKRS_DO_SUB16I _mm256_sub_epi16
	#define _ALKRS_DO_MULLO16I _mm256_mullo_epi16
	#define _ALKRS_DO_MULHI16I _mm256_mulhi_epi16
	#define _ALKRS_DO_SLLI16I _mm256_slli_epi16
	#define _ALKRS_DO_SRLI16I _mm256_srli_epi16
	#define _ALKRS_DO_SRAI16I _mm256_srai_epi16

	#define _ALKRS_DO_ADD32I _mm256_add_epi32
	#define _ALKRS_DO_SUB32I _mm256_sub_epi32
	#define _ALKRS_DO_MULLO32I _mm256_mullo_epi32
	#define _ALKRS_DO_MULHI32I _mm256_mulhi_epi32
	#define _ALKRS_DO_SLLI32I _mm256_slli_epi32
	#define _ALKRS_DO_SRLI32I _mm256_srli_epi32
	#define _ALKRS_DO_SRAI32I _mm256_srai_epi32

	#define _ALKRS_DO_ADD64I _mm256_add_epi64
	#define _ALKRS_DO_SUB64I _mm256_sub_epi64
	#define _ALKRS_DO_MULLO64I _mm256_mullo_epi64
	#define _ALKRS_DO_MULHI64I _mm256_mulhi_epi64
	#define _ALKRS_DO_SLLI64I _mm256_slli_epi64
	#define _ALKRS_DO_SRLI64I _mm256_srli_epi64
	#define _ALKRS_DO_SRAI64I _mm256_srai_epi64

#else // - - - - - - - - - - - - - - - - - - - - - - - -
	#include <emmintrin.h>
        #define _ALKRS_REGTYPEF __m128
	#define _ALKRS_REGTYPEI __m128i
	#define _ALKRS_SETZERO _mm_setzero_si128
	#define _ALKRS_LOADVALUE _mm_loadu_si128
	#define _ALKRS_STOREVALUE _mm_storeu_si128
	#define _ALKRS_DO_OR _mm_or_si128
        #define _ALKRS_REGSZ 16

	#ifdef _mm_add_epi8 
	#define _ALKRS_DO_ADD8I _mm_add_epi8 
	#endif
	#define _ALKRS_DO_SUB8I _mm_sub_epi8
	#define _ALKRS_DO_SLLI8I _mm_slli_epi8
	#define _ALKRS_DO_SRLI8I _mm_srli_epi8
	#define _ALKRS_DO_SRAI8I _mm_srai_epi8

	#define _ALKRS_DO_ADD16I _mm_add_epi16
	#define _ALKRS_DO_SUB16I _mm_sub_epi16
	#define _ALKRS_DO_MULLO16I _mm_mullo_epi16
	#define _ALKRS_DO_MULHI16I _mm_mulhi_epi16
	#define _ALKRS_DO_SLLI16I _mm_slli_epi16
	#define _ALKRS_DO_SRLI16I _mm_srli_epi16
	#define _ALKRS_DO_SRAI16I _mm_srai_epi16

	#define _ALKRS_DO_ADD32I _mm_add_epi32
	#define _ALKRS_DO_SUB32I _mm_sub_epi32
	#define _ALKRS_DO_MULLO32I _mm_mullo_epi32
	#define _ALKRS_DO_MULHI32I _mm_mulhi_epi32
	#define _ALKRS_DO_SLLI32I _mm_slli_epi32
	#define _ALKRS_DO_SRLI32I _mm_srli_epi32
	#define _ALKRS_DO_SRAI32I _mm_srai_epi32

	#define _ALKRS_DO_ADD64I _mm_add_epi64
	#define _ALKRS_DO_SUB64I _mm_sub_epi64
	#define _ALKRS_DO_MULLO64I _mm_mullo_epi64
	#define _ALKRS_DO_MULHI64I _mm_mulhi_epi64
	#define _ALKRS_DO_SLLI64I _mm_slli_epi64
	#define _ALKRS_DO_SRLI64I _mm_srli_epi64
	#define _ALKRS_DO_SRAI64I _mm_srai_epi64

#endif // - - - - - - - - - - - - - - - - - - - - - - -

#else

#define _ALKRS_SIMDMODE 0
#define _ALKRS_REGTYPEF double float
#define _ALKRS_REGTYPEI uint64_t
#define _ALKRS_SETZERO() (uint64_t)0;
#define _ALKRS_LOADVALUE(PtrValue) ((uint64_t*)PtrValue)[0]
#define _ALKRS_STOREVALUE(PtrValue,PasteValue) PtrValue[0] = PasteValue
#define _ALKRS_DO_OR(a,b) (a | b)
#define _ALKRS_DO_SHIFTL(a,b) (a << b)
#define _ALKRS_REGSZ 8

#endif

 #ifdef _POSIX_THREADS 

#include <pthread.h>
#define _ALKR_PARAMODE 1
#else

#define _ALKR_PARAMODE 0
#endif
