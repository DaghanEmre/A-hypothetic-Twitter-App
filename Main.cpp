//============================================================================
// Name        : deneme.cpp
// Author      : Daghan Emre Aytac
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "User.h"
#include <vector>
#include "Post.h"
#include <sstream>
#include "ImagePost.h"
#include "TextPost.h"

using namespace std;

/*PROTOTYPES*/
void IO_Operations(fstream& fp_in, fstream& fp_out, vector<User>& user_List);
void AddUser(fstream& fp_out, string userName, string personalComment, vector<User>& user_List);
int returnUserIndex(string userName, vector<User>& user_List);

/*******************************************************************************************/

int main() {
	vector<User> user_List;			/*Holds all users*/

	fstream fp_in, fp_out;

	IO_Operations(fp_in, fp_out, user_List);

	fp_out.close();
	string a;
	std::cin >> a;
	return 0;
}

/*******************************************************************************************/

void IO_Operations(fstream& fp_in, fstream& fp_out, vector<User>& user_List)
{
	fp_in.open("input.txt", ios::in);
	fp_out.open("out.txt", ios::out);

	std::string line;
	std::string token1, token2, token3;

	if (fp_in.is_open() && fp_out.is_open()){

		while (getline(fp_in, line)){
			token1 = line.substr(0, line.find(" "));

			/************************* ADD USER **********************************/

			if (token1.compare("AddUser") == 0){

				string userName, personalComment;

				std::size_t pos = line.find(" ");				/*This code finds the first white space index*/
				line.erase(line.begin(), line.begin() + pos + 1);	/*That code remove the string from begin to first white space index*/

				userName = line.substr(0, line.find(" "));

				std::size_t pos2 = line.find(" ");				/*This code finds the second white space index*/
				line.erase(line.begin(), line.begin() + pos2 + 1);	/*That code remove the string from begin to second white space index*/

				personalComment = line;							/*The rest of the string is personal comment*/

				AddUser(fp_out, userName, personalComment, user_List);

			}

			/************************* FOLLOW USER **********************************/

			else if (token1.compare("FollowUser") == 0){
				string follower, followee;
				string commendField = "abc";

				std::size_t pos = line.find(" ");				/*This code finds the first white space index*/
				line.erase(line.begin(), line.begin() + pos + 1);	/*That code remove the string from begin to first white space index*/

				follower = line.substr(0, line.find(" "));

				std::size_t pos2 = line.find(" ");				/*This code finds the second white space index*/
				line.erase(line.begin(), line.begin() + pos2 + 1);	/*That code remove the string from begin to second white space index*/

				followee = line.substr(0, line.size());

				int follower_Index = returnUserIndex(follower, user_List);
				int followee_Index = returnUserIndex(followee, user_List);
				if (follower_Index < 0){
					cout << "Err: " << "the user '" << follower << "' could not be found!" << endl;
					fp_out << "Err: " << "the user '" << follower << "' could not be found!" << endl;
				}
				else if (followee_Index < 0){
					cout << "Err: " << "the user '" << followee << "' could not be found!" << endl;
					fp_out << "Err: " << "the user '" << followee << "' could not be found!" << endl;
				}
				else if (followee.compare(follower) == 0){
					cout << "Err: " << followee << " cannot follow itself" << endl;
					fp_out << "Err: " << followee << " cannot follow itself" << endl;
				}
				else{
					User* user_Follower = new User(follower, commendField);
					User* user_Followee = new User(followee, commendField);

					user_List.at(followee_Index).addFollower_Followee(user_Follower, user_Followee, follower, followee, fp_out, 0);
					user_List.at(follower_Index).addFollower_Followee(user_Follower, user_Followee, follower, followee, fp_out, 1);
					cout << follower << " followed " << followee << endl;
					fp_out << follower << " followed " << followee << endl;
				}

			}

			/************************* ADD POST **********************************/

			else if (token1.compare("AddPost") == 0){
				string userName, commendField;
				int post_Width, post_Height, post_ID;

				std::size_t pos = line.find(" ");				/*This code finds the first white space index*/
				line.erase(line.begin(), line.begin() + pos + 1);	/*That code remove the string from begin to first white space index*/

				userName = line.substr(0, line.find(" "));

				std::size_t pos2 = line.find(" ");				/*This code finds the second white space index*/
				line.erase(line.begin(), line.begin() + pos2 + 1);	/*That code remove the string from begin to second white space index*/

				istringstream buffer((line.substr(0, line.find(" "))));	/*That part converts string Post Id to integer*/
				buffer >> post_ID;

				std::size_t pos3 = line.find(" ");				/*This code finds the third white space index*/
				line.erase(line.begin(), line.begin() + pos3 + 1);	/*That code remove the string from begin to third white space index*/

				int index = returnUserIndex(userName, user_List);
				if (index >= 0){

					if (line.find(" ") != std::string::npos){			/*That part identifies if there is size information or not*/
						token2 = line.substr(0, line.find(" "));
						token3 = line.substr(line.find(" ") + 1, line.size() - 1);

						commendField = token2.substr(1, (token2.size() - 2));

						string Width = token3.substr(0, token3.find("x"));
						string Height = token3.substr(token3.find("x") + 1, token3.size() - 1);

						istringstream buffer2(Width);				/*That part converts string Post Width to integer*/
						istringstream buffer3(Height);				/*That part converts string Post Height to integer*/
						buffer2 >> post_Width;
						buffer3 >> post_Height;

						Post* imagePost = new ImagePost(userName, post_ID, commendField, post_Width, post_Height);		/*Image Post is created*/
						user_List.at(index).addPost(imagePost);														/*Image Post is added to the an user's post vector*/

					}
					else{
						commendField = line.substr(1, line.size() - 2);

						Post* textPost = new TextPost(userName, post_ID, commendField);									/*Text Post is created*/
						user_List.at(index).addPost(textPost);															/*Text Post is added to the an user's post vector*/

					}
				}
				else{
					cout << "Err: the user '" << userName << "' could not be found!" << endl;
					fp_out << "Err: the user '" << userName << "' could not be found!" << endl;
				}


			}

			/************************* LIKE POST **********************************/

			else if (token1.compare("LikePost") == 0){
				string liker, liked, personelCommend;
				int post_ID, liker_Index, liked_Index;

				std::size_t pos = line.find(" ");				/*This code finds the first white space index*/
				line.erase(line.begin(), line.begin() + pos + 1);	/*That code remove the string from begin to first white space index*/

				liker = line.substr(0, line.find(" "));

				std::size_t pos2 = line.find(" ");				/*This code finds the second white space index*/
				line.erase(line.begin(), line.begin() + pos2 + 1);	/*That code remove the string from begin to second white space index*/

				liked = line.substr(0, line.find(" "));

				std::size_t pos3 = line.find(" ");				/*This code finds the third white space index*/
				line.erase(line.begin(), line.begin() + pos3 + 1);	/*That code remove the string from begin to third white space index*/

				istringstream buffer(line.substr(0, line.size()));
				buffer >> post_ID;

				liker_Index = returnUserIndex(liker, user_List);
				liked_Index = returnUserIndex(liked, user_List);


				if (user_List.at(liked_Index).getUserPosts().size() == 0){
					cout << "Err: " << user_List.at(liked_Index).getUserName() << "'s post could not be found!" << endl;
					fp_out << "Err: " << user_List.at(liked_Index).getUserName() << "'s post could not be found!" << endl;

				}
				else if (liker_Index < 0){
					cout << "Err: " << "the user '" << liker << "' could not be found!" << endl;
					fp_out << "Err: " << "the user '" << liker << "' could not be found!" << endl;
				}
				else if (liked_Index < 0){
					cout << "Err: " << "the user '" << liked << "' could not be found!" << endl;
					fp_out << "Err: " << "the user '" << liked << "' could not be found!" << endl;
				}
				else if (user_List.at(liked_Index).returnSpecificPost(post_ID, fp_out, liked) != NULL){
					User* user = new User(liker, personelCommend);

					user_List.at(liked_Index).returnSpecificPost(post_ID, fp_out, liked)->addLikers(user);
					cout << liker << " has liked " << liked << "' post" << endl;
					fp_out << liker << " has liked " << liked << "' post" << endl;

				}
				else{

				}

			}

			/************************* VIEW USER **********************************/

			else if (token1.compare("ViewUser") == 0){
				string userName;
				int user_Index;

				std::size_t pos = line.find(" ");				/*This code finds the first white space index*/
				line.erase(line.begin(), line.begin() + pos + 1);	/*That code remove the string from begin to first white space index*/

				userName = line.substr(0, line.size());

				user_Index = returnUserIndex(userName, user_List);

				if (user_Index < 0){
					cout << "Err: " << "the user '" << userName << "' could not be found!" << endl;
				}
				else{
					user_List.at(user_Index).viewUser(fp_out);
				}

			}

			/************************* BLOCK USER **********************************/

			else if (token1.compare("BlockUser") == 0){
				string userName1, userName2;

				std::size_t pos = line.find(" ");				/*This code finds the first white space index*/
				line.erase(line.begin(), line.begin() + pos + 1);	/*That code remove the string from begin to first white space index*/

				userName1 = line.substr(0, line.find(" "));

				std::size_t pos2 = line.find(" ");				/*This code finds the second white space index*/
				line.erase(line.begin(), line.begin() + pos2 + 1);	/*That code remove the string from begin to second white space index*/

				userName2 = line.substr(0, line.size());

				cout << userName1 << " has blocked " << userName2 << endl;
				fp_out << userName1 << " has blocked " << userName2 << endl;


			}

			/************************* REPOST **********************************/

			else if (token1.compare("Repost") == 0){
				string userNameReposter, userNameReposted;

				std::size_t pos = line.find(" ");				/*This code finds the first white space index*/
				line.erase(line.begin(), line.begin() + pos + 1);	/*That code remove the string from begin to first white space index*/

				userNameReposter = line.substr(0, line.find(" "));

				std::size_t pos2 = line.find(" ");				/*This code finds the second white space index*/
				line.erase(line.begin(), line.begin() + pos2 + 1);	/*That code remove the string from begin to second white space index*/

				userNameReposted = line.substr(0, line.find(" "));

				cout << userNameReposter << " has reposted " << userNameReposted << endl;
				fp_out << userNameReposter << " has reposted " << userNameReposted << endl;

			}

			/************************* UNFOLLOW USER **********************************/

			else if (token1.compare("UnfollowUser") == 0){
				string userName1, userName2;

				std::size_t pos = line.find(" ");				/*This code finds the first white space index*/
				line.erase(line.begin(), line.begin() + pos + 1);	/*That code remove the string from begin to first white space index*/

				userName1 = line.substr(0, line.find(" "));

				std::size_t pos2 = line.find(" ");				/*This code finds the second white space index*/
				line.erase(line.begin(), line.begin() + pos2 + 1);	/*That code remove the string from begin to second white space index*/

				userName2 = line.substr(0, line.size());

				cout << userName2 << " has been unfollowed by " << userName1 << endl;
				fp_out << userName2 << " has been unfollowed by " << userName1 << endl;
			}

			else
			{
				cout << "---Wrong Command---" << endl;
				fp_out << "---Wrong Command---" << endl;

			}

		}
	}
	else{
		cerr << "input/output files can't open" << endl;
		fp_out << "input/output files can't open" << endl;
	}

	fp_in.close();
}

/*******************************************************************************************/

int returnUserIndex(string userName, vector<User>& user_List){
	unsigned int i;
	int iterator = -1;

	if (user_List.size() > 0){
		for (i = 0; i<user_List.size(); i++){
			if (user_List.at(i).getUserName() == userName){
				return i;
			}
		}
	}
	return iterator;
}

/*******************************************************************************************/

void AddUser(fstream& fp_out, string userName, string personalComment, vector<User>& user_List)
{
	if (returnUserIndex(userName, user_List) < 0){
		User* user = new User(userName, personalComment);			/*User object is created if the current user name is different previous ones*/
		user_List.push_back(*user);									/*User object is added to the user_List vector*/
		cout << "User" << " '" << user->getUserName() << "' " << "has been created" << endl;
		fp_out << "User" << " '" << user->getUserName() << "' " << "has been created" << endl;
	}
	else{
		cout << "Err: The user username has already been created." << endl;
		fp_out << "Err: The user username has already been created." << endl;
	}
}

/*******************************************************************************************/

