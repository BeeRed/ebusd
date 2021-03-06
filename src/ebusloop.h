/*
 * Copyright (C) Roland Jax 2012-2014 <roland.jax@liwest.at>
 *
 * This file is part of ebusd.
 *
 * ebusd is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ebusd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ebusd. If not, see http://www.gnu.org/licenses/.
 */

#ifndef EBUSLOOP_H_
#define EBUSLOOP_H_

#include "libebus.h"
#include "wqueue.h"
#include "thread.h"

using namespace libebus;


class EBusLoop : public Thread
{

public:
	EBusLoop();
	~EBusLoop();

	void* run();
	void stop() { m_stop = true; }

	std::string getData() { return m_cycBuffer.remove(); }

	void addBusCommand(BusCommand* busCommand) { m_sendBuffer.add(busCommand); }
	BusCommand* getBusCommand() { return m_recvBuffer.remove(); }

	void dump(const bool dumpState) { m_bus->setDumpState(dumpState); }

private:
	std::string m_deviceName;
	Bus* m_bus;
	WQueue<std::string> m_cycBuffer;
	bool m_stop;
	WQueue<BusCommand*> m_sendBuffer;
	WQueue<BusCommand*> m_recvBuffer;
	int m_retries;

};

#endif // EBUSLOOP_H_
