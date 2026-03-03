#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sum.h"

// Helper to execute a command and capture stdout + stderr + exit code
// Used for CLI integration tests
#include <array>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>

// Structure to hold command execution results
struct CmdResult {
    std::string out;      // Standard output from command
    std::string err;      // Standard error from command
    int exitCode;         // Exit code of the command
};

// Execute a command and capture both stdout and stderr separately
// @param cmd: Command string to execute
// @return: CmdResult containing stdout, stderr, and exit code
static CmdResult runCommand(const std::string &cmd) {
    // Create a temporary file for capturing stderr
    char tmpfile[] = "/tmp/test_stderr_XXXXXX";
    int fd = mkstemp(tmpfile);
    if (fd == -1) return {"", "", -1};
    close(fd);

    // Redirect stderr to temporary file
    std::string fullCmd = cmd + " 2>" + tmpfile;
    
    // Capture stdout using popen
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
    
    // Read stderr from the temporary file
    std::string err;
    FILE *errFile = fopen(tmpfile, "r");
    if (errFile) {
        while (fgets(buffer.data(), buffer.size(), errFile) != nullptr) {
            err += buffer.data();
        }
        fclose(errFile);
        unlink(tmpfile);  // Clean up temporary file
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

// Test: Default mode (sum) with valid input
TEST(CliTest, SumDefault) {
    // Assume tests run from build directory where SumOuFibo is located
    auto r = runCommand("./SumOuFibo 5");
    // Verify successful execution
    EXPECT_EQ(r.exitCode, 0);
    // Verify correct output (sum of 1+2+3+4+5 = 15)
    EXPECT_EQ(r.out, "15\n");
}

// Test: Fibonacci mode with -f flag
TEST(CliTest, FiboOption) {
    // Execute with -f flag to compute Fibonacci
    auto r = runCommand("./SumOuFibo -f 10");
    // Verify successful execution
    EXPECT_EQ(r.exitCode, 0);
    // Verify correct Fibonacci output (10th Fibonacci number = 55)
    EXPECT_EQ(r.out, "55\n");
}

// Test: Error handling - missing required argument
TEST(CliTest, ErrorMissingArg) {
    // Execute without required argument
    auto r = runCommand("./SumOuFibo");
    // Verify non-zero exit code (error case)
    EXPECT_NE(r.exitCode, 0);
    // Verify stderr contains usage information
    EXPECT_THAT(r.err, ::testing::HasSubstr("Usage:"));
    EXPECT_THAT(r.err, ::testing::HasSubstr("entier"));
}

// Test: Error handling - invalid argument (non-numeric)
TEST(CliTest, ErrorInvalidNum) {
    // Execute with non-numeric argument
    auto r = runCommand("./SumOuFibo abc");
    // Verify non-zero exit code (error case)
    EXPECT_NE(r.exitCode, 0);
    // Verify stderr contains error message
    EXPECT_THAT(r.err, ::testing::HasSubstr("Argument non valide"));
    // Verify the invalid argument is mentioned
    EXPECT_THAT(r.err, ::testing::HasSubstr("abc"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
