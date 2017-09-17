#ifndef _DATAMODEL_H_
#define _DATAMODEL_H_

/* System includes */
#include <winsock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <atomic>

/* Libraries */
#pragma comment(lib, "ws2_32.lib")

/* Local Project Includes */
#include "../logging/logger.h"
#include "altimeter_dm.h"

/* Typedefs */
typedef char Byte;

namespace MagusEngine
{
	class DataModel
	{
	public:
		bool Initialise();

		float GetAltitude();

		Altimeter_DataModel* GetAltitudeDM();

	private:
		/* Data Models */
		Altimeter_DataModel _altimeter;
	};
}
#endif