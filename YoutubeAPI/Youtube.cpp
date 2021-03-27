#include<iostream>
#include<restclient-cpp/restclient.h>
#include<json/json.h>
#include<string>
#include <exception>
#include "Youtube.h"
#include "YoutubeSearch.h"
#include "URLBuilder.h"

namespace YoutubeAPI
{

	Youtube::Youtube(std::string key)
	{
		RestClient::init();
		this->key = key;
	}

	YoutubeSearch Youtube::search(std::string query, int maxResults, std::string pageToken, ResultOrder order, ResultType type)
	{
		URLBuilder url = URLBuilder(this->ApiURL + "search");
		url.add_param("q", query);
		if (pageToken != "none")
		{
			url.add_param("pageToken", pageToken);
		}
		if (order != ResultOrder::NONE)
		{
			url.add_param("order", this->getOrderValue(order));
		}
		if (type != ResultType::NONE)
		{
			url.add_param("type", this->getTypeValue(type));
		}
		url.add_param("maxResults", std::to_string(maxResults));
		url.add_param("part", "snippet");
		url.add_param("key", this->key);

		RestClient::Response response = RestClient::get(url.get_url());

		Json::Value root;
		std::istringstream sin(response.body);
		std::cout << response.body << std::endl;

		sin >> root;

		YoutubeSearch search = YoutubeSearch();

		
		if (root["error"])
		{
			search.errorCode = root["error"]["code"].asInt();
			search.errorMessage = root["error"]["message"].asString();
			search.errorStatus = root["error"]["status"].asString();
			search.errorReason = root["error"]["errors"][0]["reason"].asString();
			search.HaveError = true;
		}
		else {
			search.HaveError = false;
			search.etag = root["etag"].asString();
			search.nextPageToken = root["nextPageToken"].asString();
			search.regionCode = root["regionCode"].asString();
			search.totalResults = root["pageInfo"]["totalResults"].asInt();
			search.resultsPerPage = root["pageInfo"]["resultsPerPage"].asInt();
			
			for (Json::Value item : root["items"])
			{
				SearchItem video;
				video.etag = item["etag"].asString();
				video.videoId = item["id"]["videoId"].asString();
				
				video.publishedAt = item["snippet"]["publishedAt"].asString();
				video.channelId = item["snippet"]["channelId"].asString();
				video.title = item["snippet"]["title"].asString();
				video.description = item["snippet"]["description"].asString();
				video.channelTitle = item["snippet"]["channelTitle"].asString();
				video.publishTime = item["snippet"]["publishTime"].asString();

				video.Thumbnail_default = 
				{ 
					item["snippet"]["thumbnails"]["default"]["url"].asString(),
					item["snippet"]["thumbnails"]["default"]["width"].asInt(),
					item["snippet"]["thumbnails"]["default"]["height"].asInt(),
				};

				video.Thumbnail_medium =
				{
					item["snippet"]["thumbnails"]["medium"]["url"].asString(),
					item["snippet"]["thumbnails"]["medium"]["width"].asInt(),
					item["snippet"]["thumbnails"]["medium"]["height"].asInt(),
				};

				video.Thumbnail_high =
				{
					item["snippet"]["thumbnails"]["high"]["url"].asString(),
					item["snippet"]["thumbnails"]["high"]["width"].asInt(),
					item["snippet"]["thumbnails"]["high"]["height"].asInt(),
				};

				search.items.push_back(video);
			}
		}

		return search;
	}

	void Youtube::set_api_url(std::string url)
	{
		this->ApiURL = url;
	}

	std::string Youtube::getTypeValue(ResultType type)
	{
		switch (type)
		{
		case YoutubeAPI::ResultType::VIDEO:
			return "video";
			break;
		case YoutubeAPI::ResultType::CHANNEL:
			return "channel";
			break;
		case YoutubeAPI::ResultType::PLAYLIST:
			return "playlist";
			break;
		}
		return "none";
	}

	std::string Youtube::getOrderValue(ResultOrder order)
	{
		switch (order)
		{
		case YoutubeAPI::ResultOrder::DATE:
			return "date";
			break;
		case YoutubeAPI::ResultOrder::RATING:
			return "rating";
			break;
		case YoutubeAPI::ResultOrder::TITLE:
			return "title";
			break;
		case YoutubeAPI::ResultOrder::VIDEO_COUNT:
			return "videoCount";
			break;
		case YoutubeAPI::ResultOrder::VIEW_COUNT:
			return "viewCount";
			break;
		case YoutubeAPI::ResultOrder::RELEVANCE:
			return "relevance";
			break;
		}
		return "none";
	}

	Youtube::~Youtube()
	{

	}
};


