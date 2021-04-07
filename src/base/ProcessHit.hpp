#ifndef __PETSYS__PROCESS_HIT_HPP__DEFINED__
#define __PETSYS__PROCESS_HIT_HPP__DEFINED__

#include <UnorderedEventHandler.hpp>
#include <Event.hpp>
#include <SystemConfig.hpp>
#include <Instrumentation.hpp>


namespace PETSYS {
	
class ProcessHit : public UnorderedEventHandler<RawHit, Hit> {
private:
	SystemConfig *systemConfig;
	EventStream *eventStream;
	
	uint32_t nReceived;
	uint32_t nReceivedInvalid;
	uint32_t nTDCCalibrationMissing;
	uint32_t nQDCCalibrationMissing;
	uint32_t nEnergyCalibrationMissing;
	uint32_t nXYZMissing;
	uint32_t nSent;
public:
	ProcessHit(SystemConfig *systemConfig, EventStream *eventStream, EventSink<Hit> *sink);
	virtual void report();
	
protected:
	virtual EventBuffer<Hit> * handleEvents (EventBuffer<RawHit> *inBuffer);
};
	
}

#endif // __PETSYS__PROCESS_HIT_HPP__DEFINED__
