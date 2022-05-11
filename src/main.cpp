#include <iostream>
#include "xpcsc.hpp"
#include "aids.hpp"

int main()
{
    std::vector<xpcsc::Bytes> aids;
    xpcsc::Connection c;

    try {
        c.init();
    } catch (xpcsc::PCSCError &e) {
        std::cerr << "[Error] Connection to PC/SC failed: " << e.what() << std::endl;
        return 1;
    }
    // get readers list
    auto readers = c.readers();
    if (readers.empty()) {
        std::cerr << "[Error] No connected readers" << std::endl;
        return 1;
    } else {
        std::cout << "Readers count : " << readers.size() << std::endl;
    }
    try {
        for (const auto &r: readers) {
            if (r == "ACS ACR1281 1S Dual Reader(2)") {
                while (true) {
                    xpcsc::Reader reader = c.wait_for_reader_card(r);
                    std::cout << reader.handle << std::endl;
                    for (const auto &aid: xpcsc::aids()) {
                        std::cout << "IN" << std::endl;
//                        if (read_app(c, reader, aid)) {
//                            break;
//                        }
                    }
                    c.wait_for_card_remove(r);


//                    TODO: Непонятно пока, нужно лы вызывать этот метод
                    c.disconnect_card(reader, SCARD_EJECT_CARD);
                }
            }
        }
    } catch (xpcsc::PCSCError &e) {
        std::cerr << "Wait for card failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}