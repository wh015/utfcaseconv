#if (CATCH2_VERSION < 3)
    #define CATCH_CONFIG_MAIN
    #define CATCH_CONFIG_ENABLE_BENCHMARKING
    #include <catch2/catch.hpp>
#else
    #include <catch2/catch_test_macros.hpp>
    #include <catch2/benchmark/catch_benchmark.hpp>
#endif

