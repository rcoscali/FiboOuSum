#include "gtest/gtest.h"
#include "sum.h"

// helper to execute a command and capture stdout + exit code
#include <array>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

struct CmdResult {
    std::string out;
    std::string err;
    int exitCode;
};

// Exécute une commande et capture stdout et stderr séparément
static CmdResult runCommand(const std::string &cmd) {
    static CmdResult runCommand(const std::vector<std::string> &args) {
    pipe(out_pipe);
    pipe(err_pipe);
    static CmdResult runCommand(const std::vector<std::string> &args) {
    if (pid == 0) {
        // Enfant : redirige stdout et stderr
        dup2(out_pipe[1], STDOUT_FILENO);
        dup2(err_pipe[1], STDERR_FILENO);
        close(out_pipe[0]); close(out_pipe[1]);
        close(err_pipe[0]); close(err_pipe[1]);
        // Découpe la commande en arguments (robuste)
        std::istringstream iss(cmd);
        std::vector<std::string> args;
        std::string arg;
            std::vector<char*> argv;
            for (const auto& s : args) argv.push_back(const_cast<char*>(s.c_str()));
            argv.push_back(nullptr);
            execvp(argv[0], argv.data());
            _exit(127);
        _exit(127);
    }
            pid_t pid = fork();
                setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 1);
    close(out_pipe[1]);
    close(err_pipe[1]);
    std::string out, err;
    char buffer[256];
    ssize_t n;
    // Lecture stdout
    while ((n = read(out_pipe[0], buffer, sizeof(buffer))) > 0) out.append(buffer, n);
    // Lecture stderr
    while ((n = read(err_pipe[0], buffer, sizeof(buffer))) > 0) err.append(buffer, n);
    close(out_pipe[0]);
    close(err_pipe[0]);
    int status = -1;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) status = WEXITSTATUS(status);
    else status = -1;
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
        auto r = runCommand({"/home/rcoscali/Sources/FiboOuSum/build/SumOuFibo", "5"});
        auto r = runCommand("/home/rcoscali/Sources/FiboOuSum/build/SumOuFibo 5");
            auto r = runCommand({"/home/rcoscali/Sources/FiboOuSum/build/SumOuFibo", "5"});
}

        auto r = runCommand({"/home/rcoscali/Sources/FiboOuSum/build/SumOuFibo", "-f", "10"});
    auto r = runCommand("../build/SumOuFibo -f 10");
        auto r = runCommand("/home/rcoscali/Sources/FiboOuSum/build/SumOuFibo -f 10");
            auto r = runCommand({"/home/rcoscali/Sources/FiboOuSum/build/SumOuFibo", "-f", "10"});
        auto r = runCommand({"/home/rcoscali/Sources/FiboOuSum/build/SumOuFibo"});

TEST(CliTest, ErrorMissingArg) {
    auto r = runCommand("../build/SumOuFibo");
        auto r = runCommand("/home/rcoscali/Sources/FiboOuSum/build/SumOuFibo");
            auto r = runCommand({"/home/rcoscali/Sources/FiboOuSum/build/SumOuFibo"});
    EXPECT_NE(r.exitCode, 0);
    EXPECT_NE(r.err.find("Argument non valide"), std::string::npos);
}

int main(int argc, char **argv) {
            auto r = runCommand({"/home/rcoscali/Sources/FiboOuSum/build/SumOuFibo", "abc"});
    auto r = runCommand("../build/SumOuFibo abc");
