#ifndef __THEATRE_SYSTEM_H__
#define __THEATRE_SYSTEM_H__

/////////////////////////////////////////////////////////////////////////////////////////////
// 
//																		
//////////////////////////////////////////////////////////////////////////////////////////////

#include "../../common/CommonAll.h"


class Processor
{
  public:
	  static EErorCode Process(ClientRequest Req,Response *res);
	  static void printErrorCode(EErorCode err);
	  static void test1();
	  static void testbookingEngine();
	  static void test();
}; //CDejaChatGALRoomChat

#endif //__THEATRE_SYSTEM_H__