#include "YoutubeChannels.h"

namespace YoutubeAPI
{
	YoutubeChannels::YoutubeChannels()
	{

	}

	YoutubeChannels::~YoutubeChannels()
	{
		this->errors.clear();
		this->videos.clear();
	}
}