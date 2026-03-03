#include "gtest/gtest.h"
#include "sum.h"

// helper to execute a command and capture stdout + exit code
#include <array>
#include <cstdio>
#include <memory>
#include <string>
#include <sys/wait.h>
#include <sstream>

struct CmdResult {
    std::string out;
    std::string err;
    int exitCode;
};

static CmdResult runCommand(const std::string &cmd) {
    std::array<char, 128> buffer;
    std::string resultOut, resultErr;
    FILE *pipe = popen((cmd + " 2>&1").c_str(), "r");
    if (!pipe) return {"", "", -1};
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        resultOut += buffer.data();
    }
    int rc = pclose(pipe);
    int status = -1;
    if (WIFEXITED(rc))
        status = WEXITSTATUS(rc);

    // Separate stdout and stderr
    std::istringstream stream(resultOut);
    std::string line;
    while (std::getline(stream, line)) {
        if (line.find("Error:") == 0) {
            resultErr += line + "\n";
        } else {
            resultOut += line + "\n";
        }
    }

    return {resultOut, resultErr, status};
}

TEST(SumTest, BasicCases) {
    EXPECT_EQ(compute_sum(1), 1);
    EXPECT_EQ(compute_sum(5), 15);
    EXPECT_EQ(compute_sum(0), 0);
    EXPECT_EQ(compute_sum(-3), 0);
}

TEST(FiboTest, BasicCases) {
    EXPECT_EQ(fibo(1), 1);
    EXPECT_EQ(fibo(2), 1);
    EXPECT_EQ(fibo(10), 55);
    EXPECT_EQ(fibo(0), 0);
    EXPECT_EQ(fibo(-5), 0);
}

TEST(CliTest, SumDefault) {
    // assume tests run from build directory where SumOuFibo is located
    auto r = runCommand("./SumOuFibo 5");
    EXPECT_EQ(r.exitCode, 0);
    EXPECT_EQ(r.out, "15\n");
}

TEST(CliTest, FiboOption) {
    auto r = runCommand("./SumOuFibo -f 10");
    EXPECT_EQ(r.exitCode, 0);
    EXPECT_EQ(r.out, "55\n");
}

TEST(CliTest, ErrorMissingArg) {
    auto r = runCommand("./SumOuFibo");
    EXPECT_NE(r.exitCode, 0);
    EXPECT_FALSE(r.err.empty());
    EXPECT_TRUE(r.err.find("Error: Missing argument") != std::string::npos);
}

TEST(CliTest, ErrorInvalidNum) {
    auto r = runCommand("./SumOuFibo abc");
    EXPECT_NE(r.exitCode, 0);
    EXPECT_FALSE(r.err.empty());
    EXPECT_TRUE(r.err.find("Error: Invalid number") != std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
