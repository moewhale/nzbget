/*
 *  This file is part of nzbget
 *
 *  Copyright (C) 2004 Sven Henkel <sidddy@users.sourceforge.net>
 *  Copyright (C) 2007-2015 Andrey Prygunkov <hugbug@users.sourceforge.net>
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


#ifndef FRONTEND_H
#define FRONTEND_H

#include "Thread.h"
#include "Log.h"
#include "DownloadInfo.h"
#include "MessageBase.h"
#include "QueueEditor.h"

class Frontend : public Thread
{
private:
	MessageList m_remoteMessages;

	bool RequestMessages();
	bool RequestFileList();

protected:
	bool m_summary = false;
	bool m_fileList = false;
	uint32 m_neededLogEntries = 0;
	uint32 m_neededLogFirstId = 0;
	int m_updateInterval;

	// summary
	int m_currentDownloadSpeed = 0;
	int64 m_remainingSize = 0;
	bool m_pauseDownload = false;
	int m_downloadLimit = 0;
	int m_threadCount = 0;
	int m_postJobCount = 0;
	int m_upTimeSec = 0;
	int m_dnTimeSec = 0;
	int64 m_allBytes = 0;
	bool m_standBy = false;

	bool PrepareData();
	void FreeData();
	MessageList* LockMessages();
	void UnlockMessages();
	DownloadQueue* LockQueue();
	void UnlockQueue();
	bool IsRemoteMode();
	void InitMessageBase(SNzbRequestBase* messageBase, int request, int size);
	void ServerPauseUnpause(bool pause);
	bool RequestPauseUnpause(bool pause);
	void ServerSetDownloadRate(int rate);
	bool RequestSetDownloadRate(int rate);
	bool ServerEditQueue(DownloadQueue::EEditAction action, int offset, int entry);
	bool RequestEditQueue(DownloadQueue::EEditAction action, int offset, int id);

public:
	Frontend();
};

#endif
