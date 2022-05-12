/*
 * Copyright (c) 2022, Mikhail Vorontsov <mikhail.vorontsov@gmail.com>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef XPCSC_CONSTANTS_HPP
#define XPCSC_CONSTANTS_HPP

#include <xpcsc.hpp>

#define CHECK_BIT(value, b) (((value) >> (b))&1)

const xpcsc::Bytes TAG_EMV_FCI = {0x6F};
const xpcsc::Bytes TAG_EMV_FCI_PD = {0xA5};
const xpcsc::Bytes TAG_EMV_FCI_SFI = {0x88};
const xpcsc::Bytes TAG_PSD_REC = {0x70};
const xpcsc::Bytes TAG_PSD_TAG = {0x61};
const xpcsc::Bytes TAG_PSD_AID_TAG = {0x4F};
const xpcsc::Bytes TAG_EMV_FCI_APP_LABEL = {0x50};
const xpcsc::Bytes TAG_EMV_FCI_APP_PDOL = {0x9F, 0x38};

const xpcsc::Bytes TAG_PRIM = {0x80};
const xpcsc::Bytes TAG_STRUCT = {0x77};

const xpcsc::Bytes TAG_EMV_AIP = {0x82};
const xpcsc::Bytes TAG_EMV_AFL = {0x94};

#endif //XPCSC_CONSTANTS_HPP
