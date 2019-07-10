#include "runFairMQDevice.h"

// #include "KoaDigiSource.h"

// PixelDetector example
#include "KoaMQSampler.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
  options.add_options()
    ("file-name",    bpo::value<std::vector<std::string>>()                                  , "Path to the input file")
    ("max-index",    bpo::value<int64_t>                 ()->default_value(-1)               , "number of events to read")
    ("branch-name",  bpo::value<std::vector<std::string>>()->required()                      , "branch name")
    ("sampler-type", bpo::value<std::string>             ()->default_value("FairFileSource") , "FairSource type")
    ("out-channel",  bpo::value<std::string>             ()->default_value("data-out")       , "output channel name")
    ("ack-channel",  bpo::value<std::string>             ()->default_value("")               , "ack channel name");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& config)
{
  std::string              samplerType = config.GetValue<std::string>             ("sampler-type");
  std::vector<std::string> filename    = config.GetValue<std::vector<std::string>>("file-name");

  KoaMQSampler* sampler = new KoaMQSampler();

  if      ( samplerType == "FairFileSource" ) {
  }
  else if ( samplerType == "KoaDigiSource" ) {
    if ( filename.size() >= 1 ) {
      // KoaDigiSource* digiSource = new KoaDigiSource(filename.at(0));
      // sampler->SetSource(digiSource);
    }
  }	  
  else {
    LOG(error) << "Sampler \"" << samplerType 
               << "\" unknown! Set it to \"FairFileSource\" or \"KoaDigiSource\"";
    return NULL;
  }

  return sampler;
}
