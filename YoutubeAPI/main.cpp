#include<iostream>
#include "Youtube.h"


int main(int argc, const char* argv[])
{
	std::string token = "";
	YoutubeAPI::Youtube youtube = YoutubeAPI::Youtube(token);

	//YoutubeAPI::YoutubeSearch res =  youtube.search("cats", 25,"none",YoutubeAPI::ResultOrder::NONE,YoutubeAPI::ResultType::VIDEO);
	
	//YoutubeAPI::YoutubeRegionSearch res = youtube.region("fr_FR");

	YoutubeAPI::YoutubeVideos res = youtube.videos("81GQNPJip2Y");

	if (res.HaveError)
	{
		std::cout << res.errors[0] << std::endl;
	}
	else {
		for (YoutubeAPI::VideoItem item : res.videos)
		{
			std::cout << "title:"<< item.title << std::endl;
		}
	}

	return 0;
}