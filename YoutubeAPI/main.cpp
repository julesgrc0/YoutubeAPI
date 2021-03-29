#include<iostream>
#include "Youtube.h"


int main(int argc, const char* argv[])
{
	std::string token = "";
	YoutubeAPI::Youtube youtube = YoutubeAPI::Youtube(token);

	//YoutubeAPI::YoutubeSearch res =  youtube.search("", 25,"none",YoutubeAPI::ResultOrder::NONE,YoutubeAPI::ResultType::VIDEO);
	
	//YoutubeAPI::YoutubeRegionSearch res = youtube.region("");

	//YoutubeAPI::YoutubeVideos res = youtube.videos("");

	//YoutubeAPI::YoutubePlaylist res = youtube.playlist("", 3);

	YoutubeAPI::YoutubeComments res = youtube.comments("", 25);

	if (res.HaveError)
	{
		std::cout << res.errors[0] << std::endl;
	}
	else {
		for (YoutubeAPI::CommentItem item : res.comments)
		{
			std::cout << "title:"<< item.likeCount << std::endl;
		}
	}

	return 0;
}