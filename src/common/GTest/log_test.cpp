#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include "log.h"

TEST(LogClass, reOPEN_withOutExist)
{
    Log::OPEN();

    Log::ERR("patata\n");
    Log::ERR("tomate\n");
    Log::ERR("pera\n");
    Log::FLUSH();
    
    std::ifstream file;
    std::string line;
    file.open(Log::FNAME(Log::err));
    std::getline(file, line);
    GTEST_ASSERT_EQ(line, "patata");
    std::getline(file, line);
    GTEST_ASSERT_EQ(line, "tomate");
    std::getline(file, line);
    GTEST_ASSERT_EQ(line, "pera");
    file.close();
    Log::OPEN();
}

TEST(LogClass, test_LOG)
{
    Log::LOG("mes-3");
    Log::LOG("mess-3 b");
    Log::LOG("mess-3 c\n");
    Log::LOG("mess-3 d\n");
    Log::FLUSH();

    std::ifstream file;
    std::string line;
    file.open(Log::FNAME(Log::log));
    std::getline(file, line);
    GTEST_ASSERT_EQ(line, "mes-3mess-3 bmess-3 c");
    std::getline(file, line);
    GTEST_ASSERT_EQ(line, "mess-3 d");
    file.close();

}

TEST(LogClass, test_Error)
{
    Log::ERR("error mes-3");
    Log::ERR("error mess-3 b");
    Log::ERR("error mess-3 c");
    Log::ERR("error mes-3 aa\n");
    Log::ERR("error mess-3 bb\n");
    Log::ERR(" ");
    Log::FLUSH();

    std::ifstream file;
    std::string line;
    file.open(Log::FNAME(Log::err));
    std::getline(file, line);
    GTEST_ASSERT_EQ(line, "error mes-3error mess-3 berror mess-3 cerror mes-3 aa");
    std::getline(file, line);
    GTEST_ASSERT_EQ(line, "error mess-3 bb");
    std::getline(file, line);
    GTEST_ASSERT_EQ(line, " ");
    file.close();
}


TEST(LogClass, reOPEN)
{
    Log::ERR("error mes-3\n");
    Log::ERR("error mess-3 b\n");
    Log::ERR("error mess-3 c\n");
    Log::OPEN();

    Log::ERR("patata\n");
    Log::ERR("tomate\n");
    Log::ERR("pera\n");
    Log::FLUSH();

    std::ifstream file;
    std::string line;
    file.open(Log::FNAME(Log::err));
    std::getline(file, line);
    GTEST_ASSERT_EQ(line, "patata");
    std::getline(file, line);
    GTEST_ASSERT_EQ(line, "tomate");
    std::getline(file, line);
    GTEST_ASSERT_EQ(line, "pera");
    file.close();
}
