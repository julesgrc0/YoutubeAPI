#pragma once

#include<iostream>
#include<vector>
#include "YoutubeVideos.h"

namespace YoutubeAPI
{
	class YoutubeChannels
	{
	public:
		YoutubeChannels();
		~YoutubeChannels();

		std::vector<VideoItem> videos;
		std::string etag;
		std::string nextPageToken;
		int totalResults;

		std::vector<std::string> errors;
		int errorCode;
		bool HaveError;
	};
};

