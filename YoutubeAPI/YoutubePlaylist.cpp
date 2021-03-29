#include "YoutubePlaylist.h"

namespace YoutubeAPI
{
	YoutubePlaylist::YoutubePlaylist()
	{

	}

	YoutubePlaylist::~YoutubePlaylist()
	{
		this->videos.clear();
		this->errors.clear();
	}
};