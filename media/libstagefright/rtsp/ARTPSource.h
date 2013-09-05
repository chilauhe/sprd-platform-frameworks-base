/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef A_RTP_SOURCE_H_

#define A_RTP_SOURCE_H_

#include <stdint.h>

#include <media/stagefright/foundation/ABase.h>
#include <utils/List.h>
#include <utils/RefBase.h>

namespace android {

struct ABuffer;
struct AMessage;
struct ARTPAssembler;
struct ASessionDescription;

struct ARTPSource : public RefBase {
    ARTPSource(
            uint32_t id,
            const sp<ASessionDescription> &sessionDesc, size_t index,
            const sp<AMessage> &notify);

    void processRTPPacket(const sp<ABuffer> &buffer);
    void timeUpdate(uint32_t rtpTime, uint64_t ntpTime);
    void timeUpdate2(uint32_t rtpTime, uint64_t ntpTime);//@hong	
    void byeReceived();

    List<sp<ABuffer> > *queue() { return &mQueue; }

    void addReceiverReport(const sp<ABuffer> &buffer);
    void addFIR(const sp<ABuffer> &buffer);

    bool timeEstablished() const {
        return mNumTimes == 2;
    }
	uint32_t getSampeRate(){return mHZ ;};
    void setLocalTimestamps(bool local); //@hong
	
private:
    uint32_t mID;
    uint32_t mHighestSeqNumber;
    int32_t mNumBuffersReceived;

    List<sp<ABuffer> > mQueue;
    sp<ARTPAssembler> mAssembler;

    size_t mNumTimes;
    uint64_t mNTPTime[2];
    uint32_t mRTPTime[2];

    uint64_t mLastNTPTime;
    int64_t mLastNTPTimeUpdateUs;
	
    bool mLocalTimestamps; //@hong
    int64_t mDeltaT;
    uint64_t mStartingT;
    uint32_t mStartRTP;
    uint64_t mPeriodCheck;

    size_t myNumTimes;//@hong
    int64_t mylocalBaseNTP;
    int64_t myBaseNTP;
    uint64_t myNTPTime[2];
    uint32_t myRTPTime[2];
    uint32_t mHZ;

		
    bool mIssueFIRRequests;
    int64_t mLastFIRRequestUs;
    uint8_t mNextFIRSeqNo;

    uint64_t RTP2NTP(uint32_t rtpTime) const;

	sp<AMessage> mNotify;

    bool queuePacket(const sp<ABuffer> &buffer);

    DISALLOW_EVIL_CONSTRUCTORS(ARTPSource);
};

}  // namespace android

#endif  // A_RTP_SOURCE_H_