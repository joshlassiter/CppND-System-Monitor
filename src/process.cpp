#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpuUtilization; }

// TODO: Return the command that generated this process
string Process::Command() { 
    command == LinuxParser::Command(pid);
    return command; }

// TODO: Return this process's memory utilization
string Process::Ram() { 
    ram = LinuxParser::Ram(pid);
    return ram; }

// TODO: Return the user (name) that generated this process
string Process::User() {
    user = LinuxParser::User(pid);
     return user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
    upTime = LinuxParser::UpTime(pid); 
    return upTime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }