/*
 * Copyright (C) 2009 The Android Open Source Project
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

#ifndef M4V_H263_SPRD_DECODER_H_

#define M4V_H263_SPRD_DECODER_H_

#include <media/stagefright/MediaBuffer.h>
#include <media/stagefright/MediaSource.h>

struct tagvideoDecControls;

namespace android {

struct M4vH263SPRDDecoder : public MediaSource,
                        public MediaBufferObserver {
    M4vH263SPRDDecoder(const sp<MediaSource> &source);

    virtual status_t start(MetaData *params);
    virtual status_t stop();

    virtual sp<MetaData> getFormat();

    virtual status_t read(
            MediaBuffer **buffer, const ReadOptions *options);

    virtual void signalBufferReturned(MediaBuffer *buffer);

protected:
    virtual ~M4vH263SPRDDecoder();

private:
    sp<MediaSource> mSource;
    bool mStarted;
    int32_t mWidth, mHeight;

    sp<MetaData> mFormat;

    tagvideoDecControls *mHandle;
    MediaBuffer *mFrames[2];
    MediaBuffer *mInputBuffer;

    uint8_t *mCodecInterBuffer;
    uint32_t mCodecInterBufferSize;
    uint8_t *mCodecExtraBuffer;
    uint32_t mCodecExtraBufferSize;
    bool mCodecExtraBufferMalloced;

    int32_t mNumSamplesOutput_;
    int64_t mTargetTimeUs;

    void allocateFrames(int32_t width, int32_t height);
    void releaseFrames();

    M4vH263SPRDDecoder(const M4vH263SPRDDecoder &);
    M4vH263SPRDDecoder &operator=(const M4vH263SPRDDecoder &);
};

}  // namespace android

#endif  // M4V_H263_SPRD_DECODER_H_