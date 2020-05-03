#ifndef KOA_TEXTUTILITY_H
#define KOA_TEXTUTILITY_H

#include "TSystem.h"
#include "KoaMapEncoder.h"
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>

/*
 * Text I/O utility for fitting parameters of recoil detector
 * ValueContainer is the basic unit for storing a list of parameters, with the encoded id as key
 *
 * Usage (fitting paramters as an example)
 * // 1. define a ParameterList 
 * using namespace KoaUtility;
 * ParameterList fitParameters;
 * // 2. add parameter value container to this list
 * auto fitMean = addValueContainer(fitParameters, "Mean");
 * auto fitSigma = addValueContainer(fitParameters, "Sigma");
 * // 3. fill in the values
 * ....
 * // 4. print out values to text file
 * printValueList(fitParameters, "fit_result.txt");
 * // 5. Read paramter values from text file
 * readParameterList("file.txt")
 * // 6. Binary operation between two set of parameters
 * calcValueContainer<T,operator>(left,right,result)
 */

namespace KoaUtility {

  using IndexContainer = std::vector<Int_t>;

  template<typename T>
  using ValueContainer = std::map<Int_t, T>; // one parameter, the key is chId in Recoil Detector

  template<typename T>
  using Parameter = std::pair<std::string, ValueContainer<T>>; // string is the name of this parameter

  template<typename T>
  using ParameterList = std::list<Parameter<T>>; // a group of parameters which are related will be print out together

  //
  template<typename T>
  typename ParameterList<T>::iterator findValueContainer(ParameterList<T>& paramList, std::string paramName)
  {
    typename ParameterList<T>::iterator it;
    for ( it = paramList.begin() ; it != paramList.end(); it++ ) {
      if (it->first == paramName ) {
        break;
      }
    }

    return it;
  }

  // print one parameter to screen
  template<typename T>
  void printValueContainer(const ValueContainer<T>& valueContainer, std::string paramName)
  {
    std::cout << paramName << ":" << std::endl;
    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    for( const auto& value : valueContainer ) {
      TString volName;
      Int_t ChID = value.first;
      Int_t ch = encoder->DecodeChannelID(ChID, volName);
      volName.ReplaceAll("Sensor", "");
      volName.Append(Form("_%d\t", ch+1));
      std::cout << volName.Data() << value.second << std::endl;
    }
  }

  template<typename T>
  void printValueContainer(ParameterList<T>& paramList, std::string paramName)
  {
    const auto it = findValueContainer<T>(paramList, paramName);
    if (it != paramList.end()) {
      const auto& valueContainer = it->second;

      printValueContainer(valueContainer, paramName);
    }
    else {
      std::cout << "No parameter ValueContainer " << paramName << "exists!" << std::endl;
    }
  }

  template<typename T>
  void printParameter(Parameter<T>& parameter)
  {
    printValueContainer(parameter.second, parameter.first);
  }

  // user should define a ParameterList by himself and then add new ValueContainer into it
  // the return value is a reference to the newly added ValueContainer
  template<typename T>
  ValueContainer<T>& addValueContainer( ParameterList<T>& paramList, // the list where the newly defined ValueContainer is stored
                                        std::string paramName) // the name is the key to the newly booked ValueContainer
  {
    auto inserted = findValueContainer<T>(paramList, paramName);
    if (inserted != paramList.end()) {
      std::cout << "Warning : ValueContainer with name " << paramName << " already exists!" << std::endl;
      return inserted->second;
    }
    else {
      ValueContainer<T> new_container;
      paramList.emplace_back(std::make_pair(paramName, std::move(new_container)));

      auto& back = paramList.back();
      return back.second;
    }
  }

  //
  template<typename T>
  void resetValueContainer(ValueContainer<T>& valueContainer, T resetValue = 0)
  {
    for ( auto& value : valueContainer ) {
      value.second = resetValue;
    }
  }

