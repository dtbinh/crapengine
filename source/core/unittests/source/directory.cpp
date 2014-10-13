
#include "UnitTest++.h"

#include "directory.h"

crap::directory_t* my_dir;

namespace
{

TEST(CreateDirectoryT)
{
    my_dir = new crap::directory_t;
}

TEST(OpenDirectory)
{
    crap::openDirectory( my_dir, "../../../data" );
}

TEST(PrintDirectory)
{
    do
    {
        std::cout << "FileName " << crap::directoryName( my_dir ) << " is a directory?->" << crap::isDirectory("../../../data", my_dir) << std::endl;
    } while( crap::nextDirectory( my_dir ) );
}

TEST(CloseDirectory)
{
    crap::closeDirectory( my_dir );
}

TEST(DestroyDirectory)
{
    delete my_dir;
}

}
