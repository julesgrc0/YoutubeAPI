#include<iostream>
#include<vector>
#include "URLBuilder.h"

namespace YoutubeAPI
{
	URLBuilder::URLBuilder(std::string url)
	{
		this->url = url;
	}

	void URLBuilder::add_param(std::string id, std::string value)
	{
		this->params.emplace_back(std::pair<std::string, std::string>(id,value));
	}

	void URLBuilder::remove_param(std::string id)
	{
		int i = 0;
		for(std::pair<std::string, std::string> item : this->params)
		{
			if (item.first == id)
			{
				this->params.erase(this->params.begin() + i);
			}
			i++;
		}
	}

	std::string URLBuilder::get_url()
	{
		std::string result = this->url;
		for (size_t i = 0; i < this->params.size(); i++)
		{
			if (i == 0)
			{
				result += "?" + this->params[i].first + "=" + this->params[i].second;
			}
			else {
				result += "&" + this->params[i].first + "=" + this->params[i].second;
			}
		}

		return result;
	}

	URLBuilder::~URLBuilder()
	{

	}

};