#include<iostream>
#include<restclient-cpp/restclient.h>
#include<json/json.h>
#include<string>
#include <exception>
#include "Youtube.h"
#include "YoutubeSearch.h"
#include "URLBuilder.h"
#include "YoutubeVideos.h"

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

		sin >> root;

		YoutubeSearch search = YoutubeSearch();

		
		if (root["error"])
		{
			search.errorCode = root["error"]["code"].asInt();
			search.errorMessage = root["error"]["message"].asString();
			search.errorStatus = root["error"]["status"].asString();
			for (Json::Value item : root["error"]["errors"])
			{
				search.errorReasons.push_back(item["reason"].asString());
			}
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

	YoutubeRegionSearch Youtube::region(std::string id)
	{
		URLBuilder url = URLBuilder(this->ApiURL + "i18nRegions");
		url.add_param("hl", id);
		url.add_param("part", "snippet");
		url.add_param("key", this->key);

		RestClient::Response response = RestClient::get(url.get_url());

		Json::Value root;
		std::istringstream sin(response.body);

		sin >> root;

		YoutubeRegionSearch search = YoutubeRegionSearch();

		if (root["error"])
		{
			search.errorCode = root["error"]["code"].asInt();
			for (Json::Value item : root["error"]["errors"])
			{
				search.errors.push_back(item["message"].asString());
			}
			search.HaveError = true;
		}
		else 
		{
			search.HaveError = false;
			search.etag = root["etag"].asString();

			for (Json::Value item : root["items"])
			{
				search.regions.push_back({
					item["etag"].asString(),
					item["id"].asString(),
					item["snippet"]["gl"].asString(),
					item["snippet"]["name"].asString()
					});
			}
		}

		return search;
	}

	YoutubeVideos Youtube::videos(std::string id)
	{
		URLBuilder url = URLBuilder(this->ApiURL + "videos");
		url.add_param("id", id);
		url.add_param("part", "snippet");
		url.add_param("key", this->key);

		RestClient::Response response = RestClient::get(url.get_url());

		Json::Value root;
		std::istringstream sin(response.body);

		sin >> root;

		YoutubeVideos result = YoutubeVideos();

		if (root["error"])
		{
			result.errorCode = root["error"]["code"].asInt();
			for (Json::Value item : root["error"]["errors"])
			{
				result.errors.push_back(item["message"].asString());
			}
			result.HaveError = true;
		}
		else {
			result.HaveError = false;

			for (Json::Value item : root["items"])
			{
				VideoItem video = {
					item["id"].asString(),
					item["etag"].asString(),
					item["snippet"]["publishedAt"].asString(),
					item["snippet"]["channelId"].asString(),
					item["snippet"]["title"].asString(),
					item["snippet"]["description"].asString(),
					item["snippet"]["channelTitle"].asString(),
					item["snippet"]["categoryId"].asString(),
				};

				for (Json::Value tag : item["snippet"]["tags"])
				{
					video.tags.push_back(tag.asString());
				}

				for (Json::Value thumbnail : item["snippet"]["thumbnails"])
				{
					video.Thumbnails.push_back({
						thumbnail["url"].asString(),
						thumbnail["width"].asInt(),
						thumbnail["height"].asInt()
						});
				}

				result.videos.push_back(video);
			}
		}

		return result;
	}

	YoutubePlaylist Youtube::playlist(std::string id,int max,std::string pageToken)
	{
		URLBuilder url = URLBuilder(this->ApiURL + "playlistItems");
		url.add_param("playlistId", id);
		url.add_param("part", "snippet");
		url.add_param("maxResults", std::to_string(max));
		if (pageToken != "none")
		{
			url.add_param("pageToken", pageToken);
		}
		url.add_param("key", this->key);

		RestClient::Response response = RestClient::get(url.get_url());

		Json::Value root;
		std::istringstream sin(response.body);

		sin >> root;

		YoutubePlaylist result = YoutubePlaylist();

		if (root["error"])
		{
			result.errorCode = root["error"]["code"].asInt();
			for (Json::Value item : root["error"]["errors"])
			{
				result.errors.push_back(item["message"].asString());
			}
			result.HaveError = true;
		}
		else 
		{
			result.nextPageToken = root["nextPageToken"].asString();
			result.etag = root["etag"].asString();

			for (Json::Value item : root["items"])
			{
				VideoPlaylistItem video = {
					item["id"].asString(),
					item["etag"].asString(),
					item["snippet"]["publishedAt"].asString(),
					item["snippet"]["channelId"].asString(),
					item["snippet"]["title"].asString(),
					item["snippet"]["description"].asString(),
					item["snippet"]["channelTitle"].asString(),
					item["snippet"]["categoryId"].asString(),
				};
				video.position = root["snippet"]["position"].asInt();
				video.videoId = root["snippet"]["resourceId"]["videoId"].asString();
				video.videoOwnerChannelTitle = root["snippet"]["videoOwnerChannelTitle"].asString();
				video.videoOwnerChannelId = root["snippet"]["videoOwnerChannelTitle"].asString();

				for (Json::Value tag : item["snippet"]["tags"])
				{
					video.tags.push_back(tag.asString());
				}

				for (Json::Value thumbnail : item["snippet"]["thumbnails"])
				{
					video.Thumbnails.push_back({
						thumbnail["url"].asString(),
						thumbnail["width"].asInt(),
						thumbnail["height"].asInt()
						});
				}

				result.videos.push_back(video);
			}
			result.totalsResults = root["pageInfo"]["totalResults"].asInt();
		}

		return result;
	}

	YoutubeComments Youtube::comments(std::string id,int max)
	{
		URLBuilder url = URLBuilder(this->ApiURL + "commentThreads");
		url.add_param("videoId", id);
		url.add_param("maxResults", std::to_string(max));
		url.add_param("part", "snippet");
		url.add_param("textFormat", "plainText");
		url.add_param("key", this->key);

		RestClient::Response response = RestClient::get(url.get_url());

		Json::Value root;
		std::istringstream sin(response.body);

		sin >> root;

		YoutubeComments result = YoutubeComments();

		if (root["error"])
		{
			result.errorCode = root["error"]["code"].asInt();
			for (Json::Value item : root["error"]["errors"])
			{
				result.errors.push_back(item["message"].asString());
			}
			result.HaveError = true;
		}
		else
		{
			result.HaveError = false;
			result.nextPageToken = root["pageInfo"]["nextPageToken"].asString();
			result.totalsResults = root["pageInfo"]["totalResults"].asInt();

			for (Json::Value item : root["items"])
			{
				CommentItem comment =
				{
					item["id"].asString(),
					item["etag"].asString(),
					item["snippet"]["topLevelComment"]["snippet"]["textDisplay"].asString(),
					item["snippet"]["topLevelComment"]["snippet"]["textOriginal"].asString(),
					item["snippet"]["topLevelComment"]["snippet"]["authorDisplayName"].asString(),
					item["snippet"]["topLevelComment"]["snippet"]["authorProfileImageUrl"].asString(),
					item["snippet"]["topLevelComment"]["snippet"]["authorChannelUrl"].asString(),
					item["snippet"]["topLevelComment"]["snippet"]["authorChannelId"]["value"].asString(),
					item["snippet"]["topLevelComment"]["snippet"]["publishedAt"].asString(),
					item["snippet"]["topLevelComment"]["snippet"]["updatedAt"].asString(),

					item["snippet"]["topLevelComment"]["snippet"]["likeCount"].asInt(),
					item["snippet"]["totalReplyCount"].asInt(),
					item["snippet"]["isPublic"].asBool(),
					item["snippet"]["canReply"].asBool(),
				};

				result.comments.push_back(comment);
			}
		}

		return result;
	}

	YoutubeChannels Youtube::channels(std::string id, int max)
	{	
		URLBuilder url = URLBuilder(this->ApiURL + "search");
		url.add_param("channelId", id);
		url.add_param("maxResults", std::to_string(max));
		url.add_param("part", "snippet");
		url.add_param("order", "date");
		url.add_param("key", this->key);

		RestClient::Response response = RestClient::get(url.get_url());

		Json::Value root;
		std::istringstream sin(response.body);

		sin >> root;

		YoutubeChannels result = YoutubeChannels();

		if (root["error"])
		{
			result.errorCode = root["error"]["code"].asInt();
			for (Json::Value item : root["error"]["errors"])
			{
				result.errors.push_back(item["message"].asString());
			}
			result.HaveError = true;
		}
		else
		{
			result.HaveError = false;
			result.totalResults = root["pageInfo"]["totalResults"].asInt();
			result.nextPageToken = root["nextPageToken"].asString();

			for (Json::Value item : root["items"])
			{
				VideoItem video = {
					item["id"]["videoId"].asString(),
					item["etag"].asString(),
					item["snippet"]["publishedAt"].asString(),
					item["snippet"]["channelId"].asString(),
					item["snippet"]["title"].asString(),
					item["snippet"]["description"].asString(),
					item["snippet"]["channelTitle"].asString(),
					item["snippet"]["categoryId"].asString(),
				};

				for (Json::Value tag : item["snippet"]["tags"])
				{
					video.tags.push_back(tag.asString());
				}

				for (Json::Value thumbnail : item["snippet"]["thumbnails"])
				{
					video.Thumbnails.push_back({
						thumbnail["url"].asString(),
						thumbnail["width"].asInt(),
						thumbnail["height"].asInt()
						});
				}

				result.videos.push_back(video);
			}
		}

		return result;
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


