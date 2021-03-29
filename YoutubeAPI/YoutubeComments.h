#pragma once
#include<iostream>
#include<vector>

namespace YoutubeAPI
{
	typedef struct CommentItem
	{
		std::string id;
		std::string etag;
		std::string textDisplay;
		std::string textOriginal;
		std::string authorDisplayName;
		std::string authorProfileImageUrl;
		std::string authorChannelUrl;
		std::string authorChannelId;
		std::string publishedAt;
		std::string updatedAt;
		
		int likeCount;
		int totalReplyCount;
		bool isPublic;
		bool canReply;
	};

	class YoutubeComments
	{
	public:
		YoutubeComments();
		~YoutubeComments();
	
		std::vector<CommentItem> comments;
		std::string etag;
		std::string nextPageToken;
		int totalsResults;

		std::vector<std::string> errors;
		int errorCode;
		bool HaveError;
	};

};
