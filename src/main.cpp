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

#include <iostream>

//#include "aids.hpp"
#include "card_apps.hpp"
#include "config.hpp"
#include "parser.hpp"
#include "xpcsc.hpp"

int main() {
	std::vector<xpcsc::Bytes> aids;
	xpcsc::Parser prsr;
	xpcsc::Config config = xpcsc::Config::get()
							   .setContactLess(false)
							   .setReadTransactions(false)
							   .setReadAllAids(false)
							   .setReadAt(false)
							   .setReadCplc(false)
							   .setRemoveDefaultParsers(false);

	prsr.setConfig(config);
	xpcsc::Connection c;

	try {
		c.init();
	} catch (xpcsc::PCSCError& e) {
		std::cerr << "[Error] Connection to PC/SC failed: " << e.what() << std::endl;
		return 1;
	}
	// get readers list
	auto readers = c.readers();
	if (readers.empty()) {
		std::cerr << "[Error] No connected readers" << std::endl;
		//        TODO: Нужно добавить коды и описание ошибок
		std::exit(EXIT_FAILURE);
	} else {
		std::cout << "Readers count : " << readers.size() << std::endl;
		for (const auto& r : readers) {
			std::cout << r << std::endl;
		}
	}
	try {
		for (const auto& r : readers) {
			if (r == "ACS ACR1281 1S Dual Reader(2)") {
				while (true) {

					xpcsc::Reader reader = c.wait_for_reader_card(r);
					std::cout << reader.handle << std::endl;
					xpcsc::Parser parser;
					auto card = parser.readCard();
					auto apps = xpcsc::read_apps_from_pse(c, reader);

					std::cout << "AID APPS" << std::endl;

					for (const auto &ap : apps) {
						std::cout << xpcsc::format(ap);
					}
					std::cout << std::endl << std::flush;
					if (!apps.empty()) {
						for (const auto& aid : apps) {
							xpcsc::read_app(c, reader, aid);
						}
					} /*else {
						for (const auto& aid : xpcsc::aids()) {
							std::cout << "IN" << std::endl;
							if (xpcsc::read_app(xpcsc::Connection::get(), reader, aid)) { break; }
						}
					}*/
					c.wait_for_card_remove(r);
					// TODO: Непонятно пока, нужно лы вызывать этот метод
					c.disconnect_card(reader, SCARD_LEAVE_CARD);
					std::cout << "Disconnect Card" << std::endl;
				}
			}
		}
	} catch (xpcsc::PCSCError& e) {
		std::cerr << "Wait for card failed: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}