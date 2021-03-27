#pragma once
#include<iostream>
#include<vector>

namespace YoutubeAPI
{
	class URLBuilder
	{
	public:
		URLBuilder(std::string);
		~URLBuilder();

		void add_param(std::string, std::string);
		void remove_param(std::string);
		std::string get_url();
	private:
		std::string url;
		std::vector<std::pair<std::string, std::string>> params;
	};
};

