/*
* TextPost.h
*
*  Created on: 26 Kas 2015
*      Author: Emre_PC
*/

#ifndef TEXTPOST_H_
#define TEXTPOST_H_

#include "Post.h"
#include <string>

class TextPost : public Post {
public:
	TextPost(string owner, int post_ID, string commentField)
		:Post(owner, post_ID, commentField){}

	virtual ~TextPost();
};

#endif /* TEXTPOST_H_ */
