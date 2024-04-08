#pragma once

namespace LeaderEngine
{
	enum class NetworkPacketType
	{
		CONNECT,
		DISCONNECT,
		ACCEPTED,
		REFUSED,
		ERROR,
		ENTITIES,
	};
}