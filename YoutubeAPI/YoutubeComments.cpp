#include "YoutubeComments.h"

namespace YoutubeAPI
{
	YoutubeComments::YoutubeComments()
	{

	}

	YoutubeComments::~YoutubeComments()
	{
		this->comments.clear();
		this->errors.clear();
	}
};