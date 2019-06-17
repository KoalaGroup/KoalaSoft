/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 KoaMapHandler header file                    ------
// -----                 Created 13/06/19  by Y. Zhou                 -----
// -------------------------------------------------------------------------


/** KoaMapHandler.h
 ** Helper class to encode the detector channel id and electronics channel id
 ** It is designed to be used for decoding the raw binary data for DAQ
 ** @author Y.Zhou <y.zhou@fz-juelich.de>
 **/

/** As a first step, the mapping relation is hardcoded into the class member.
 ** In the future, a more flexible configuration should be implemented.
 ** TODO:
 **   1. read a mapping configuration file, better based on EMS config file
 **/
#ifndef KOAMAPHANDLER_H
#define KOAMAPHANDLER_H 1

#include "TObject.h"

class KoaMapHandler : public TObject
{
 public:
  KoaMapHandler();
  ~KoaMapHandler();

 private:

  ClassDef(KoaMapHandler, 1)
};

#endif
