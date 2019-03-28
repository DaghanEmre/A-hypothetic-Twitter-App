/*
* Post.cpp
*
*  Created on: 25 Kas 2015
*      Author: Emre_PC
*/

#include "Post.h"
#include <string>

/*Post Constructor*/
Post::Post(string owner, int post_ID, string commentField) {

	this->post_ID = post_ID;
	this->owner = owner;
	this->commentField = commentField;
}

void Post::addLikers(User *liker){
	likers.push_back(liker);
}

Post::~Post() {
	// TODO Auto-generated destructor stub
}

