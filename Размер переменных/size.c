



#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <wchar.h>
#include <time.h>
#include <inttypes.h>


//Команда для запуска:
//gcc size.c -o sizes
//./sizes.exe




int main() {
    // Basic char types
    printf("Type: char\n");
    printf("  Size: %zu bytes\n", sizeof(char));
    printf("  Range: %d to %d\n", CHAR_MIN, CHAR_MAX);

    printf("Type: signed char\n");
    printf("  Size: %zu bytes\n", sizeof(signed char));
    printf("  Range: %d to %d\n", SCHAR_MIN, SCHAR_MAX);

    printf("Type: unsigned char\n");
    printf("  Size: %zu bytes\n", sizeof(unsigned char));
    printf("  Range: 0 to %u\n", UCHAR_MAX);

    // Const char types
    printf("Type: const char\n");
    printf("  Size: %zu bytes\n", sizeof(const char));

    printf("Type: const signed char\n");
    printf("  Size: %zu bytes\n", sizeof(const signed char));

    printf("Type: const unsigned char\n");
    printf("  Size: %zu bytes\n", sizeof(const unsigned char));

    // Pointers to char types
    printf("Type: char*\n");
    printf("  Size: %zu bytes\n", sizeof(char*));

    printf("Type: signed char*\n");
    printf("  Size: %zu bytes\n", sizeof(signed char*));

    printf("Type: unsigned char*\n");
    printf("  Size: %zu bytes\n", sizeof(unsigned char*));

    printf("Type: const char*\n");
    printf("  Size: %zu bytes\n", sizeof(const char*));

    printf("Type: const signed char*\n");
    printf("  Size: %zu bytes\n", sizeof(const signed char*));

    printf("Type: const unsigned char*\n");
    printf("  Size: %zu bytes\n", sizeof(const unsigned char*));

    // Arrays of char types
    printf("Type: char[]\n");
    printf("  Size: %zu bytes\n", sizeof(char[10])); // Example with array size 10

    printf("Type: signed char[]\n");
    printf("  Size: %zu bytes\n", sizeof(signed char[10])); // Example with array size 10

    printf("Type: unsigned char[]\n");
    printf("  Size: %zu bytes\n", sizeof(unsigned char[10])); // Example with array size 10

    printf("Type: const char[]\n");
    printf("  Size: %zu bytes\n", sizeof(const char[10])); // Example with array size 10

    printf("Type: const signed char[]\n");
    printf("  Size: %zu bytes\n", sizeof(const signed char[10])); // Example with array size 10

    printf("Type: const unsigned char[]\n");
    printf("  Size: %zu bytes\n", sizeof(const unsigned char[10])); // Example with array size 10

    // Two-dimensional arrays of char types
    printf("Type: char[][]\n");
    printf("  Size: %zu bytes\n", sizeof(char[10][10])); // Example with array size 10x10

    printf("Type: signed char[][]\n");
    printf("  Size: %zu bytes\n", sizeof(signed char[10][10])); // Example with array size 10x10

    printf("Type: unsigned char[][]\n");
    printf("  Size: %zu bytes\n", sizeof(unsigned char[10][10])); // Example with array size 10x10

    printf("Type: const char[][]\n");
    printf("  Size: %zu bytes\n", sizeof(const char[10][10])); // Example with array size 10x10

    printf("Type: const signed char[][]\n");
    printf("  Size: %zu bytes\n", sizeof(const signed char[10][10])); // Example with array size 10x10

    printf("Type: const unsigned char[][]\n");
    printf("  Size: %zu bytes\n", sizeof(const unsigned char[10][10])); // Example with array size 10x10

    printf("Type: short\n");
    printf("  Size: %zu bytes\n", sizeof(short));
    printf("  Range: %d to %d\n", SHRT_MIN, SHRT_MAX);
    
    printf("Type: unsigned short\n");
    printf("  Size: %zu bytes\n", sizeof(unsigned short));
    printf("  Range: 0 to %u\n", USHRT_MAX);
    
    printf("Type: int\n");
    printf("  Size: %zu bytes\n", sizeof(int));
    printf("  Range: %d to %d\n", INT_MIN, INT_MAX);
    
    printf("Type: unsigned int\n");
    printf("  Size: %zu bytes\n", sizeof(unsigned int));
    printf("  Range: 0 to %u\n", UINT_MAX);
    
    printf("Type: long int\n");
    printf("  Size: %zu bytes\n", sizeof(long int));
    printf("  Range: %ld to %ld\n", LONG_MIN, LONG_MAX);
    
    printf("Type: long long int\n");
    printf("  Size: %zu bytes\n", sizeof(long long int));
    printf("  Range: %lld to %lld\n", LLONG_MIN, LLONG_MAX);
    
    printf("Type: signed long int\n");
    printf("  Size: %zu bytes\n", sizeof(signed long int));
    printf("  Range: %ld to %ld\n", LONG_MIN, LONG_MAX);
    
    printf("Type: signed long long\n");
    printf("  Size: %zu bytes\n", sizeof(signed long long));
    printf("  Range: %lld to %lld\n", LLONG_MIN, LLONG_MAX);
    
    printf("Type: unsigned long int\n");
    printf("  Size: %zu bytes\n", sizeof(unsigned long int));
    printf("  Range: 0 to %lu\n", ULONG_MAX);
    
    printf("Type: unsigned long long\n");
    printf("  Size: %zu bytes\n", sizeof(unsigned long long));
    printf("  Range: 0 to %llu\n", ULLONG_MAX);
    
    printf("Type: float\n");
    printf("  Size: %zu bytes\n", sizeof(float));
    printf("  Range: %e to %e\n", FLT_MIN, FLT_MAX);
    
    printf("Type: double\n");
    printf("  Size: %zu bytes\n", sizeof(double));
    printf("  Range: %e to %e\n", DBL_MIN, DBL_MAX);
    
    printf("Type: long double\n");
    printf("  Size: %zu bytes\n", sizeof(long double));
    printf("  Range: %Le to %Le\n", LDBL_MIN, LDBL_MAX);
    
    printf("Type: bool\n");
    printf("  Size: %zu bytes\n", sizeof(bool));
    printf("  Range: 0 to 1\n");
    
    printf("Type: size_t\n");
    printf("  Size: %zu bytes\n", sizeof(size_t));
    printf("  Range: 0 to %zu\n", SIZE_MAX);
    
    printf("Type: void*\n");
    printf("  Size: %zu bytes\n", sizeof(void*));
    
    printf("Type: char*\n");
    printf("  Size: %zu bytes\n", sizeof(char*));
    
    printf("Type: int*\n");
    printf("  Size: %zu bytes\n", sizeof(int*));
    
    printf("Type: int8_t\n");
    printf("  Size: %zu bytes\n", sizeof(int8_t));
    printf("  Range: %" PRId8 " to %" PRId8 "\n", INT8_MIN, INT8_MAX);
    
    printf("Type: uint8_t\n");
    printf("  Size: %zu bytes\n", sizeof(uint8_t));
    printf("  Range: 0 to %" PRIu8 "\n", UINT8_MAX);
    
    printf("Type: int16_t\n");
    printf("  Size: %zu bytes\n", sizeof(int16_t));
    printf("  Range: %" PRId16 " to %" PRId16 "\n", INT16_MIN, INT16_MAX);
    
    printf("Type: uint16_t\n");
    printf("  Size: %zu bytes\n", sizeof(uint16_t));
    printf("  Range: 0 to %" PRIu16 "\n", UINT16_MAX);
    
    printf("Type: int32_t\n");
    printf("  Size: %zu bytes\n", sizeof(int32_t));
    printf("  Range: %" PRId32 " to %" PRId32 "\n", INT32_MIN, INT32_MAX);
    
    printf("Type: uint32_t\n");
    printf("  Size: %zu bytes\n", sizeof(uint32_t));
    printf("  Range: 0 to %" PRIu32 "\n", UINT32_MAX);
    
    printf("Type: int64_t\n");
    printf("  Size: %zu bytes\n", sizeof(int64_t));
    printf("  Range: %" PRId64 " to %" PRId64 "\n", INT64_MIN, INT64_MAX);
    
    printf("Type: uint64_t\n");
    printf("  Size: %zu bytes\n", sizeof(uint64_t));
    printf("  Range: 0 to %" PRIu64 "\n", UINT64_MAX);
    
    printf("Type: intptr_t\n");
    printf("  Size: %zu bytes\n", sizeof(intptr_t));
    printf("  Range: %" PRIdPTR " to %" PRIdPTR "\n", INTPTR_MIN, INTPTR_MAX);
    
    printf("Type: uintptr_t\n");
    printf("  Size: %zu bytes\n", sizeof(uintptr_t));
    printf("  Range: 0 to %" PRIuPTR "\n", UINTPTR_MAX);
    
    printf("Type: ptrdiff_t\n");
    printf("  Size: %zu bytes\n", sizeof(ptrdiff_t));
    printf("  Range: %td to %td\n", PTRDIFF_MIN, PTRDIFF_MAX);
    
    printf("Type: wchar_t\n");
    printf("  Size: %zu bytes\n", sizeof(wchar_t));
    printf("  Range: %d to %d\n", WCHAR_MIN, WCHAR_MAX);
    
    printf("Type: time_t\n");
    printf("  Size: %zu bytes\n", sizeof(time_t));

    // Const types
    printf("Const Type: const int\n");
    printf("  Size: %zu bytes\n", sizeof(const int));
    
    printf("Const Type: const unsigned int\n");
    printf("  Size: %zu bytes\n", sizeof(const unsigned int));
    
    printf("Const Type: const long int\n");
    printf("  Size: %zu bytes\n", sizeof(const long int));
    
    printf("Const Type: const unsigned long int\n");
    printf("  Size: %zu bytes\n", sizeof(const unsigned long int));
    
    printf("Const Type: const float\n");
    printf("  Size: %zu bytes\n", sizeof(const float));
    
    printf("Const Type: const double\n");
    printf("  Size: %zu bytes\n", sizeof(const double));
    
    printf("Const Type: const char\n");
    printf("  Size: %zu bytes\n", sizeof(const char));
    
    printf("Const Type: const signed char\n");
    printf("  Size: %zu bytes\n", sizeof(const signed char));
    
    printf("Const Type: const unsigned char\n");
    printf("  Size: %zu bytes\n", sizeof(const unsigned char));
    
    printf("Const Type: const short\n");
    printf("  Size: %zu bytes\n", sizeof(const short));
    
    printf("Const Type: const unsigned short\n");
    printf("  Size: %zu bytes\n", sizeof(const unsigned short));
    
    printf("Const Type: const void*\n");
    printf("  Size: %zu bytes\n", sizeof(const void*));

    printf("Const Type: const char*\n");
    printf("  Size: %zu bytes\n", sizeof(const char*));
    
    printf("Const Type: const int*\n");
    printf("  Size: %zu bytes\n", sizeof(const int*));


    return 0;
}
