#include "processor.h"
#include "linux_parser.h"
#include <vector>
using std::vector;
using std::string;
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
      vector <string> util = LinuxParser::CpuUtilization();
   float total, idle, newTot, newId, X;
   
   for (  int i=0; i<util.size();i++){
      total += stof(util[i]);
   }
   
   idle = stof(util[3])+ stof(util[4]);

    newTot = total - oldTot;
    newId = idle - oldId; 
    oldTot = total;
    oldId =   idle;
   
   X = (newTot - newId)/newTot;
   
    return X;  }