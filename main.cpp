#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

class Helper
{
public:
	static int StringLength(char* str)
	{
		int count = 0;
		for (int i = 0; str[i] != 0; i++)
		{
			count++;
		}
		return count;
	}

	static void StringCopy(char*& dest, char*& src)
	{
		for (int i = 0; src[i] != 0; i++)
		{
			dest[i] = src[i];
		}
	}

	static char* GetStringFromBuffer(char* str)
	{
		char* string = new char[StringLength(str) + 1];
		StringCopy(string, str);
		string[StringLength(str)] = 0;

		return string;
	}

};

class Date
{
private:
	int day;
	int month;
	int year;


public:
	Date()
	{
		day = 14;
		month = 1;
		year = 2003;
	}

	Date(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}

	void setDate(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}

	void print()
	{
		cout << day << "/" << month << "/" << year;
	}

	int getDay()
	{
		return day;
	}

	int getMonth()
	{
		return month;
	}

	int getYear()
	{
		return year;
	}

	bool operator<(const Date& other) const
	{
		if (year < other.year)
			return true;

		else if (year == other.year && month < other.month)
			return true;

		else if (year == other.year && month == other.month && day < other.day)
			return true;
		else
			return false;
	}

	bool operator>(const Date& other) const
	{

		if (year > other.year)
			return true;

		else if (year == other.year && month > other.month)
			return true;

		else if (year == other.year && month == other.month && day > other.day)
			return true;
		else
			return false;
	}

	bool operator==(const Date& other) const
	{
		return year == other.year && month == other.month && day == other.day;
	}
};




class Obj
{
private:
	char* id;

public:
	Obj()
	{
		id = 0;
	}

	Obj(const char* setID)
	{
		int len = strlen(setID);
		id = new char[len + 1];
		strcpy_s(id, len + 1, setID);
	}

	char* getID()
	{
		return id;
	}

	void setID(const char* setID)
	{
		int len = strlen(setID);
		id = new char[len + 1];
		strcpy_s(id, len + 1, setID);
	}

	~Obj()
	{
		if (id != 0)
		{
			delete[] id;
		}
	}

	virtual void print() = 0;
	virtual void printname() = 0;

};

class Post;
class Page;
class User;

class User : public Obj
{
private:
	User** friends;
	Page** likedpages;
	char* fname;
	char* lname;
	char** friendIDs;
	char** pagesIDs;
	int fnum;					//number of friends
	int pnum;					//number of liked pages
	int posts;
	Post** timeline;



public:
	friend class Helper;

	User()
	{
		posts = 0;
		timeline = new Post * [10];
		friendIDs = new char* [10];
		pagesIDs = new char* [10];
		friends = new User * [10];
		likedpages = new Page * [10];
		for (int i = 0; i < 10; i++)
		{
			friendIDs[i] = 0;
			pagesIDs[i] = 0;
			friends[i] = 0;
			likedpages[i] = 0;
		}
		fname = 0;
		lname = 0;

	}

	~User();


	int getfnum()
	{
		return fnum;
	}

	int getpnum()
	{
		return pnum;
	}

	char** getfids()
	{
		return friendIDs;
	}
	char** getpids()
	{
		return pagesIDs;
	}

	void setData(char* fn, char* ln, char* id)
	{
		int len1 = strlen(fn);
		int len2 = strlen(ln);

		fname = new char[len1 + 1];
		lname = new char[len2 + 1];

		strcpy_s(fname, len1 + 1, fn);
		strcpy_s(lname, len2 + 1, ln);

		Obj::setID(id);
	}

	void readData(ifstream& fin)
	{
		char* id1 = new char[5];
		char* fname1 = new char[25];
		char* lname1 = new char[25];

		fin >> id1;
		fin >> fname1;
		fin >> lname1;

		this->setData(fname1, lname1, id1);

		delete[] id1;
		delete[] fname1;
		delete[] lname1;

		//friendIDs = new char* [10];

		char* tempid = new char[5];
		fin >> tempid;

		fnum = 0;
		while (tempid[0] != '-')
		{
			friendIDs[fnum] = Helper::GetStringFromBuffer(tempid);
			fnum++;
			fin >> tempid;
		}

		//pagesIDs = new char* [10];

		fin >> tempid;

		pnum = 0;
		while (tempid[0] != '-')
		{
			pagesIDs[pnum] = Helper::GetStringFromBuffer(tempid);
			pnum++;
			fin >> tempid;
		}

		delete[] tempid;

	}

