#pragma once
#include<iostream>
#include<vector>
#include "YoutubeVideos.h"

namespace YoutubeAPI
{
	typedef struct VideoPlaylistItem
	{
		std::string id;
		std::string etag;
		std::string publishedAt;
		std::string channelId;
		std::string title;
		std::string description;
		std::string channelTitle;
		std::string categoryId;
		std::string videoId;
		std::string videoOwnerChannelTitle;
		std::string videoOwnerChannelId;
		int position;

		std::vector<std::string> tags;
		std::vector<ItemThumbnail> Thumbnails;
	};


	class YoutubePlaylist
	{
	public:
		YoutubePlaylist();
		~YoutubePlaylist();

		std::vector<VideoPlaylistItem> videos;
		std::string nextPageToken;
		std::string etag;
		int totalsResults;

		std::vector<std::string> errors;
		int errorCode;
		bool HaveError;
	};
};

