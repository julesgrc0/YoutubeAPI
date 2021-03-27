#include<iostream>
#include "Youtube.h"


int main(int argc, const char* argv[])
{
	std::string token = "";
	YoutubeAPI::Youtube youtube = YoutubeAPI::Youtube(token);

	YoutubeAPI::YoutubeSearch res =  youtube.search("cats", 25,"none",YoutubeAPI::ResultOrder::NONE,YoutubeAPI::ResultType::VIDEO);
	
	if (res.HaveError)
	{
		std::cout << res.errorMessage << std::endl;
	}
	else {
		std::cout << res.items[0].title << std::endl;
	}

	return 0;
}