	char* getname()
	{
		int len1 = strlen(fname);
		int len2 = strlen(lname);
		char* fullname = new char[len1 + len2 + 3];
		int i = 0;
		for (int j = 0; j < len1; j++)
		{
			fullname[i] = fname[j];
			i++;
		}

		fullname[i] = ' ';
		i++;

		for (int j = 0; j < len2; j++)
		{
			fullname[i] = lname[j];
			i++;
		}

		fullname[i] = 0;
		return fullname;
	}

	void addToFriend(User*& add, int num)
	{
		if (friends == 0)
		{
			//				friends = new User* [10];
			for (int i = 0; i < 10; i++)
			{
				friends[i] = new User();
			}
		}
		friends[num] = add;
	}

	void setLikedPage(Page*& add, int num)
	{
		if (likedpages == 0)
		{
			likedpages = new Page * [10];
			for (int i = 0; i < 10; i++)
			{
				likedpages[i] = 0;
			}
		}
		likedpages[num] = add;
	}

	void print()
	{
		cout << getID() << " - " << getname() << endl;
	}


	void printFriends()
	{
		cout << getname() << " - Friends List\n";
		cout << "------------------------------\n";
		for (int i = 0; i < fnum; i++)
		{
			friends[i]->print();
		}
	}

	void printLikedPages();

	void likePost(Post*&, User*&);

	void printname()
	{
		cout << fname << " " << lname;
	}

	void addPost(Post*&);

	void viewTimeline();

	void viewLatest(Date);

	void viewHomepage(Date);

	void viewMemories(Date);

	void shareMemory(Post*&, char*, User*&, Date);



};

class Page : public Obj
{
private:
	char* pageTitle;
	int posts;
	Post** timeline;

public:
	Page()
	{
		pageTitle = 0;
		posts = 0;
		timeline = new Post * [10];
	}

	~Page();

	char* getTitle()
	{
		return pageTitle;
	}

	void setData(char* title, char* id)
	{
		int len = strlen(title);
		pageTitle = new char[len + 1];
		strcpy_s(pageTitle, len + 1, title);

		Obj::setID(id);
	}

	void readData(ifstream& fin)
	{
		char* tempID = new char[5];
		char* name = new char[50];
		fin >> tempID;
		fin.getline(name, 50);

		this->setData(name, tempID);

		delete[] tempID;
		delete[] name;
	}

	Page* searchPage(Page**& searchArray, char* key, int num)
	{
		for (int i = 0; i < num; i++)
		{
			if (strcmp(key, searchArray[i]->getID()) == 0)
			{
				return searchArray[i];
			}
		}
	}

	void print()
	{
		cout << getID() << " - " << getTitle() << endl;
	}

	void printname()
	{
		cout << getTitle();
	}

	void addPost(Post*&);

	void viewLatest(Date);

	void viewTimeline();



};


void User::printLikedPages()
{
	cout << getname() << " - Liked Pages\n";
	cout << "------------------------------\n";
	for (int i = 0; i < pnum; i++)
	{
		likedpages[i]->print();
	}


}

class Activity
{
private:
	int type;
	char* value;

public:
	Activity()
	{
		type = 0;
		value = 0;
	}

	~Activity()
	{
		delete[] value;
	}

	void setType(int t)
	{
		type = t;
	}

	int getType()
	{
		return type;
	}

	void setValue(char* txt)
	{
		int len = strlen(txt);
		value = new char[len + 1];
		strcpy_s(value, len + 1, txt);
	}

	void print()
	{
		if (type == 1)
		{
			cout << " is feeling";
		}
		else if (type == 2)
		{
			cout << " is thinking about";
		}

		else if (type == 3)
		{
			cout << " is making";
		}

		else if (type == 4)
		{
			cout << " is celebrating";
		}

		cout << value << ".\n";
	}
};

