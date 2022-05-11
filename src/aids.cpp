//
//  Created by Mikhail Vorontsov (aka voronmikha) on 12.05.2022.
//
// MIT License
//
// Copyright (c) 2022 voronmikha.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

// Project: Universal Faster Payments Gateway
// Subproject: xpcsc
// Name:    aids.cpp
//

#include "aids.hpp"

std::vector<xpcsc::Bytes> xpcsc::aids()
{
    return {
            {0xA0, 0x00, 0x00, 0x00, 0x03, 0x20, 0x10}, // Visa Electron
            {0xA0, 0x00, 0x00, 0x00, 0x03, 0x10, 0x10}, // Visa Debit
            {0xA0, 0x00, 0x00, 0x00, 0x98, 0x08, 0x48}, // Visa Credit
            {0xA0, 0x00, 0x00, 0x00, 0x04, 0x10, 0x10}, // MasterCard
            {0xA0, 0x00, 0x00, 0x06, 0x58, 0x10, 0x10}, // MIR
            {0xA0, 0x00, 0x00, 0x04, 0x32, 0x00, 0x01}  // PRO100
    };
}