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
using std::stof;

// TODO: Return this process's ID
int Process::Pid() { 
    return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
   string line, num, x ;
  float tot, ans;
  long seconds;
  long utime , stime;
  long cutime, cstime;
    std::stringstream ss;
    ss<< pid;
    ss >> num;
    std::ifstream stream(LinuxParser::kProcDirectory + num + LinuxParser::kStatFilename );
    if(stream.is_open()){
      
      	while(std::getline(stream,line)){
        std::istringstream linestream(line);
        for(int i =0; i < 17 ; i++){
          linestream >> x;
         
          
          if(i == 13){
            
              utime = stol(x);
                        
          }  
          else if(i == 14){
            
              stime = stol(x);
            
             
          }
          else if(i == 15){
            
              cutime = stol(x);
            
            
          }
          else if(i == 16){
            
              cstime = stol(x);
            tot = utime + stime + cutime + cstime;
        seconds = Process::UpTime() ;
        ans = ((tot/sysconf(_SC_CLK_TCK))/ seconds);
        cpuUtilization = ans;
		return cpuUtilization;
             
          }
          else {
          
          }
          
          
          
        } 
         
          
        }
      
    }
        

return 0;
    
    
}
// TODO: Return the command that generated this process
string Process::Command() { 
    command = LinuxParser::Command(pid);
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
long Process::UpTime() {
    upTime = LinuxParser::UpTime() - LinuxParser::UpTime(pid); 
    return upTime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  if (stof(a.ram) < stof(this->ram)){
        return true;
    }else{
        return false;
    } }