class Comment
{
private:
	char* id;
	Obj* poster;
	char* posterID;
	Post* post;
	char* postID;
	char* text;


public:
	Comment()
	{
		id = 0;
		poster = 0;
		post = 0;
		text = 0;
	}

	~Comment();


	char* getPostID()
	{
		return postID;
	}

	char* getPosterID()
	{
		return posterID;
	}

	void setPost(Post*& postptr)
	{
		post = postptr;
	}


	void setPoster(Obj*& objptr)
	{
		poster = objptr;
	}


	void setID(char* str)
	{
		int length = strlen(str);
		id = new char[length + 1];
		strcpy_s(id, length + 1, str);
	}

	void setpostID(char* str)
	{
		int length = strlen(str);
		postID = new char[length + 1];
		strcpy_s(postID, length + 1, str);
	}

	void setposterID(char* str)
	{
		int length = strlen(str);
		posterID = new char[length + 1];
		strcpy_s(posterID, length + 1, str);
	}

	void setText(char* str)
	{
		int length = strlen(str);
		text = new char[length + 1];
		strcpy_s(text, length + 1, str);
	}


	void ReadData(ifstream& fin)
	{
		char* tempid = new char[7];
		fin >> tempid;
		setID(tempid);


		fin >> tempid;
		setpostID(tempid);

		fin >> tempid;
		setposterID(tempid);

		char* txt = new char[60];
		fin.getline(txt, 60);
		setText(txt);

		delete[] tempid;
		delete[] txt;
	}

	void print()
	{
		poster->printname();
		cout << " wrote: \"" << text << "\"" << endl;
	}






};

class Post : public Obj
{
private:
	int postType;
	char* text;
	int totallikes;
	Obj** likes;
	Date sharedDate;
	Obj* sharedBy;
	Comment** comments;
	int totalcomments;
	Activity activity;
	char** likedIDs;
	char* sharerID;
	Post* memory;

public:
	friend class Helper;

	Post()
	{
		memory = 0;
		totalcomments = 0;
		postType = 0;
		text = 0;
		totallikes = 0;
		likes = 0;
		sharedBy = 0;
		likedIDs = new char* [10];
		comments = new Comment * [10];
		for (int i = 0; i < 10; i++)
		{
			comments[i] = new Comment();
			likedIDs[i] = 0;
		}
		likes = new Obj * [10];
	}

	~Post()
	{
		delete[] text;
		for (int i = 0; i < 10; i++)
		{
			delete[] likedIDs[i];
			//delete[] comments[i];
			//delete[] likes[i];
		}

		delete[] likedIDs;
		delete[] comments;
		//delete[] likes;
		//	delete[] sharedBy;
		delete[] sharerID;

		//if (memory != 0)
		//{
		//	delete[] memory;
		//}
	}

	int getLikes()
	{
		return totallikes;
	}

	char** getLikeIDs()
	{
		return likedIDs;
	}

	Date getDate()
	{
		return sharedDate;
	}

	void setText(char* txt)
	{
		int len = strlen(txt);
		text = new char[len + 1];
		strcpy_s(text, len + 1, txt);
	}

	void setsID(char* str)
	{
		int len = strlen(str);
		sharerID = new char[len + 1];
		strcpy_s(sharerID, len + 1, str);
	}

	char* getSID()
	{
		return sharerID;
	}

	int getType()
	{
		return postType;
	}

	void setSharer(Obj*& sb)
	{
		sharedBy = sb;
	}

	void setMemory(Post*& m, int d, int mon, int y)
	{
		postType = 3;
		memory = m;
		sharedDate.setDate(d, mon, y);

	}

	void ReadData(ifstream& fin)
	{
		fin >> postType;
		char* postID = new char[7];
		fin >> postID;
		Obj::setID(postID);


		int d, m, y;
		fin >> d;
		fin >> m;
		fin >> y;

		sharedDate.setDate(d, m, y);

		char* temptxt = new char[100];
		fin.ignore();
		fin.getline(temptxt, 100);
		setText(temptxt);

		if (postType == 2)
		{
			int t;
			fin >> t;
			activity.setType(t);
			char* vl = new char[50];
			fin.getline(vl, 50);
			activity.setValue(vl);
			delete[] vl;
		}

		char* tempID = new char[4];
		fin >> tempID;
		setsID(tempID);


		//			likes = new Obj*[15];

		fin >> tempID;
		while (tempID[0] != '-')
		{
			likedIDs[totallikes] = Helper::GetStringFromBuffer(tempID);
			totallikes++;
			fin >> tempID;
		}

		delete[] postID;
		delete[] temptxt;
		delete[] tempID;


	}


