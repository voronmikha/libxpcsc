/*
* Copyright (c) 2017, Sergey Stolyarov <sergei@regolit.com>
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
#include <PCSC/pcsclite.h>
#include <PCSC/winscard.h>
#include <PCSC/wintypes.h>
#else
#include <pcsclite.h>
#include <winscard.h>
#include <wintypes.h>
#endif

struct readers_list {
	LPSTR name_reader;
};
typedef readers_list RD_LIST;

void print_bytes(BYTE* bytes, BYTE bytes_size) {
	for (BYTE i = 0; i < bytes_size; ++i) {
		printf("%02X ", bytes[i]);
	}
	printf("\n");
}

int main(int argc, char** argv) {
	LONG result;
	SCARDCONTEXT sc_context;

	// initialize pcsc library
	result = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &sc_context);
	if (result != SCARD_S_SUCCESS) {
		printf("%s\n", pcsc_stringify_error(result));
		return 1;
	}
	printf("\nConnection to PC/SC established");

	// calculate required memory size for a list of readers
	DWORD readers_size = 0;

	result = SCardListReaders(sc_context, NULL, 0, &readers_size);
	if (result != SCARD_S_SUCCESS) {
		SCardReleaseContext(sc_context);
		printf("%s\n", pcsc_stringify_error(result));
		return 1;
	}

	// allocate memory and fetch readers list
	LPSTR readers;
	readers = (LPSTR)malloc(readers_size);
	//	readers = calloc(1, readers_size);

	result = SCardListReaders(sc_context, NULL, readers, &readers_size);
	if (result != SCARD_S_SUCCESS) {
		SCardReleaseContext(sc_context);
		printf("%s\n", pcsc_stringify_error(result));
		return 1;
	}

	char READER_LIST[3][256];

	char name_reader[256];
	int list_count = 0;
	int offset = 0;
	//	TODO: Похоже, что readers_size-1 это потому что медод возвращает на 1 символ больше
	for (size_t counter = 0; counter < readers_size - 1; ++counter) {
		if (readers[counter] != '\0') {
			name_reader[offset++] = readers[counter];
		} else {
			strcpy(READER_LIST[list_count++], name_reader);
			offset = 0;
		}
	}
	printf("\n++++++++++++++++++++\n");
	for (int i = 0; i < 3; ++i) {
		printf("%s\n", READER_LIST[i]);
	}
	printf("++++++++++++++++++++\n");
	//	for (int i = 0; i < 3; i++)
	//		printf("%s\n", READER_LIST[i]);

	printf("\n_____________________________________\n");
	// take first reader, 256-bytes buffer should be enough
	char reader_name[256] = {0};

	if (readers_size > 1) {
		strncpy(reader_name, readers, 255);
	} else {
		printf("No readers found!\n");
		return 2;
	}

	free(readers);

	printf("Use reader '%s'\n", reader_name);

	// connect to reader and wait for card
	SCARD_READERSTATE sc_reader_states[1];
	sc_reader_states[0].szReader = reader_name;
	sc_reader_states[0].dwCurrentState = SCARD_STATE_EMPTY;

	result = SCardGetStatusChange(sc_context, INFINITE, sc_reader_states, 1);
	if (result != SCARD_S_SUCCESS) {
		SCardReleaseContext(sc_context);
		printf("%s\n", pcsc_stringify_error(result));
		return 1;
	}

	// connect to inserted card
	SCARDHANDLE reader;
	DWORD active_protocol;

	result = SCardConnect(sc_context, "ACS ACR1281 1S Dual Reader(2)", SCARD_SHARE_SHARED, SCARD_PROTOCOL_T1, &reader,
						  &active_protocol);
	if (result != SCARD_S_SUCCESS) {
		SCardReleaseContext(sc_context);
		printf("%s\n", pcsc_stringify_error(result));
		return 1;
	}

	if (active_protocol == SCARD_PROTOCOL_T0) { printf("Card connected, protocol to use: T0.\n"); }
	if (active_protocol == SCARD_PROTOCOL_T1) { printf("Card connected, protocol to use: T1.\n"); }

	// send APDU to get UID
	BYTE send_buffer[] = {0xff, 0xca, 0x00, 0x00, 0x0};
	BYTE recv_buffer[0x20];
	DWORD recv_length = sizeof(recv_buffer);

	result = SCardTransmit(reader, SCARD_PCI_T1, send_buffer, sizeof(send_buffer), NULL, recv_buffer, &recv_length);
	if (result != SCARD_S_SUCCESS) {
		SCardDisconnect(reader, SCARD_RESET_CARD);
		SCardReleaseContext(sc_context);
		printf("%s\n", pcsc_stringify_error(result));
		return 1;
	}

	printf("Response APDU: ");
	print_bytes(recv_buffer, recv_length);

	BYTE SW1 = recv_buffer[recv_length - 2];
	BYTE SW2 = recv_buffer[recv_length - 1];
	int SW = SW1 * 256 + SW2;

	if (SW != 0x9000) {
		printf("Failed to fetch UID! SW1=%02X, SW2=%02X\n", SW1, SW2);
	} else {
		printf("Success!\n");
		printf("Card UID: ");
		print_bytes(recv_buffer, recv_length - 2);
	}

	// disconnect from card
	result = SCardDisconnect(reader, SCARD_RESET_CARD);
	if (result != SCARD_S_SUCCESS) {
		SCardReleaseContext(sc_context);
		printf("%s\n", pcsc_stringify_error(result));
		return 1;
	}

	// relase connection to library
	result = SCardReleaseContext(sc_context);
	if (result != SCARD_S_SUCCESS) {
		printf("%s\n", pcsc_stringify_error(result));
		return 1;
	}
	printf("Connection to PC/SC closed\n");

	return 0;
}