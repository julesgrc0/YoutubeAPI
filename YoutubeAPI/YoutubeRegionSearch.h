#pragma once
#include<iostream>
#include<vector>

namespace YoutubeAPI
{
	typedef struct RegionItem
	{
		std::string etag;
		std::string id;
		std::string gl;
		std::string name;
	};

	class YoutubeRegionSearch
	{
	public:
		YoutubeRegionSearch();
		~YoutubeRegionSearch();
		
		std::string etag;
		std::vector<RegionItem> regions;

		std::vector <std::string> errors;
		int errorCode;
		bool HaveError;
	};
};