  //
  template<typename T, template<typename> class BinaryOperator = std::divides>
  void calcValueContainer(ValueContainer<T>& lhsContainer, ValueContainer<T>& rhsContainer, ValueContainer<T>& resultContainer)
  {
    BinaryOperator<T> binaryOperator;

    for ( auto& lhsValue : lhsContainer ) {
      auto chId = lhsValue.first;
      auto& lhs = lhsValue.second;
      auto& rhs = rhsContainer[chId];
      auto& result = resultContainer[chId];
      result = binaryOperator(lhs, rhs);
    }
  }

  // print out a ParameterList, i.e. a group of parameters which are related, for example the fitting parameters such as mean and sigma
  template<typename T>
  void printValueList(const ParameterList<T>& paramList,
                      std::string fileName) // name of the output text file
  {
    //
    auto itFirst = paramList.begin();
    if( itFirst == paramList.end() ) {
      std::cout << "No parameters contained in the paramList" << std::endl;
      return;
    }

    //
    std::ofstream ftxt(gSystem->ExpandPathName(fileName.c_str()));
    if(!ftxt.is_open()){
      std::cout << "Can't open file : " << fileName << '\n';
      return;
    }

    // header row
    ftxt << std::setw(12) << std::left << "Name" ;
    ftxt << std::setw(12) << std::left << "Id";
    for( auto& parameter : paramList ) {
      ftxt << std::setw(12) << std::left << parameter.first;
    }
    ftxt << std::endl;

    // loop through all channels
    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    for( const auto& channel : itFirst->second ) {
      TString volName;
      Int_t ChID = channel.first;
      Int_t ch = encoder->DecodeChannelID(ChID, volName);
      volName.ReplaceAll("Sensor", "");
      volName.Append(Form("_%d", ch+1));
      ftxt << std::setw(12) << std::left << volName.Data();
      ftxt << std::setw(12) << std::left << ChID;
      //
      for( const auto& parameter : paramList ) {
        const auto& values = parameter.second;
        ftxt << std::setw(12) << std::left << values.at(ChID);
      }
      ftxt << std::endl;
    }

    //
    ftxt.close();
  }

  //
  template<typename T>
  void printValueList(const ParameterList<T>& paramList)
  {
    //
    auto itFirst = paramList.begin();
    if( itFirst == paramList.end() ) {
      std::cout << "No parameters contained in the paramList" << std::endl;
      return;
    }

    // header row
    std::cout << std::setw(12) << std::left << "Name";
    std::cout << std::setw(12) << std::left << "Id";
    for( auto& parameter : paramList ) {
      std::cout << std::setw(12) << std::left << parameter.first;
    }
    std::cout << "\n";

    // loop through all channels
    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    for( const auto& channel : itFirst->second ) {
      TString volName;
      Int_t ChID = channel.first;
      Int_t ch = encoder->DecodeChannelID(ChID, volName);
      volName.ReplaceAll("Sensor", "");
      volName.Append(Form("_%d", ch+1));
      std::cout << std::setw(12) << std::left << volName.Data();
      std::cout << std::setw(12) << std::left << ChID;
      //
      for( const auto& parameter : paramList ) {
        const auto& values = parameter.second;
        std::cout << std::setw(12) << std::left << values.at(ChID);
      }
      std::cout << "\n";
    }
  }

  //
  template<typename T>
  ParameterList<T> readParameterList(std::string fileName)
  {
    ParameterList<T> paramList;

    std::ifstream ftxt;
    ftxt.open(gSystem->ExpandPathName(fileName.c_str()));
    if (!ftxt.is_open()) {
      std::cout << "Can't open file : " << fileName << '\n';
    }

    std::vector<std::string> containers;
    std::string line, token;
    std::stringstream ssline;

    // get and analyze the header line
    std::getline(ftxt, line);
    ssline.str(line);
    ssline >> token >> token;
    while (ssline >> token) {
      addValueContainer(paramList, token);
      containers.emplace_back(token);
    }

    std::string name;
    Int_t id;
    T value;
    Int_t index;
    while (!ftxt.eof()) {
      std::getline(ftxt, line);
      std::stringstream ss(line);

      index = 0;
      ss >> name >> id;
      while (ss >> value) {
        auto it = findValueContainer(paramList, containers[index++]);
        auto& container = it->second;
        container[id] = value;
      }
    }

    ftxt.close();

    return paramList;
  }
};

#endif
