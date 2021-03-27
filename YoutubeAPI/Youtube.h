#pragma once
#include<iostream>
#include "YoutubeSearch.h"

namespace YoutubeAPI 
{
	enum class ResultOrder {
		DATE,
		RATING,
		TITLE,
		VIDEO_COUNT,
		VIEW_COUNT,
		RELEVANCE,
		NONE
	};

	enum class ResultType {
		VIDEO,
		CHANNEL,
		PLAYLIST,
		NONE
	};

	class Youtube
	{
	public:
		Youtube(std::string);
		~Youtube();
		YoutubeSearch search(std::string query, int maxResults = 25, std::string pageToken = "none", ResultOrder order = ResultOrder::NONE, ResultType type = ResultType::NONE);

		void set_api_url(std::string);
	private:
		std::string getOrderValue(ResultOrder);
		std::string getTypeValue(ResultType);
		std::string key;
		std::string ApiURL = "https://youtube.googleapis.com/youtube/v3/";
	};

};

