#pragma once
#inlcude <string>
using namespace std;
class User {
	string name;
};
class Provider {
	string name;
};
class Catalog {
	string name;
};
class File {
	string name;
};
class Revision {
	string text;
};
class CLoudStorage{
	User user;
	Provider provider;
	Catalog catalog;
	File file;
	Revision revision;
	bool operator <(const CLoudStorage& other) {
		return user < other.user;
	}
}