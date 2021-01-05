#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>

using namespace utility;                    // 문자열 변환등 공통 유틸리티
using namespace web;                        // URI등 공통 웹 기능
using namespace web::http;                  // HTTP 관련 공통 기능
using namespace web::http::client;          // HTTP 클라이언트 기능
using namespace concurrency::streams;       // 비동기 스트림

struct Pingable
{
	virtual std::wstring ping(const std::wstring& message) = 0;
};

struct Pong : Pingable
{
	std::wstring ping(const std::wstring& message) override
	{
		return message + L" pong";
	}
};

struct RemotePong : Pingable
{
	std::wstring ping(const std::wstring& message) override
	{
		std::wstring result;
		http_client client(U("http://localhost:9149/"));
		uri_builder builder(U("/api/values/"));
		builder.append(message);

		pplx::task<std::wstring> task = client.request(
			methods::GET, builder.to_string()).then([=](http_response r)
				{
					return r.extract_string();
				}
			);

		task.wait();
		return task.get();
	}
};

void tryit(Pingable& pp)
{
	std::wcout << pp.ping(L"ping") << "\n";
}

int main()
{
	RemotePong pp; // Pong => RemotePong
	for (int i = 0; i < 3; ++i)
		tryit(pp);
}