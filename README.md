# Youtube API

A basic library for using the youtube data api.
require installing json and restclient-cpp library. you can install them with vcpkg.

## Usage

```cpp
#include <iostream>
#include "Youtube.h"

int main(int argc, const char** argv)
{
    // Your youtube key
    std::string token = "";
	YoutubeAPI::Youtube youtube = YoutubeAPI::Youtube(token);

    return 0;
}
```

> Search

Search in youtube by category (channels,video,playlist).

```cpp
YoutubeAPI::YoutubeSearch res =  youtube.search("",
 25, // max results
 "none", // pageToken
 YoutubeAPI::ResultOrder::NONE, // order
 YoutubeAPI::ResultType::VIDEO); // result type

if (res.HaveError) // check for api errors
{
	std::cout << res.errors[0] << std::endl;
}else
{
    // your code here
}
```

> Region

```cpp
Get region name by region id.

YoutubeAPI::YoutubeRegionSearch res = youtube.region("fr_FR"); // region id
```

> Video

Get video info by video id.

```cpp
YoutubeAPI::YoutubeVideos res = youtube.videos(""); // video id
```

> Playlist

List video from playlist.

```cpp
YoutubeAPI::YoutubePlaylist res = youtube.playlist("", 3); // video id + max results
```

> Comments

List comments from a video.

```cpp
YoutubeAPI::YoutubeComments res = youtube.comments("", 25); // video id + max results
```
