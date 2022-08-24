#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <math.h>
#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
using std::set;
using std::size_t;
using std::string;
using std::vector;
/*You need to complete the mentioned TODOs in order to satisfy the rubric criteria "The student will be able to extract and display basic data about the system."

You need to properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    processes_.clear();
    vector <int> p = LinuxParser::Pids();
    for(  unsigned int i=0;i<=p.size()-1; i++){
      
        Process x = Process(p.at(i));
      
        if(x.Command() != "unknown" && x.CpuUtilization() != 0  &&  x.Ram() != "unknown")
        {
        processes_.push_back(x);
        }
    }
   std::sort(processes_.begin(), processes_.end());
    return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    string x = LinuxParser::Kernel();
    return x; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    float x = LinuxParser::MemoryUtilization();
    return x; }

// TODO: Return the operating system name
std::string System::OperatingSystem() {
    std::string x = LinuxParser::OperatingSystem();
     return x; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    int x = LinuxParser::RunningProcesses();
    return x; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    int x = LinuxParser::TotalProcesses();
    return x;
     }

// TODO: Return the number of seconds since the system started running
long System::UpTime() { 
    long  x = LinuxParser::UpTime();
    return x; }
