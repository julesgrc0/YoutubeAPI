#pragma once
#include<iostream>
#include<vector>

namespace YoutubeAPI
{
	typedef struct ItemThumbnail
	{
		std::string url;
		int width;
		int height;
	};

	typedef struct SearchItem
	{
		std::string videoId;
		std::string etag;
		std::string publishedAt;
		std::string channelId;
		std::string title;
		std::string channelTitle;
		std::string publishTime;
		std::string description;
		ItemThumbnail Thumbnail_default;
		ItemThumbnail Thumbnail_medium;
		ItemThumbnail Thumbnail_high;
	};

	class YoutubeSearch
	{
	public:
		YoutubeSearch();
		~YoutubeSearch();

		bool HaveError;
		int errorCode;
		std::string errorMessage;
		std::string errorStatus;
		std::string errorReason;

		std::string regionCode;
		std::string nextPageToken;
		std::string etag;
		int totalResults;
		int resultsPerPage;
		std::vector<SearchItem> items;
	};
};

