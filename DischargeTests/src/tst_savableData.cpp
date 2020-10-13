#include "catch.hpp"
#include "testToolbox.h"

#include "SavableData.h"

TEST_CASE("SavableData creation", "[SavableData]")
{
    SavableData data;

    CHECK(data.size() == 0);
    CHECK(data.pos() == 0);
    CHECK(data.atEnd() == true);
}

TEST_CASE("SavableData add one byte", "[SavableData]")
{
    SavableData data;

    data.add(0xff);

    CHECK(data.size() == 1);
    CHECK(data.pos() == 0);
    CHECK(data.atEnd() == false);

    CHECK(data.read() == 0xff);
    CHECK(data.pos() == 1);
    CHECK(data.atEnd() == true);
}

TEST_CASE("SavableData add multiple bytes", "[SavableData]")
{
    SavableData data;
    char text[] = "Some Data";

    data.add(RawBytesConst(text), sizeof(text));

    CHECK(data.size() == sizeof(text));
    CHECK(data.pos() == 0);
    CHECK(data.atEnd() == false);

    CHECK(data.read() == 'S');
    CHECK(data.read() == 'o');
    CHECK(data.read() == 'm');
    CHECK(data.pos() == 3);

    data.seek(8);
    CHECK(data.read() == 'a');
    CHECK(data.read() == '\0');
    CHECK(data.atEnd() == true);
}


TEST_CASE("SavableData add other savable", "[SavableData]")
{
    SavableData data1;
    SavableData data2;

    char text1[] = "Some ";
    char text2[] = "Data";

    data1.add(RawBytesConst(text1), sizeof(text1) - 1);
    data2.add(RawBytesConst(text2), sizeof(text2));
    data1.add(data2);

    CHECK(data1.size() == 10);

    CHECK(data1.read() == 'S');
    CHECK(data1.read() == 'o');
    CHECK(data1.read() == 'm');
    CHECK(data1.pos() == 3);

    data1.seek(8);
    CHECK(data1.read() == 'a');
    CHECK(data1.read() == '\0');
    CHECK(data1.atEnd() == true);
}

TEST_CASE("SavableData read multiple bytes", "[SavableData]")
{
    SavableData data;
    char text[] = "Some Data";
    char out[sizeof(text)];

    data.add(RawBytesConst(text), sizeof(text));
    data.read(RawBytes(out), sizeof(out));

    CHECK(strcmp(text, out) == 0);
}