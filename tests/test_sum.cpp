#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sum.h"

// helper to execute a command and capture stdout + stderr + exit code
#include <array>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>

struct CmdResult {
    std::string out;
    std::string err;
    int exitCode;
};

static CmdResult runCommand(const std::string &cmd) {
    char tmpfile[] = "/tmp/test_stderr_XXXXXX";
    int fd = mkstemp(tmpfile);
    if (fd == -1) return {"", "", -1};
    close(fd);

    std::string fullCmd = cmd + " 2>" + tmpfile;
    
    std::array<char, 128> buffer;
    std::string out;
    FILE *pipe = popen(fullCmd.c_str(), "r");
    if (!pipe) {
        unlink(tmpfile);
        return {"", "", -1};
    }
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        out += buffer.data();
    }
    int rc = pclose(pipe);
    int status = -1;
    if (WIFEXITED(rc))
        status = WEXITSTATUS(rc);
    
    // Read stderr from tempfile
    std::string err;
    FILE *errFile = fopen(tmpfile, "r");
    if (errFile) {
        while (fgets(buffer.data(), buffer.size(), errFile) != nullptr) {
            err += buffer.data();
        }
        fclose(errFile);
        unlink(tmpfile);
    }
    
    return {out, err, status};
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
    EXPECT_THAT(r.err, ::testing::HasSubstr("Usage:"));
    EXPECT_THAT(r.err, ::testing::HasSubstr("entier"));
}

TEST(CliTest, ErrorInvalidNum) {
    auto r = runCommand("./SumOuFibo abc");
    EXPECT_NE(r.exitCode, 0);
    EXPECT_THAT(r.err, ::testing::HasSubstr("Argument non valide"));
    EXPECT_THAT(r.err, ::testing::HasSubstr("abc"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
