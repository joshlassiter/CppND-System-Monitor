#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string label, value;
  string line; 
  float memTot, memFree, memUtil;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if(stream.is_open()){
    while (std::getline(stream,line)){
        std::istringstream linestream(line);
        while(linestream >> label >> value){
          if (label == "MemTotal:"){
            memTot = std:: stof(value);

          }
          else if(label == "MemFree:"){
            memFree = std:: stof(value);
          }
        }
    }

    memUtil = memTot - memFree;
  }
  return memUtil; }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
    long time;
    string line, t;
    std::ifstream stream(kProcDirectory + kUptimeFilename);
    if(stream.is_open()){
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> t;
      time = stol(t);

    }
   return time; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
    long jiffies = UpTime() * sysconf(_SC_CLK_TCK);

   return jiffies; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { 
  std::stringstream ss;
  string num;
    ss<< pid;
    ss >> num;
  long jiffies;
  string line, lable, NotNeeded, Utime, Stime,Cutime, Cstime;
  long utime, stime,cutime, cstime;
  std::ifstream stream(kProcDirectory + num + kStatFilename);
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >>lable >> NotNeeded >>  NotNeeded >> NotNeeded >> NotNeeded >> NotNeeded >> NotNeeded >> NotNeeded >> NotNeeded >> NotNeeded >> NotNeeded >> NotNeeded >> NotNeeded >> Utime >> Stime >> Cutime >>Cstime;  ;
    utime = stol(Utime);
    stime = stol(Stime);
    cutime = stol(Cutime);
    cstime = stol(Cstime);
    

    jiffies = utime + stime + cutime + cstime;
  }

   return jiffies; }

// TODO: Read anB return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  long jiffies;
  string line, lable, User, Nice, System, Idle, IoWait, Irq, SoftIrq, Steal, Guest, Guest_Nice;
  long user, nice,system,idle,ioWait,irq,softIrq,steal,guest,guest_Nice,j;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >>lable >> User >>  Nice >> System >> Idle >> IoWait >> Irq >> SoftIrq >> Steal >> Guest >> Guest_Nice ;
    user = stol(User);
    nice = stol(Nice);
    system = stol(System);
    idle = stol(Idle);
    ioWait = stol(IoWait);
    irq = stol(Irq);
    softIrq = stol(SoftIrq);
    steal = stol(Steal);
    guest = stol(Guest);
    guest_Nice = stol(Guest_Nice);

    jiffies = (user + nice+system+irq+softIrq+steal+guest+guest_Nice+j)/sysconf(_SC_CLK_TCK);
  }

   return jiffies;}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { long jiffies;
  string line, lable, User, Nice, System, Idle, IoWait, Irq, SoftIrq, Steal, Guest, Guest_Nice;
  long user, nice,system,idle,ioWait,irq,softIrq,steal,guest,guest_Nice,j;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >>lable >> User >>  Nice >> System >> Idle >> IoWait >> Irq >> SoftIrq >> Steal >> Guest >> Guest_Nice ;
    user = stol(User);
    nice = stol(Nice);
    system = stol(System);
    idle = stol(Idle);
    ioWait = stol(IoWait);
    irq = stol(Irq);
    softIrq = stol(SoftIrq);
    steal = stol(Steal);
    guest = stol(Guest);
    guest_Nice = stol(Guest_Nice);

    jiffies = idle + ioWait;
  }

   return jiffies;}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector <string> cpuUtil;
  string line;
  string x;
  std::ifstream stream(kProcDirectory + kStatFilename );
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    for (int i = 0; i<=10; i++){
      linestream >> x;
      if (x != "0" && x!="cpu" ){
        cpuUtil.push_back(x);
      }
    }
  }
  return cpuUtil; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string lable, value;
  string line;
  int procceses;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      linestream >> lable >> value;
      if (lable == "processes"){
          procceses = stoi(value);
          return procceses;
      }
    }
  }
  return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { string lable, value;
  string line;
  int runningProc;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      linestream >> lable >> value;
      if (lable == "proc_running"){
          runningProc = stoi(value);
          return runningProc;
      }
    }
  }return 0; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
    string line, num;
    std::stringstream ss;
    ss<< pid;
    ss >> num;
    std::ifstream stream(kProcDirectory + num + kCmdlineFilename );
    if(stream.is_open()){
      std::getline(stream,line);
    }

   return line; }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {  
  string line, num, lable, data, ram;
  int mem,value;
    std::stringstream ss;
    ss<< pid;
    ss >> num;
    std::ifstream stream(kProcDirectory + num + kStatusFilename );
    if(stream.is_open()){
      
      while(std::getline(stream,line)){
        std::istringstream linestream(line);
        linestream >> lable >> data;
        if(lable == "Vmsize:"){
          mem = stoi(data);
          value = mem/1000;
          std::stringstream aa;
          aa<<value;
          aa >> ram;
          return ram;
        }
      }
    }

   return 0;  }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line, num, lable, id;
  
    std::stringstream ss;
    ss<< pid;
    ss >> num;
    std::ifstream stream(kProcDirectory + num + kStatusFilename );
    if(stream.is_open()){
      
      while(std::getline(stream,line)){
        std::istringstream linestream(line);
        linestream >> lable >> id;
        if(lable == "Uid:"){
         
          return id;
        }
      }
    }

   return 0;  }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  
  string line, user, value, id;
  string check = LinuxParser::Uid(pid);
    std::stringstream ss;
    
    std::ifstream stream(kPasswordPath );
    if(stream.is_open()){
      
      while(std::getline(stream,line)){
        std::istringstream linestream(line);
        std::replace(line.begin(),line.end(), ':', ' ');
        linestream >> user >> value;
        if(user == check){
         
          return value;
        }
      }
    }

   return 0;  }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line, num, value, ans;
  long Uptime;
    std::stringstream ss;
    ss<< pid;
    ss >> num;
    std::ifstream stream(kProcDirectory + num + kStatusFilename );
    if(stream.is_open()){
      
      while(std::getline(stream,line)){
        std::istringstream linestream(line);
        linestream >> value >> value >> value >> value >> value >> value >> value >> value >> value >> value >> value >> value >> value >> value >> value >> value >> value >> value >> value >> value >> value >> ans;
        Uptime = stol(ans);
          return Uptime;
        }
    }
    }
