#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include "processor.h"
using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { 
    return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
   string line, num, x;
  float Uptime, tot, seconds, ans;
  float utime , stime;
  float cutime, cstime, starttime;
    std::stringstream ss;
    ss<< pid;
    ss >> num;
    std::ifstream stream(LinuxParser::kProcDirectory + num + LinuxParser::kStatusFilename );
    if(stream.is_open()){
      
      
        std::istringstream linestream(line);
        for(int i =0; i < 22 ; i++){
          linestream >> x;
          if(i = 13){
            utime = stof(x);
          }  
          if(i = 14){
            stime = stof(x);
          }
          if(i = 15){
            cutime = stof(x);
          }
          if(i = 16){
            cstime = stof(x);
          }
          if(i=21){
            starttime = stof(x);
          }
        }
        
        //tot = utime - stime;
        tot = utime + stime + cutime + cstime;
        seconds = LinuxParser::UpTime(pid) - (starttime / sysconf(_SC_CLK_TCK) );
        ans = 100 * ((tot/sysconf(_SC_CLK_TCK))/ seconds);


    }
    return ans;  }

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
bool Process::operator<(Process const& a) const {
  if (stof(a.ram) < stof(this->ram)){
        return true;
    }else{
        return false;
    } }
