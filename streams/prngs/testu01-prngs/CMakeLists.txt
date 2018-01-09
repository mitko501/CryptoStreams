# TestU01 downloaded from: http://simul.iro.umontreal.ca/testu01/TestU01.zip date of zip: 10-Feb-2015 19:23

file(GLOB testu01-includes
        "includes/*.h"
        "includes/*.c"
        )


add_library(testu01-prngs STATIC EXCLUDE_FROM_ALL
        ${testu01-includes}

        # interface
        testu01_generator.h
        testu01_interface.h

        # unif01 functions
        functions/unif01/unif01.c # unif01.h is basic header file needed for all geenrators so it is in include directory not here
        functions/unif01/dummy_generator.h

        # ulcg functions
        functions/ulcg/ulcg.h
        functions/ulcg/ulcg.c
        functions/ulcg/ulcg_generator.h

        # umrg functions
        functions/umrg/umrg.h
        functions/umrg/umrg.c
        )

target_link_libraries(testu01-prngs eacirc-core)
