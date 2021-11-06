#pragma once
#include "wrapperPch.h"
//TODO: fill out fields when wrapper is initialized
namespace OGL {
	static struct DeviceInfo {
		unsigned majVersion = 4;
		unsigned minVersion = 6;
		bool dsa = false; //Direct state access
		bool bindlessOperations = false;
		bool modularShaders = false;
		//etc..
	};
}