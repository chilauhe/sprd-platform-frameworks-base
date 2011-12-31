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

#ifndef AVC_UTILS_H_

#define AVC_UTILS_H_

#include <media/stagefright/foundation/ABuffer.h>

namespace android {

struct ABitReader;

void FindAVCDimensions(
        const sp<ABuffer> &seqParamSet, int32_t *width, int32_t *height);

unsigned parseUE(ABitReader *br);

status_t getNextNALUnit(
        const uint8_t **_data, size_t *_size,
        const uint8_t **nalStart, size_t *nalSize,
        bool startCodeFollows = false);

struct MetaData;
sp<MetaData> MakeAVCCodecSpecificData(const sp<ABuffer> &accessUnit);

bool IsIDR(const sp<ABuffer> &accessUnit);
bool IskeyFrame(const sp<ABuffer> &accessUnit,int32_t mpegtype);

}  // namespace android

#endif  // AVC_UTILS_H_
