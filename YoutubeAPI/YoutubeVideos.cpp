#include "YoutubeVideos.h"

namespace YoutubeAPI 
{
	YoutubeVideos::YoutubeVideos()
	{

	}

	YoutubeVideos::~YoutubeVideos()
	{
		this->videos.clear();
		this->errors.clear();
	}
}