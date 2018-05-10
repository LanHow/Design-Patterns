#include <gtest/gtest.h>
#include "ut_fs.h"
#include "ut_iterator.h"
#include "ut_visitor.h"

int main( int argc , char **argv )
{
    testing :: InitGoogleTest( &argc , argv ) ;
    return RUN_ALL_TESTS( ) ;
}