	void setLiked(Obj*& liker, int num)
	{

		likes[num] = liker;
	}

	void addlike(User*& usrptr)
	{
		Obj* objptr = static_cast<Obj*>(usrptr);
		likes[totallikes] = objptr;
		totallikes++;
	}

	void printLikedList()
	{
		if (likes[0] == 0)
		{
			cout << endl << "This post has 0 likes.";
			return;
		}
		for (int i = 0; i < totallikes; i++)
		{
			likes[i]->print();
		}
	}

	void addComment(Comment*& cmt)
	{
		comments[totalcomments] = cmt;
		totalcomments++;
	}

	void print()
	{

		sharedBy->printname();

		if (activity.getType() != 0)
		{
			activity.print();
		}
		else
		{
			cout << " shared ";
		}

		cout << text << " ... (";
		sharedDate.print();
		cout << ")\n";

		if (comments != 0)
		{
			for (int i = 0; i < totalcomments; i++)
			{
				cout << "		";
				comments[i]->print();
			}
		}


	}

	void printMemory()
	{
		sharedBy->printname();
		cout << " shared a memory ";
		cout << " ... (";
		sharedDate.print();
		cout << ")\n";

		cout << text << endl << endl;

		memory->print();
	}

	void printname()
	{

	}



};

Comment::~Comment()
{
	delete[] id;
	//delete[] poster;
	delete[] posterID;
	//delete[] post;
	delete[] postID;
	delete[] text;
}

void User::likePost(Post*& postptr, User*& userptr)
{
	postptr->addlike(userptr);
}

void User::addPost(Post*& postptr)
{
	timeline[posts] = postptr;
	posts++;
}

void Page::addPost(Post*& postptr)
{
	timeline[posts] = postptr;
	posts++;
}

void User::viewTimeline()
{
	for (int i = 0; i < posts; i++)
	{
		if (timeline[i]->getType() == 3)
		{
			timeline[i]->printMemory();
		}
		else
			timeline[i]->print();
		cout << endl << endl;
	}
}

void Page::viewTimeline()
{
	for (int i = 0; i < posts; i++)
	{
		timeline[i]->print();
		cout << endl << endl;
	}
}

void User::viewLatest(Date cd)
{
	for (int i = 0; i < posts; i++)
	{
		Date tempdate = timeline[i]->getDate();
		if (tempdate.getDay() == cd.getDay() || tempdate.getDay() == (cd.getDay() - 1))
		{
			if (timeline[i]->getType() == 3)
				timeline[i]->printMemory();
			else
				timeline[i]->print();
		}
	}

}

void Page::viewLatest(Date cd)
{
	for (int i = 0; i < posts; i++)
	{
		Date tempdate = timeline[i]->getDate();
		if (tempdate.getDay() == cd.getDay() || tempdate.getDay() == (cd.getDay() - 1))
		{
			timeline[i]->print();
		}
	}
}

void User::viewHomepage(Date cd)
{
	for (int i = 0; i < fnum; i++)
	{
		friends[i]->viewLatest(cd);
		cout << endl;
	}

	for (int i = 0; i < pnum; i++)
	{
		likedpages[i]->viewLatest(cd);
		cout << endl;
	}
}

void User::viewMemories(Date cd)
{
	cout << endl << "\033[3mWe hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\033[0m";
	cout << endl;

	for (int i = 0; i < posts; i++)
	{
		Date tempdate = timeline[i]->getDate();;
		if (tempdate.getDay() == cd.getDay() && tempdate.getMonth() == cd.getMonth())
		{
			int k = cd.getYear() - tempdate.getYear();
			cout << "On this day\n " << k << " years ago \n";
			timeline[i]->print();

			cout << endl;
		}
	}
}

