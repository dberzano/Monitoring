///
/// \file 5-Benchmark.cxx
/// \author Adam Wegrzynek <adam.wegrzynek@cern.ch>
///

#include "Monitoring/MonitoringFactory.h"
#include <boost/program_options.hpp>
#include <random>

using Monitoring = AliceO2::Monitoring::MonitoringFactory;

int main(int argc, char *argv[]) {
  int sleep = 1000000;
  std::string stringMetric = "stringMetric";
  std::string doubleMetric = "doubleMetric";
  std::string intMetric = "intMetric";

  std::random_device rd;
  std::mt19937 mt(rd());

  std::uniform_real_distribution<double> doubleDist(1.0, 100.0);
  std::uniform_int_distribution<> intDist(1, 100);

  double doubleValue = doubleDist(mt);
  std::string stringValue = "sampleString" + std::to_string(intDist(mt));
  int intValue = intDist(mt);

  boost::program_options::options_description desc("Allowed options");
  desc.add_options()
    ("sleep", boost::program_options::value<int>(), "Thread sleep in microseconds")
    ("config", boost::program_options::value<std::string>()->required(), "Config file path")
  ;
  
  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  boost::program_options::notify(vm);

  if (vm.count("sleep")) {
    sleep = vm["sleep"].as<int>();
  }

  try {
    // configure monitoring (once per process), pass configuration path as parameter
    Monitoring::Configure("file://" + vm["config"].as<std::string>());
  } catch (std::string &e) {
    std::cout << "Configuration file not found.\n" << e << std::endl;
    std::exit(EXIT_FAILURE);
  }  

  for (;;) {
    Monitoring::Get().send(stringValue, stringMetric);
    Monitoring::Get().send(doubleValue, doubleMetric);
    Monitoring::Get().send(intValue, intMetric);
    std::this_thread::sleep_for(std::chrono::microseconds(sleep));
  }
}	
