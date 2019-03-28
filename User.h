/*
* User.h
*
*  Created on: 25 Kas 2015
*      Author: Emre_PC
*/

#ifndef USER_H_
#define USER_H_

class Post;

#include <string>
#include <vector>
#include "Post.h"

using namespace std;

class User {
public:

	User(string userName_l, string personelComment_l);
	virtual ~User();

	/*********************************************************/
	/*Getter-Setter Methods*/

	const std::vector<User>& getBlockedUsers() const {
		return blocked_Users;
	}

	const string& getPersonelComment() const {
		return personelComment;
	}

	void setPersonelComment(const string& personelComment) {
		this->personelComment = personelComment;
	}

	const string& getUserName() const {
		return userName;
	}

	void setUserName(const string& userName) {
		this->userName = userName;
	}

	const std::vector<User>& getFollowers() const {
		return followers;
	}

	const std::vector<User>& getFollowees() const {
		return followees;
	}

	Post* returnSpecificPost(int post_ID, fstream& fp_out, string liked);

	void addFollower_Followee(User* user_Follower, User* user_Followee, string follower, string followee, fstream& fp_out, int control);

	void addPost(Post *post);

	void viewUser(fstream& fp_out);

	int returnPostIndex(int post_ID);

	const std::vector<Post*>& getUserPosts() const {
		return user_Posts;
	}

private:
	string userName;
	string personelComment;
	std::vector<User> blocked_Users; /*Users who are blocked by the current user*/
	std::vector<User> followers; /*Users who follow current user*/
	std::vector<Post*> user_Posts; /*Posts that are received to current user*/
	std::vector<User> followees; /*Users whom are being followed by current user*/
};

#endif /* USER_H_ */
