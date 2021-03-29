// --------------------------------------------------------
// ----     PndSdsApvHit header file                       ---
// ----     Created 07.01.09 HGZ by Lars Ackermann      ---
// ----     on the basic of the ana tool of dts         ---
// --------------------------------------------------------

/** PndSdsApvHit.h
*@author L.Ackermann <lars.ackermann@physik.tu-dresden.de>
**/

#ifndef PNDSDSAPV_H
#define PNDSDSAPV_H
#include "TObject.h"
#include <iostream>

//! Class to store data of Apv-Sensors

class PndSdsApvHit : public TObject
{
   public :
	PndSdsApvHit(){}
	/**
	main constructor, used to create ApvHit with resonable information
	@param eventID event ID
	@param moduleID ID of used sensor module
	@param fe frontend ID
	@param trigger trigger ID
	@param timestamp trigger time stamp
	@param frame frame ID
	@param channel cannel
	@param adc ADC height in channel
	@param length frame length in this channel
	*/
	PndSdsApvHit(long int eventID, Int_t moduleID, Int_t fe, Int_t triggerID, Int_t timestamp, Int_t frame, Int_t channel, Double_t adc, Int_t length)
	: fEventID(eventID), fModuleID(moduleID), fFeID(fe), fTriggerID(triggerID), fChannel(channel), fTimestamp(timestamp), fFrameID(frame), fADC(adc), fLength(length)
	{}
	~PndSdsApvHit(){}

		/**
		@fn Int_t GetChannel() const
        get hit channel index
        @return channel index of hit
        */
        Int_t GetChannel() const { return fChannel; }

		/**
		@fn Int_t GetTimestamp() const
        get hit timestamp
        @return timestamp in the event
        */
        Int_t GetTimestamp() const { return fTimestamp; }

        /**
        @fn Int_t GetFrameID() const
        @return index of frame where the hit occured in the event 
        */
        Int_t GetFrameID() const { return fFrameID; }

        /**
        @fn Double_t GetADC() const
        @return amplitude of the hit
        */
        Double_t GetADC() const { return fADC; }

        /**
        @fn Int_t GetLength() const
        @return length of the hit over threshold
        */
        Int_t GetLength() const { return fLength; }

        /**
        @fn Int_t GetFeID() const
        @return fe ID
        */
        Int_t GetFeID() const { return fFeID; }

        /**
        @fn void SetFeID(Int_t new_FE)
	    set new FeID (needed for faking)
        @return void
        */
        void SetFeID(Int_t new_FE) { fFeID=new_FE; return; }

        /**
        @fn long int GetEventID() const
        @return event ID
        */
        long int GetEventID() const { return fEventID; }

	/**
        @fn Int_t GetModuleID() const
        @return module ID
        */
        Int_t GetModuleID() const { return fModuleID; }

        /**
        @fn Int_t GetTriggerID() const
        @return trigger ID
        */
        Int_t GetTriggerID() const { return fTriggerID; }

   private :
	long int fEventID;	/// store event ID
	Int_t fModuleID;	/// store moduleID
	Int_t fFeID;		/// store fe ID (should be betwen 0 and 2)
	Int_t fTriggerID;	/// store trigger ID
	Int_t fChannel;		/// store channel (should be betwen 0 and 127)
	Int_t fTimestamp;	/// store timestamp
	Int_t fFrameID;		/// store frame ID
	Double_t fADC;		/// store ADC height
	Int_t fLength;		/// store frame length 

	ClassDef(PndSdsApvHit,1);
};
ClassImp(PndSdsApvHit);
#endif
