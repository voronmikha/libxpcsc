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

#include "aids.hpp"

std::vector<xpcsc::Bytes> xpcsc::aids()
{
    return {
            {0xA0, 0x00, 0x00, 0x00, 0x03, 0x20, 0x10}, // Visa Electron
            {0xA0, 0x00, 0x00, 0x00, 0x03, 0x10, 0x10}, // Visa Debit
            {0xA0, 0x00, 0x00, 0x00, 0x98, 0x08, 0x48}, // Visa Credit
            {0xA0, 0x00, 0x00, 0x00, 0x03, 0x10, 0x10}, // Visa Credit
            {0xA0, 0x00, 0x00, 0x00, 0x04, 0x10, 0x10}, // MasterCard
            {0xA0, 0x00, 0x00, 0x06, 0x58, 0x10, 0x10}, // MIR
            {0xA0, 0x00, 0x00, 0x06, 0x58, 0x10, 0x11}, // MIR2
            {0xA0, 0x00, 0x00, 0x06, 0x58, 0x20, 0x10}, // MIR Credit
            {0xA0, 0x00, 0x00, 0x04, 0x32, 0x00, 0x01}  // PRO100
    };
}

//MIR_DBT2("MIR Russia Debit2", null, "A0 00 00 06 58 10 11"), //
//MIR_CRD("MIR Russia Credit", null, "A0 00 00 06 58 20 10"), //
