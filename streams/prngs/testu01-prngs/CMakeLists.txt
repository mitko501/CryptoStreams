# TestU01 downloaded from: http://simul.iro.umontreal.ca/testu01/TestU01.zip date of zip: 10-Feb-2015 19:23

file(GLOB testu01-includes
        "includes/*.h"
        "includes/*.c"
        )


add_library(testu01-prngs STATIC EXCLUDE_FROM_ALL
        ${testu01-includes}
        functions/unif01/unif01.c
        functions/unif01/dummy_generator.h
        testu01_generator.h
        testu01_interface.h
        )

target_link_libraries(testu01-prngs eacirc-core)
