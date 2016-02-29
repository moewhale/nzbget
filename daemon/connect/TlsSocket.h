/*
 *  This file is part of nzbget
 *
 *  Copyright (C) 2008-2015 Andrey Prygunkov <hugbug@users.sourceforge.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * $Revision$
 * $Date$
 *
 */

#ifndef TLSSOCKET_H
#define TLSSOCKET_H

#ifndef DISABLE_TLS

#include "NString.h"

class TlsSocket
{
private:
	bool m_isClient;
	CString m_certFile;
	CString m_keyFile;
	CString m_cipher;
	SOCKET m_socket;
	bool m_suppressErrors = false;
	bool m_initialized = false;
	bool m_connected = false;
	int m_retCode;

	// using "void*" to prevent the including of GnuTLS/OpenSSL header files into TlsSocket.h
	void* m_context = nullptr;
	void* m_session = nullptr;

	void ReportError(const char* errMsg);

	static void Final();
	friend class TlsSocketFinalizer;

protected:
	virtual void PrintError(const char* errMsg);

public:
	TlsSocket(SOCKET socket, bool isClient, const char* certFile,
		const char* keyFile, const char* cipher) :
		m_socket(socket), m_isClient(isClient), m_certFile(certFile),
		m_keyFile(keyFile), m_cipher(cipher) {}
	virtual ~TlsSocket();
	static void Init();
	bool Start();
	void Close();
	int Send(const char* buffer, int size);
	int Recv(char* buffer, int size);
	void SetSuppressErrors(bool suppressErrors) { m_suppressErrors = suppressErrors; }
};

#endif
#endif
