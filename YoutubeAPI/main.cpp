#include<iostream>
#include "Youtube.h"


int main(int argc, const char* argv[])
{
	std::string token = "";
	YoutubeAPI::Youtube youtube = YoutubeAPI::Youtube(token);

	//YoutubeAPI::YoutubeSearch res =  youtube.search("cats", 25,"none",YoutubeAPI::ResultOrder::NONE,YoutubeAPI::ResultType::VIDEO);
	
	YoutubeAPI::YoutubeRegionSearch res = youtube.region("fr_FR");

	if (res.HaveError)
	{
		std::cout << res.errors[0] << std::endl;
	}
	else {
		for (YoutubeAPI::RegionItem item : res.regions)
		{
			std::cout << item.name << std::endl;
		}
	}

	return 0;
}