void User::shareMemory(Post*& mem, char* txt, User*& self, Date cd)
{
	Post* reshare = new Post;
	reshare->setMemory(mem, cd.getDay(), cd.getMonth(), cd.getYear());
	Obj* objptr = static_cast<Obj*>(self);
	reshare->setSharer(objptr);

	reshare->setText(txt);

	self->addPost(reshare);
}

User::~User()
{
	for (int i = 0; i < 10; i++)
	{
		//	delete[] timeline[i];
		delete[] friendIDs[i];
		delete pagesIDs[i];
		//	delete[] friends[i];
		//	delete[] likedpages[i];
	}

	delete[] timeline;
	delete[] friendIDs;
	delete[] pagesIDs;
	delete[] likedpages;
	delete[] fname;
	delete[] lname;

}

Page::~Page()
{
	delete[] pageTitle;
	//	for (int i = 0; i < 10; i++)
	//	{
	//		delete[] timeline[i];
	//	}

	delete[] timeline;
}



class Facebook
{
private:
	int usersnum;
	int pagesnum;
	int postsnum;
	int commentsnum;
	User** users;
	Page** pages;
	Post** posts;
	Comment** comments;
	User* currentuser;
	Date currentDate;

public:

	void setCurrentDate()
	{
		currentDate.setDate(15, 11, 2017);
		cout << "Current date set at: ";
		currentDate.print();
		cout << endl;
	}

	~Facebook()
	{
		for (int i = 0; i < usersnum; i++)
		{
			delete users[i];
		}

		for (int i = 0; i < pagesnum; i++)
		{
			delete pages[i];
		}

		for (int i = 0; i < postsnum; i++)
		{
			delete posts[i];
		}

		for (int i = 0; i < commentsnum; i++)
		{
			delete comments[i];
		}

		delete[] users;
		delete[] pages;
		delete[] posts;
		delete[] comments;
		//delete[] currentuser;

	}

