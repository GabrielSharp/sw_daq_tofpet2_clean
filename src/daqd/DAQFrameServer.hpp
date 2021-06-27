#ifndef __DAQFRAMESERVER_HPP__DEFINED__
#define __DAQFRAMESERVER_HPP__DEFINED__

#include "FrameServer.hpp"

#include "boost/tuple/tuple.hpp"
#include <boost/unordered_map.hpp> 
#include "boost/date_time/posix_time/posix_time.hpp"

namespace PETSYS {
	
class AbstractDAQCard {
protected:
	AbstractDAQCard();

public:
	virtual ~AbstractDAQCard();

	virtual int getWords(uint64_t *buffer, int count) = 0;
	virtual void clearReplyQueue() = 0;
	virtual int sendCommand(uint64_t *packetBuffer, int packetBufferSize) = 0;
	virtual int recvReply(uint64_t *packetBuffer, int packetBufferSize) = 0;
	virtual int setAcquistionOnOff(bool enable) = 0;
	virtual uint64_t getPortUp() = 0;
	virtual uint64_t getPortCounts(int channel, int whichCount) = 0;
	virtual int setSorter(unsigned mode);
	virtual int setCoincidenceTrigger(CoincidenceTriggerConfig *config);
	virtual int setGateEnable(unsigned mode);
};

class DAQFrameServer : public FrameServer
{
protected:
	DAQFrameServer(AbstractDAQCard *card, const char * shmName, int shmfd, RawDataFrame * shmPtr, int debugLevel);
public:
	static DAQFrameServer *createFrameServer(AbstractDAQCard *card, const char * shmName, int shmfd, RawDataFrame * shmPtr, int debugLevel);
	
	virtual ~DAQFrameServer();	


	int sendCommand(int portID, int slaveID, char *buffer, int bufferSize, int commandLength);
	
	virtual void startAcquisition(int mode);
	virtual void stopAcquisition();
	virtual uint64_t getPortUp();
	virtual uint64_t getPortCounts(int port, int whichCount);
	virtual int setSorter(unsigned mode);
	virtual int setCoincidenceTrigger(CoincidenceTriggerConfig *config);
	virtual int setGateEnable(unsigned mode);

private:
	AbstractDAQCard *DP;
	
protected:

	void * doWork();
	
};

}
#endif
