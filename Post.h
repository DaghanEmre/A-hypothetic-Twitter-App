/*
* Post.h
*
*  Created on: 25 Kas 2015
*      Author: Emre_PC
*/

#ifndef POST_H_
#define POST_H_

class User;

#include "User.h"
#include <vector>
#include <string>
using namespace std;

class Post {
public:

	Post(string owner, int post_ID, string commentField);
	virtual ~Post();

	/*********************************************************/
	/*Getter-Setter Methods*/

	int getPostId() const {
		return post_ID;
	}

	void setPostId(int postId) {
		post_ID = postId;
	}

	const string& getCommentField() const {
		return commentField;
	}

	void setCommentField(const string& commentField) {
		this->commentField = commentField;
	}

	const string& getOwner() const {
		return owner;
	}

	void setOwner(const string& owner) {
		this->owner = owner;
	}

	const vector<User*>& getLikers() const {
		return likers;
	}

	void addLikers(User *liker);

protected:
	int post_ID;
	string owner;
	string commentField;
	vector<User*> likers;

};

#endif /* POST_H_ */
