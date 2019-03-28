/*
* ImagePost.h
*
*  Created on: 26 Kas 2015
*      Author: Emre_PC
*/

#ifndef IMAGEPOST_H_
#define IMAGEPOST_H_

#include "Post.h"
#include <string>

class ImagePost : public Post {
public:
	ImagePost(string owner, int post_ID, string commentField, int post_Width, int post_Height)
		:Post(owner, post_ID, commentField)
	{
		this->post_Width = post_Width;
		this->post_Height = post_Height;
	}
	virtual ~ImagePost();

	int getTotalPixels(void) {
		return post_Height * post_Width;
	}

	void setPostHeight(int postHeight) {
		post_Height = postHeight;
	}

	void setPostWidth(int postWidth) {
		post_Width = postWidth;
	}

private:
	int post_Width;
	int post_Height;

};

#endif /* IMAGEPOST_H_ */
