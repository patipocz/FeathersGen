#include <gtest/gtest.h>
#include "Feather.h"

int main(int argc ,char **argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

TEST(Feather,construct)
{
    Feather createFeatherTest();
   
}