	void menu()
	{
		char input;
		int num;

		while (true)
		{
			cout << endl;
			cout << "Press number to select... \n";
			cout << endl;

			cout << "<h> View homepage\n";
			cout << endl;
			cout << "<0> View Friends List\n";
			cout << "<1> View Liked Pages\n";
			cout << "<2> Share a memory\n";
			cout << "<3> Like a post\n";
			cout << "<4> View likes of a post\n";
			cout << "<5> Comment on a post\n";
			cout << "<6> View a post\n";
			cout << "<7> View user timeline\n";
			cout << "<8> View page timeline\n";
			cout << "<9> View your memories\n";
			cout << endl;
			cout << "<o> Logout.\n";
			cout << "<x> Exit program.\n";
			input = _getch();

			if (input == '0')
			{
				system("CLS");
				viewFriends();
				cout << endl << endl << "Press any key to return to menu...";
				_getch();
				system("CLS");
			}

			else if (input == 'h')
			{
				system("CLS");
				currentuser->viewHomepage(currentDate);
				cout << endl << endl << "Press any key to return to menu...";
				_getch();
				system("CLS");
			}
			else if (input == '1')
			{
				system("CLS");
				viewLikedPages();
				cout << endl << endl << "Press any key to return to menu...";
				_getch();
				system("CLS");
			}

			else if (input == '2')
			{
				system("CLS");
				cout << "Enter post id: ";
				char* tempid = new char[8];
				cin >> tempid;

				Post* postptr = searchPost(tempid);
				if (postptr == 0)
				{
					cout << "No post found with this ID\n";
				}

				else
				{
					cout << "Enter text to add: ";
					char* desc = new char[60];
					cin.ignore();
					cin.getline(desc, 60);

					currentuser->shareMemory(postptr, desc, currentuser, currentDate);
					cout << "Succesfully shared memory!";
				}

				cout << endl << endl << "Press any key to return to menu...";
				_getch();
				system("CLS");

			}

			else if (input == '3')
			{
				system("CLS");
				cout << "Enter ID of post to like: ";
				char* tempID = new char[7];
				cin >> tempID;
				addLike(tempID);
				cout << "Post successfully liked!\n";
				cout << endl << endl << "Press any key to return to menu...";
				_getch();
				system("CLS");
			}

			else if (input == '4')
			{
				system("CLS");
				cout << "Enter post id: ";
				char* tempid = new char[7];
				cin >> tempid;

				Post* postptr = searchPost(tempid);

				cout << endl << "Post liked by: \n" << endl;
				postptr->printLikedList();

				cout << endl << endl << "Press any key to return to menu...";
				_getch();
				system("CLS");
			}
			else if (input == '5')
			{
				system("CLS");
				cout << "Enter id of post you wish to comment on: ";
				char* pID = new char[7];
				cin >> pID;

				Post* postptr = searchPost(pID);

				cout << "Enter your comment: ";
				char* cmnt = new char[70];
				cin.ignore();
				cin.getline(cmnt, 70);

				Comment* inputcmnt = new Comment();
				inputcmnt->setPost(postptr);
				inputcmnt->setText(cmnt);

				Obj* objptr = static_cast<Obj*>(currentuser);
				inputcmnt->setPoster(objptr);

				postptr->addComment(inputcmnt);

				cout << "Comment successfully posted!";

				cout << endl << endl << "Press any key to return to menu...";
				_getch();
				system("CLS");


			}

			else if (input == '6')
			{
				system("CLS");
				cout << "Enter post id: ";
				char* tempid = new char[7];
				cin >> tempid;

				Post* postptr = searchPost(tempid);
				cout << endl << endl;
				postptr->print();

				cout << endl << endl << "Press any key to return to menu...";
				_getch();
				system("CLS");
			}

			else if (input == '7')
			{
				system("CLS");
				cout << "Enter user id: ";
				char* tempid = new char[4];
				cin >> tempid;

				User* userptr = searchUser(tempid);
				cout << endl;

				userptr->viewTimeline();

				cout << endl << endl << "Press any key to return to menu...";
				_getch();
				system("CLS");
			}

			else if (input == '8')
			{
				system("CLS");
				cout << "Enter page id: ";
				char* tempid = new char[4];
				cin >> tempid;

				Page* pageptr = searchPage(tempid);
				cout << endl;

				pageptr->viewTimeline();

				cout << endl << endl << "Press any key to return to menu...";
				_getch();
				system("CLS");
			}

			else if (input == '9')
			{
				system("CLS");
				currentuser->viewMemories(currentDate);
				cout << endl << endl << "Press any key to return to menu...";
				_getch();
				system("CLS");
			}

			else if (input == 'o')
			{
				system("CLS");
				cout << "Enter your user id: ";
				char* tempid = new char[5];
				cin >> tempid;
				setCurrentUser(tempid);
				delete[] tempid;
				cout << endl << endl << "Press any key to return to menu...";
				_getch();
				system("CLS");
			}
			else if (input == 'x')
				return;

			else
				cout << "Invalid input. Please try again.\n";

		}
	}

	void viewFriends()
	{
		cout << endl;
		currentuser->printFriends();
	}

	void viewLikedPages()
	{
		currentuser->printLikedPages();
	}

	void loadUsersData()
	{
		ifstream fin;
		fin.open("usersData.txt");


		if (fin.is_open())
		{
			fin >> usersnum;
			users = new User * [usersnum];

			for (int i = 0; i < usersnum; i++)
			{
				users[i] = new User();
				users[i]->readData(fin);
			}
		}

	}

	void loadPagesData()
	{
		ifstream fin;
		fin.open("pagesData.txt");

		if (fin.is_open())
		{
			fin >> pagesnum;
			pages = new Page * [pagesnum];

			for (int i = 0; i < pagesnum; i++)
			{
				pages[i] = new Page();
				pages[i]->readData(fin);
			}
		}
	}

	Page* searchPage(char* key)
	{
		for (int i = 0; i < pagesnum; i++)
		{
			if (strcmp(key, pages[i]->getID()) == 0)
			{
				return pages[i];
			}
		}

		return 0;
	}

	User* searchUser(char* key)
	{
		for (int i = 0; i < usersnum; i++)
		{
			if (strcmp(key, users[i]->getID()) == 0)
			{
				return users[i];
			}
		}

		return 0;
	}

	Post* searchPost(char* key)
	{
		for (int i = 0; i < postsnum; i++)
		{
			if (strcmp(key, posts[i]->getID()) == 0)
			{
				return posts[i];
			}
		}

		return 0;
	}

