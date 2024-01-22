#pragma once
#ifndef __PACKET_H__
#define __PACKET_H__

enum class EPacketType
{
	Calculate = 10
	, Image = 20
	, Move = 30
	, MAX
};

#pragma pack(push, 1)
typedef struct _Header
{
	unsigned short Length;
	unsigned short PacketType;
} Header;


typedef struct _Data	//typedef : c언어에서 사용하는 키워드. 앞으로 ~라고 부르겠다.  as를 생각하자.
{
	int FirstNumber;
	int SecondNumber;
	char Operator;
} Data;


#pragma pack(pop)

#endif //__PACKET_H__