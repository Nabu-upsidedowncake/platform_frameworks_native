/*
 * Copyright (C) 2022 The Android Open Source Project
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
#include <fuzzbinder/libbinder_ndk_driver.h>

#include <fuzzbinder/libbinder_driver.h>
#include <fuzzbinder/random_parcel.h>

// libbinder_ndk doesn't export this header which breaks down its API for NDK
// and APEX users, but we need access to it to fuzz.
#include "../../ndk/ibinder_internal.h"

namespace android {

void fuzzService(AIBinder* binder, FuzzedDataProvider&& provider) {
    fuzzService(binder->getBinder(), std::move(provider));
}

} // namespace android

extern "C" {
// This API is used by fuzzers to automatically fuzz aidl services
void fuzzRustService(void* binder, const uint8_t* data, size_t len) {
    AIBinder* aiBinder = static_cast<AIBinder*>(binder);
    FuzzedDataProvider provider(data, len);
    android::fuzzService(aiBinder, std::move(provider));
}
} // extern "C"
