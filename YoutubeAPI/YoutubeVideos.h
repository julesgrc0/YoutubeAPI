#pragma once
#include<iostream>
#include<vector>
#include "YoutubeSearch.h"

namespace YoutubeAPI 
{
	typedef struct VideoItem
	{
		std::string id;
		std::string etag;
		std::string publishedAt;
		std::string channelId;
		std::string title;
		std::string description;
		std::string channelTitle;
		std::string categoryId;

		std::vector<std::string> tags;
		std::vector<ItemThumbnail> Thumbnails;
	};

	class YoutubeVideos
	{
	public:
		YoutubeVideos();
		~YoutubeVideos();

		std::vector<VideoItem> videos;
		
		bool HaveError;
		std::string errorCode;
		std::vector<std::string> errors;
	};

}