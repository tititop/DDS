#pragma once

#include <minclude.h>
#include "RTPS/data/sub_message_elements.h"
#include "RTPS/data/interface.h"
#include "RTPS/data/data.h"
#include "RTPS/data/structure.h"
#include <socket/MXTSocket.h>
#include <thread>
#include <chrono>

namespace DDS::Data {
	extern std::map<__submessage_header_type_defines::submessage_kind_t, std::function<SubMessageElement* ()> > s_sub_message_creater;
}


void PrintMessage(const DDS::Data::Message& msg)
{
	size_t message_size = msg.GetAllSize();
	pout << strval(message_size);

	std::string msgstr = "";
	msg.ToString(msgstr);
	pout << strval(msgstr);
}

void GetTestMsg(DDS::Data::Message& ans)
{
	DDS::Data::TestSubMessageElement::ptr test_element(new DDS::Data::TestSubMessageElement);
	test_element->SetStr("xx uu pp oo zz yy");

	DDS::Data::SubMessage::ptr sub_message(new DDS::Data::SubMessage);
	sub_message->SetElement(test_element);

	ans.AddSubMessage(sub_message);
	ans.AddSubMessage(sub_message);
	ans.AddSubMessage(sub_message);
}

void TestSerialization()
{
	// message
	DDS::Data::Message msg;
	DDS::Data::Message msg_reader;
	GetTestMsg(msg);
	PrintMessage(msg);

	size_t msg_size = msg.GetAllSize();
	uint8_t* buffer = nullptr;

	// message to buffer
	buffer = (uint8_t*)malloc(msg_size);
	memset(buffer, 0, msg_size);
	msg.SetBuffer((uint8_t*)(buffer), msg_size);

	// buffer to message
	msg_reader.FromBuffer(buffer, msg.GetAllSize());
	PrintMessage(msg_reader);
}
#define xx_server_port 5555
#define xx_server_ip "192.168.0.108"
void ServerProcess(uint8_t* tmp_buffer, const size_t buffer_max_len)
{
	DDS::Data::Message msg;
	GetTestMsg(msg);
	SOCKET sock = 0;
	sock = listen_one_client(xx_server_ip, xx_server_port);
	PrintMessage(msg);
	pout << strval(sock);

	while (1) {
		size_t msg_len = msg.GetAllSize();
		msg.SetBuffer(tmp_buffer, buffer_max_len);

		pout << strval(msg_len);
		bool is_send_right = write_to_socket(sock, (const char*)tmp_buffer, msg_len);
		pout << strval(msg_len);
		if (false == is_send_right) {
			break;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void ClientProcess(uint8_t* tmp_buffer, const size_t buffer_max_len)
{
	DDS::Data::Message msg;
	SOCKET sock = 0;
	size_t nRecv = 0;
	sock = init_tcp_client(xx_server_ip, xx_server_port);
	pout << strval(sock);

	while (1) {
		msg.ClearSubMessage();
		memset(tmp_buffer, 0, buffer_max_len);
		nRecv = buffer_max_len;

		bool is_send_right = read_from_socket(sock, (char*)tmp_buffer, nRecv);
		if (false == is_send_right) {
			break;
		}
		pout << strval(nRecv);
		msg.FromBuffer(tmp_buffer, nRecv);

		PrintMessage(msg);
	}
}

void TestMessageSerializationInSocket(int is_server)
{

	constexpr size_t buffer_max_len = 1024 * 4;
	uint8_t* tmp_buffer = (uint8_t*)malloc(buffer_max_len + 1);
	memset(tmp_buffer, 0, buffer_max_len + 1);

	start_winsock();

	if (is_server) {
		while (1) {
			ServerProcess(tmp_buffer, buffer_max_len);
		}
	}
	else {
		while (1)
		{
			ClientProcess(tmp_buffer, buffer_max_len);
		}
	}
	stop_winsock();

}

#define __STRUCT_NAME structure_test
#define __STRUCT_BODY							\
	FIELD(long long, field_ll, 0)				\
	FIELD(double, field_dbl, 0.001122)			\
	FIELD(std::string, field_string, "xxx")		\
//
#include <reflection/serialization/serialization.h>

void TestReflection()
{
	structure_test st;
	std::cout << st;
	st.field_ll = 2;
	st.field_dbl = 2.1122;
	st.field_string = "yyy";

	std::cout << st;

}
int main(int argc, char** argv)
{
	//PrintCmdline(argc, argv);
	TestMessageSerializationInSocket(argc % 2);
	//TestSerialization();
	//TestReflection();

}