	void addLike(char* postID)
	{
		Post* postptr = searchPost(postID);
		currentuser->likePost(postptr, currentuser);
	}


	void loadUsers()
	{
		loadUsersData();
		loadPagesData();

		for (int i = 0; i < usersnum; i++)
		{
			int f = users[i]->getfnum();
			int p = users[i]->getpnum();
			char** friendIDs = users[i]->getfids();
			char** pageIDs = users[i]->getpids();

			for (int j = 0; j < f; j++)
			{
				User* usrptr = searchUser(friendIDs[j]);
				if (usrptr != 0)
				{
					users[i]->addToFriend(usrptr, j);
				}
			}

			for (int k = 0; k < p; k++)
			{
				Page* pgptr = searchPage(pageIDs[k]);
				if (pgptr != 0)
				{
					users[i]->setLikedPage(pgptr, k);
					//	pgptr->addLike();
				}
			}


		}

	}

	void loadPostsData()
	{
		ifstream fin;
		fin.open("postsData.txt");

		if (fin.is_open())
		{
			fin >> postsnum;
			posts = new Post * [postsnum];

			for (int i = 0; i < postsnum; i++)
			{
				posts[i] = new Post();
				posts[i]->ReadData(fin);
			}
		}
	}

	void loadPosts()
	{
		loadPostsData();

		for (int i = 0; i < postsnum; i++)
		{
			char* SID = posts[i]->getSID();
			if (SID[0] == 'u')
			{
				User* userptr = searchUser(SID);
				userptr->addPost(posts[i]);
				Obj* objptr = static_cast<Obj*>(userptr);
				posts[i]->setSharer(objptr);
			}
			else if (SID[0] == 'p')
			{
				Page* pageptr = searchPage(SID);
				pageptr->addPost(posts[i]);
				Obj* objptr = static_cast<Obj*>(pageptr);
				posts[i]->setSharer(objptr);
			}

			char** ids = posts[i]->getLikeIDs();

			int num = posts[i]->getLikes();
			for (int j = 0; j < num; j++)
			{
				char* tempID = ids[j];
				if (tempID[0] == 'u')
				{
					User* usrptr = searchUser(tempID);
					Obj* objptr = static_cast<Obj*>(usrptr);
					posts[i]->setLiked(objptr, j);
				}

				else if (tempID[0] == 'p')
				{
					Page* pgptr = searchPage(tempID);
					Obj* objptr = static_cast<Obj*>(pgptr);
					posts[i]->setLiked(objptr, j);
				}
			}
		}
	}

	void loadCommentsData()
	{
		ifstream fin;
		fin.open("commentsData.txt");

		if (fin.is_open())
		{
			fin >> commentsnum;
			comments = new Comment * [20];

			for (int i = 0; i < commentsnum; i++)
			{
				comments[i] = new Comment();
				comments[i]->ReadData(fin);
			}
		}
	}

	void loadComments()
	{
		loadCommentsData();

		for (int i = 0; i < commentsnum; i++)
		{
			char* postid = comments[i]->getPostID();
			Post* postptr = searchPost(postid);

			postptr->addComment(comments[i]);
			comments[i]->setPost(postptr);

			char* posterid = comments[i]->getPosterID();
			if (posterid[0] == 'u')
			{
				User* userptr = searchUser(posterid);
				Obj* objptr = static_cast<Obj*>(userptr);
				comments[i]->setPoster(objptr);
			}

			else if (posterid[0] == 'p')
			{
				Page* pgptr = searchPage(posterid);
				Obj* objptr = static_cast<Obj*>(pgptr);
				comments[i]->setPoster(objptr);
			}

		}
	}

	void setCurrentUser(char* setid)
	{
		User* usrptr = searchUser(setid);
		currentuser = usrptr;

		cout << currentuser->getname() << " logged in.\n\n";
	}

};




int main()
{
	Facebook fb;
	fb.setCurrentDate();
	fb.loadUsers();
	fb.loadPosts();
	fb.loadComments();

	cout << "Enter your user id: ";
	char* tempid = new char[5];
	cin >> tempid;

	fb.setCurrentUser(tempid);

	fb.menu();








}








