/*
* User.cpp
*
*  Created on: 25 Kas 2015
*      Author: Emre_PC
*/

#include "User.h"
#include <iostream>
#include <fstream>
#include "ImagePost.h"

User::User(string userName_l, string personelComment_l) {
	userName = userName_l;
	personelComment = personelComment_l;

}

void User::addPost(Post *post){
	user_Posts.push_back(post);
}

void User::viewUser(fstream& fp_out){
	unsigned int index;

	cout << "------------------------------------------------" << endl;
	fp_out << "------------------------------------------------" << endl;
	cout << userName << " following [" << followees.size() << "] - blocked [" << blocked_Users.size() << "] users - [" << user_Posts.size() << "] posts." << endl;
	fp_out << userName << " following [" << followees.size() << "] - blocked [" << blocked_Users.size() << "] users - [" << user_Posts.size() << "] posts." << endl;
	cout << personelComment << endl;
	fp_out << personelComment << endl;
	cout << "---------------------Tweets---------------------" << endl;
	fp_out << "---------------------Tweets---------------------" << endl;

	for (index = 0; index < user_Posts.size(); index++){
		cout << "'" << user_Posts.at(index)->getCommentField() << "' - Likes: " << user_Posts.at(index)->getLikers().size() << endl;
		fp_out << "'" << user_Posts.at(index)->getCommentField() << "' - Likes: " << user_Posts.at(index)->getLikers().size() << endl;
	}
	cout << "------------------------------------------------" << endl;
	fp_out << "------------------------------------------------" << endl;
}

Post* User::returnSpecificPost(int post_ID, fstream& fp_out, string liked){
	unsigned int index;
	int i = -1;

	for (index = 0; index < user_Posts.size(); index++){
		if (user_Posts.at(index)->getPostId() == post_ID){
			i = index;
		}
	}
	if (i<0){

		cout << "Err: " << liked << "'s post could not be found!" << endl;
		fp_out << "Err: " << liked << "'s post could not be found!" << endl;

		return NULL;
	}
	else{
		return user_Posts.at(i);
	}
}

void User::addFollower_Followee(User* user_Follower, User* user_Followee, string follower, string followee, fstream& fp_out, int control){
	unsigned int index;
	int i = -1;
	if (followers.size()>0){
		for (index = 0; index < followers.size(); index++){
			if (followers.at(index).getUserName() == follower){
				i = index;
				cout << "Err: " << follower << " has already followed " << followee << endl;
				fp_out << "Err: " << follower << " has already followed " << followee << endl;
			}
			if (followers.at(index).getUserName() == followee){
				i = index;
				cout << "Err: " << followee << " cannot follow itself" << endl;
				fp_out << "Err: " << followee << " cannot follow itself" << endl;
			}
		}
	}
	if (i>0){

	}
	else{
		if (control == 0){
			followers.push_back(*user_Follower);
		}
		else{
			followees.push_back(*user_Followee);
		}
	}

}

int User::returnPostIndex(int post_ID){
	unsigned int index;
	int i = -1;
	for (index = 0; index < user_Posts.size(); index++){
		if (user_Posts.at(index)->getPostId() == post_ID){
			return index;
		}
	}
	return i;
}

User::~User(void) {

}

